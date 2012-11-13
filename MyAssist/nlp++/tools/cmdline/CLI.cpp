#include "CLI.h"
#include "tools/cmdline/doccat/DoccatTool.h"
#include "tools/cmdline/doccat/DoccatTrainerTool.h"
#include "tools/cmdline/doccat/DoccatConverterTool.h"
#include "tools/cmdline/dictionary/DictionaryBuilderTool.h"
#include "tools/cmdline/tokenizer/SimpleTokenizerTool.h"
#include "tools/cmdline/tokenizer/TokenizerMETool.h"
#include "tools/cmdline/tokenizer/TokenizerTrainerTool.h"
#include "tools/cmdline/tokenizer/TokenizerMEEvaluatorTool.h"
#include "tools/cmdline/tokenizer/TokenizerCrossValidatorTool.h"
#include "tools/cmdline/tokenizer/TokenizerConverterTool.h"
#include "tools/cmdline/tokenizer/DictionaryDetokenizerTool.h"
#include "tools/cmdline/sentdetect/SentenceDetectorTool.h"
#include "tools/cmdline/sentdetect/SentenceDetectorTrainerTool.h"
#include "tools/cmdline/sentdetect/SentenceDetectorEvaluatorTool.h"
#include "tools/cmdline/sentdetect/SentenceDetectorCrossValidatorTool.h"
#include "tools/cmdline/sentdetect/SentenceDetectorConverterTool.h"
#include "tools/cmdline/namefind/TokenNameFinderTool.h"
#include "tools/cmdline/namefind/TokenNameFinderTrainerTool.h"
#include "tools/cmdline/namefind/TokenNameFinderEvaluatorTool.h"
#include "tools/cmdline/namefind/TokenNameFinderCrossValidatorTool.h"
#include "tools/cmdline/namefind/TokenNameFinderConverterTool.h"
#include "tools/cmdline/namefind/CensusDictionaryCreatorTool.h"
#include "tools/cmdline/postag/POSTaggerTool.h"
#include "tools/cmdline/postag/POSTaggerTrainerTool.h"
#include "tools/cmdline/postag/POSTaggerEvaluatorTool.h"
#include "tools/cmdline/postag/POSTaggerCrossValidatorTool.h"
#include "tools/cmdline/postag/POSTaggerConverter.h"
#include "tools/cmdline/chunker/ChunkerMETool.h"
#include "tools/cmdline/chunker/ChunkerTrainerTool.h"
#include "tools/cmdline/chunker/ChunkerEvaluatorTool.h"
#include "tools/cmdline/chunker/ChunkerCrossValidatorTool.h"
#include "tools/cmdline/chunker/ChunkerConverterTool.h"
#include "tools/cmdline/parser/ParserTool.h"
#include "tools/cmdline/parser/ParserTrainerTool.h"
#include "tools/cmdline/parser/BuildModelUpdaterTool.h"
#include "tools/cmdline/parser/CheckModelUpdaterTool.h"
#include "tools/cmdline/parser/TaggerModelReplacerTool.h"
#include "tools/cmdline/TerminateToolException.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            using opennlp::tools::cmdline::chunker::ChunkerConverterTool;
            using opennlp::tools::cmdline::chunker::ChunkerCrossValidatorTool;
            using opennlp::tools::cmdline::chunker::ChunkerEvaluatorTool;
            using opennlp::tools::cmdline::chunker::ChunkerMETool;
            using opennlp::tools::cmdline::chunker::ChunkerTrainerTool;
            using opennlp::tools::cmdline::dictionary::DictionaryBuilderTool;
            using opennlp::tools::cmdline::doccat::DoccatConverterTool;
            using opennlp::tools::cmdline::doccat::DoccatTool;
            using opennlp::tools::cmdline::doccat::DoccatTrainerTool;
            using opennlp::tools::cmdline::namefind::CensusDictionaryCreatorTool;
            using opennlp::tools::cmdline::namefind::TokenNameFinderConverterTool;
            using opennlp::tools::cmdline::namefind::TokenNameFinderCrossValidatorTool;
            using opennlp::tools::cmdline::namefind::TokenNameFinderEvaluatorTool;
            using opennlp::tools::cmdline::namefind::TokenNameFinderTool;
            using opennlp::tools::cmdline::namefind::TokenNameFinderTrainerTool;
            using opennlp::tools::cmdline::parser::BuildModelUpdaterTool;
            using opennlp::tools::cmdline::parser::CheckModelUpdaterTool;
            using opennlp::tools::cmdline::parser::ParserTool;
            using opennlp::tools::cmdline::parser::ParserTrainerTool;
            using opennlp::tools::cmdline::parser::TaggerModelReplacerTool;
            using opennlp::tools::cmdline::postag::POSTaggerConverter;
            using opennlp::tools::cmdline::postag::POSTaggerCrossValidatorTool;
            using opennlp::tools::cmdline::postag::POSTaggerEvaluatorTool;
            using opennlp::tools::cmdline::postag::POSTaggerTrainerTool;
            using opennlp::tools::cmdline::sentdetect::SentenceDetectorConverterTool;
            using opennlp::tools::cmdline::sentdetect::SentenceDetectorCrossValidatorTool;
            using opennlp::tools::cmdline::sentdetect::SentenceDetectorEvaluatorTool;
            using opennlp::tools::cmdline::sentdetect::SentenceDetectorTool;
            using opennlp::tools::cmdline::sentdetect::SentenceDetectorTrainerTool;
            using opennlp::tools::cmdline::tokenizer::DictionaryDetokenizerTool;
            using opennlp::tools::cmdline::tokenizer::SimpleTokenizerTool;
            using opennlp::tools::cmdline::tokenizer::TokenizerConverterTool;
            using opennlp::tools::cmdline::tokenizer::TokenizerCrossValidatorTool;
            using opennlp::tools::cmdline::tokenizer::TokenizerMEEvaluatorTool;
            using opennlp::tools::cmdline::tokenizer::TokenizerMETool;
            using opennlp::tools::cmdline::tokenizer::TokenizerTrainerTool;
const std::string CLI::CMD = "opennlp";
java::util::Map<std::string, CmdLineTool*> *CLI::toolLookupMap = 0;

            CLI::CLI()
            {
              toolLookupMap = new LinkedHashMap<std::string, CmdLineTool*>();

              std::vector<CmdLineTool*> tools = std::list<CmdLineTool*>();

              // Docoument Categorizer
              tools.push_back(new DoccatTool());
              tools.push_back(new DoccatTrainerTool());
              tools.push_back(new DoccatConverterTool());

              // Dictionary Builder
              tools.push_back(new DictionaryBuilderTool());

              // Tokenizer
              tools.push_back(new SimpleTokenizerTool());
              tools.push_back(new TokenizerMETool());
              tools.push_back(new TokenizerTrainerTool());
              tools.push_back(new TokenizerMEEvaluatorTool());
              tools.push_back(new TokenizerCrossValidatorTool());
              tools.push_back(new TokenizerConverterTool());
              tools.push_back(new DictionaryDetokenizerTool());

              // Sentence detector
              tools.push_back(new SentenceDetectorTool());
              tools.push_back(new SentenceDetectorTrainerTool());
              tools.push_back(new SentenceDetectorEvaluatorTool());
              tools.push_back(new SentenceDetectorCrossValidatorTool());
              tools.push_back(new SentenceDetectorConverterTool());

              // Name Finder
              tools.push_back(new TokenNameFinderTool());
              tools.push_back(new TokenNameFinderTrainerTool());
              tools.push_back(new TokenNameFinderEvaluatorTool());
              tools.push_back(new TokenNameFinderCrossValidatorTool());
              tools.push_back(new TokenNameFinderConverterTool());
              tools.push_back(new CensusDictionaryCreatorTool());


              // POS Tagger
              tools.push_back(new opennlp::tools::cmdline::postag::POSTaggerTool());
              tools.push_back(new POSTaggerTrainerTool());
              tools.push_back(new POSTaggerEvaluatorTool());
              tools.push_back(new POSTaggerCrossValidatorTool());
              tools.push_back(new POSTaggerConverter());

              // add evaluator
              // add cv validator

              // Chunker
              tools.push_back(new ChunkerMETool());
              tools.push_back(new ChunkerTrainerTool());
              tools.push_back(new ChunkerEvaluatorTool());
              tools.push_back(new ChunkerCrossValidatorTool());
              tools.push_back(new ChunkerConverterTool());

              // Parser
              tools.push_back(new ParserTool());
              tools.push_back(new ParserTrainerTool()); // trains everything
              tools.push_back(new BuildModelUpdaterTool()); // re-trains  build model
              tools.push_back(new CheckModelUpdaterTool()); // re-trains  build model
              tools.push_back(new TaggerModelReplacerTool());

              for (std::vector<CmdLineTool*>::const_iterator tool = tools.begin(); tool != tools.end(); ++tool)
              {
                toolLookupMap->put((*tool)->getName(), *tool);
              }

              toolLookupMap = Collections::unmodifiableMap(toolLookupMap);
            }

            Set<std::string> *CLI::getToolNames()
            {
              return toolLookupMap->keySet();
            }

            void CLI::usage()
            {
              std::cout << "Usage: " + CMD + " TOOL" << std::endl;
              std::cout << "where TOOL is one of:" << std::endl;

              // distance of tool name from line start
              int numberOfSpaces = 25;

              for (Map<std::string, CmdLineTool*>::const_iterator tool = toolLookupMap->begin(); tool != toolLookupMap->end(); ++tool)
              {

                std::cout << "  " + tool->second->getName();

                for (int i = 0; i < abs(tool->second->getName()->length() - numberOfSpaces); i++)
                {
                  std::cout << " ";
                }

                std::cout << tool->second->getShortDescription() << std::endl;
              }

              std::cout << "All tools print help when invoked with help parameter" << std::endl;
              std::cout << "Example: opennlp SimpleTokenizer help" << std::endl;
            }

            void CLI::main(std::string args[])
            {

              if (sizeof(args) / sizeof(args[0]) == 0)
              {
                usage();
                exit(1);
              }

              std::string toolArguments[sizeof(args) / sizeof(args[0]) - 1];
              System::arraycopy(args, 1, toolArguments, 0, sizeof(toolArguments) / sizeof(toolArguments[0]));

              CmdLineTool *tool = toolLookupMap->get(args[0]);

              if (tool == 0)
              {
                usage();
                exit(1);
              }
              else if (sizeof(args) / sizeof(args[0]) > 1 && args[1] == "help")
              {
                std::cout << tool->getHelp() << std::endl;
                exit(1);
              }

              try
              {
                tool->run(toolArguments);
              }
              catch (TerminateToolException e)
              {

                if (e->what() != 0)
                  System::err::println(e->what());

                exit(e->getCode());
              }
            }
        }
    }
}
