#include "TokenizerCrossValidatorTool.h"
#include "tools/cmdline/ArgumentParser.h"
#include "tools/cmdline/CLI.h"
#include "tools/cmdline/TerminateToolException.h"
#include "tools/cmdline/CmdLineUtil.h"
#include "tools/util/TrainingParameters.h"
#include "tools/cmdline/tokenizer/TokenizerTrainerTool.h"
#include "tools/tokenize/TokenSample.h"
#include "tools/util/ObjectStream.h"
#include "tools/tokenize/TokenizerCrossValidator.h"
#include "tools/tokenize/TokenizerEvaluationMonitor.h"
#include "tools/cmdline/tokenizer/TokenEvaluationErrorListener.h"
#include "tools/dictionary/Dictionary.h"
#include "tools/util/eval/FMeasure.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace tokenizer
            {
                using opennlp::tools::cmdline::ArgumentParser;
                using opennlp::tools::cmdline::CLI;
                using opennlp::tools::cmdline::CmdLineTool;
                using opennlp::tools::cmdline::CmdLineUtil;
                using opennlp::tools::cmdline::TerminateToolException;
                using opennlp::tools::cmdline::params::CVParams;
                using opennlp::tools::dictionary::Dictionary;
                using opennlp::tools::tokenize::TokenSample;
                using opennlp::tools::tokenize::TokenizerCrossValidator;
                using opennlp::tools::tokenize::TokenizerEvaluationMonitor;
                using opennlp::tools::util::ObjectStream;
                using opennlp::tools::util::eval::FMeasure;

                std::string TokenizerCrossValidatorTool::getName()
                {
                  return "TokenizerCrossValidator";
                }

                std::string TokenizerCrossValidatorTool::getShortDescription()
                {
                  return "K-fold cross validator for the learnable tokenizer";
                }

                std::string TokenizerCrossValidatorTool::getHelp()
                {
                  return "Usage: " + CLI::CMD + " " + getName() + " " + ArgumentParser::createUsage(CVToolParams::typeid);
                }

                void TokenizerCrossValidatorTool::run(std::string args[])
                {
                  if (!ArgumentParser::validateArguments(args, CVToolParams::typeid))
                  {
                    System::err::println(getHelp());
                    throw TerminateToolException(1);
                  }

                  CVToolParams *params = ArgumentParser::parse(args, CVToolParams::typeid);

                  opennlp::tools::util::TrainingParameters *mlParams = CmdLineUtil::loadTrainingParameters(params->getParams(), false);

                  File *trainingDataInFile = params->getData();
                  CmdLineUtil::checkInputFile("Training Data", trainingDataInFile);

                  Charset *encoding = params->getEncoding();

                  ObjectStream<TokenSample*> *sampleStream = TokenizerTrainerTool::openSampleData("Training Data", trainingDataInFile, encoding);


                  TokenizerCrossValidator *validator;

                  if (mlParams == 0)
                    mlParams = TokenizerTrainerTool::createTrainingParameters(params->getIterations(), params->getCutoff());

                  TokenizerEvaluationMonitor *listener = 0;
                  if (params->getMisclassified())
                  {
                    listener = new TokenEvaluationErrorListener();
                  }

                  try
                  {
                    Dictionary *dict = TokenizerTrainerTool::loadDict(params->getAbbDict());

                    validator = new TokenizerCrossValidator(params->getLang(), dict, params->getAlphaNumOpt(), mlParams, listener);

                    validator->evaluate(sampleStream, params->getFolds());
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

                  FMeasure *result = validator->getFMeasure();

//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                  std::cout << result->toString() << std::endl;
                }
            }
        }
    }
}
