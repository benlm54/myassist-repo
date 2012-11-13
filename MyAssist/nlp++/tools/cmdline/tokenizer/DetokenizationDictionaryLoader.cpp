#include "DetokenizationDictionaryLoader.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace tokenizer
            {
                using opennlp::tools::cmdline::ModelLoader;
                using opennlp::tools::tokenize::DetokenizationDictionary;
                using opennlp::tools::util::InvalidFormatException;

                DetokenizationDictionaryLoader::DetokenizationDictionaryLoader() : opennlp.tools.cmdline.ModelLoader<opennlp.tools.tokenize.DetokenizationDictionary>("detokenizer dictionary")
                {
                }

                opennlp::tools::tokenize::DetokenizationDictionary *DetokenizationDictionaryLoader::loadModel(InputStream *modelIn) throw(IOException, InvalidFormatException)
                {
                  return new DetokenizationDictionary(modelIn);
                }
            }
        }
    }
}
