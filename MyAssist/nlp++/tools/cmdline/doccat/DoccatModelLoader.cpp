#include "DoccatModelLoader.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace doccat
            {
                using opennlp::tools::cmdline::ModelLoader;
                using opennlp::tools::doccat::DoccatModel;
                using opennlp::tools::util::InvalidFormatException;

                DoccatModelLoader::DoccatModelLoader() : opennlp.tools.cmdline.ModelLoader<opennlp.tools.doccat.DoccatModel>("Document Categorizer")
                {
                }

                opennlp::tools::doccat::DoccatModel *DoccatModelLoader::loadModel(InputStream *modelIn) throw(IOException, InvalidFormatException)
                {
                  return new DoccatModel(modelIn);
                }
            }
        }
    }
}
