#include "DoccatConverterTool.h"
#include "tools/formats/LeipzigDocumentSampleStreamFactory.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace doccat
            {
                using opennlp::tools::cmdline::AbstractConverterTool;
                using opennlp::tools::cmdline::ObjectStreamFactory;
                using opennlp::tools::doccat::DocumentSample;
                using opennlp::tools::formats::LeipzigDocumentSampleStreamFactory;
java::util::Map<std::string, opennlp::tools::cmdline::ObjectStreamFactory<opennlp::tools::doccat::DocumentSample*>*> *const DoccatConverterTool::streamFactories = 0;

                DoccatConverterTool::DoccatConverterTool()
                {
                  Map<std::string, ObjectStreamFactory<DocumentSample*>*> *mutableStreamFactories = std::map<std::string, ObjectStreamFactory<DocumentSample*>*>();

                  mutableStreamFactories->put("leipzig", new LeipzigDocumentSampleStreamFactory());

                  streamFactories = Collections::unmodifiableMap(mutableStreamFactories);
                }

                std::string DoccatConverterTool::getName()
                {
                  return "DoccatConverter";
                }

                std::string DoccatConverterTool::getShortDescription()
                {
                  return "";
                }

                opennlp::tools::cmdline::ObjectStreamFactory<DocumentSample*> *DoccatConverterTool::createStreamFactory(const std::string &format)
                {
                  return streamFactories->get(format);
                }
            }
        }
    }
}
