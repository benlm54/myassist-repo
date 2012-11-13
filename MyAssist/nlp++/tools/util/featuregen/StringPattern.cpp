#include "StringPattern.h"

namespace opennlp
{
    namespace tools
    {
        namespace util
        {
            namespace featuregen
            {

                StringPattern::StringPattern(int pattern, int digits) : pattern(pattern), digits(digits)
                {
                }

                bool StringPattern::isAllLetter()
                {
                  return (pattern & ALL_LETTERS) > 0;
                }

                bool StringPattern::isInitialCapitalLetter()
                {
                  return (pattern & INITAL_CAPITAL_LETTER) > 0;
                }

                bool StringPattern::isAllCapitalLetter()
                {
                  return (pattern & ALL_CAPITAL_LETTER) > 0;
                }

                bool StringPattern::isAllLowerCaseLetter()
                {
                  return (pattern & ALL_LOWERCASE_LETTER) > 0;
                }

                bool StringPattern::isAllDigit()
                {
                  return (pattern & ALL_DIGIT) > 0;
                }

                int StringPattern::digits()
                {
                  return digits_Renamed;
                }

                bool StringPattern::containsPeriod()
                {
                  return (pattern & CONTAINS_PERIOD) > 0;
                }

                bool StringPattern::containsComma()
                {
                  return (pattern & CONTAINS_COMMA) > 0;
                }

                bool StringPattern::containsSlash()
                {
                  return (pattern & CONTAINS_SLASH) > 0;
                }

                bool StringPattern::containsDigit()
                {
                  return (pattern & CONTAINS_DIGIT) > 0;
                }

                bool StringPattern::containsHyphen()
                {
                  return (pattern & CONTAINS_HYPHEN) > 0;
                }

                bool StringPattern::containsLetters()
                {
                  return (pattern & CONTAINS_LETTERS) > 0;
                }

                opennlp::tools::util::featuregen::StringPattern *StringPattern::recognize(const std::string &token)
                {

                  int pattern = ALL_CAPITAL_LETTER | ALL_LOWERCASE_LETTER | ALL_DIGIT | ALL_LETTERS;

                  int digits = 0;

                  for (int i = 0; i < token.length(); i++)
                  {
                    const char ch = token[i];

                    const int letterType = char::getType(ch);

                    bool isLetter = letterType == char::UPPERCASE_LETTER || letterType == char::LOWERCASE_LETTER || letterType == char::TITLECASE_LETTER || letterType == char::MODIFIER_LETTER || letterType == char::OTHER_LETTER;

                    if (isLetter)
                    {
                      pattern |= CONTAINS_LETTERS;
                      pattern &= ~ALL_DIGIT;

                      if (letterType == char::UPPERCASE_LETTER)
                      {
                        if (i == 0)
                        {
                          pattern |= INITAL_CAPITAL_LETTER;
                        }

                        pattern |= CONTAINS_UPPERCASE;

                        pattern &= ~ALL_LOWERCASE_LETTER;
                      }
                      else
                      {
                        pattern &= ~ALL_CAPITAL_LETTER;
                      }
                    }
                    else
                    {
                      // contains chars other than letter, this means
                      // it can not be one of these:
                      pattern &= ~ALL_LETTERS;
                      pattern &= ~ALL_CAPITAL_LETTER;
                      pattern &= ~ALL_LOWERCASE_LETTER;

                      if (letterType == char::DECIMAL_DIGIT_NUMBER)
                      {
                        pattern |= CONTAINS_DIGIT;
                        digits++;
                      }
                      else
                      {
                        pattern &= ~ALL_DIGIT;
                      }

                      switch (ch)
                      {
                      case ',':
                        pattern |= CONTAINS_COMMA;
                        break;

                      case '.':
                        pattern |= CONTAINS_PERIOD;
                        break;

                      case '/':
                        pattern |= CONTAINS_SLASH;
                        break;

                      case '-':
                        pattern |= CONTAINS_HYPHEN;
                        break;

                      default:
                        break;
                      }
                    }
                  }

                  return new StringPattern(pattern, digits);
                }
            }
        }
    }
}
