#include "Entry.h"

namespace opennlp
{
    namespace tools
    {
        namespace dictionary
        {
            namespace serializer
            {
                using opennlp::tools::util::StringList;

                Entry::Entry(StringList *tokens, Attributes *attributes)
                {
                  this->tokens = tokens;
                  this->attributes = attributes;
                }

                opennlp::tools::util::StringList *Entry::getTokens()
                {
                  return tokens;
                }

                opennlp::tools::dictionary::serializer::Attributes *Entry::getAttributes()
                {
                  return attributes;
                }
            }
        }
    }
}
