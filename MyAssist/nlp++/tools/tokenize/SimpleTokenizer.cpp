#include "SimpleTokenizer.h"
#include "tools/util/StringUtil.h"
#include "tools/tokenize/Tokenizer.h"

namespace opennlp
{
    namespace tools
    {
        namespace tokenize
        {
            using opennlp::tools::util::Span;
            using opennlp::tools::util::StringUtil;
SimpleTokenizer *const SimpleTokenizer::INSTANCE = 0;

            SimpleTokenizer::SimpleTokenizer()
            {
              INSTANCE = new SimpleTokenizer();
            }

            SimpleTokenizer::SimpleTokenizer()
            {
            }

            Span *SimpleTokenizer::tokenizePos(const std::string &s)
            {
              CharacterEnum *charType = CharacterEnum::WHITESPACE;
              CharacterEnum *state = charType;

              std::vector<Span*> tokens = std::vector<Span*>();
              int sl = s.length();
              int start = -1;
              char pc = 0;
              for (int ci = 0; ci < sl; ci++)
              {
                char c = s[ci];
                if (StringUtil::isWhitespace(c))
                {
                  charType = CharacterEnum::WHITESPACE;
                }
                else if (isalpha(c))
                {
                  charType = CharacterEnum::ALPHABETIC;
                }
                else if (isdigit(c))
                {
                  charType = CharacterEnum::NUMERIC;
                }
                else
                {
                  charType = CharacterEnum::OTHER;
                }
                if (state == CharacterEnum::WHITESPACE)
                {
                  if (charType != CharacterEnum::WHITESPACE)
                  {
                    start = ci;
                  }
                }
                else
                {
                  if (charType != state || charType == CharacterEnum::OTHER && c != pc)
                  {
                    tokens.push_back(new Span(start, ci));
                    start = ci;
                  }
                }
                state = charType;
                pc = c;
              }
              if (charType != CharacterEnum::WHITESPACE)
              {
                tokens.push_back(new Span(start, sl));
              }
              return tokens.toArray(new Span[tokens.size()]);
            }

            void SimpleTokenizer::main(std::string args[]) throw(IOException)
            {
              if (sizeof(args) / sizeof(args[0]) != 0)
              {
                System::err::println("Usage:  java opennlp.tools.tokenize.SimpleTokenizer < sentences");
                exit(1);
              }
              opennlp::tools::tokenize::Tokenizer *tokenizer = new SimpleTokenizer();
              java::io::BufferedReader *inReader = new java::io::BufferedReader(new java::io::InputStreamReader(System::in));
              for (std::string line = inReader->readLine(); line != ""; line = inReader->readLine())
              {
                if (line == "")
                {
                  std::cout << std::endl;
                }
                else
                {
//ORIGINAL LINE: String[] tokens = tokenizer.tokenize(line);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                  std::string *tokens = tokenizer->tokenize(line);
                  if (tokens->length > 0)
                  {
                    std::cout << tokens[0];
                  }
                  for (int ti = 1,tn = tokens->length;ti < tn;ti++)
                  {
                    std::cout << " " + tokens[ti];
                  }
                  std::cout << std::endl;
                }
              }
            }

CharacterEnum *const CharacterEnum::WHITESPACE = new CharacterEnum("whitespace");
CharacterEnum *const CharacterEnum::ALPHABETIC = new CharacterEnum("alphabetic");
CharacterEnum *const CharacterEnum::NUMERIC = new CharacterEnum("numeric");
CharacterEnum *const CharacterEnum::OTHER = new CharacterEnum("other");

            CharacterEnum::CharacterEnum(const std::string &name)
            {
              this->name = name;
            }

            std::string CharacterEnum::ToString()
            {
              return name;
            }
        }
    }
}
