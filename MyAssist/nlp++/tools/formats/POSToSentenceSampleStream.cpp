#include "POSToSentenceSampleStream.h"

namespace opennlp
{
    namespace tools
    {
        namespace formats
        {
            using opennlp::tools::postag::POSSample;
            using opennlp::tools::tokenize::Detokenizer;
            using opennlp::tools::util::ObjectStream;

            POSToSentenceSampleStream::POSToSentenceSampleStream(Detokenizer *detokenizer, ObjectStream<POSSample*> *samples, int chunkSize) : AbstractToSentenceSampleStream<opennlp.tools.postag.POSSample>(detokenizer, samples, chunkSize)
            {

            }

            std::string *POSToSentenceSampleStream::toSentence(POSSample *sample)
            {
              return sample->getSentence();
            }
        }
    }
}
