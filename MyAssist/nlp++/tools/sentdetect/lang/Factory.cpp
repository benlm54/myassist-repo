#include "Factory.h"
#include "tools/sentdetect/DefaultEndOfSentenceScanner.h"
#include "tools/sentdetect/lang/th/SentenceContextGenerator.h"
#include "tools/sentdetect/DefaultSDContextGenerator.h"

namespace opennlp
{
    namespace tools
    {
        namespace sentdetect
        {
            namespace lang
            {
                using opennlp::tools::sentdetect::DefaultEndOfSentenceScanner;
                using opennlp::tools::sentdetect::DefaultSDContextGenerator;
                using opennlp::tools::sentdetect::EndOfSentenceScanner;
                using opennlp::tools::sentdetect::SDContextGenerator;
                using opennlp::tools::sentdetect::lang::th::SentenceContextGenerator;

                opennlp::tools::sentdetect::EndOfSentenceScanner *Factory::createEndOfSentenceScanner(const std::string &languageCode)
                {
                  if ((std::string("th")) == languageCode)
                  {
                    return new DefaultEndOfSentenceScanner(new char[]{' ','\n'});
                  }

                  return new DefaultEndOfSentenceScanner(new char[]{'.', '!', '?'});
                }

                opennlp::tools::sentdetect::SDContextGenerator *Factory::createSentenceContextGenerator(const std::string &languageCode, Set<std::string> *abbreviations)
                {

                  if ((std::string("th")) == languageCode)
                  {
                    return new SentenceContextGenerator();
                  }

                  return new DefaultSDContextGenerator(abbreviations, new char[]{'.', '!', '?'});
                }

                opennlp::tools::sentdetect::SDContextGenerator *Factory::createSentenceContextGenerator(const std::string &languageCode)
                {
                  return createSentenceContextGenerator(languageCode, Collections::emptySet<std::string>());
                }
            }
        }
    }
}
