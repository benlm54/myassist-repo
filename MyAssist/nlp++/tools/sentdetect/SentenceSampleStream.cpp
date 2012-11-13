#include "SentenceSampleStream.h"
#include "tools/util/Span.h"
#include "StringBuilder.h"
#include "S.h"

namespace opennlp
{
    namespace tools
    {
        namespace sentdetect
        {
            using opennlp::tools::util::FilterObjectStream;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::Span;

            SentenceSampleStream::SentenceSampleStream(ObjectStream<std::string> *sentences) : opennlp.tools.util.FilterObjectStream<String, SentenceSample>(new EmptyLinePreprocessorStream(sentences))
            {
            }

            opennlp::tools::sentdetect::SentenceSample *SentenceSampleStream::read() throw(IOException)
            {

              StringBuilder *sentencesString = new StringBuilder();
              std::vector<Span*> sentenceSpans = std::list<Span*>();

              std::string sentence;
              while ((sentence = samples->read()) != "" && sentence != "")
              {

                int begin = sentencesString->length();
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'trim' method:
                sentencesString->append(sentence.trim());
                int end = sentencesString->length();
                sentenceSpans.push_back(new Span(begin, end));
                sentencesString->append(' ');
              }

              if (sentenceSpans.size() > 0)
              {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                return new SentenceSample(sentencesString->toString(), sentenceSpans.toArray(new Span[sentenceSpans.size()]));
              }
              else
              {
                return 0;
              }
            }
        }
    }
}
