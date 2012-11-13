#include "TokenFeatureGenerator.h"

namespace opennlp
{
    namespace tools
    {
        namespace util
        {
            namespace featuregen
            {

const std::string TokenFeatureGenerator::WORD_PREFIX = "w";

                TokenFeatureGenerator::TokenFeatureGenerator(bool lowercase)
                {
                  this->lowercase = lowercase;
                }

                TokenFeatureGenerator::TokenFeatureGenerator()
                {
                }

                void TokenFeatureGenerator::createFeatures(std::vector<std::string> &features, std::string tokens[], int index, std::string preds[])
                {
                  if (lowercase)
                  {
                    features.push_back(WORD_PREFIX + "=" + tokens[index].toLowerCase());
                  }
                  else
                  {
                    features.push_back(WORD_PREFIX + "=" + tokens[index]);
                  }
                }
            }
        }
    }
}
