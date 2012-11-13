#include "ParserModelLoader.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace parser
            {
                using opennlp::tools::cmdline::ModelLoader;
                using opennlp::tools::parser::ParserModel;
                using opennlp::tools::util::InvalidFormatException;

                ParserModelLoader::ParserModelLoader() : opennlp.tools.cmdline.ModelLoader<opennlp.tools.parser.ParserModel>("Parser")
                {
                }

                opennlp::tools::parser::ParserModel *ParserModelLoader::loadModel(InputStream *modelIn) throw(IOException, InvalidFormatException)
                {
                  return new ParserModel(modelIn);
                }
            }
        }
    }
}
