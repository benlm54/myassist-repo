#include "POSModelLoader.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace postag
            {
                using opennlp::tools::cmdline::ModelLoader;
                using opennlp::tools::postag::POSModel;
                using opennlp::tools::util::InvalidFormatException;

                POSModelLoader::POSModelLoader() : opennlp.tools.cmdline.ModelLoader<opennlp.tools.postag.POSModel>("POS Tagger")
                {
                }

                opennlp::tools::postag::POSModel *POSModelLoader::loadModel(InputStream *modelIn) throw(IOException, InvalidFormatException)
                {
                  return new POSModel(modelIn);
                }
            }
        }
    }
}
