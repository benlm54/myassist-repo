#include "TokenNameFinderModelLoader.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace namefind
            {
                using opennlp::tools::cmdline::ModelLoader;
                using opennlp::tools::namefind::TokenNameFinderModel;
                using opennlp::tools::util::InvalidFormatException;

                TokenNameFinderModelLoader::TokenNameFinderModelLoader() : opennlp.tools.cmdline.ModelLoader<opennlp.tools.namefind.TokenNameFinderModel>("Token Name Finder")
                {
                }

                opennlp::tools::namefind::TokenNameFinderModel *TokenNameFinderModelLoader::loadModel(InputStream *modelIn) throw(IOException, InvalidFormatException)
                {
                  return new TokenNameFinderModel(modelIn);
                }
            }
        }
    }
}
