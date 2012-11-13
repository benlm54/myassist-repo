#include "SentenceDetectorCrossValidatorTool.h"
#include "tools/cmdline/ArgumentParser.h"
#include "tools/cmdline/CLI.h"
#include "tools/cmdline/TerminateToolException.h"
#include "tools/cmdline/CmdLineUtil.h"
#include "tools/util/TrainingParameters.h"
#include "tools/cmdline/sentdetect/SentenceDetectorTrainerTool.h"
#include "tools/sentdetect/SentenceSample.h"
#include "tools/util/ObjectStream.h"
#include "tools/sentdetect/SDCrossValidator.h"
#include "tools/sentdetect/SentenceDetectorEvaluationMonitor.h"
#include "tools/cmdline/sentdetect/SentenceEvaluationErrorListener.h"
#include "tools/dictionary/Dictionary.h"
#include "tools/util/eval/FMeasure.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace sentdetect
            {
                using opennlp::tools::cmdline::ArgumentParser;
                using opennlp::tools::cmdline::CLI;
                using opennlp::tools::cmdline::CmdLineTool;
                using opennlp::tools::cmdline::CmdLineUtil;
                using opennlp::tools::cmdline::TerminateToolException;
                using opennlp::tools::cmdline::params::CVParams;
                using opennlp::tools::dictionary::Dictionary;
                using opennlp::tools::sentdetect::SDCrossValidator;
                using opennlp::tools::sentdetect::SentenceDetectorEvaluationMonitor;
                using opennlp::tools::sentdetect::SentenceSample;
                using opennlp::tools::util::ObjectStream;
                using opennlp::tools::util::TrainingParameters;
                using opennlp::tools::util::eval::FMeasure;

                std::string SentenceDetectorCrossValidatorTool::getName()
                {
                  return "SentenceDetectorCrossValidator";
                }

                std::string SentenceDetectorCrossValidatorTool::getShortDescription()
                {
                  return "K-fold cross validator for the learnable sentence detector";
                }

                std::string SentenceDetectorCrossValidatorTool::getHelp()
                {
                  return "Usage: " + CLI::CMD + " " + getName() + " " + ArgumentParser::createUsage(CVToolParams::typeid);
                }

                void SentenceDetectorCrossValidatorTool::run(std::string args[])
                {

                  if (!ArgumentParser::validateArguments(args, CVToolParams::typeid))
                  {
                    System::err::println(getHelp());
                    throw TerminateToolException(1);
                  }

                  CVToolParams *params = ArgumentParser::parse(args, CVToolParams::typeid);

                  TrainingParameters *mlParams = CmdLineUtil::loadTrainingParameters(params->getParams(), false);

                  File *trainingDataInFile = params->getData();
                  CmdLineUtil::checkInputFile("Training Data", trainingDataInFile);

                  Charset *encoding = params->getEncoding();

                  ObjectStream<SentenceSample*> *sampleStream = SentenceDetectorTrainerTool::openSampleData("Training Data", trainingDataInFile, encoding);

                  SDCrossValidator *validator;

                  SentenceDetectorEvaluationMonitor *errorListener = 0;
                  if (params->getMisclassified())
                  {
                    errorListener = new SentenceEvaluationErrorListener();
                  }

                  if (mlParams == 0)
                  {
                    mlParams = new TrainingParameters();
                    mlParams->put(TrainingParameters::ALGORITHM_PARAM, "MAXENT");
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                    mlParams->put(TrainingParameters::ITERATIONS_PARAM, int::toString(params->getIterations()));
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                    mlParams->put(TrainingParameters::CUTOFF_PARAM, int::toString(params->getCutoff()));
                  }

                  try
                  {
                    Dictionary *abbreviations = SentenceDetectorTrainerTool::loadDict(params->getAbbDict());
                    validator = new SDCrossValidator(params->getLang(), mlParams, abbreviations, errorListener);

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
