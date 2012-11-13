#include "Parser.h"
#include "tools/dictionary/Dictionary.h"
#include "tools/parser/PosSampleStream.h"
#include "tools/postag/POSModel.h"
#include "tools/postag/POSTaggerME.h"
#include "tools/chunker/ChunkerME.h"
#include "tools/chunker/ChunkerModel.h"
#include "tools/parser/ChunkContextGenerator.h"
#include "tools/parser/ChunkSampleStream.h"
#include "tools/parser/ParserEventTypeEnum.h"
#include "tools/parser/chunking/ParserEventStream.h"
#include "tools/parser/treeinsert/ParserEventStream.h"
#include "model/TrainUtil.h"
#include "tools/parser/ParserType.h"
#include "tools/parser/lang/en/HeadRules.h"
#include "maxent/GIS.h"
#include "model/TwoPassDataIndexer.h"

namespace opennlp
{
    namespace tools
    {
        namespace parser
        {
            namespace treeinsert
            {
                using opennlp::model::AbstractModel;
                using opennlp::model::MaxentModel;
                using opennlp::model::TrainUtil;
                using opennlp::model::TwoPassDataIndexer;
                using opennlp::tools::chunker::Chunker;
                using opennlp::tools::chunker::ChunkerME;
                using opennlp::tools::chunker::ChunkerModel;
                using opennlp::tools::dictionary::Dictionary;
                using opennlp::tools::parser::AbstractBottomUpParser;
                using opennlp::tools::parser::ChunkContextGenerator;
                using opennlp::tools::parser::ChunkSampleStream;
                using opennlp::tools::parser::HeadRules;
                using opennlp::tools::parser::Parse;
                using opennlp::tools::parser::ParserChunkerSequenceValidator;
                using opennlp::tools::parser::ParserEventTypeEnum;
                using opennlp::tools::parser::ParserModel;
                using opennlp::tools::parser::ParserType;
                using opennlp::tools::parser::PosSampleStream;
                using opennlp::tools::postag::POSModel;
                using opennlp::tools::postag::POSTagger;
                using opennlp::tools::postag::POSTaggerME;
                using opennlp::tools::util::ObjectStream;
                using opennlp::tools::util::TrainingParameters;
const std::string Parser::DONE = "d";
const std::string Parser::ATTACH_SISTER = "s";
const std::string Parser::ATTACH_DAUGHTER = "d";
const std::string Parser::NON_ATTACH = "n";
const std::string Parser::BUILT = "built";
bool Parser::checkComplete = false;

                Parser::Parser(ParserModel *model, int beamSize, double advancePercentage)
                {
                }

                Parser::Parser(ParserModel *model)
                {
                }

                Parser::Parser(AbstractModel *buildModel, AbstractModel *attachModel, AbstractModel *checkModel, POSTagger *tagger, Chunker *chunker, HeadRules *headRules, int beamSize, double advancePercentage) : opennlp.tools.parser.AbstractBottomUpParser(tagger,chunker,headRules,beamSize,advancePercentage)
                {
                  this->buildModel = buildModel;
                  this->attachModel = attachModel;
                  this->checkModel = checkModel;

                  this->buildContextGenerator = new BuildContextGenerator();
                  this->attachContextGenerator = new AttachContextGenerator(punctSet);
                  this->checkContextGenerator = new CheckContextGenerator(punctSet);

                  this->bprobs = new double[buildModel->getNumOutcomes()];
                  this->aprobs = new double[attachModel->getNumOutcomes()];
                  this->cprobs = new double[checkModel->getNumOutcomes()];

                  this->doneIndex = buildModel->getIndex(DONE);
                  this->sisterAttachIndex = attachModel->getIndex(ATTACH_SISTER);
                  this->daughterAttachIndex = attachModel->getIndex(ATTACH_DAUGHTER);
                  this->nonAttachIndex = attachModel->getIndex(NON_ATTACH);
                  attachments = new int[] {daughterAttachIndex,sisterAttachIndex};
                  this->completeIndex = checkModel->getIndex(Parser::COMPLETE);
                }

                Parser::Parser(AbstractModel *buildModel, AbstractModel *attachModel, AbstractModel *checkModel, POSTagger *tagger, Chunker *chunker, HeadRules *headRules)
                {
                }

                std::vector<Parse*> Parser::getRightFrontier(Parse *root, Set<std::string> *punctSet)
                {
                  std::vector<Parse*> rf = std::list<Parse*>();
                  Parse *top;
                  if (root->getType() == AbstractBottomUpParser::TOP_NODE || root->getType() == AbstractBottomUpParser::INC_NODE)
                  {
                    top = collapsePunctuation(root->getChildren(),punctSet)[0];
                  }
                  else
                  {
                    top = root;
                  }
                  while (!top->isPosTag())
                  {
                    rf.push_back(0,top);
//ORIGINAL LINE: opennlp.tools.parser.Parse[] kids = top.getChildren();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                    Parse *kids = top->getChildren();
                    top = kids[kids->length - 1];
                  }
                  return std::vector<Parse*>(rf);
                }

                void Parser::setBuilt(Parse *p)
                {
                  std::string l = p->getLabel();
                  if (l == "")
                  {
                    p->setLabel(Parser::BUILT);
                  }
                  else
                  {
                    if (isComplete(p))
                    {
                      p->setLabel(Parser::BUILT + "." + Parser::COMPLETE);
                    }
                    else
                    {
                      p->setLabel(Parser::BUILT + "." + Parser::INCOMPLETE);
                    }
                  }
                }

                void Parser::setComplete(Parse *p)
                {
                  std::string l = p->getLabel();
                  if (!isBuilt(p))
                  {
                    p->setLabel(Parser::COMPLETE);
                  }
                  else
                  {
                    p->setLabel(Parser::BUILT + "." + Parser::COMPLETE);
                  }
                }

                void Parser::setIncomplete(Parse *p)
                {
                  if (!isBuilt(p))
                  {
                    p->setLabel(Parser::INCOMPLETE);
                  }
                  else
                  {
                    p->setLabel(Parser::BUILT + "." + Parser::INCOMPLETE);
                  }
                }

                bool Parser::isBuilt(Parse *p)
                {
                  std::string l = p->getLabel();
                  if (l == "")
                  {
                    return false;
                  }
                  else
                  {
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'startsWith' method:
                    return l.startsWith(Parser::BUILT);
                  }
                }

                bool Parser::isComplete(Parse *p)
                {
                  std::string l = p->getLabel();
                  if (l == "")
                  {
                    return false;
                  }
                  else
                  {
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'endsWith' method:
                    return l.endsWith(Parser::COMPLETE);
                  }
                }

                Parse *Parser::advanceChunks(Parse *p, double minChunkScore)
                {
//ORIGINAL LINE: opennlp.tools.parser.Parse[] parses = super.advanceChunks(p, minChunkScore);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                  Parse *parses = AbstractBottomUpParser::advanceChunks(p, minChunkScore);
                  for (int pi = 0;pi < parses->length;pi++)
                  {
//ORIGINAL LINE: opennlp.tools.parser.Parse[] chunks = parses[pi].getChildren();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                    Parse *chunks = parses[pi]->getChildren();
                    for (int ci = 0;ci < chunks->length;ci++)
                    {
                      setComplete(chunks[ci]);
                    }
                  }
                  return parses;
                }

                Parse *Parser::advanceParses(Parse *p, double probMass)
                {
                  double q = 1 - probMass;
                  /// <summary>
                  /// The index of the node which will be labeled in this iteration of advancing the parse. </summary>
                  int advanceNodeIndex;
                  /// <summary>
                  /// The node which will be labeled in this iteration of advancing the parse. </summary>
                  Parse *advanceNode = 0;
//ORIGINAL LINE: opennlp.tools.parser.Parse[] originalChildren = p.getChildren();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                  Parse *originalChildren = p->getChildren();
//ORIGINAL LINE: opennlp.tools.parser.Parse[] children = collapsePunctuation(originalChildren,punctSet);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                  Parse *children = collapsePunctuation(originalChildren,punctSet);
                  int numNodes = children->length;
                  if (numNodes == 0)
                  {
                    return 0;
                  }
                  else if (numNodes == 1) //put sentence initial and final punct in top node
                  {
                    if (children[0]->isPosTag())
                    {
                      return 0;
                    }
                    else
                    {
                      p->expandTopNode(children[0]);
                      return new Parse[] {p};
                    }
                  }
                  //determines which node needs to adanced.
                  for (advanceNodeIndex = 0; advanceNodeIndex < numNodes; advanceNodeIndex++)
                  {
                    advanceNode = children[advanceNodeIndex];
                    if (!isBuilt(advanceNode))
                    {
                      break;
                    }
                  }
                  int originalZeroIndex = mapParseIndex(0,children,originalChildren);
                  int originalAdvanceIndex = mapParseIndex(advanceNodeIndex,children,originalChildren);
                  std::vector<Parse*> newParsesList = std::vector<Parse*>();
                  //call build model
                  buildModel->eval(buildContextGenerator->getContext(children, advanceNodeIndex), bprobs);
                  double doneProb = bprobs[doneIndex];
                  if (debugOn)
                      std::cout << "adi=" + advanceNodeIndex + " " + advanceNode->getType() + "." + advanceNode->getLabel() + " " + advanceNode + " choose build=" + (1 - doneProb) + " attach=" + doneProb << std::endl;
                  if (1 - doneProb > q)
                  {
                    double bprobSum = 0;
                    while (bprobSum < probMass)
                    {
                      /// <summary>
                      /// The largest unadvanced labeling. </summary>
                      int max = 0;
                      for (int pi = 1; pi < bprobs->length; pi++) //for each build outcome
                      {
                        if (bprobs[pi] > bprobs[max])
                        {
                          max = pi;
                        }
                      }
                      if (bprobs[max] == 0)
                      {
                        break;
                      }
                      double bprob = bprobs[max];
                      bprobs[max] = 0; //zero out so new max can be found
                      bprobSum += bprob;
                      std::string tag = buildModel->getOutcome(max);
                      if (tag != DONE)
                      {
                        Parse *newParse1 = static_cast<Parse*>(p->clone());
                        Parse *newNode = new Parse(p->getText(),advanceNode->getSpan(),tag,bprob,advanceNode->getHead());
                        newParse1->insert(newNode);
                        newParse1->addProb(log(bprob));
                        newParsesList.push_back(newParse1);
                        if (checkComplete)
                        {
                          cprobs = checkModel->eval(checkContextGenerator->getContext(newNode,children,advanceNodeIndex,false));
                          if (debugOn)
                              std::cout << "building " + tag + " " + bprob + " c=" + cprobs[completeIndex] << std::endl;
                          if (cprobs[completeIndex] > probMass) //just complete advances
                          {
                            setComplete(newNode);
                            newParse1->addProb(log(cprobs[completeIndex]));
                            if (debugOn)
                                std::cout << "Only advancing complete node" << std::endl;
                          }
                          else if (1 - cprobs[completeIndex] > probMass) //just incomplete advances
                          {
                            setIncomplete(newNode);
                            newParse1->addProb(log(1 - cprobs[completeIndex]));
                            if (debugOn)
                                std::cout << "Only advancing incomplete node" << std::endl;
                          }
                          else //both complete and incomplete advance
                          {
                            if (debugOn)
                                std::cout << "Advancing both complete and incomplete nodes" << std::endl;
                            setComplete(newNode);
                            newParse1->addProb(log(cprobs[completeIndex]));

                            Parse *newParse2 = static_cast<Parse*>(p->clone());
                            Parse *newNode2 = new Parse(p->getText(),advanceNode->getSpan(),tag,bprob,advanceNode->getHead());
                            newParse2->insert(newNode2);
                            newParse2->addProb(log(bprob));
                            newParsesList.push_back(newParse2);
                            newParse2->addProb(log(1 - cprobs[completeIndex]));
                            setIncomplete(newNode2); //set incomplete for non-clone
                          }
                        }
                        else
                        {
                          if (debugOn)
                              std::cout << "building " + tag + " " + bprob << std::endl;
                        }
                      }
                    }
                  }
                  //advance attaches
                  if (doneProb > q)
                  {
                    Parse *newParse1 = static_cast<Parse*>(p->clone()); //clone parse
                    //mark nodes as built
                    if (checkComplete)
                    {
                      if (isComplete(advanceNode))
                      {
                        newParse1->setChild(originalAdvanceIndex,Parser::BUILT + "." + Parser::COMPLETE); //replace constituent being labeled to create new derivation
                      }
                      else
                      {
                        newParse1->setChild(originalAdvanceIndex,Parser::BUILT + "." + Parser::INCOMPLETE); //replace constituent being labeled to create new derivation
                      }
                    }
                    else
                    {
                      newParse1->setChild(originalAdvanceIndex,Parser::BUILT); //replace constituent being labeled to create new derivation
                    }
                    newParse1->addProb(log(doneProb));
                    if (advanceNodeIndex == 0) //no attach if first node.
                    {
                      newParsesList.push_back(newParse1);
                    }
                    else
                    {
                      std::vector<Parse*> rf = getRightFrontier(p,punctSet);
                      for (int fi = 0,fs = rf.size();fi < fs;fi++)
                      {
                        Parse *fn = rf[fi];
                        attachModel->eval(attachContextGenerator->getContext(children, advanceNodeIndex,rf,fi), aprobs);
                        if (debugOn)
                        {
                          //List cs = java.util.Arrays.asList(attachContextGenerator.getContext(children, advanceNodeIndex,rf,fi,punctSet));
                          std::cout << "Frontier node(" + fi + "): " + fn->getType() + "." + fn->getLabel() + " " + fn + " <- " + advanceNode->getType() + " " + advanceNode + " d=" + aprobs[daughterAttachIndex] + " s=" + aprobs[sisterAttachIndex] + " " << std::endl;
                        }
                        for (int ai = 0;ai < attachments->length;ai++)
                        {
                          double prob = aprobs[attachments[ai]];
                          //should we try an attach if p > threshold and
                          // if !checkComplete then prevent daughter attaching to chunk
                          // if checkComplete then prevent daughter attacing to complete node or
                          //    sister attaching to an incomplete node
                          if (prob > q && ((!checkComplete && (attachments[ai] != daughterAttachIndex || !isComplete(fn))) || (checkComplete && ((attachments[ai] == daughterAttachIndex && !isComplete(fn)) || (attachments[ai] == sisterAttachIndex && isComplete(fn))))))
                          {
                            Parse *newParse2 = newParse1->cloneRoot(fn,originalZeroIndex);
//ORIGINAL LINE: opennlp.tools.parser.Parse[] newKids = Parser.collapsePunctuation(newParse2.getChildren(),punctSet);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                            Parse *newKids = Parser::collapsePunctuation(newParse2->getChildren(),punctSet);
                            //remove node from top level since were going to attach it (including punct)
                            for (int ri = originalZeroIndex + 1;ri <= originalAdvanceIndex;ri++)
                            {
                              //System.out.println(at"-removing "+(originalZeroIndex+1)+" "+newParse2.getChildren()[originalZeroIndex+1]);
                              newParse2->remove(originalZeroIndex + 1);
                            }
                            std::vector<Parse*> crf = getRightFrontier(newParse2,punctSet);
                            Parse *updatedNode;
                            if (attachments[ai] == daughterAttachIndex) //attach daughter
                            {
                              updatedNode = crf[fi];
                              updatedNode->add(advanceNode,headRules);
                            }
                            else //attach sister
                            {
                              Parse *psite;
                              if (fi + 1 < crf.size())
                              {
                                psite = crf[fi + 1];
                                updatedNode = psite->adjoin(advanceNode,headRules);
                              }
                              else
                              {
                                psite = newParse2;
                                updatedNode = psite->adjoinRoot(advanceNode,headRules,originalZeroIndex);
                                newKids[0] = updatedNode;
                              }
                            }
                            //update spans affected by attachment
                            for (int ni = fi + 1;ni < crf.size();ni++)
                            {
                              Parse *node = crf[ni];
                              node->updateSpan();
                            }
                            //if (debugOn) {System.out.print(ai+"-result: ");newParse2.show();System.out.println();}
                            newParse2->addProb(log(prob));
                            newParsesList.push_back(newParse2);
                            if (checkComplete)
                            {
                              cprobs = checkModel->eval(checkContextGenerator->getContext(updatedNode,newKids,advanceNodeIndex,true));
                              if (cprobs[completeIndex] > probMass)
                              {
                                setComplete(updatedNode);
                                newParse2->addProb(log(cprobs[completeIndex]));
                                if (debugOn)
                                    std::cout << "Only advancing complete node" << std::endl;
                              }
                              else if (1 - cprobs[completeIndex] > probMass)
                              {
                                setIncomplete(updatedNode);
                                newParse2->addProb(log(1 - cprobs[completeIndex]));
                                if (debugOn)
                                    std::cout << "Only advancing incomplete node" << std::endl;
                              }
                              else
                              {
                                setComplete(updatedNode);
                                Parse *newParse3 = newParse2->cloneRoot(updatedNode,originalZeroIndex);
                                newParse3->addProb(log(cprobs[completeIndex]));
                                newParsesList.push_back(newParse3);
                                setIncomplete(updatedNode);
                                newParse2->addProb(log(1 - cprobs[completeIndex]));
                                if (debugOn)
                                    std::cout << "Advancing both complete and incomplete nodes; c=" + cprobs[completeIndex] << std::endl;
                              }
                            }
                          }
                          else
                          {
                            if (debugOn)
                                std::cout << "Skipping " + fn->getType() + "." + fn->getLabel() + " " + fn + " daughter=" + (attachments[ai] == daughterAttachIndex) + " complete=" + isComplete(fn) + " prob=" + prob << std::endl;
                          }
                        }
                        if (checkComplete && !isComplete(fn))
                        {
                          if (debugOn)
                              std::cout << "Stopping at incomplete node(" + fi + "): " + fn->getType() + "." + fn->getLabel() + " " + fn << std::endl;
                          break;
                        }
                      }
                    }
                  }
                  Parse newParses[newParsesList.size()];
                  newParsesList.toArray(newParses);
                  return newParses;
                }

                void Parser::advanceTop(Parse *p)
                {
                  p->setType(TOP_NODE);
                }

                opennlp::tools::parser::ParserModel *Parser::train(const std::string &languageCode, ObjectStream<Parse*> *parseSamples, HeadRules *rules, TrainingParameters *mlParams) throw(IOException)
                {

                  Map<std::string, std::string> *manifestInfoEntries = std::map<std::string, std::string>();

                  System::err::println("Building dictionary");
                  Dictionary *mdict = buildDictionary(parseSamples, rules, mlParams);

                  parseSamples->reset();

                  // tag
                  POSModel *posModel = POSTaggerME::train(languageCode, new PosSampleStream(parseSamples), mlParams->getParameters("tagger"), 0, 0);

                  parseSamples->reset();

                  // chunk
                  ChunkerModel *chunkModel = ChunkerME::train(languageCode, new ChunkSampleStream(parseSamples), new ChunkContextGenerator(), mlParams->getParameters("chunker"));

                  parseSamples->reset();

                  // build
                  System::err::println("Training builder");
                  opennlp::model::EventStream *bes = new ParserEventStream(parseSamples, rules, opennlp::tools::parser::BUILD, mdict);
                  Map<std::string, std::string> *buildReportMap = std::map<std::string, std::string>();
                  AbstractModel *buildModel = TrainUtil::train(bes, mlParams->getSettings("build"), buildReportMap);
                  opennlp::tools::parser::chunking::Parser::mergeReportIntoManifest(manifestInfoEntries, buildReportMap, "build");

                  parseSamples->reset();

                  // check
                  System::err::println("Training checker");
                  opennlp::model::EventStream *kes = new ParserEventStream(parseSamples, rules, opennlp::tools::parser::CHECK);
                  Map<std::string, std::string> *checkReportMap = std::map<std::string, std::string>();
                  AbstractModel *checkModel = TrainUtil::train(kes, mlParams->getSettings("check"), checkReportMap);
                  opennlp::tools::parser::chunking::Parser::mergeReportIntoManifest(manifestInfoEntries, checkReportMap, "check");

                  parseSamples->reset();

                  // attach 
                  System::err::println("Training attacher");
                  opennlp::model::EventStream *attachEvents = new ParserEventStream(parseSamples, rules, opennlp::tools::parser::ATTACH);
                  Map<std::string, std::string> *attachReportMap = std::map<std::string, std::string>();
                  AbstractModel *attachModel = TrainUtil::train(attachEvents, mlParams->getSettings("attach"), attachReportMap);
                  opennlp::tools::parser::chunking::Parser::mergeReportIntoManifest(manifestInfoEntries, attachReportMap, "attach");

                  // TODO: Remove cast for HeadRules
                  return new ParserModel(languageCode, buildModel, checkModel, attachModel, posModel, chunkModel, static_cast<opennlp::tools::parser::lang::en::HeadRules*>(rules), opennlp::tools::parser::ParserType_Renamed::TREEINSERT, manifestInfoEntries);
                }

                opennlp::tools::parser::ParserModel *Parser::train(const std::string &languageCode, ObjectStream<Parse*> *parseSamples, HeadRules *rules, int iterations, int cut) throw(IOException)
                {

                  TrainingParameters *params = new TrainingParameters();
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                  params->put("dict", TrainingParameters::CUTOFF_PARAM, int::toString(cut));

//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                  params->put("tagger", TrainingParameters::CUTOFF_PARAM, int::toString(cut));
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                  params->put("tagger", TrainingParameters::ITERATIONS_PARAM, int::toString(iterations));
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                  params->put("chunker", TrainingParameters::CUTOFF_PARAM, int::toString(cut));
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                  params->put("chunker", TrainingParameters::ITERATIONS_PARAM, int::toString(iterations));
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                  params->put("check", TrainingParameters::CUTOFF_PARAM, int::toString(cut));
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                  params->put("check", TrainingParameters::ITERATIONS_PARAM, int::toString(iterations));
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                  params->put("build", TrainingParameters::CUTOFF_PARAM, int::toString(cut));
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                  params->put("build", TrainingParameters::ITERATIONS_PARAM, int::toString(iterations));

                  return train(languageCode, parseSamples, rules, params);
                }

                opennlp::model::AbstractModel *Parser::train(opennlp::model::EventStream *es, int iterations, int cut) throw(IOException)
                {
                  return opennlp::maxent::GIS::trainModel(iterations, new TwoPassDataIndexer(es, cut));
                }
            }
        }
    }
}
