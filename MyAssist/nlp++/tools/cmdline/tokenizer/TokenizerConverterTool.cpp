#include "TokenizerConverterTool.h"
#include "tools/formats/ConllXTokenSampleStreamFactory.h"
#include "tools/formats/POSToTokenSampleStreamFactory.h"
#include "tools/formats/NameToTokenSampleStreamFactory.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace tokenizer
            {
                using opennlp::tools::cmdline::AbstractConverterTool;
                using opennlp::tools::cmdline::ObjectStreamFactory;
                using opennlp::tools::formats::ConllXTokenSampleStreamFactory;
                using opennlp::tools::formats::NameToTokenSampleStreamFactory;
                using opennlp::tools::formats::POSToTokenSampleStreamFactory;
                using opennlp::tools::tokenize::TokenSample;
java::util::Map<std::string, opennlp::tools::cmdline::ObjectStreamFactory<opennlp::tools::tokenize::TokenSample*>*> *const TokenizerConverterTool::streamFactories = 0;

                TokenizerConverterTool::TokenizerConverterTool()
                {
                  Map<std::string, ObjectStreamFactory<TokenSample*>*> *mutableStreamFactories = std::map<std::string, ObjectStreamFactory<TokenSample*>*>();

                  mutableStreamFactories->put("conllx", new ConllXTokenSampleStreamFactory());
                  mutableStreamFactories->put("pos", new POSToTokenSampleStreamFactory());
                  mutableStreamFactories->put("namefinder", new NameToTokenSampleStreamFactory());

                  streamFactories = Collections::unmodifiableMap(mutableStreamFactories);
                }

                std::string TokenizerConverterTool::getName()
                {
                  return "TokenizerConverter";
                }

                std::string TokenizerConverterTool::getShortDescription()
                {
                  return "";
                }

                opennlp::tools::cmdline::ObjectStreamFactory<TokenSample*> *TokenizerConverterTool::createStreamFactory(const std::string &format)
                {
                  return streamFactories->get(format);
                }
            }
        }
    }
}
