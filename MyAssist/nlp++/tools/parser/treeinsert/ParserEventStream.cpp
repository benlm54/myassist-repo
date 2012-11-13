#include "ParserEventStream.h"
#include "tools/parser/Parser.h"
#include "tools/parser/chunking/Parser.h"
#include "tools/parser/treeinsert/Parser.h"
#include "tools/parser/AbstractBottomUpParser.h"
#include "tools/util/Span.h"
#include "model/AbstractModel.h"
#include "maxent/io/SuffixSensitiveGISModelReader.h"
#include "model/EventStream.h"
#include "tools/parser/ParseSampleStream.h"
#include "tools/util/PlainTextByLineStream.h"

namespace opennlp
{
    namespace tools
    {
        namespace parser
        {
            namespace treeinsert
            {
                using opennlp::maxent::io::SuffixSensitiveGISModelReader;
                using opennlp::model::AbstractModel;
                using opennlp::model::Event;
                using opennlp::tools::dictionary::Dictionary;
                using opennlp::tools::parser::AbstractBottomUpParser;
                using opennlp::tools::parser::AbstractParserEventStream;
                using opennlp::tools::parser::HeadRules;
                using opennlp::tools::parser::Parse;
                using opennlp::tools::parser::ParseSampleStream;
                using opennlp::tools::parser::ParserEventTypeEnum;
                using opennlp::tools::util::InvalidFormatException;
                using opennlp::tools::util::ObjectStream;
                using opennlp::tools::util::PlainTextByLineStream;
                using opennlp::tools::util::Span;

                ParserEventStream::ParserEventStream(ObjectStream<Parse*> *d, HeadRules *rules, ParserEventTypeEnum etype, Dictionary *dict) : opennlp.tools.parser.AbstractParserEventStream(d, rules, etype, dict)
                {
                }

                void ParserEventStream::init()
                {
                  buildContextGenerator = new BuildContextGenerator();
                  attachContextGenerator = new AttachContextGenerator(punctSet);
                  checkContextGenerator = new CheckContextGenerator(punctSet);
                }

                ParserEventStream::ParserEventStream(ObjectStream<Parse*> *d, HeadRules *rules, ParserEventTypeEnum etype) : opennlp.tools.parser.AbstractParserEventStream(d, rules, etype)
                {
                }

                Map<Parse*, int> *ParserEventStream::getNonAdjoinedParent(Parse *node)
                {
                  Map<Parse*, int> *parents = std::map<Parse*, int>();
                  Parse *parent = node->getParent();
                  int index = indexOf(node,parent);
                  parents->put(parent, index);
                  while (parent->getType() == node->getType())
                  {
                    node = parent;
                    parent = parent->getParent();
                    index = indexOf(node,parent);
                    parents->put(parent,int(index));
                  }
                  return parents;
                }

                int ParserEventStream::indexOf(Parse *child, Parse *parent)
                {
//ORIGINAL LINE: opennlp.tools.parser.Parse[] kids = Parser.collapsePunctuation(parent.getChildren(),punctSet);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                  Parse *kids = Parser::collapsePunctuation(parent->getChildren(),punctSet);
                  for (int ki = 0;ki < kids->length;ki++)
                  {
                    if (child == kids[ki])
                    {
                      return ki;
                    }
                  }
                  return -1;
                }

                int ParserEventStream::nonPunctChildCount(Parse *node)
                {
                  return sizeof(Parser::collapsePunctuation(node->getChildren(),punctSet)) / sizeof(Parser::collapsePunctuation(node->getChildren(),punctSet)[0]);
                }

                bool ParserEventStream::lastChild(Parse *child, Parse *parent)
                {
                  bool lc = AbstractParserEventStream::lastChild(child, parent);
                  while (!lc)
                  {
                    Parse *cp = child->getParent();
                    if (cp != parent && cp->getType() == child->getType())
                    {
                      lc = AbstractParserEventStream::lastChild(cp,parent);
                      child = cp;
                    }
                    else
                    {
                      break;
                    }
                  }
                  return lc;
                }

                void ParserEventStream::addParseEvents(std::vector<Event*> &parseEvents, Parse chunks[])
                {
                  /// <summary>
                  /// Frontier nodes built from node in a completed parse.  Specifically,
                  /// they have all their children regardless of the stage of parsing.
                  /// </summary>
                  std::vector<Parse*> rightFrontier = std::vector<Parse*>();
                  std::vector<Parse*> builtNodes = std::vector<Parse*>();
                  /// <summary>
                  /// Nodes which characterize what the parse looks like to the parser as its being built.
                  /// Specifically, these nodes don't have all their children attached like the parents of
                  /// the chunk nodes do.
                  /// </summary>
                  Parse currentChunks[sizeof(chunks) / sizeof(chunks[0])];
                  for (int ci = 0;ci < sizeof(chunks) / sizeof(chunks[0]);ci++)
                  {
                    currentChunks[ci] = static_cast<Parse*>(chunks[ci]->clone());
                    currentChunks[ci]->setPrevPunctuation(chunks[ci]->getPreviousPunctuationSet());
                    currentChunks[ci]->setNextPunctuation(chunks[ci]->getNextPunctuationSet());
                    currentChunks[ci]->setLabel(Parser::COMPLETE);
                    chunks[ci]->setLabel(Parser::COMPLETE);
                  }
                  for (int ci = 0;ci < sizeof(chunks) / sizeof(chunks[0]);ci++)
                  {
                    //System.err.println("parserEventStream.addParseEvents: chunks="+Arrays.asList(chunks));
                    Parse *parent = chunks[ci]->getParent();
                    Parse *prevParent = chunks[ci];
                    int off = 0;
                    //build un-built parents
                    if (!chunks[ci]->isPosTag())
                    {
                      builtNodes.push_back(off++,chunks[ci]);
                    }
                    //perform build stages
                    while (parent->getType() != AbstractBottomUpParser::TOP_NODE && parent->getLabel() == "")
                    {
                      if (parent->getLabel() == "" && prevParent->getType() != parent->getType())
                      {
                        //build level
                        if (debug)
                            System::err::println("Build: " + parent->getType() + " for: " + currentChunks[ci]);
                        if (etype == opennlp::tools::parser::BUILD)
                        {
                          parseEvents.push_back(new Event(parent->getType(), buildContextGenerator->getContext(currentChunks, ci)));
                        }
                        builtNodes.push_back(off++,parent);
                        Parse *newParent = new Parse(currentChunks[ci]->getText(),currentChunks[ci]->getSpan(),parent->getType(),1,0);
                        newParent->add(currentChunks[ci],rules);
                        newParent->setPrevPunctuation(currentChunks[ci]->getPreviousPunctuationSet());
                        newParent->setNextPunctuation(currentChunks[ci]->getNextPunctuationSet());
                        currentChunks[ci]->setParent(newParent);
                        currentChunks[ci] = newParent;
                        newParent->setLabel(Parser::BUILT);
                        //see if chunk is complete
                        if (lastChild(chunks[ci], parent))
                        {
                          if (etype == opennlp::tools::parser::CHECK)
                          {
                            parseEvents.push_back(new Event(Parser::COMPLETE, checkContextGenerator->getContext(currentChunks[ci],currentChunks, ci,false)));
                          }
                          currentChunks[ci]->setLabel(Parser::COMPLETE);
                          parent->setLabel(Parser::COMPLETE);
                        }
                        else
                        {
                          if (etype == opennlp::tools::parser::CHECK)
                          {
                            parseEvents.push_back(new Event(Parser::INCOMPLETE, checkContextGenerator->getContext(currentChunks[ci],currentChunks,ci,false)));
                          }
                          currentChunks[ci]->setLabel(Parser::INCOMPLETE);
                          parent->setLabel(Parser::COMPLETE);
                        }

                        chunks[ci] = parent;
                        //System.err.println("build: "+newParent+" for "+parent);
                      }
                      //TODO: Consider whether we need to set this label or train parses at all.
                      parent->setLabel(Parser::BUILT);
                      prevParent = parent;
                      parent = parent->getParent();
                    }
                    //decide to attach
                    if (etype == opennlp::tools::parser::BUILD)
                    {
                      parseEvents.push_back(new Event(Parser::DONE, buildContextGenerator->getContext(currentChunks, ci)));
                    }
                    //attach node
                    std::string attachType = "";
                    /// <summary>
                    /// Node selected for attachment. </summary>
                    Parse *attachNode = 0;
                    int attachNodeIndex = -1;
                    if (ci == 0)
                    {
                      Parse *top = new Parse(currentChunks[ci]->getText(),new Span(0,currentChunks[ci]->getText()->length()),AbstractBottomUpParser::TOP_NODE,1,0);
                      top->insert(currentChunks[ci]);
                    }
                    else
                    {
                      /// <summary>
                      /// Right frontier consisting of partially-built nodes based on current state of the parse. </summary>
                      std::vector<Parse*> currentRightFrontier = Parser::getRightFrontier(currentChunks[0],punctSet);
                      if (currentRightFrontier.size() != rightFrontier.size())
                      {
                        System::err::println("fontiers mis-aligned: " + currentRightFrontier.size() + " != " + rightFrontier.size() + " " + currentRightFrontier + " " + rightFrontier);
                        exit(1);
                      }
                      Map<Parse*, int> *parents = getNonAdjoinedParent(chunks[ci]);
                      //try daughters first.
                      for (int cfi = 0;cfi < currentRightFrontier.size();cfi++)
                      {
                        Parse *frontierNode = rightFrontier[cfi];
                        Parse *cfn = currentRightFrontier[cfi];
                        if (!Parser::checkComplete || Parser::COMPLETE != cfn->getLabel())
                        {
                          int i = parents->get(frontierNode);
                          if (debug)
                              System::err::println("Looking at attachment site (" + cfi + "): " + cfn->getType() + " ci=" + i + " cs=" + nonPunctChildCount(cfn) + ", " + cfn + " :for " + currentChunks[ci]->getType() + " " + currentChunks[ci] + " -> " + parents);
                          if (attachNode == 0 && i != 0 && i == nonPunctChildCount(cfn))
                          {
                            attachType = Parser::ATTACH_DAUGHTER;
                            attachNodeIndex = cfi;
                            attachNode = cfn;
                            if (etype == opennlp::tools::parser::ATTACH)
                            {
                              parseEvents.push_back(new Event(attachType, attachContextGenerator->getContext(currentChunks, ci, currentRightFrontier, attachNodeIndex)));
                            }
                            //System.err.println("daughter attach "+attachNode+" at "+fi);
                          }
                        }
                        else
                        {
                          if (debug)
                              System::err::println("Skipping (" + cfi + "): " + cfn->getType() + "," + cfn->getPreviousPunctuationSet() + " " + cfn + " :for " + currentChunks[ci]->getType() + " " + currentChunks[ci] + " -> " + parents);
                        }
                        // Can't attach past first incomplete node.
                        if (Parser::checkComplete && cfn->getLabel() == Parser::INCOMPLETE)
                        {
                          if (debug)
                              System::err::println("breaking on incomplete:" + cfn->getType() + " " + cfn);
                          break;
                        }
                      }
                      //try sisters, and generate non-attach events.
                      for (int cfi = 0;cfi < currentRightFrontier.size();cfi++)
                      {
                        Parse *frontierNode = rightFrontier[cfi];
                        Parse *cfn = currentRightFrontier[cfi];
                        if (attachNode == 0 && parents->containsKey(frontierNode->getParent()) && frontierNode->getType() == frontierNode->getParent()->getType()) //&& frontierNode.getParent().getLabel() == null) {
                        {
                          attachType = Parser::ATTACH_SISTER;
                          attachNode = cfn;
                          attachNodeIndex = cfi;
                          if (etype == opennlp::tools::parser::ATTACH)
                          {
                            parseEvents.push_back(new Event(Parser::ATTACH_SISTER, attachContextGenerator->getContext(currentChunks, ci, currentRightFrontier, cfi)));
                          }
                          chunks[ci]->getParent()->setLabel(Parser::BUILT);
                          //System.err.println("in search sister attach "+attachNode+" at "+cfi);
                        }
                        else if (cfi == attachNodeIndex)
                        {
                          //skip over previously attached daughter.
                        }
                        else
                        {
                          if (etype == opennlp::tools::parser::ATTACH)
                          {
                            parseEvents.push_back(new Event(Parser::NON_ATTACH, attachContextGenerator->getContext(currentChunks, ci, currentRightFrontier, cfi)));
                          }
                        }
                        //Can't attach past first incomplete node.
                        if (Parser::checkComplete && cfn->getLabel() == Parser::INCOMPLETE)
                        {
                          if (debug)
                              System::err::println("breaking on incomplete:" + cfn->getType() + " " + cfn);
                          break;
                        }
                      }
                      //attach Node
                      if (attachNode != 0)
                      {
                        if (attachType == Parser::ATTACH_DAUGHTER)
                        {
                          Parse *daughter = currentChunks[ci];
                          if (debug)
                              System::err::println("daughter attach a=" + attachNode->getType() + ":" + attachNode + " d=" + daughter + " com=" + lastChild(chunks[ci], rightFrontier[attachNodeIndex]));
                          attachNode->add(daughter,rules);
                          daughter->setParent(attachNode);
                          if (lastChild(chunks[ci], rightFrontier[attachNodeIndex]))
                          {
                            if (etype == opennlp::tools::parser::CHECK)
                            {
                              parseEvents.push_back(new Event(Parser::COMPLETE, checkContextGenerator->getContext(attachNode,currentChunks,ci,true)));
                            }
                            attachNode->setLabel(Parser::COMPLETE);
                          }
                          else
                          {
                            if (etype == opennlp::tools::parser::CHECK)
                            {
                              parseEvents.push_back(new Event(Parser::INCOMPLETE, checkContextGenerator->getContext(attachNode,currentChunks,ci,true)));
                            }
                          }
                        }
                        else if (attachType == Parser::ATTACH_SISTER)
                        {
                          Parse *frontierNode = rightFrontier[attachNodeIndex];
                          rightFrontier[attachNodeIndex] = frontierNode->getParent();
                          Parse *sister = currentChunks[ci];
                          if (debug)
                              System::err::println("sister attach a=" + attachNode->getType() + ":" + attachNode + " s=" + sister + " ap=" + attachNode->getParent() + " com=" + lastChild(chunks[ci], rightFrontier[attachNodeIndex]));
                          Parse *newParent = attachNode->getParent()->adjoin(sister,rules);

                          newParent->setParent(attachNode->getParent());
                          attachNode->setParent(newParent);
                          sister->setParent(newParent);
                          if (attachNode == currentChunks[0])
                          {
                            currentChunks[0] = newParent;
                          }
                          if (lastChild(chunks[ci], rightFrontier[attachNodeIndex]))
                          {
                            if (etype == opennlp::tools::parser::CHECK)
                            {
                              parseEvents.push_back(new Event(Parser::COMPLETE, checkContextGenerator->getContext(newParent,currentChunks,ci,true)));
                            }
                            newParent->setLabel(Parser::COMPLETE);
                          }
                          else
                          {
                            if (etype == opennlp::tools::parser::CHECK)
                            {
                              parseEvents.push_back(new Event(Parser::INCOMPLETE, checkContextGenerator->getContext(newParent,currentChunks,ci,true)));
                            }
                            newParent->setLabel(Parser::INCOMPLETE);
                          }

                        }
                        //update right frontier
                        for (int ni = 0;ni < attachNodeIndex;ni++)
                        {
                          //System.err.println("removing: "+rightFrontier.get(0));
                          rightFrontier.remove(0);
                        }
                      }
                      else
                      {
                        //System.err.println("No attachment!");
                        throw std::exception("No Attachment: " + chunks[ci]);
                      }
                    }
                    rightFrontier.addAll(0,builtNodes);
                    builtNodes.clear();
                  }
                }

                void ParserEventStream::main(std::string args[]) throw(java::io::IOException, InvalidFormatException)
                {
                  if (sizeof(args) / sizeof(args[0]) == 0)
                  {
                    System::err::println("Usage ParserEventStream -[tag|chunk|build|attach] [-fun] [-dict dictionary] [-model model] head_rules < parses");
                    exit(1);
                  }
                  ParserEventTypeEnum etype = 0;
                  bool fun = false;
                  int ai = 0;
                  Dictionary *dict = 0;
                  AbstractModel *model = 0;

//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'startsWith' method:
                  while (ai < sizeof(args) / sizeof(args[0]) && args[ai].startsWith("-"))
                  {
                    if (args[ai] == "-build")
                    {
                      etype = opennlp::tools::parser::BUILD;
                    }
                    else if (args[ai] == "-attach")
                    {
                      etype = opennlp::tools::parser::ATTACH;
                    }
                    else if (args[ai] == "-chunk")
                    {
                      etype = opennlp::tools::parser::CHUNK;
                    }
                    else if (args[ai] == "-check")
                    {
                      etype = opennlp::tools::parser::CHECK;
                    }
                    else if (args[ai] == "-tag")
                    {
                      etype = opennlp::tools::parser::TAG;
                    }
                    else if (args[ai] == "-fun")
                    {
                      fun = true;
                    }
                    else if (args[ai] == "-dict")
                    {
                      ai++;
                      dict = new Dictionary(new FileInputStream(args[ai]));
                    }
                    else if (args[ai] == "-model")
                    {
                      ai++;
                      model = (new SuffixSensitiveGISModelReader(new File(args[ai])))->getModel();
                    }
                    else
                    {
                      System::err::println("Invalid option " + args[ai]);
                      exit(1);
                    }
                    ai++;
                  }
                  HeadRules *rules = new opennlp::tools::parser::lang::en::HeadRules(args[ai++]);
                  if (fun)
                  {
                    Parse::useFunctionTags(true);
                  }
                  opennlp::model::EventStream *es = new ParserEventStream(new ParseSampleStream(new PlainTextByLineStream(new java::io::InputStreamReader(System::in))), rules, etype, dict);
                  while (es->hasNext())
                  {
                    Event *e = es->next();
                    if (model != 0)
                    {
                      std::cout << model->eval(e->getContext())[model->getIndex(e->getOutcome())] + " ";
                    }
                    std::cout << e << std::endl;
                      es++;
                  }
                }
            }
        }
    }
}
