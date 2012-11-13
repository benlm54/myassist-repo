#include "TokenNameFinderConverterTool.h"
#include "tools/formats/Conll02NameSampleStreamFactory.h"
#include "tools/formats/Conll03NameSampleStreamFactory.h"
#include "tools/formats/ad/ADNameSampleStreamFactory.h"
#include "tools/formats/BioNLP2004NameSampleStreamFactory.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace namefind
            {
                using opennlp::tools::cmdline::AbstractConverterTool;
                using opennlp::tools::cmdline::ObjectStreamFactory;
                using opennlp::tools::formats::BioNLP2004NameSampleStreamFactory;
                using opennlp::tools::formats::Conll02NameSampleStreamFactory;
                using opennlp::tools::formats::Conll03NameSampleStreamFactory;
                using opennlp::tools::formats::ad::ADNameSampleStreamFactory;
                using opennlp::tools::namefind::NameSample;
java::util::Map<std::string, opennlp::tools::cmdline::ObjectStreamFactory<opennlp::tools::namefind::NameSample*>*> *const TokenNameFinderConverterTool::streamFactories = 0;

                TokenNameFinderConverterTool::TokenNameFinderConverterTool()
                {
                  Map<std::string, ObjectStreamFactory<NameSample*>*> *mutableStreamFactories = std::map<std::string, ObjectStreamFactory<NameSample*>*>();

                  mutableStreamFactories->put("conll02", new Conll02NameSampleStreamFactory());
                  mutableStreamFactories->put("conll03", new Conll03NameSampleStreamFactory());
                  mutableStreamFactories->put("ad", new ADNameSampleStreamFactory());
                  mutableStreamFactories->put("bionlp2004", new BioNLP2004NameSampleStreamFactory());

                  streamFactories = Collections::unmodifiableMap(mutableStreamFactories);
                }

                std::string TokenNameFinderConverterTool::getName()
                {
                  return "TokenNameFinderConverter";
                }

                std::string TokenNameFinderConverterTool::getShortDescription()
                {
                  return "converts foreign data formats to native format";
                }

                opennlp::tools::cmdline::ObjectStreamFactory<NameSample*> *TokenNameFinderConverterTool::createStreamFactory(const std::string &format)
                {
                  return streamFactories->get(format);
                }
            }
        }
    }
}
