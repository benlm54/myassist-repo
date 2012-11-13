#include "DefaultEndOfSentenceScanner.h"
#include "StringBuffer.h"

namespace opennlp
{
    namespace tools
    {
        namespace sentdetect
        {
            using opennlp::maxent::IntegerPool;
opennlp::maxent::IntegerPool *const DefaultEndOfSentenceScanner::INT_POOL = new opennlp::maxent::IntegerPool(500);

            DefaultEndOfSentenceScanner::DefaultEndOfSentenceScanner(char eosCharacters[])
            {
              this->eosCharacters = eosCharacters;
            }

            std::vector<int> DefaultEndOfSentenceScanner::getPositions(const std::string &s)
            {
              return getPositions(s.toCharArray());
            }

            std::vector<int> DefaultEndOfSentenceScanner::getPositions(StringBuffer *buf)
            {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              return getPositions(buf->toString()->toCharArray());
            }

            std::vector<int> DefaultEndOfSentenceScanner::getPositions(char cbuf[])
            {
              std::vector<int> l = std::vector<int>();
//ORIGINAL LINE: char[] eosCharacters = getEndOfSentenceCharacters();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              char *eosCharacters = getEndOfSentenceCharacters();
              for (int i = 0; i < sizeof(cbuf) / sizeof(cbuf[0]); i++)
              {
                for (int ci = 0;ci < eosCharacters->length;ci++)
                {
                  if (cbuf[i] == eosCharacters[ci])
                  {
                      l.push_back(INT_POOL->get_Renamed(i));
                      break;
                  }
                }
              }
              return l;
            }

            char *DefaultEndOfSentenceScanner::getEndOfSentenceCharacters()
            {
              return eosCharacters;
            }
        }
    }
}
