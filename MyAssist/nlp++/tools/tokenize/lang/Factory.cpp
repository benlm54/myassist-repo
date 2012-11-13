#include "Factory.h"
#include "tools/tokenize/DefaultTokenContextGenerator.h"

namespace opennlp
{
    namespace tools
    {
        namespace tokenize
        {
            namespace lang
            {
                using opennlp::tools::tokenize::DefaultTokenContextGenerator;
                using opennlp::tools::tokenize::TokenContextGenerator;
const std::string Factory::DEFAULT_ALPHANUMERIC = "^[A-Za-z0-9]+$";

                Pattern *Factory::getAlphanumeric(const std::string &languageCode)
                {
                  if ((std::string("pt")) == languageCode)
                  {
                    return Pattern::compile("^[0-9a-záãâàéêíóõôúüçA-Z�?ÃÂÀÉÊ�?ÓÕÔÚÜÇ]+$");
                  }

                  return Pattern::compile(DEFAULT_ALPHANUMERIC);
                }

                opennlp::tools::tokenize::TokenContextGenerator *Factory::createTokenContextGenerator(const std::string &languageCode, Set<std::string> *abbreviations)
                {
                  return new DefaultTokenContextGenerator(abbreviations);
                }
            }
        }
    }
}
