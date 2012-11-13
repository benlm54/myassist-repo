#include "ChunkerCrossValidatorTool.h"
#include "tools/cmdline/ArgumentParser.h"
#include "tools/cmdline/CLI.h"
#include "tools/cmdline/TerminateToolException.h"
#include "tools/cmdline/CmdLineUtil.h"
#include "tools/util/TrainingParameters.h"
#include "tools/chunker/ChunkSample.h"
#include "tools/cmdline/chunker/ChunkerTrainerTool.h"
#include "tools/util/ObjectStream.h"
#include "tools/util/eval/EvaluationMonitor.h"
#include "tools/cmdline/chunker/ChunkerDetailedFMeasureListener.h"
#include "tools/cmdline/chunker/ChunkEvaluationErrorListener.h"
#include "tools/chunker/ChunkerCrossValidator.h"
#include "tools/chunker/ChunkerEvaluationMonitor.h"
#include "tools/util/eval/FMeasure.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace chunker
            {
                using opennlp::tools::chunker::ChunkSample;
                using opennlp::tools::chunker::ChunkerCrossValidator;
                using opennlp::tools::chunker::ChunkerEvaluationMonitor;
                using opennlp::tools::cmdline::ArgumentParser;
                using opennlp::tools::cmdline::CLI;
                using opennlp::tools::cmdline::CmdLineTool;
                using opennlp::tools::cmdline::CmdLineUtil;
                using opennlp::tools::cmdline::TerminateToolException;
                using opennlp::tools::cmdline::params::CVParams;
                using opennlp::tools::cmdline::params::DetailedFMeasureEvaluatorParams;
                using opennlp::tools::util::ObjectStream;
                using opennlp::tools::util::TrainingParameters;
                using opennlp::tools::util::eval::EvaluationMonitor;
                using opennlp::tools::util::eval::FMeasure;

                std::string ChunkerCrossValidatorTool::getName()
                {
                  return "ChunkerCrossValidator";
                }

                std::string ChunkerCrossValidatorTool::getShortDescription()
                {
                  return "K-fold cross validator for the chunker";
                }

                std::string ChunkerCrossValidatorTool::getHelp()
                {
                  return "Usage: " + CLI::CMD + " " + getName() + " " + ArgumentParser::createUsage(CVToolParams::typeid);
                }

                void ChunkerCrossValidatorTool::run(std::string args[])
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

                  ObjectStream<ChunkSample*> *sampleStream = ChunkerTrainerTool::openSampleData("Training Data", trainingDataInFile, params->getEncoding());

                  std::vector<EvaluationMonitor<ChunkSample*>*> listeners = std::list<EvaluationMonitor<ChunkSample*>*>();
                  ChunkerDetailedFMeasureListener *detailedFMeasureListener = 0;
                  if (params->getMisclassified())
                  {
                    listeners.push_back(new ChunkEvaluationErrorListener());
                  }
                  if (params->getDetailedF())
                  {
                    detailedFMeasureListener = new ChunkerDetailedFMeasureListener();
                    listeners.push_back(detailedFMeasureListener);
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

                  ChunkerCrossValidator *validator = new ChunkerCrossValidator(params->getLang(), mlParams, listeners.toArray(new ChunkerEvaluationMonitor[listeners.size()]));

                  try
                  {
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

                  if (detailedFMeasureListener == 0)
                  {
                    FMeasure *result = validator->getFMeasure();
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                    std::cout << result->toString() << std::endl;
                  }
                  else
                  {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                    std::cout << detailedFMeasureListener->toString() << std::endl;
                  }
                }
            }
        }
    }
}
