#include "TokenizerMEEvaluatorTool.h"
#include "tools/cmdline/ArgumentParser.h"
#include "tools/cmdline/CLI.h"
#include "tools/cmdline/params/EvaluatorParams.h"
#include "tools/cmdline/TerminateToolException.h"
#include "tools/cmdline/tokenizer/TokenizerModelLoader.h"
#include "tools/tokenize/TokenizerModel.h"
#include "tools/tokenize/TokenizerEvaluationMonitor.h"
#include "tools/cmdline/tokenizer/TokenEvaluationErrorListener.h"
#include "tools/tokenize/TokenizerEvaluator.h"
#include "tools/tokenize/TokenizerME.h"
#include "tools/cmdline/CmdLineUtil.h"
#include "tools/cmdline/tokenizer/TokenizerTrainerTool.h"
#include "tools/tokenize/TokenSample.h"
#include "tools/util/ObjectStream.h"

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
                using opennlp::tools::cmdline::params::EvaluatorParams;
                using opennlp::tools::tokenize::TokenSample;
                using opennlp::tools::tokenize::TokenizerEvaluationMonitor;
                using opennlp::tools::tokenize::TokenizerEvaluator;
                using opennlp::tools::tokenize::TokenizerModel;
                using opennlp::tools::util::ObjectStream;

                std::string TokenizerMEEvaluatorTool::getName()
                {
                  return "TokenizerMEEvaluator";
                }

                std::string TokenizerMEEvaluatorTool::getShortDescription()
                {
                  return "evaluator for the learnable tokenizer";
                }

                std::string TokenizerMEEvaluatorTool::getHelp()
                {
                  return "Usage: " + CLI::CMD + " " + getName() + " " + ArgumentParser::createUsage(EvaluatorParams::typeid);
                }

                void TokenizerMEEvaluatorTool::run(std::string args[])
                {
                  if (!ArgumentParser::validateArguments(args, EvaluatorParams::typeid))
                  {
                    System::err::println(getHelp());
                    throw TerminateToolException(1);
                  }

                  EvaluatorParams *params = ArgumentParser::parse(args, EvaluatorParams::typeid);

                  Charset *encoding = params->getEncoding();

                  TokenizerModel *model = (new TokenizerModelLoader())->load(params->getModel());

                  TokenizerEvaluationMonitor *missclassifiedListener = 0;
                  if (params->getMisclassified())
                  {
                    missclassifiedListener = new TokenEvaluationErrorListener();
                  }

                  TokenizerEvaluator *evaluator = new TokenizerEvaluator(new opennlp::tools::tokenize::TokenizerME(model), missclassifiedListener);

                  std::cout << "Evaluating ... ";

                  File *testData = params->getData();
                  CmdLineUtil::checkInputFile("Test data", testData);

                  ObjectStream<TokenSample*> *sampleStream = TokenizerTrainerTool::openSampleData("Test", testData, encoding);

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

                  std::cout << evaluator->getFMeasure() << std::endl;
                }
            }
        }
    }
}
