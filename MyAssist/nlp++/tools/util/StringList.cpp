#include "StringList.h"
#include "StringBuffer.h"

namespace opennlp
{
    namespace tools
    {
        namespace util
        {

            StringList::StringList(const std::string &singleToken)
            {
              tokens = new std::string[] {singleToken.intern()};
            }

            StringList::StringList(...)
            {

              if (tokens == 0 || tokens->length == 0)
              {
                throw IllegalArgumentException();
              }

              this->tokens = new std::string[tokens->length];

              for (int i = 0; i < tokens->length; i++)
              {
                this->tokens[i] = tokens[i].intern();
              }
            }

            std::string StringList::getToken(int index)
            {
              return tokens[index];
            }

            int StringList::size()
            {
              return tokens->length;
            }

            Iterator<std::string> *StringList::iterator()
            {
              return new IteratorAnonymousInnerClassHelper();
            }

            bool StringList::IteratorAnonymousInnerClassHelper::hasNext()
            {
              return index < outerInstance->size();
            }

            std::string StringList::IteratorAnonymousInnerClassHelper::next()
            {

              if (hasNext())
              {
                return outerInstance->getToken(index++);
              }
              else
              {
                throw NoSuchElementException();
              }
            }

            void StringList::IteratorAnonymousInnerClassHelper::remove()
            {
              throw UnsupportedOperationException();
            }

            bool StringList::compareToIgnoreCase(StringList *tokens)
            {

              if (size() == tokens->size())
              {
                for (int i = 0; i < size(); i++)
                {

                  if (getToken(i).compareToIgnoreCase(tokens->getToken(i)) != 0)
                  {
                    return false;
                  }
                }
              }
              else
              {
                return false;
              }

              return true;
            }

            bool StringList::Equals(void *obj)
            {

              bool result;

              if (this == obj)
              {
                result = true;
              }
              else if (dynamic_cast<StringList*>(obj) != 0)
              {
                StringList *tokenList = static_cast<StringList*>(obj);

                result = Arrays::equals(tokens, tokenList->tokens);
              }
              else
              {
                result = false;
              }

              return result;
            }

            int StringList::GetHashCode()
            {
              int numBitsRegular = 32 / size();
              int numExtra = 32 % size();
              int maskExtra = static_cast<int>(static_cast<unsigned int>(0xFFFFFFFF) >> (32 - numBitsRegular + 1));
              int maskRegular = static_cast<int>(static_cast<unsigned int>(0xFFFFFFFF) >> 32 - numBitsRegular);
              int code = 0x000000000;
              int leftMostBit = 0;

              for (int wi = 0; wi < size(); wi++)
              {
                int word;
                int mask;
                int numBits;
                if (wi < numExtra)
                {
                  mask = maskExtra;
                  numBits = numBitsRegular + 1;
                }
                else
                {
                  mask = maskRegular;
                  numBits = numBitsRegular;
                }
                word = getToken(wi).hashCode() & mask; // mask off top bits
                word <<= 32 - leftMostBit - numBits; // move to correct position
                leftMostBit += numBits; // set for next iteration
                code |= word;
              }

              return code;
            }

            std::string StringList::ToString()
            {
              StringBuffer *string = new StringBuffer();

              string->append('[');

              for (int i = 0; i < size(); i++)
              {
                string->append(getToken(i));

                if (i < size() - 1)
                {
                  string->append(',');
                }
              }

              string->append(']');

//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              return string->toString();
            }
        }
    }
}
