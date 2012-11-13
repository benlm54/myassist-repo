#include "SentenceDetectorConverterTool.h"
#include "tools/formats/ConllXSentenceSampleStreamFactory.h"
#include "tools/formats/POSToSentenceSampleStreamFactory.h"
#include "tools/formats/NameToSentenceSampleStreamFactory.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace sentdetect
            {
                using opennlp::tools::cmdline::AbstractConverterTool;
                using opennlp::tools::cmdline::ObjectStreamFactory;
                using opennlp::tools::formats::ConllXSentenceSampleStreamFactory;
                using opennlp::tools::formats::NameToSentenceSampleStreamFactory;
                using opennlp::tools::formats::POSToSentenceSampleStreamFactory;
                using opennlp::tools::sentdetect::SentenceSample;
java::util::Map<std::string, opennlp::tools::cmdline::ObjectStreamFactory<opennlp::tools::sentdetect::SentenceSample*>*> *const SentenceDetectorConverterTool::streamFactories = 0;

                SentenceDetectorConverterTool::SentenceDetectorConverterTool()
                {
                  Map<std::string, ObjectStreamFactory<SentenceSample*>*> *mutableStreamFactories = std::map<std::string, ObjectStreamFactory<SentenceSample*>*>();

                  mutableStreamFactories->put("conllx", new ConllXSentenceSampleStreamFactory());
                  mutableStreamFactories->put("pos", new POSToSentenceSampleStreamFactory());
                  mutableStreamFactories->put("namefinder", new NameToSentenceSampleStreamFactory());

                  streamFactories = Collections::unmodifiableMap(mutableStreamFactories);
                }

                std::string SentenceDetectorConverterTool::getName()
                {
                  return "SentenceDetectorConverter";
                }

                std::string SentenceDetectorConverterTool::getShortDescription()
                {
                  return "";
                }

                opennlp::tools::cmdline::ObjectStreamFactory<SentenceSample*> *SentenceDetectorConverterTool::createStreamFactory(const std::string &format)
                {
                  return streamFactories->get(format);
                }
            }
        }
    }
}
