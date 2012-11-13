#include "ChunkerModelLoader.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace chunker
            {
                using opennlp::tools::chunker::ChunkerModel;
                using opennlp::tools::cmdline::ModelLoader;
                using opennlp::tools::util::InvalidFormatException;

                ChunkerModelLoader::ChunkerModelLoader() : opennlp.tools.cmdline.ModelLoader<opennlp.tools.chunker.ChunkerModel>("Chunker")
                {
                }

                opennlp::tools::chunker::ChunkerModel *ChunkerModelLoader::loadModel(InputStream *modelIn) throw(IOException, InvalidFormatException)
                {
                  return new ChunkerModel(modelIn);
                }
            }
        }
    }
}
