#include "DefaultTokenContextGenerator.h"
#include "tools/util/StringUtil.h"

namespace opennlp
{
    namespace tools
    {
        namespace tokenize
        {
            using opennlp::tools::util::StringUtil;

            DefaultTokenContextGenerator::DefaultTokenContextGenerator()
            {
            }

            DefaultTokenContextGenerator::DefaultTokenContextGenerator(Set<std::string> *inducedAbbreviations) : inducedAbbreviations(inducedAbbreviations)
            {
            }

            std::string *DefaultTokenContextGenerator::getContext(const std::string &sentence, int index)
            {
              std::vector<std::string> preds = std::vector<std::string>();
              std::string prefix = sentence.substr(0, index);
              std::string suffix = sentence.substr(index);
              preds.push_back("p=" + prefix);
              preds.push_back("s=" + suffix);
              if (index > 0)
              {
                addCharPreds("p1", sentence[index - 1], preds);
                if (index > 1)
                {
                  addCharPreds("p2", sentence[index - 2], preds);
                  preds.push_back("p21=" + sentence[index - 2] + sentence[index - 1]);
                }
                else
                {
                  preds.push_back("p2=bok");
                }
                preds.push_back("p1f1=" + sentence[index - 1] + sentence[index]);
              }
              else
              {
                preds.push_back("p1=bok");
              }
              addCharPreds("f1", sentence[index], preds);
              if (index + 1 < sentence.length())
              {
                addCharPreds("f2", sentence[index + 1], preds);
                preds.push_back("f12=" + sentence[index] + sentence[index + 1]);
              }
              else
              {
                preds.push_back("f2=bok");
              }
              if (sentence[0] == '&' && sentence[sentence.length() - 1] == ';')
              {
                preds.push_back("cc"); //character code
              }

              if (index == sentence.length() - 1 && inducedAbbreviations->contains(sentence))
              {
                preds.push_back("pabb");
              }

              if (inducedAbbreviations->contains(sentence))
              {
                preds.push_back("abb");
              }

              std::string context[preds.size()];
              preds.toArray(context);
              return context;
            }

            void DefaultTokenContextGenerator::addCharPreds(const std::string &key, char c, std::vector<std::string> &preds)
            {
              preds.push_back(key + "=" + c);
              if (isalpha(c))
              {
                preds.push_back(key + "_alpha");
                if (isupper(c))
                {
                  preds.push_back(key + "_caps");
                }
              }
              else if (isdigit(c))
              {
                preds.push_back(key + "_num");
              }
              else if (StringUtil::isWhitespace(c))
              {
                preds.push_back(key + "_ws");
              }
              else
              {
                if (c == '.' || c == '?' || c == '!')
                {
                  preds.push_back(key + "_eos");
                }
                else if (c == '`' || c == '"' || c == '\'')
                {
                  preds.push_back(key + "_quote");
                }
                else if (c == '[' || c == '{' || c == '(')
                {
                  preds.push_back(key + "_lp");
                }
                else if (c == ']' || c == '}' || c == ')')
                {
                  preds.push_back(key + "_rp");
                }
              }
            }
        }
    }
}
