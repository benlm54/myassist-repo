#include "BuildModelUpdaterTool.h"
#include "tools/cmdline/parser/ParserTrainerTool.h"
#include "tools/dictionary/Dictionary.h"
#include "model/EventStream.h"
#include "tools/parser/ParserEventTypeEnum.h"
#include "tools/parser/chunking/ParserEventStream.h"
#include "model/AbstractModel.h"
#include "tools/parser/chunking/Parser.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace parser
            {
                using opennlp::model::AbstractModel;
                using opennlp::tools::dictionary::Dictionary;
                using opennlp::tools::parser::Parse;
                using opennlp::tools::parser::ParserEventTypeEnum;
                using opennlp::tools::parser::ParserModel;
                using opennlp::tools::parser::chunking::Parser;
                using opennlp::tools::parser::chunking::ParserEventStream;
                using opennlp::tools::util::ObjectStream;

                std::string BuildModelUpdaterTool::getName()
                {
                  return "BuildModelUpdater";
                }

                std::string BuildModelUpdaterTool::getShortDescription()
                {
                  return "trains and updates the build model in a parser model";
                }

                opennlp::tools::parser::ParserModel *BuildModelUpdaterTool::trainAndUpdate(ParserModel *originalModel, ObjectStream<Parse*> *parseSamples, ModelUpdaterParams *parameters) throw(IOException)
                {

                    Dictionary *mdict = ParserTrainerTool::buildDictionary(parseSamples, originalModel->getHeadRules(), parameters->getCutoff());

                    parseSamples->reset();

                    // TODO: training individual models should be in the chunking parser, not here
                    // Training build
                    std::cout << "Training builder" << std::endl;
                    opennlp::model::EventStream *bes = new ParserEventStream(parseSamples, originalModel->getHeadRules(), opennlp::tools::parser::BUILD, mdict);
                    AbstractModel *buildModel = Parser::train(bes, parameters->getIterations(), parameters->getCutoff());

                    parseSamples->close();

                    return originalModel->updateBuildModel(buildModel);
                }
            }
        }
    }
}
