#include "POSTaggerCrossValidatorTool.h"
#include "tools/cmdline/ArgumentParser.h"
#include "tools/cmdline/CLI.h"
#include "tools/cmdline/TerminateToolException.h"
#include "tools/cmdline/CmdLineUtil.h"
#include "tools/util/TrainingParameters.h"
#include "tools/cmdline/postag/POSTaggerTrainerTool.h"
#include "tools/postag/POSSample.h"
#include "tools/util/ObjectStream.h"
#include "tools/postag/POSTaggerCrossValidator.h"
#include "tools/postag/POSTaggerEvaluationMonitor.h"
#include "tools/cmdline/postag/POSEvaluationErrorListener.h"
#include "tools/postag/POSDictionary.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace postag
            {
                using opennlp::tools::cmdline::ArgumentParser;
                using opennlp::tools::cmdline::CLI;
                using opennlp::tools::cmdline::CmdLineTool;
                using opennlp::tools::cmdline::CmdLineUtil;
                using opennlp::tools::cmdline::TerminateToolException;
                using opennlp::tools::cmdline::params::CVParams;
                using opennlp::tools::postag::POSDictionary;
                using opennlp::tools::postag::POSSample;
                using opennlp::tools::postag::POSTaggerCrossValidator;
                using opennlp::tools::postag::POSTaggerEvaluationMonitor;
                using opennlp::tools::util::ObjectStream;
                using opennlp::tools::util::TrainingParameters;

                std::string POSTaggerCrossValidatorTool::getName()
                {
                  return "POSTaggerCrossValidator";
                }

                std::string POSTaggerCrossValidatorTool::getShortDescription()
                {
                  return "K-fold cross validator for the learnable POS tagger";
                }

                std::string POSTaggerCrossValidatorTool::getHelp()
                {
                  return "Usage: " + CLI::CMD + " " + getName() + " " + ArgumentParser::createUsage(CVToolParams::typeid);
                }

                void POSTaggerCrossValidatorTool::run(std::string args[])
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

                  ObjectStream<POSSample*> *sampleStream = POSTaggerTrainerTool::openSampleData("Training Data", trainingDataInFile, params->getEncoding());

                  POSTaggerCrossValidator *validator;

                  POSTaggerEvaluationMonitor *missclassifiedListener = 0;
                  if (params->getMisclassified())
                  {
                    missclassifiedListener = new POSEvaluationErrorListener();
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
                    // TODO: Move to util method ...
                    POSDictionary *tagdict = 0;
                    if (params->getDict() != 0)
                    {
                      tagdict = POSDictionary::create(new FileInputStream(params->getDict()));
                    }

                    validator = new POSTaggerCrossValidator(params->getLang(), mlParams, tagdict, params->getNgram(), missclassifiedListener);

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

                  std::cout << "done" << std::endl;

                  std::cout << std::endl;

                  std::cout << "Accuracy: " + validator->getWordAccuracy() << std::endl;
                }
            }
        }
    }
}
