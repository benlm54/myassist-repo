#include "SentenceModelLoader.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace sentdetect
            {
                using opennlp::tools::cmdline::ModelLoader;
                using opennlp::tools::sentdetect::SentenceModel;
                using opennlp::tools::util::InvalidFormatException;

                SentenceModelLoader::SentenceModelLoader() : opennlp.tools.cmdline.ModelLoader<opennlp.tools.sentdetect.SentenceModel>("Sentence Detector")
                {
                }

                opennlp::tools::sentdetect::SentenceModel *SentenceModelLoader::loadModel(InputStream *modelIn) throw(IOException, InvalidFormatException)
                {
                  return new SentenceModel(modelIn);
                }
            }
        }
    }
}
