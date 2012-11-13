#include "WordTagSampleStream.h"
#include "tools/util/InvalidFormatException.h"
#include "S.h"

namespace opennlp
{
    namespace tools
    {
        namespace postag
        {
            using opennlp::tools::util::FilterObjectStream;
            using opennlp::tools::util::InvalidFormatException;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::PlainTextByLineStream;
java::util::logging::Logger *WordTagSampleStream::logger = java::util::logging::Logger::getLogger(WordTagSampleStream::typeid::getName());

            WordTagSampleStream::WordTagSampleStream(Reader *sentences) throw(IOException) : opennlp.tools.util.FilterObjectStream<String, POSSample>(new PlainTextByLineStream(sentences))
            {
            }

            WordTagSampleStream::WordTagSampleStream(ObjectStream<std::string> *sentences) : opennlp.tools.util.FilterObjectStream<String, POSSample>(sentences)
            {
            }

            opennlp::tools::postag::POSSample *WordTagSampleStream::read() throw(IOException)
            {

              std::string sentence = samples->read();

              if (sentence != "")
              {
                POSSample *sample;
                try
                {
                  sample = POSSample::parse(sentence);
                }
                catch (InvalidFormatException e)
                {

                  if (logger->isLoggable(Level::WARNING))
                  {
                    logger->warning("Error during parsing, ignoring sentence: " + sentence);
                  }

                  sample = new POSSample(new std::string[]{}, new std::string[]{});
                }

                return sample;
              }
              else
              {
                // sentences stream is exhausted
                return 0;
              }
            }
        }
    }
}
