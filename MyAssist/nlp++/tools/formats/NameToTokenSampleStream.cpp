#include "NameToTokenSampleStream.h"
#include "S.h"

namespace opennlp
{
    namespace tools
    {
        namespace formats
        {
            using opennlp::tools::namefind::NameSample;
            using opennlp::tools::tokenize::Detokenizer;
            using opennlp::tools::tokenize::TokenSample;
            using opennlp::tools::util::FilterObjectStream;
            using opennlp::tools::util::ObjectStream;

            NameToTokenSampleStream::NameToTokenSampleStream(Detokenizer *detokenizer, ObjectStream<NameSample*> *samples) : opennlp.tools.util.FilterObjectStream<opennlp.tools.namefind.NameSample, opennlp.tools.tokenize.TokenSample>(samples), detokenizer(detokenizer)
            {

            }

            opennlp::tools::tokenize::TokenSample *NameToTokenSampleStream::read() throw(IOException)
            {
              NameSample *nameSample = samples->read();

              TokenSample *tokenSample = 0;

              if (nameSample != 0)
              {
                tokenSample = new TokenSample(detokenizer, nameSample->getSentence());
              }

              return tokenSample;
            }
        }
    }
}
