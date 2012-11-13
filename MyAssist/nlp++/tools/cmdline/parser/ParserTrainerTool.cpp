#include "ParserTrainerTool.h"
#include "tools/cmdline/ArgumentParser.h"
#include "tools/cmdline/CLI.h"
#include "tools/cmdline/CmdLineUtil.h"
#include "tools/cmdline/TerminateToolException.h"
#include "tools/parser/ParseSampleStream.h"
#include "tools/util/PlainTextByLineStream.h"
#include "tools/parser/chunking/Parser.h"
#include "tools/util/TrainingParameters.h"
#include "model/TrainUtil.h"
#include "tools/parser/ParserModel.h"
#include "tools/parser/treeinsert/Parser.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace parser
            {
                using opennlp::model::TrainUtil;
                using opennlp::tools::cmdline::ArgumentParser;
                using opennlp::tools::cmdline::CLI;
                using opennlp::tools::cmdline::CmdLineTool;
                using opennlp::tools::cmdline::CmdLineUtil;
                using opennlp::tools::cmdline::TerminateToolException;
                using opennlp::tools::cmdline::params::TrainingToolParams;
                using opennlp::tools::dictionary::Dictionary;
                using opennlp::tools::parser::HeadRules;
                using opennlp::tools::parser::Parse;
                using opennlp::tools::parser::ParseSampleStream;
                using opennlp::tools::parser::ParserModel;
                using opennlp::tools::parser::ParserType;
                using opennlp::tools::parser::chunking::Parser;
                using opennlp::tools::util::ObjectStream;
                using opennlp::tools::util::PlainTextByLineStream;

                std::string ParserTrainerTool::getName()
                {
                  return "ParserTrainer";
                }

                std::string ParserTrainerTool::getShortDescription()
                {
                  return "trains the learnable parser";
                }

                std::string ParserTrainerTool::getHelp()
                {
                  return "Usage: " + CLI::CMD + " " + getName() + " " + ArgumentParser::createUsage(TrainerToolParams::typeid);
                }

                opennlp::tools::util::ObjectStream<Parse*> *ParserTrainerTool::openTrainingData(File *trainingDataFile, Charset *encoding)
                {

                  CmdLineUtil::checkInputFile("Training data", trainingDataFile);

                  System::err::print("Opening training data ... ");

                  FileInputStream *trainingDataIn;
                  try
                  {
                    trainingDataIn = new FileInputStream(trainingDataFile);
                  }
                  catch (FileNotFoundException e)
                  {
                    System::err::println("failed");
                    System::err::println("File not found: " + e->getMessage());
                    throw TerminateToolException(-1);
                  }

                  System::err::println("done");

                  return new ParseSampleStream(new PlainTextByLineStream(trainingDataIn->getChannel(), encoding));
                }

                opennlp::tools::dictionary::Dictionary *ParserTrainerTool::buildDictionary(ObjectStream<Parse*> *parseSamples, HeadRules *headRules, int cutoff)
                {
                  System::err::print("Building dictionary ...");

                  Dictionary *mdict;
                  try
                  {
                    mdict = Parser::buildDictionary(parseSamples, headRules, cutoff);
                  }
                  catch (IOException e)
                  {
                    System::err::println("Error while building dictionary: " + e->getMessage());
//JAVA TO C++ CONVERTER WARNING: Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
                    delete mdict;
                  }
                  System::err::println("done");

                  return mdict;
                }

                opennlp::tools::parser::ParserType ParserTrainerTool::parseParserType(const std::string &typeAsString)
                {
                  ParserType type = 0;
                  if (typeAsString != "" && typeAsString.length() > 0)
                  {
                    type = opennlp::tools::parser::ParserType_Renamed::parse(typeAsString);
                    if (type == 0)
                    {
                      System::err::println("ParserType training parameter is invalid!");
                      throw TerminateToolException(-1);
                    }
                  }

                  return type;
                }

                void ParserTrainerTool::run(std::string args[])
                {

                  if (!ArgumentParser::validateArguments(args, TrainerToolParams::typeid))
                  {
                    System::err::println(getHelp());
                    throw TerminateToolException(1);
                  }

                  TrainerToolParams *params = ArgumentParser::parse(args, TrainerToolParams::typeid);

                  opennlp::tools::util::TrainingParameters *mlParams = CmdLineUtil::loadTrainingParameters(params->getParams(), true);

                  if (mlParams != 0)
                  {
                    if (!TrainUtil::isValid(mlParams->getSettings("build")))
                    {
                      System::err::println("Build training parameters are invalid!");
                      throw TerminateToolException(-1);
                    }

                    if (!TrainUtil::isValid(mlParams->getSettings("check")))
                    {
                      System::err::println("Check training parameters are invalid!");
                      throw TerminateToolException(-1);
                    }

                    if (!TrainUtil::isValid(mlParams->getSettings("attach")))
                    {
                      System::err::println("Attach training parameters are invalid!");
                      throw TerminateToolException(-1);
                    }

                    if (!TrainUtil::isValid(mlParams->getSettings("tagger")))
                    {
                      System::err::println("Tagger training parameters are invalid!");
                      throw TerminateToolException(-1);
                    }

                    if (!TrainUtil::isValid(mlParams->getSettings("chunker")))
                    {
                      System::err::println("Chunker training parameters are invalid!");
                      throw TerminateToolException(-1);
                    }
                  }

                  ObjectStream<Parse*> *sampleStream = openTrainingData(params->getData(), params->getEncoding());

                  File *modelOutFile = params->getModel();
                  CmdLineUtil::checkOutputFile("parser model", modelOutFile);

                  ParserModel *model;
                  try
                  {

                    HeadRules *rules = new opennlp::tools::parser::lang::en::HeadRules(new InputStreamReader(new FileInputStream(params->getHeadRules()), params->getEncoding()));

                    ParserType type = parseParserType(params->getParserType());

                    if (mlParams == 0)
                    {
                      if (opennlp::tools::parser::ParserType_Renamed::CHUNKING::equals(type))
                      {
                        model = Parser::train(params->getLang(), sampleStream, rules, params->getIterations(), params->getCutoff());
                      }
                      else if (opennlp::tools::parser::ParserType_Renamed::TREEINSERT::equals(type))
                      {
                        model = opennlp::tools::parser::treeinsert::Parser::train(params->getLang(), sampleStream, rules, params->getIterations(), params->getCutoff());
                      }
                      else
                      {
                        throw IllegalStateException();
                      }
                    }
                    else
                    {
                      if (opennlp::tools::parser::ParserType_Renamed::CHUNKING::equals(type))
                      {
                        model = Parser::train(params->getLang(), sampleStream, rules, mlParams);
                      }
                      else if (opennlp::tools::parser::ParserType_Renamed::TREEINSERT::equals(type))
                      {
                        model = opennlp::tools::parser::treeinsert::Parser::train(params->getLang(), sampleStream, rules, mlParams);
                      }
                      else
                      {
                        throw IllegalStateException();
                      }

                    }
                  }
                  catch (IOException e)
                  {
                    CmdLineUtil::printTrainingIoError(e);
                    throw TerminateToolException(-1);
                  }
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
                  finally
                  {
                    try
                    {
                      sampleStream->close();
                    }
                    catch (IOException e)
                    {
                      // sorry that this can fail
                    }
                  }

                  CmdLineUtil::writeModel("parser", modelOutFile, model);
                }
            }
        }
    }
}
