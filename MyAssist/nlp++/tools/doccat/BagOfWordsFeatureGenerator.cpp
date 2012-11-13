#include "BagOfWordsFeatureGenerator.h"
#include "tools/util/featuregen/StringPattern.h"

namespace opennlp
{
    namespace tools
    {
        namespace doccat
        {
            using opennlp::tools::util::featuregen::StringPattern;

            BagOfWordsFeatureGenerator::BagOfWordsFeatureGenerator()
            {
                InitializeInstanceFields();
            }

            BagOfWordsFeatureGenerator::BagOfWordsFeatureGenerator(bool useOnlyAllLetterTokens)
            {
              InitializeInstanceFields();
              this->useOnlyAllLetterTokens = useOnlyAllLetterTokens;
            }

            Collection<std::string> *BagOfWordsFeatureGenerator::extractFeatures(std::string text[])
            {

              Collection<std::string> *bagOfWords = std::vector<std::string>(sizeof(text) / sizeof(text[0]));

              for (int i = 0; i < sizeof(text) / sizeof(text[0]); i++)
              {

                if (useOnlyAllLetterTokens)
                {
                  StringPattern *pattern = StringPattern::recognize(text[i]);

                  if (pattern->isAllLetter())
                    bagOfWords->add("bow=" + text[i]);
                }
                else
                {
                  bagOfWords->add("bow=" + text[i]);
                }
              }

              return bagOfWords;
            }

            void BagOfWordsFeatureGenerator::InitializeInstanceFields()
            {
                useOnlyAllLetterTokens = false;
            }
        }
    }
}
