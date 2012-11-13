#include "TaggerModelReplacerTool.h"
#include "tools/cmdline/CLI.h"
#include "tools/cmdline/TerminateToolException.h"
#include "tools/cmdline/parser/ParserModelLoader.h"
#include "tools/parser/ParserModel.h"
#include "tools/cmdline/postag/POSModelLoader.h"
#include "tools/postag/POSModel.h"
#include "tools/cmdline/CmdLineUtil.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace parser
            {
                using opennlp::tools::cmdline::CLI;
                using opennlp::tools::cmdline::CmdLineTool;
                using opennlp::tools::cmdline::CmdLineUtil;
                using opennlp::tools::cmdline::TerminateToolException;
                using opennlp::tools::cmdline::postag::POSModelLoader;
                using opennlp::tools::parser::ParserModel;
                using opennlp::tools::postag::POSModel;

                std::string TaggerModelReplacerTool::getName()
                {
                  return "TaggerModelReplacer";
                }

                std::string TaggerModelReplacerTool::getShortDescription()
                {
                  return "replaces the tagger model in a parser model";
                }

                std::string TaggerModelReplacerTool::getHelp()
                {
                  return "Usage: " + CLI::CMD + " " + getName() + " parser.model tagger.model";
                }

                void TaggerModelReplacerTool::run(std::string args[])
                {

                  if (sizeof(args) / sizeof(args[0]) != 2)
                  {
                    std::cout << getHelp() << std::endl;
                    throw TerminateToolException(1);
                  }

                  File *parserModelInFile = new File(args[0]);
                  ParserModel *parserModel = (new ParserModelLoader())->load(parserModelInFile);

                  File *taggerModelInFile = new File(args[1]);
                  POSModel *taggerModel = (new POSModelLoader())->load(taggerModelInFile);

                  ParserModel *updatedParserModel = parserModel->updateTaggerModel(taggerModel);

                  CmdLineUtil::writeModel("parser", parserModelInFile, updatedParserModel);
                }
            }
        }
    }
}
