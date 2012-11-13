#include "LeipzigDoccatSampleStream.h"
#include "tools/tokenize/SimpleTokenizer.h"
#include "StringBuilder.h"
#include "S.h"

namespace opennlp
{
    namespace tools
    {
        namespace formats
        {
            using opennlp::tools::doccat::DocumentSample;
            using opennlp::tools::tokenize::SimpleTokenizer;
            using opennlp::tools::util::FilterObjectStream;
            using opennlp::tools::util::PlainTextByLineStream;

            LeipzigDoccatSampleStream::LeipzigDoccatSampleStream(const std::string &language, int sentencesPerDocument, InputStream *in_Renamed) throw(IOException) : opennlp.tools.util.FilterObjectStream<String, opennlp.tools.doccat.DocumentSample>(new PlainTextByLineStream(in, "UTF-8")), language(language), sentencesPerDocument(sentencesPerDocument)
            {
            }

            opennlp::tools::doccat::DocumentSample *LeipzigDoccatSampleStream::read() throw(IOException)
            {

              int count = 0;

              StringBuilder *sampleText = new StringBuilder();

              std::string line;
              while (count < sentencesPerDocument && (line = samples->read()) != "")
              {

//ORIGINAL LINE: String tokens[] = opennlp.tools.tokenize.SimpleTokenizer.INSTANCE.tokenize(line);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                std::string *tokens = SimpleTokenizer::INSTANCE->tokenize(line);

                if (tokens->length == 0)
                {
                  throw IOException("Empty lines are not allowed!");
                }

                // Always skip first token, that is the sentence number!
                for (int i = 1; i < tokens->length; i++)
                {
                  sampleText->append(tokens[i]);
                  sampleText->append(' ');
                }

                count++;
              }


              if (sampleText->length() > 0)
              {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                return new DocumentSample(language, sampleText->toString());
              }

              return 0;
            }
        }
    }
}
