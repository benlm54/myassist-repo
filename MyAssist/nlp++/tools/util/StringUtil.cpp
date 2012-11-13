#include "StringUtil.h"
#include "CharSequence.h"

namespace opennlp
{
    namespace tools
    {
        namespace util
        {

            bool StringUtil::isWhitespace(char charCode)
            {
              return isspace(charCode) || char::getType(charCode) == char::SPACE_SEPARATOR;
            }

            bool StringUtil::isWhitespace(int charCode)
            {
              return isspace(charCode) || char::getType(charCode) == char::SPACE_SEPARATOR;
            }

            std::string StringUtil::toLowerCase(CharSequence *string)
            {

              char lowerCaseChars[string->length()];

              for (int i = 0; i < string->length(); i++)
              {
                lowerCaseChars[i] = tolower(string[i]);
              }

              return std::string(lowerCaseChars);
            }

            std::string StringUtil::toUpperCase(CharSequence *string)
            {
              char upperCaseChars[string->length()];

              for (int i = 0; i < string->length(); i++)
              {
                upperCaseChars[i] = toupper(string[i]);
              }

              return std::string(upperCaseChars);
            }

            bool StringUtil::isEmpty(CharSequence *theString)
            {
              return theString->length() == 0;
            }
        }
    }
}
