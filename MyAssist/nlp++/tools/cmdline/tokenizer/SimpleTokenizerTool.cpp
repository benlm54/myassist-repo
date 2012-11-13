#include "SimpleTokenizerTool.h"
#include "tools/cmdline/CLI.h"
#include "tools/cmdline/TerminateToolException.h"
#include "tools/cmdline/tokenizer/CommandLineTokenizer.h"
#include "tools/tokenize/SimpleTokenizer.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace tokenizer
            {
                using opennlp::tools::cmdline::CLI;
                using opennlp::tools::cmdline::CmdLineTool;
                using opennlp::tools::cmdline::TerminateToolException;

                std::string SimpleTokenizerTool::getName()
                {
                  return "SimpleTokenizer";
                }

                std::string SimpleTokenizerTool::getShortDescription()
                {
                  return "character class tokenizer";
                }

                std::string SimpleTokenizerTool::getHelp()
                {
                  return "Usage: " + CLI::CMD + " " + getName() + " < sentences";
                }

                void SimpleTokenizerTool::run(std::string args[])
                {
                  if (sizeof(args) / sizeof(args[0]) != 0)
                  {
                    std::cout << getHelp() << std::endl;
                    throw TerminateToolException(1);
                  }

                  CommandLineTokenizer *tokenizer = new CommandLineTokenizer(opennlp::tools::tokenize::SimpleTokenizer::INSTANCE);

                  tokenizer->process();
                }
            }
        }
    }
}
