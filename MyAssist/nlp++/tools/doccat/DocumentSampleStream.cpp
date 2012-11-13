#include "DocumentSampleStream.h"
#include "tools/tokenize/WhitespaceTokenizer.h"
#include "S.h"

namespace opennlp
{
    namespace tools
    {
        namespace doccat
        {
            using opennlp::tools::tokenize::WhitespaceTokenizer;
            using opennlp::tools::util::FilterObjectStream;
            using opennlp::tools::util::ObjectStream;

            DocumentSampleStream::DocumentSampleStream(ObjectStream<std::string> *samples) : opennlp.tools.util.FilterObjectStream<String, DocumentSample>(samples)
            {
            }

            opennlp::tools::doccat::DocumentSample *DocumentSampleStream::read() throw(IOException)
            {
              std::string sampleString = samples->read();

              if (sampleString != "")
              {

                // Whitespace tokenize entire string
//ORIGINAL LINE: String tokens[] = opennlp.tools.tokenize.WhitespaceTokenizer.INSTANCE.tokenize(sampleString);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                std::string *tokens = WhitespaceTokenizer::INSTANCE->tokenize(sampleString);

                DocumentSample *sample;

                if (tokens->length > 1)
                {
                  std::string category = tokens[0];
                  std::string docTokens[tokens->length - 1];
                  System::arraycopy(tokens, 1, docTokens, 0, tokens->length - 1);

                  sample = new DocumentSample(category, docTokens);
                }
                else
                {
                  throw IOException("Empty lines, or lines with only a category string are not allowed!");
                }

                return sample;
              }
              else
              {
                return 0;
              }
            }
        }
    }
}
