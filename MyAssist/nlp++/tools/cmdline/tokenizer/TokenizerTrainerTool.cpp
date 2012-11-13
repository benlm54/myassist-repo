#include "TokenizerTrainerTool.h"
#include "tools/cmdline/ArgumentParser.h"
#include "tools/cmdline/CLI.h"
#include "tools/cmdline/CmdLineUtil.h"
#include "tools/util/PlainTextByLineStream.h"
#include "tools/tokenize/TokenSampleStream.h"
#include "tools/cmdline/TerminateToolException.h"
#include "model/TrainUtil.h"
#include "tools/tokenize/TokenizerModel.h"
#include "tools/tokenize/TokenizerME.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace tokenizer
            {
                using opennlp::model::TrainUtil;
                using opennlp::tools::cmdline::ArgumentParser;
                using opennlp::tools::cmdline::CLI;
                using opennlp::tools::cmdline::CmdLineTool;
                using opennlp::tools::cmdline::CmdLineUtil;
                using opennlp::tools::cmdline::TerminateToolException;
                using opennlp::tools::cmdline::params::TrainingToolParams;
                using opennlp::tools::dictionary::Dictionary;
                using opennlp::tools::tokenize::TokenSample;
                using opennlp::tools::tokenize::TokenSampleStream;
                using opennlp::tools::tokenize::TokenizerModel;
                using opennlp::tools::util::ObjectStream;
                using opennlp::tools::util::PlainTextByLineStream;
                using opennlp::tools::util::TrainingParameters;

                std::string TokenizerTrainerTool::getName()
                {
                  return "TokenizerTrainer";
                }

                std::string TokenizerTrainerTool::getShortDescription()
                {
                  return "trainer for the learnable tokenizer";
                }

                std::string TokenizerTrainerTool::getHelp()
                {
                  return "Usage: " + CLI::CMD + " " + getName() + " " + ArgumentParser::createUsage(TrainerToolParams::typeid);
                }

                opennlp::tools::util::ObjectStream<TokenSample*> *TokenizerTrainerTool::openSampleData(const std::string &sampleDataName, File *sampleDataFile, Charset *encoding)
                {
                  CmdLineUtil::checkInputFile(sampleDataName + " Data", sampleDataFile);

                  FileInputStream *sampleDataIn = CmdLineUtil::openInFile(sampleDataFile);

                  ObjectStream<std::string> *lineStream = new PlainTextByLineStream(sampleDataIn->getChannel(), encoding);

                  return new TokenSampleStream(lineStream);
                }

                opennlp::tools::dictionary::Dictionary *TokenizerTrainerTool::loadDict(File *f) throw(IOException)
                {
                  Dictionary *dict = 0;
                  if (f != 0)
                  {
                    CmdLineUtil::checkInputFile("abb dict", f);
                    dict = new Dictionary(new FileInputStream(f));
                  }
                  return dict;
                }

                void TokenizerTrainerTool::run(std::string args[])
                {
                  if (!ArgumentParser::validateArguments(args, TrainerToolParams::typeid))
                  {
                    System::err::println(getHelp());
                    throw TerminateToolException(1);
                  }

                  TrainerToolParams *params = ArgumentParser::parse(args, TrainerToolParams::typeid);

                  TrainingParameters *mlParams = CmdLineUtil::loadTrainingParameters(params->getParams(), false);

                  if (mlParams != 0)
                  {
                    if (!TrainUtil::isValid(mlParams->getSettings()))
                    {
                      System::err::println("Training parameters file is invalid!");
                      throw TerminateToolException(-1);
                    }

                    if (TrainUtil::isSequenceTraining(mlParams->getSettings()))
                    {
                      System::err::println("Sequence training is not supported!");
                      throw TerminateToolException(-1);
                    }
                  }

                  File *trainingDataInFile = params->getData();
                  File *modelOutFile = params->getModel();

                  CmdLineUtil::checkOutputFile("tokenizer model", modelOutFile);
                  ObjectStream<TokenSample*> *sampleStream = openSampleData("Training", trainingDataInFile, params->getEncoding());

                  if (mlParams == 0)
                    mlParams = createTrainingParameters(params->getIterations(), params->getCutoff());

                  TokenizerModel *model;
                  try
                  {
                    Dictionary *dict = loadDict(params->getAbbDict());
                    model = opennlp::tools::tokenize::TokenizerME::train(params->getLang(), sampleStream, dict, params->getAlphaNumOpt(), mlParams);
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

                  CmdLineUtil::writeModel("tokenizer", modelOutFile, model);
                }

                opennlp::tools::util::TrainingParameters *TokenizerTrainerTool::createTrainingParameters(int iterations, int cutoff)
                {
                  TrainingParameters *mlParams = new TrainingParameters();
                  mlParams->put(TrainingParameters::ALGORITHM_PARAM, "MAXENT");
                  mlParams->put(TrainingParameters::ITERATIONS_PARAM, StringConverterHelper::toString(iterations));
                  mlParams->put(TrainingParameters::CUTOFF_PARAM, StringConverterHelper::toString(cutoff));
                  return mlParams;
                }
            }
        }
    }
}
