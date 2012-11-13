#include "POSTaggerEvaluatorTool.h"
#include "tools/cmdline/ArgumentParser.h"
#include "tools/cmdline/CLI.h"
#include "tools/cmdline/params/EvaluatorParams.h"
#include "tools/cmdline/TerminateToolException.h"
#include "tools/cmdline/CmdLineUtil.h"
#include "tools/cmdline/postag/POSModelLoader.h"
#include "tools/postag/POSModel.h"
#include "tools/postag/POSTaggerEvaluationMonitor.h"
#include "tools/cmdline/postag/POSEvaluationErrorListener.h"
#include "tools/postag/POSEvaluator.h"
#include "tools/postag/POSTaggerME.h"
#include "tools/cmdline/postag/POSTaggerTrainerTool.h"
#include "tools/postag/POSSample.h"
#include "tools/util/ObjectStream.h"

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
                using opennlp::tools::cmdline::params::EvaluatorParams;
                using opennlp::tools::postag::POSEvaluator;
                using opennlp::tools::postag::POSModel;
                using opennlp::tools::postag::POSSample;
                using opennlp::tools::postag::POSTaggerEvaluationMonitor;
                using opennlp::tools::util::ObjectStream;

                std::string POSTaggerEvaluatorTool::getName()
                {
                  return "POSTaggerEvaluator";
                }

                std::string POSTaggerEvaluatorTool::getShortDescription()
                {
                  return "";
                }

                std::string POSTaggerEvaluatorTool::getHelp()
                {
                  return "Usage: " + CLI::CMD + " " + getName() + " " + ArgumentParser::createUsage(EvaluatorParams::typeid);
                }

                void POSTaggerEvaluatorTool::run(std::string args[])
                {
                  if (!ArgumentParser::validateArguments(args, EvaluatorParams::typeid))
                  {
                    System::err::println(getHelp());
                    throw TerminateToolException(1);
                  }

                  EvaluatorParams *params = ArgumentParser::parse(args, EvaluatorParams::typeid);

                  File *testData = params->getData();
                  CmdLineUtil::checkInputFile("Test data", testData);

                  Charset *encoding = params->getEncoding();

                  POSModel *model = (new POSModelLoader())->load(params->getModel());

                  POSTaggerEvaluationMonitor *missclassifiedListener = 0;
                  if (params->getMisclassified())
                  {
                    missclassifiedListener = new POSEvaluationErrorListener();
                  }

                  POSEvaluator *evaluator = new POSEvaluator(new opennlp::tools::postag::POSTaggerME(model), missclassifiedListener);

                    std::cout << "Evaluating ... ";

                    ObjectStream<POSSample*> *sampleStream = POSTaggerTrainerTool::openSampleData("Test", testData, encoding);

                    try
                    {
                      evaluator->evaluate(sampleStream);
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
                        sampleStream->close();
                      }
                      catch (IOException e)
                      {
                        // sorry that this can fail
                      }
                    }

                    std::cout << "done" << std::endl;

                    std::cout << std::endl;

                    std::cout << "Accuracy: " + evaluator->getWordAccuracy() << std::endl;
                }
            }
        }
    }
}
