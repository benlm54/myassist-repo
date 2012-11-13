#include "ChunkerEvaluatorTool.h"
#include "tools/cmdline/ArgumentParser.h"
#include "tools/cmdline/CLI.h"
#include "tools/cmdline/TerminateToolException.h"
#include "tools/cmdline/CmdLineUtil.h"
#include "tools/chunker/ChunkerModel.h"
#include "tools/cmdline/chunker/ChunkerModelLoader.h"
#include "tools/util/eval/EvaluationMonitor.h"
#include "tools/cmdline/chunker/ChunkerDetailedFMeasureListener.h"
#include "tools/cmdline/chunker/ChunkEvaluationErrorListener.h"
#include "tools/chunker/ChunkerEvaluationMonitor.h"
#include "tools/chunker/ChunkerEvaluator.h"
#include "tools/chunker/ChunkerME.h"
#include "tools/chunker/DefaultChunkerSequenceValidator.h"
#include "tools/cmdline/chunker/ChunkerTrainerTool.h"
#include "tools/cmdline/PerformanceMonitor.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace chunker
            {
                using opennlp::tools::chunker::ChunkSample;
                using opennlp::tools::chunker::ChunkerEvaluationMonitor;
                using opennlp::tools::chunker::ChunkerEvaluator;
                using opennlp::tools::chunker::ChunkerME;
                using opennlp::tools::chunker::ChunkerModel;
                using opennlp::tools::chunker::DefaultChunkerSequenceValidator;
                using opennlp::tools::cmdline::ArgumentParser;
                using opennlp::tools::cmdline::CLI;
                using opennlp::tools::cmdline::CmdLineTool;
                using opennlp::tools::cmdline::CmdLineUtil;
                using opennlp::tools::cmdline::PerformanceMonitor;
                using opennlp::tools::cmdline::TerminateToolException;
                using opennlp::tools::cmdline::params::DetailedFMeasureEvaluatorParams;
                using opennlp::tools::cmdline::params::EvaluatorParams;
                using opennlp::tools::util::ObjectStream;
                using opennlp::tools::util::eval::EvaluationMonitor;

                std::string ChunkerEvaluatorTool::getName()
                {
                  return "ChunkerEvaluator";
                }

                std::string ChunkerEvaluatorTool::getShortDescription()
                {
                  return "Measures the performance of the Chunker model with the reference data";
                }

                std::string ChunkerEvaluatorTool::getHelp()
                {
                  return "Usage: " + CLI::CMD + " " + getName() + " " + ArgumentParser::createUsage(EvalToolParams::typeid);
                }

                void ChunkerEvaluatorTool::run(std::string args[])
                {

                    if (!ArgumentParser::validateArguments(args, EvaluatorParams::typeid))
                    {
                    System::err::println(getHelp());
                    throw TerminateToolException(1);
                    }

                    EvalToolParams *params = ArgumentParser::parse(args, EvalToolParams::typeid);

                    File *testData = params->getData();

                  CmdLineUtil::checkInputFile("Test data", testData);

                  Charset *encoding = params->getEncoding();

                  ChunkerModel *model = (new ChunkerModelLoader())->load(params->getModel());

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

                  ChunkerEvaluator *evaluator = new ChunkerEvaluator(new ChunkerME(model, ChunkerME::DEFAULT_BEAM_SIZE, new DefaultChunkerSequenceValidator()), listeners.toArray(new ChunkerEvaluationMonitor[listeners.size()]));

                  ObjectStream<ChunkSample*> * const sampleStream = ChunkerTrainerTool::openSampleData("Test", testData, encoding);

                  PerformanceMonitor * const monitor = new PerformanceMonitor("sent");

                  ObjectStream<ChunkSample*> *measuredSampleStream = new ObjectStreamAnonymousInnerClassHelper();

                  monitor->startAndPrintThroughput();

                  try
                  {
                    evaluator->evaluate(measuredSampleStream);
                  }
                  catch (IOException e)
                  {
                    System::err::println("failed");
                    System::err::println("Reading test data error " + e->getMessage());
                    throw TerminateToolException(-1);
                  }
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
                  finally
                  {
                    try
                    {
                      measuredSampleStream->close();
                    }
                    catch (IOException e)
                    {
                      // sorry that this can fail
                    }
                  }

                  monitor->stopAndPrintFinalResult();

                  std::cout << std::endl;

                  if (detailedFMeasureListener == 0)
                  {
                    std::cout << evaluator->getFMeasure() << std::endl;
                  }
                  else
                  {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                    std::cout << detailedFMeasureListener->toString() << std::endl;
                  }
                }

                opennlp::tools::chunker::ChunkSample *ChunkerEvaluatorTool::ObjectStreamAnonymousInnerClassHelper::read() throw(IOException)
                {
                  monitor::incrementCounter();
                  return sampleStream::read();
                }

                void ChunkerEvaluatorTool::ObjectStreamAnonymousInnerClassHelper::reset() throw(IOException)
                {
                  sampleStream::reset();
                }

                void ChunkerEvaluatorTool::ObjectStreamAnonymousInnerClassHelper::close() throw(IOException)
                {
                  sampleStream->close();
                }
            }
        }
    }
}
