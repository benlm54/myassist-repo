#include "TokenizerMETool.h"
#include "tools/cmdline/CLI.h"
#include "tools/cmdline/TerminateToolException.h"
#include "tools/cmdline/tokenizer/TokenizerModelLoader.h"
#include "tools/tokenize/TokenizerModel.h"
#include "tools/cmdline/tokenizer/CommandLineTokenizer.h"
#include "tools/tokenize/TokenizerME.h"

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
                using opennlp::tools::tokenize::TokenizerModel;

                std::string TokenizerMETool::getName()
                {
                  return "TokenizerME";
                }

                std::string TokenizerMETool::getShortDescription()
                {
                  return "learnable tokenizer";
                }

                std::string TokenizerMETool::getHelp()
                {
                  return "Usage: " + CLI::CMD + " " + getName() + " model < sentences";
                }

                void TokenizerMETool::run(std::string args[])
                {
                  if (sizeof(args) / sizeof(args[0]) != 1)
                  {
                    std::cout << getHelp() << std::endl;
                    throw TerminateToolException(1);
                  }

                  TokenizerModel *model = (new TokenizerModelLoader())->load(new File(args[0]));

                  CommandLineTokenizer *tokenizer = new CommandLineTokenizer(new opennlp::tools::tokenize::TokenizerME(model));

                  tokenizer->process();
                }
            }
        }
    }
}
