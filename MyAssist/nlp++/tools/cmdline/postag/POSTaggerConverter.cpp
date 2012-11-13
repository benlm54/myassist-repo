#include "POSTaggerConverter.h"
#include "tools/formats/ConllXPOSSampleStreamFactory.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace postag
            {
                using opennlp::tools::cmdline::AbstractConverterTool;
                using opennlp::tools::cmdline::ObjectStreamFactory;
                using opennlp::tools::formats::ConllXPOSSampleStreamFactory;
                using opennlp::tools::postag::POSSample;
java::util::Map<std::string, opennlp::tools::cmdline::ObjectStreamFactory<opennlp::tools::postag::POSSample*>*> *const POSTaggerConverter::streamFactories = 0;

                POSTaggerConverter::POSTaggerConverter()
                {
                  Map<std::string, ObjectStreamFactory<POSSample*>*> *mutableStreamFactories = std::map<std::string, ObjectStreamFactory<POSSample*>*>();

                  mutableStreamFactories->put("conllx", new ConllXPOSSampleStreamFactory());

                  streamFactories = Collections::unmodifiableMap(mutableStreamFactories);
                }

                std::string POSTaggerConverter::getName()
                {
                  return "POSTaggerConverter";
                }

                std::string POSTaggerConverter::getShortDescription()
                {
                  return "";
                }

                opennlp::tools::cmdline::ObjectStreamFactory<POSSample*> *POSTaggerConverter::createStreamFactory(const std::string &format)
                {
                  return streamFactories->get(format);
                }
            }
        }
    }
}
