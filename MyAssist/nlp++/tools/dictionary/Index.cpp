#include "Index.h"

namespace opennlp
{
    namespace tools
    {
        namespace dictionary
        {
            using opennlp::tools::util::StringList;

            Index::Index(Iterator<StringList*> *tokenLists)
            {

              InitializeInstanceFields();
              while (tokenLists->hasNext())
              {

                StringList *tokens = tokenLists->next();

                for (int i = 0; i < tokens->size(); i++)
                {
                  this->tokens->add(tokens->getToken(i));
                }
                  tokenLists++;
              }
            }

            bool Index::contains(const std::string &token)
            {
              return tokens->contains(token);
            }

            void Index::InitializeInstanceFields()
            {
                tokens = std::set<std::string>();
            }
        }
    }
}
