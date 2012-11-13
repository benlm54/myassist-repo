#include "Parser.h"
#include "tools/util/Span.h"
#include "maxent/GIS.h"
#include "model/TwoPassDataIndexer.h"
#include "tools/dictionary/Dictionary.h"
#include "tools/parser/ParserEventTypeEnum.h"
#include "tools/parser/chunking/ParserEventStream.h"
#include "tools/parser/treeinsert/ParserEventStream.h"
#include "model/TrainUtil.h"
#include "tools/parser/PosSampleStream.h"
#include "tools/postag/POSModel.h"
#include "tools/postag/POSTaggerME.h"
#include "tools/chunker/ChunkerME.h"
#include "tools/chunker/ChunkerModel.h"
#include "tools/parser/ChunkContextGenerator.h"
#include "tools/parser/ChunkSampleStream.h"
#include "tools/parser/ParserType.h"
#include "tools/parser/lang/en/HeadRules.h"

namespace opennlp
{
    namespace tools
    {
        namespace parser
        {
            namespace chunking
            {
                using opennlp::model::AbstractModel;
                using opennlp::model::MaxentModel;
                using opennlp::model::TrainUtil;
                using opennlp::model::TwoPassDataIndexer;
                using opennlp::tools::chunker::Chunker;
                using opennlp::tools::chunker::ChunkerME;
                using opennlp::tools::chunker::ChunkerModel;
                using opennlp::tools::dictionary::Dictionary;
                using opennlp::tools::namefind::TokenNameFinderEvaluationMonitor;
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
                using opennlp::tools::util::Span;
                using opennlp::tools::util::TrainingParameters;
const std::string Parser::TOP_START = START + TOP_NODE;

                Parser::Parser(ParserModel *model, int beamSize, double advancePercentage)
                {
                }

                Parser::Parser(ParserModel *model)
                {
                }

                Parser::Parser(MaxentModel *buildModel, MaxentModel *checkModel, POSTagger *tagger, Chunker *chunker, HeadRules *headRules)
                {
                }

                Parser::Parser(MaxentModel *buildModel, MaxentModel *checkModel, POSTagger *tagger, Chunker *chunker, HeadRules *headRules, int beamSize, double advancePercentage) : opennlp.tools.parser.AbstractBottomUpParser(tagger, chunker, headRules, beamSize, advancePercentage)
                {
                  this->buildModel = buildModel;
                  this->checkModel = checkModel;
                  bprobs = new double[buildModel->getNumOutcomes()];
                  cprobs = new double[checkModel->getNumOutcomes()];
                  this->buildContextGenerator = new BuildContextGenerator();
                  this->checkContextGenerator = new CheckContextGenerator();
                  startTypeMap = std::map<std::string, std::string>();
                  contTypeMap = std::map<std::string, std::string>();
                  for (int boi = 0, bon = buildModel->getNumOutcomes(); boi < bon; boi++)
                  {
                    std::string outcome = buildModel->getOutcome(boi);
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'startsWith' method:
                    if (outcome.startsWith(START))
                    {
                      //System.err.println("startMap "+outcome+"->"+outcome.substring(START.length()));
                      startTypeMap->put(outcome, outcome.substr(START.length()));
                    }
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'startsWith' method:
                    else if (outcome.startsWith(CONT))
                    {
                      //System.err.println("contMap "+outcome+"->"+outcome.substring(CONT.length()));
                      contTypeMap->put(outcome, outcome.substr(CONT.length()));
                    }
                  }
                  topStartIndex = buildModel->getIndex(TOP_START);
                  completeIndex = checkModel->getIndex(COMPLETE);
                  incompleteIndex = checkModel->getIndex(INCOMPLETE);
                }

                void Parser::advanceTop(Parse *p)
                {
                  buildModel->eval(buildContextGenerator->getContext(p->getChildren(), 0), bprobs);
                  p->addProb(log(bprobs[topStartIndex]));
                  checkModel->eval(checkContextGenerator->getContext(p->getChildren(), TOP_NODE, 0, 0), cprobs);
                  p->addProb(log(cprobs[completeIndex]));
                  p->setType(TOP_NODE);
                }

                Parse *Parser::advanceParses(Parse *const p, double probMass)
                {
                  double q = 1 - probMass;
                  /// <summary>
                  /// The closest previous node which has been labeled as a start node. </summary>
                  Parse *lastStartNode = 0;
                  /// <summary>
                  /// The index of the closest previous node which has been labeled as a start node. </summary>
                  int lastStartIndex = -1;
                  /// <summary>
                  /// The type of the closest previous node which has been labeled as a start node. </summary>
                  std::string lastStartType = "";
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
                  //determines which node needs to be labeled and prior labels.
                  for (advanceNodeIndex = 0; advanceNodeIndex < numNodes; advanceNodeIndex++)
                  {
                    advanceNode = children[advanceNodeIndex];
                    if (advanceNode->getLabel() == "")
                    {
                      break;
                    }
                    else if (startTypeMap->containsKey(advanceNode->getLabel()))
                    {
                      lastStartType = startTypeMap->get(advanceNode->getLabel());
                      lastStartNode = advanceNode;
                      lastStartIndex = advanceNodeIndex;
                      //System.err.println("lastStart "+i+" "+lastStart.label+" "+lastStart.prob);
                    }
                  }
                  int originalAdvanceIndex = mapParseIndex(advanceNodeIndex,children,originalChildren);
                  std::vector<Parse*> newParsesList = std::vector<Parse*>(buildModel->getNumOutcomes());
                  //call build
                  buildModel->eval(buildContextGenerator->getContext(children, advanceNodeIndex), bprobs);
                  double bprobSum = 0;
                  while (bprobSum < probMass)
                  {
                    // The largest unadvanced labeling.
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
                    //System.out.println("trying "+tag+" "+bprobSum+" lst="+lst);
                    if (max == topStartIndex) // can't have top until complete
                    {
                      continue;
                    }
                    //System.err.println(i+" "+tag+" "+bprob);
                    if (startTypeMap->containsKey(tag)) //update last start
                    {
                      lastStartIndex = advanceNodeIndex;
                      lastStartNode = advanceNode;
                      lastStartType = startTypeMap->get(tag);
                    }
                    else if (contTypeMap->containsKey(tag))
                    {
                      if (lastStartNode == 0 || lastStartType != contTypeMap->get(tag))
                      {
                        continue; //Cont must match previous start or continue
                      }
                    }
                    Parse *newParse1 = static_cast<Parse*>(p->clone()); //clone parse
                    if (createDerivationString)
                        newParse1->getDerivation()->append(max)->append("-");
                    newParse1->setChild(originalAdvanceIndex,tag); //replace constituent being labeled to create new derivation
                    newParse1->addProb(log(bprob));
                    //check
                    //String[] context = checkContextGenerator.getContext(newParse1.getChildren(), lastStartType, lastStartIndex, advanceNodeIndex);
                    checkModel->eval(checkContextGenerator->getContext(collapsePunctuation(newParse1->getChildren(),punctSet), lastStartType, lastStartIndex, advanceNodeIndex), cprobs);
                    //System.out.println("check "+lastStartType+" "+cprobs[completeIndex]+" "+cprobs[incompleteIndex]+" "+tag+" "+java.util.Arrays.asList(context));
                    Parse *newParse2 = newParse1;
                    if (cprobs[completeIndex] > q) //make sure a reduce is likely
                    {
                      newParse2 = static_cast<Parse*>(newParse1->clone());
                      if (createDerivationString)
                          newParse2->getDerivation()->append(1)->append(".");
                      newParse2->addProb(log(cprobs[completeIndex]));
                      Parse cons[advanceNodeIndex - lastStartIndex + 1];
                      bool flat = true;
                      //first
                      cons[0] = lastStartNode;
                      flat &= cons[0]->isPosTag();
                      //last
                      cons[advanceNodeIndex - lastStartIndex] = advanceNode;
                      flat &= cons[advanceNodeIndex - lastStartIndex]->isPosTag();
                      //middle
                      for (int ci = 1; ci < advanceNodeIndex - lastStartIndex; ci++)
                      {
                        cons[ci] = children[ci + lastStartIndex];
                        flat &= cons[ci]->isPosTag();
                      }
                      if (!flat) //flat chunks are done by chunker
                      {
                        if (lastStartIndex == 0 && advanceNodeIndex == numNodes - 1) //check for top node to include end and begining punctuation
                        {
                          //System.err.println("ParserME.advanceParses: reducing entire span: "+new Span(lastStartNode.getSpan().getStart(), advanceNode.getSpan().getEnd())+" "+lastStartType+" "+java.util.Arrays.asList(children));
                          newParse2->insert(new Parse(p->getText(), p->getSpan(), lastStartType, cprobs[1], headRules->getHead(cons, lastStartType)));
                        }
                        else
                        {
                          newParse2->insert(new Parse(p->getText(), new Span(lastStartNode->getSpan()->getStart(), advanceNode->getSpan()->getEnd()), lastStartType, cprobs[1], headRules->getHead(cons, lastStartType)));
                        }
                        newParsesList.push_back(newParse2);
                      }
                    }
                    if (cprobs[incompleteIndex] > q) //make sure a shift is likely
                    {
                      if (createDerivationString)
                          newParse1->getDerivation()->append(0)->append(".");
                      if (advanceNodeIndex != numNodes - 1) //can't shift last element
                      {
                        newParse1->addProb(log(cprobs[incompleteIndex]));
                        newParsesList.push_back(newParse1);
                      }
                    }
                  }
                  Parse newParses[newParsesList.size()];
                  newParsesList.toArray(newParses);
                  return newParses;
                }

                opennlp::model::AbstractModel *Parser::train(opennlp::model::EventStream *es, int iterations, int cut) throw(IOException)
                {
                  return opennlp::maxent::GIS::trainModel(iterations, new TwoPassDataIndexer(es, cut));
                }

                void Parser::mergeReportIntoManifest(Map<std::string, std::string> *manifest, Map<std::string, std::string> *report, const std::string &namespace_Renamed)
                {

                  for (Map<std::string, std::string>::const_iterator entry = report->begin(); entry != report->end(); ++entry)
                  {
                    manifest->put(namespace_Renamed + "." + (*entry)->getKey(), (*entry)->getValue());
                  }
                }

                opennlp::tools::parser::ParserModel *Parser::train(const std::string &languageCode, ObjectStream<Parse*> *parseSamples, HeadRules *rules, TrainingParameters *mlParams) throw(IOException)
                {

                  System::err::println("Building dictionary");

                  Dictionary *mdict = buildDictionary(parseSamples, rules, mlParams);

                  parseSamples->reset();

                  Map<std::string, std::string> *manifestInfoEntries = std::map<std::string, std::string>();

                  // build
                  System::err::println("Training builder");
                  opennlp::model::EventStream *bes = new ParserEventStream(parseSamples, rules, opennlp::tools::parser::BUILD, mdict);
                  Map<std::string, std::string> *buildReportMap = std::map<std::string, std::string>();
                  AbstractModel *buildModel = TrainUtil::train(bes, mlParams->getSettings("build"), buildReportMap);
                  mergeReportIntoManifest(manifestInfoEntries, buildReportMap, "build");

                  parseSamples->reset();

                  // tag
                  POSModel *posModel = POSTaggerME::train(languageCode, new PosSampleStream(parseSamples), mlParams->getParameters("tagger"), 0, 0);

                  parseSamples->reset();

                  // chunk
                  ChunkerModel *chunkModel = ChunkerME::train(languageCode, new ChunkSampleStream(parseSamples), new ChunkContextGenerator(), mlParams->getParameters("chunker"));

                  parseSamples->reset();

                  // check
                  System::err::println("Training checker");
                  opennlp::model::EventStream *kes = new ParserEventStream(parseSamples, rules, opennlp::tools::parser::CHECK);
                  Map<std::string, std::string> *checkReportMap = std::map<std::string, std::string>();
                  AbstractModel *checkModel = TrainUtil::train(kes, mlParams->getSettings("check"), checkReportMap);
                  mergeReportIntoManifest(manifestInfoEntries, checkReportMap, "check");

                  // TODO: Remove cast for HeadRules
                  return new ParserModel(languageCode, buildModel, checkModel, posModel, chunkModel, static_cast<opennlp::tools::parser::lang::en::HeadRules*>(rules), opennlp::tools::parser::ParserType_Renamed::CHUNKING, manifestInfoEntries);
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
            }
        }
    }
}
