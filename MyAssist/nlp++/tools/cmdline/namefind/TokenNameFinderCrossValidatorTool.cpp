#include "TokenNameFinderCrossValidatorTool.h"
#include "tools/cmdline/ArgumentParser.h"
#include "tools/cmdline/CLI.h"
#include "tools/cmdline/TerminateToolException.h"
#include "tools/cmdline/CmdLineUtil.h"
#include "tools/util/TrainingParameters.h"
#include "tools/cmdline/namefind/TokenNameFinderTrainerTool.h"
#include "tools/namefind/NameSample.h"
#include "tools/util/ObjectStream.h"
#include "tools/namefind/TokenNameFinderCrossValidator.h"
#include "tools/util/eval/EvaluationMonitor.h"
#include "tools/cmdline/namefind/NameEvaluationErrorListener.h"
#include "tools/cmdline/namefind/TokenNameFinderDetailedFMeasureListener.h"
#include "tools/namefind/TokenNameFinderEvaluationMonitor.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace namefind
            {
                using opennlp::tools::cmdline::ArgumentParser;
                using opennlp::tools::cmdline::CLI;
                using opennlp::tools::cmdline::CmdLineTool;
                using opennlp::tools::cmdline::CmdLineUtil;
                using opennlp::tools::cmdline::TerminateToolException;
                using opennlp::tools::cmdline::params::CVParams;
                using opennlp::tools::cmdline::params::DetailedFMeasureEvaluatorParams;
                using opennlp::tools::namefind::NameSample;
                using opennlp::tools::namefind::TokenNameFinderCrossValidator;
                using opennlp::tools::namefind::TokenNameFinderEvaluationMonitor;
                using opennlp::tools::util::ObjectStream;
                using opennlp::tools::util::TrainingParameters;
                using opennlp::tools::util::eval::EvaluationMonitor;

                std::string TokenNameFinderCrossValidatorTool::getName()
                {
                  return "TokenNameFinderCrossValidator";
                }

                std::string TokenNameFinderCrossValidatorTool::getShortDescription()
                {
                  return "K-fold cross validator for the learnable Name Finder";
                }

                std::string TokenNameFinderCrossValidatorTool::getHelp()
                {
                  return "Usage: " + CLI::CMD + " " + getName() + " " + ArgumentParser::createUsage(CVToolParams::typeid);
                }

                void TokenNameFinderCrossValidatorTool::run(std::string args[])
                {
                  if (!ArgumentParser::validateArguments(args, CVToolParams::typeid))
                  {
                    System::err::println(getHelp());
                    throw TerminateToolException(1);
                  }

                  CVToolParams *params = ArgumentParser::parse(args, CVToolParams::typeid);

                  TrainingParameters *mlParams = CmdLineUtil::loadTrainingParameters(params->getParams(),false);

//ORIGINAL LINE: byte featureGeneratorBytes[] = TokenNameFinderTrainerTool.openFeatureGeneratorBytes(params.getFeaturegen());
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                  char *featureGeneratorBytes = TokenNameFinderTrainerTool::openFeatureGeneratorBytes(params->getFeaturegen());

                  Map<std::string, void*> *resources = TokenNameFinderTrainerTool::loadResources(params->getResources());

                  File *trainingDataInFile = params->getData();
                  CmdLineUtil::checkInputFile("Training Data", trainingDataInFile);

                  Charset *encoding = params->getEncoding();

                  ObjectStream<NameSample*> *sampleStream = TokenNameFinderTrainerTool::openSampleData("Training Data", trainingDataInFile, encoding);

                  TokenNameFinderCrossValidator *validator;

                  std::vector<EvaluationMonitor<NameSample*>*> listeners = std::list<EvaluationMonitor<NameSample*>*>();
                  if (params->getMisclassified())
                  {
                    listeners.push_back(new NameEvaluationErrorListener());
                  }
                  TokenNameFinderDetailedFMeasureListener *detailedFListener = 0;
                  if (params->getDetailedF())
                  {
                    detailedFListener = new TokenNameFinderDetailedFMeasureListener();
                    listeners.push_back(detailedFListener);
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
                    validator = new TokenNameFinderCrossValidator(params->getLang(), params->getType(), mlParams, featureGeneratorBytes, resources, listeners.toArray(new TokenNameFinderEvaluationMonitor[listeners.size()]));
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

                  if (detailedFListener == 0)
                  {
                    std::cout << validator->getFMeasure() << std::endl;
                  }
                  else
                  {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                    std::cout << detailedFListener->toString() << std::endl;
                  }
                }
            }
        }
    }
}
