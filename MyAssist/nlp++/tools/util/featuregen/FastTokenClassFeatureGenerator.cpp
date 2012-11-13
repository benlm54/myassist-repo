#include "FastTokenClassFeatureGenerator.h"
#include "tools/util/featuregen/StringPattern.h"

namespace opennlp
{
    namespace tools
    {
        namespace util
        {
            namespace featuregen
            {

const std::string FastTokenClassFeatureGenerator::TOKEN_CLASS_PREFIX = "wc";
const std::string FastTokenClassFeatureGenerator::TOKEN_AND_CLASS_PREFIX = "w&c";
java::util::regex::Pattern *FastTokenClassFeatureGenerator::capPeriod = 0;

                FastTokenClassFeatureGenerator::FastTokenClassFeatureGenerator()
                {
                  capPeriod = Pattern::compile("^[A-Z]\\.$");
                }

                FastTokenClassFeatureGenerator::FastTokenClassFeatureGenerator()
                {
                }

                FastTokenClassFeatureGenerator::FastTokenClassFeatureGenerator(bool genearteWordAndClassFeature)
                {
                  this->generateWordAndClassFeature = genearteWordAndClassFeature;
                }

                std::string FastTokenClassFeatureGenerator::tokenFeature(const std::string &token)
                {

                  StringPattern *pattern = StringPattern::recognize(token);

                  std::string feat;
                  if (pattern->isAllLowerCaseLetter())
                  {
                    feat = "lc";
                  }
                  else if (pattern->digits() == 2)
                  {
                    feat = "2d";
                  }
                  else if (pattern->digits() == 4)
                  {
                    feat = "4d";
                  }
                  else if (pattern->containsDigit())
                  {
                    if (pattern->containsLetters())
                    {
                      feat = "an";
                    }
                    else if (pattern->containsHyphen())
                    {
                      feat = "dd";
                    }
                    else if (pattern->containsSlash())
                    {
                      feat = "ds";
                    }
                    else if (pattern->containsComma())
                    {
                      feat = "dc";
                    }
                    else if (pattern->containsPeriod())
                    {
                      feat = "dp";
                    }
                    else
                    {
                      feat = "num";
                    }
                  }
                  else if (pattern->isAllCapitalLetter() && token.length() == 1)
                  {
                    feat = "sc";
                  }
                  else if (pattern->isAllCapitalLetter())
                  {
                    feat = "ac";
                  }
                  else if (capPeriod->matcher(token)->find())
                  {
                    feat = "cp";
                  }
                  else if (pattern->isInitialCapitalLetter())
                  {
                    feat = "ic";
                  }
                  else
                  {
                    feat = "other";
                  }

                  return (feat);
                }

                void FastTokenClassFeatureGenerator::createFeatures(std::vector<std::string> &features, std::string tokens[], int index, std::string preds[])
                {
                  std::string wordClass = tokenFeature(tokens[index]);
                  features.push_back(TOKEN_CLASS_PREFIX + "=" + wordClass);

                  if (generateWordAndClassFeature)
                  {
                    features.push_back(TOKEN_AND_CLASS_PREFIX + "=" + tokens[index].toLowerCase() + "," + wordClass);
                  }
                }
            }
        }
    }
}
