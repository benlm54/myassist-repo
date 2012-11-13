#include "POSToTokenSampleStream.h"
#include "S.h"

namespace opennlp
{
    namespace tools
    {
        namespace formats
        {
            using opennlp::tools::postag::POSSample;
            using opennlp::tools::tokenize::Detokenizer;
            using opennlp::tools::tokenize::TokenSample;
            using opennlp::tools::util::FilterObjectStream;
            using opennlp::tools::util::ObjectStream;

            POSToTokenSampleStream::POSToTokenSampleStream(Detokenizer *detokenizer, ObjectStream<POSSample*> *samples) : opennlp.tools.util.FilterObjectStream<opennlp.tools.postag.POSSample, opennlp.tools.tokenize.TokenSample>(samples), detokenizer(detokenizer)
            {


              if (detokenizer == 0)
                throw IllegalArgumentException("detokenizer must not be null!");

            }

            opennlp::tools::tokenize::TokenSample *POSToTokenSampleStream::read() throw(IOException)
            {

              POSSample *posSample = samples->read();

              TokenSample *tokenSample = 0;

              if (posSample != 0)
              {
                tokenSample = new TokenSample(detokenizer, posSample->getSentence());
              }

              return tokenSample;
            }
        }
    }
}
