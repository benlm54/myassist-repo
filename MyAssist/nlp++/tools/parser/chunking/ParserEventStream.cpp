#include "ParserEventStream.h"
#include "tools/parser/AbstractBottomUpParser.h"
#include "tools/parser/Parser.h"
#include "tools/parser/chunking/Parser.h"
#include "tools/parser/treeinsert/Parser.h"
#include "model/EventStream.h"
#include "tools/parser/ParseSampleStream.h"
#include "tools/util/PlainTextByLineStream.h"

namespace opennlp
{
    namespace tools
    {
        namespace parser
        {
            namespace chunking
            {
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

                ParserEventStream::ParserEventStream(ObjectStream<Parse*> *d, HeadRules *rules, ParserEventTypeEnum etype, Dictionary *dict) : opennlp.tools.parser.AbstractParserEventStream(d,rules,etype,dict)
                {
                }

                void ParserEventStream::init()
                {
                  if (etype == opennlp::tools::parser::BUILD)
                  {
                    this->bcg = new BuildContextGenerator(dict);
                  }
                  else if (etype == opennlp::tools::parser::CHECK)
                  {
                    this->kcg = new CheckContextGenerator();
                  }
                }

                ParserEventStream::ParserEventStream(ObjectStream<Parse*> *d, HeadRules *rules, ParserEventTypeEnum etype)
                {
                }

                bool ParserEventStream::firstChild(Parse *child, Parse *parent)
                {
                  return AbstractBottomUpParser::collapsePunctuation(parent->getChildren(), punctSet)[0] == child;
                }

                Parse *ParserEventStream::reduceChunks(Parse chunks[], int ci, Parse *parent)
                {
                  std::string type = parent->getType();
                  //  perform reduce
                  int reduceStart = ci;
                  int reduceEnd = ci;
                  while (reduceStart >= 0 && chunks[reduceStart]->getParent() == parent)
                  {
                    reduceStart--;
                  }
                  reduceStart++;
//ORIGINAL LINE: opennlp.tools.parser.Parse[] reducedChunks;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                  Parse *reducedChunks;
                  if (type != AbstractBottomUpParser::TOP_NODE)
                  {
                    reducedChunks = new Parse[sizeof(chunks) / sizeof(chunks[0]) - (reduceEnd - reduceStart + 1) + 1]; //total - num_removed + 1 (for new node)
                    //insert nodes before reduction
                    for (int ri = 0,rn = reduceStart;ri < rn;ri++)
                    {
                      reducedChunks[ri] = chunks[ri];
                    }
                    //insert reduced node
                    reducedChunks[reduceStart] = parent;
                    //propagate punctuation sets
                    parent->setPrevPunctuation(chunks[reduceStart]->getPreviousPunctuationSet());
                    parent->setNextPunctuation(chunks[reduceEnd]->getNextPunctuationSet());
                    //insert nodes after reduction
                    int ri = reduceStart + 1;
                    for (int rci = reduceEnd + 1;rci < sizeof(chunks) / sizeof(chunks[0]);rci++)
                    {
                      reducedChunks[ri] = chunks[rci];
                      ri++;
                    }
                    ci = reduceStart - 1; //ci will be incremented at end of loop
                  }
                  else
                  {
                    reducedChunks = new Parse[0];
                  }
                  return reducedChunks;
                }

                void ParserEventStream::addParseEvents(std::vector<Event*> &parseEvents, Parse chunks[])
                {
                  int ci = 0;
                  while (ci < sizeof(chunks) / sizeof(chunks[0]))
                  {
                    //System.err.println("parserEventStream.addParseEvents: chunks="+Arrays.asList(chunks));
                    Parse *c = chunks[ci];
                    Parse *parent = c->getParent();
                    if (parent != 0)
                    {
                      std::string type = parent->getType();
                      std::string outcome;
                      if (firstChild(c, parent))
                      {
                        outcome = AbstractBottomUpParser::START + type;
                      }
                      else
                      {
                        outcome = AbstractBottomUpParser::CONT + type;
                      }
                      //System.err.println("parserEventStream.addParseEvents: chunks["+ci+"]="+c+" label="+outcome+" bcg="+bcg);
                      c->setLabel(outcome);
                      if (etype == opennlp::tools::parser::BUILD)
                      {
                        parseEvents.push_back(new Event(outcome, bcg->getContext(chunks, ci)));
                      }
                      int start = ci - 1;
                      while (start >= 0 && chunks[start]->getParent() == parent)
                      {
                        start--;
                      }
                      if (lastChild(c, parent))
                      {
                        if (etype == opennlp::tools::parser::CHECK)
                        {
                          parseEvents.push_back(new Event(Parser::COMPLETE, kcg->getContext(chunks, type, start + 1, ci)));
                        }
                        //perform reduce
                        int reduceStart = ci;
                        while (reduceStart >= 0 && chunks[reduceStart]->getParent() == parent)
                        {
                          reduceStart--;
                        }
                        reduceStart++;
                        chunks = reduceChunks(chunks,ci,parent);
                        ci = reduceStart - 1; //ci will be incremented at end of loop
                      }
                      else
                      {
                        if (etype == opennlp::tools::parser::CHECK)
                        {
                          parseEvents.push_back(new Event(Parser::INCOMPLETE, kcg->getContext(chunks, type, start + 1, ci)));
                        }
                      }
                    }
                    ci++;
                  }
                }

                void ParserEventStream::main(std::string args[]) throw(java::io::IOException, InvalidFormatException)
                {
                  if (sizeof(args) / sizeof(args[0]) == 0)
                  {
                    System::err::println("Usage ParserEventStream -[tag|chunk|build|check|fun] head_rules [dictionary] < parses");
                    exit(1);
                  }
                  ParserEventTypeEnum etype = 0;
                  bool fun = false;
                  int ai = 0;
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'startsWith' method:
                  while (ai < sizeof(args) / sizeof(args[0]) && args[ai].startsWith("-"))
                  {
                    if (args[ai] == "-build")
                    {
                      etype = opennlp::tools::parser::BUILD;
                    }
                    else if (args[ai] == "-check")
                    {
                      etype = opennlp::tools::parser::CHECK;
                    }
                    else if (args[ai] == "-chunk")
                    {
                      etype = opennlp::tools::parser::CHUNK;
                    }
                    else if (args[ai] == "-tag")
                    {
                      etype = opennlp::tools::parser::TAG;
                    }
                    else if (args[ai] == "-fun")
                    {
                      fun = true;
                    }
                    else
                    {
                      System::err::println("Invalid option " + args[ai]);
                      exit(1);
                    }
                    ai++;
                  }
                  HeadRules *rules = new opennlp::tools::parser::lang::en::HeadRules(args[ai++]);
                  Dictionary *dict = 0;
                  if (ai < sizeof(args) / sizeof(args[0]))
                  {
                    dict = new Dictionary(new FileInputStream(args[ai++]),true);
                  }
                  if (fun)
                  {
                    Parse::useFunctionTags(true);
                  }
                  opennlp::model::EventStream *es = new ParserEventStream(new ParseSampleStream(new PlainTextByLineStream(new java::io::InputStreamReader(System::in))), rules, etype, dict);
                  while (es->hasNext())
                  {
                    std::cout << es->next() << std::endl;
                      es++;
                  }
                }
            }
        }
    }
}
