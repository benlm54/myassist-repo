#include "TokenizerModelLoader.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace tokenizer
            {
                using opennlp::tools::cmdline::ModelLoader;
                using opennlp::tools::tokenize::TokenizerModel;
                using opennlp::tools::util::InvalidFormatException;

                TokenizerModelLoader::TokenizerModelLoader() : opennlp.tools.cmdline.ModelLoader<opennlp.tools.tokenize.TokenizerModel>("Tokenizer")
                {
                }

                opennlp::tools::tokenize::TokenizerModel *TokenizerModelLoader::loadModel(InputStream *modelIn) throw(IOException, InvalidFormatException)
                {
                  return new TokenizerModel(modelIn);
                }
            }
        }
    }
}
