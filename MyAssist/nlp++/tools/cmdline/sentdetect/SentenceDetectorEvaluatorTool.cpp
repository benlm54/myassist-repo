#include "SentenceDetectorEvaluatorTool.h"
#include "tools/cmdline/ArgumentParser.h"
#include "tools/cmdline/CLI.h"
#include "tools/cmdline/params/EvaluatorParams.h"
#include "tools/cmdline/TerminateToolException.h"
#include "tools/cmdline/sentdetect/SentenceModelLoader.h"
#include "tools/sentdetect/SentenceModel.h"
#include "tools/cmdline/CmdLineUtil.h"
#include "tools/sentdetect/SentenceDetectorEvaluationMonitor.h"
#include "tools/cmdline/sentdetect/SentenceEvaluationErrorListener.h"
#include "tools/sentdetect/SentenceDetectorEvaluator.h"
#include "tools/sentdetect/SentenceDetectorME.h"
#include "tools/cmdline/sentdetect/SentenceDetectorTrainerTool.h"
#include "tools/sentdetect/SentenceSample.h"
#include "tools/util/ObjectStream.h"

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
                using opennlp::tools::cmdline::params::EvaluatorParams;
                using opennlp::tools::sentdetect::SentenceDetectorEvaluationMonitor;
                using opennlp::tools::sentdetect::SentenceDetectorEvaluator;
                using opennlp::tools::sentdetect::SentenceDetectorME;
                using opennlp::tools::sentdetect::SentenceModel;
                using opennlp::tools::sentdetect::SentenceSample;
                using opennlp::tools::util::ObjectStream;

                std::string SentenceDetectorEvaluatorTool::getName()
                {
                  return "SentenceDetectorEvaluator";
                }

                std::string SentenceDetectorEvaluatorTool::getShortDescription()
                {
                  return "evaluator for the learnable sentence detector";
                }

                std::string SentenceDetectorEvaluatorTool::getHelp()
                {
                  return "Usage: " + CLI::CMD + " " + getName() + " " + ArgumentParser::createUsage(EvaluatorParams::typeid);
                }

                void SentenceDetectorEvaluatorTool::run(std::string args[])
                {

                  if (!ArgumentParser::validateArguments(args, EvaluatorParams::typeid))
                  {
                    System::err::println(getHelp());
                    throw TerminateToolException(1);
                  }

                  EvaluatorParams *params = ArgumentParser::parse(args, EvaluatorParams::typeid);

                  Charset *encoding = params->getEncoding();

                  SentenceModel *model = (new SentenceModelLoader())->load(params->getModel());

                  File *trainingDataInFile = params->getData();
                  CmdLineUtil::checkInputFile("Training Data", trainingDataInFile);

                  SentenceDetectorEvaluationMonitor *errorListener = 0;
                  if (params->getMisclassified())
                  {
                    errorListener = new SentenceEvaluationErrorListener();
                  }

                  SentenceDetectorEvaluator *evaluator = new SentenceDetectorEvaluator(new SentenceDetectorME(model), errorListener);

                  std::cout << "Evaluating ... ";
                    ObjectStream<SentenceSample*> *sampleStream = SentenceDetectorTrainerTool::openSampleData("Test", trainingDataInFile, encoding);

                    try
                    {
                    evaluator->evaluate(sampleStream);
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

                    System::err::println("done");

                    std::cout << std::endl;

                    std::cout << evaluator->getFMeasure() << std::endl;
                }
            }
        }
    }
}
