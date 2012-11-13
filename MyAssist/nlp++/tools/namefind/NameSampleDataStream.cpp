#include "NameSampleDataStream.h"
#include "S.h"

namespace opennlp
{
    namespace tools
    {
        namespace namefind
        {
            using opennlp::maxent::DataStream;
            using opennlp::tools::util::FilterObjectStream;
            using opennlp::tools::util::ObjectStream;
const std::string NameSampleDataStream::START_TAG_PREFIX = "<START:";
const std::string NameSampleDataStream::START_TAG = "<START>";
const std::string NameSampleDataStream::END_TAG = "<END>";

            NameSampleDataStream::NameSampleDataStream(ObjectStream<std::string> *in_Renamed) : opennlp.tools.util.FilterObjectStream<String, NameSample>(in)
            {
            }

            opennlp::tools::namefind::NameSample *NameSampleDataStream::read() throw(IOException)
            {
                std::string token = samples->read();

                bool isClearAdaptiveData = false;

                // An empty line indicates the begin of a new article
                // for which the adaptive data in the feature generators
                // must be cleared
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'trim' method:
                while (token != "" && token.trim()->length() == 0)
                {
                    isClearAdaptiveData = true;
                    token = samples->read();
                }

                if (token != "")
                {
                  return NameSample::parse(token, isClearAdaptiveData);
                }
                else
                {
                  return 0;
                }
            }
        }
    }
}
