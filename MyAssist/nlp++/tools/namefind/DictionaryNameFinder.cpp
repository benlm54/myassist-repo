#include "DictionaryNameFinder.h"
#include "tools/util/StringList.h"

namespace opennlp
{
    namespace tools
    {
        namespace namefind
        {
            using opennlp::tools::dictionary::Dictionary;
            using opennlp::tools::dictionary::Index;
            using opennlp::tools::util::Span;
            using opennlp::tools::util::StringList;

            DictionaryNameFinder::DictionaryNameFinder(Dictionary *dictionary)
            {
              mDictionary = dictionary;
              mMetaDictionary = new Index(dictionary->begin());
            }

            Span *DictionaryNameFinder::find(std::string tokenStrings[])
            {
              std::vector<Span*> foundNames = std::list<Span*>();

              for (int startToken = 0; startToken < sizeof(tokenStrings) / sizeof(tokenStrings[0]); startToken++)
              {

                Span *foundName = 0;

//ORIGINAL LINE: String tokens[] = new String[]{};
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                std::string *tokens = new std::string[]{};

                for (int endToken = startToken; endToken < sizeof(tokenStrings) / sizeof(tokenStrings[0]); endToken++)
                {

                  std::string token = tokenStrings[endToken];

                  // TODO: improve performance here
                  std::string newTokens[tokens->length + 1];
                  System::arraycopy(tokens, 0, newTokens, 0, tokens->length);
                  newTokens[sizeof(newTokens) / sizeof(newTokens[0]) - 1] = token;
                  tokens = newTokens;

                  if (mMetaDictionary->contains(token))
                  {

                    StringList *tokenList = new StringList(tokens);

                    if (mDictionary->contains(tokenList))
                    {
                      foundName = new Span(startToken, endToken + 1);
                    }
                  }
                  else
                  {
                    break;
                  }
                }

                if (foundName != 0)
                {
                  foundNames.push_back(foundName);
                }
              }

              return foundNames.toArray(new Span[foundNames.size()]);
            }

            void DictionaryNameFinder::clearAdaptiveData()
            {
              // nothing to clear
            }
        }
    }
}
