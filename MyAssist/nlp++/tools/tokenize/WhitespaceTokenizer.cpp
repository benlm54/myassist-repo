#include "WhitespaceTokenizer.h"
#include "tools/util/StringUtil.h"

namespace opennlp
{
    namespace tools
    {
        namespace tokenize
        {
            using opennlp::tools::util::Span;
            using opennlp::tools::util::StringUtil;
WhitespaceTokenizer *const WhitespaceTokenizer::INSTANCE = new WhitespaceTokenizer();

            WhitespaceTokenizer::WhitespaceTokenizer()
            {
            }

            Span *WhitespaceTokenizer::tokenizePos(const std::string &d)
            {
              int tokStart = -1;
              std::vector<Span*>tokens = std::vector<Span*>();
              bool inTok = false;

              //gather up potential tokens
              int end = d.length();
              for (int i = 0; i < end; i++)
              {
                if (StringUtil::isWhitespace(d[i]))
                {
                  if (inTok)
                  {
                    tokens->add(new Span(tokStart, i));
                    inTok = false;
                    tokStart = -1;
                  }
                }
                else
                {
                  if (!inTok)
                  {
                    tokStart = i;
                    inTok = true;
                  }
                }
              }

              if (inTok)
              {
                tokens->add(new Span(tokStart, end));
              }

              return tokens::toArray(new Span[tokens->size()]);
            }
        }
    }
}
