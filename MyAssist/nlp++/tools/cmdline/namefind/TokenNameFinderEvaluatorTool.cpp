#include "TokenNameFinderEvaluatorTool.h"
#include "tools/cmdline/ArgumentParser.h"
#include "tools/cmdline/CLI.h"
#include "tools/cmdline/TerminateToolException.h"
#include "tools/cmdline/CmdLineUtil.h"
#include "tools/cmdline/namefind/TokenNameFinderModelLoader.h"
#include "tools/namefind/TokenNameFinderModel.h"
#include "tools/util/eval/EvaluationMonitor.h"
#include "tools/cmdline/namefind/NameEvaluationErrorListener.h"
#include "tools/cmdline/namefind/TokenNameFinderDetailedFMeasureListener.h"
#include "tools/namefind/NameFinderME.h"
#include "tools/namefind/TokenNameFinderEvaluationMonitor.h"
#include "tools/namefind/TokenNameFinderEvaluator.h"
#include "tools/cmdline/namefind/TokenNameFinderTrainerTool.h"
#include "tools/cmdline/PerformanceMonitor.h"

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
                using opennlp::tools::cmdline::PerformanceMonitor;
                using opennlp::tools::cmdline::TerminateToolException;
                using opennlp::tools::cmdline::params::DetailedFMeasureEvaluatorParams;
                using opennlp::tools::cmdline::params::EvaluatorParams;
                using opennlp::tools::namefind::NameFinderME;
                using opennlp::tools::namefind::NameSample;
                using opennlp::tools::namefind::TokenNameFinderEvaluationMonitor;
                using opennlp::tools::namefind::TokenNameFinderEvaluator;
                using opennlp::tools::namefind::TokenNameFinderModel;
                using opennlp::tools::util::ObjectStream;
                using opennlp::tools::util::eval::EvaluationMonitor;

                std::string TokenNameFinderEvaluatorTool::getName()
                {
                  return "TokenNameFinderEvaluator";
                }

                std::string TokenNameFinderEvaluatorTool::getShortDescription()
                {
                  return "";
                }

                std::string TokenNameFinderEvaluatorTool::getHelp()
                {
                  return "Usage: " + CLI::CMD + " " + getName() + " " + ArgumentParser::createUsage(EvalToolParams::typeid);
                }

                void TokenNameFinderEvaluatorTool::run(std::string args[])
                {

                  if (!ArgumentParser::validateArguments(args, EvalToolParams::typeid))
                  {
                    System::err::println(getHelp());
                    throw TerminateToolException(1);
                  }

                  EvalToolParams *params = ArgumentParser::parse(args, EvalToolParams::typeid);

                  File *testData = params->getData();
                  CmdLineUtil::checkInputFile("Test data", testData);

                  Charset *encoding = params->getEncoding();

                  TokenNameFinderModel *model = (new TokenNameFinderModelLoader())->load(params->getModel());

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

                  TokenNameFinderEvaluator *evaluator = new TokenNameFinderEvaluator(new NameFinderME(model), listeners.toArray(new TokenNameFinderEvaluationMonitor[listeners.size()]));

                  ObjectStream<NameSample*> * const sampleStream = TokenNameFinderTrainerTool::openSampleData("Test", testData, encoding);

                  PerformanceMonitor * const monitor = new PerformanceMonitor("sent");

                  ObjectStream<NameSample*> *measuredSampleStream = new ObjectStreamAnonymousInnerClassHelper();

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

                  if (detailedFListener == 0)
                  {
                    std::cout << evaluator->getFMeasure() << std::endl;
                  }
                  else
                  {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                    std::cout << detailedFListener->toString() << std::endl;
                  }
                }

                opennlp::tools::namefind::NameSample *TokenNameFinderEvaluatorTool::ObjectStreamAnonymousInnerClassHelper::read() throw(IOException)
                {
                  monitor::incrementCounter();
                  return sampleStream::read();
                }

                void TokenNameFinderEvaluatorTool::ObjectStreamAnonymousInnerClassHelper::reset() throw(IOException)
                {
                  sampleStream::reset();
                }

                void TokenNameFinderEvaluatorTool::ObjectStreamAnonymousInnerClassHelper::close() throw(IOException)
                {
                  sampleStream->close();
                }
            }
        }
    }
}
