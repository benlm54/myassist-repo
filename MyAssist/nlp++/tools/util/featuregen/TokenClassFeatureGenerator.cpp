#include "TokenClassFeatureGenerator.h"
#include "tools/util/featuregen/FeatureGeneratorUtil.h"

namespace opennlp
{
    namespace tools
    {
        namespace util
        {
            namespace featuregen
            {

const std::string TokenClassFeatureGenerator::TOKEN_CLASS_PREFIX = "wc";
const std::string TokenClassFeatureGenerator::TOKEN_AND_CLASS_PREFIX = "w&c";

                TokenClassFeatureGenerator::TokenClassFeatureGenerator()
                {
                }

                TokenClassFeatureGenerator::TokenClassFeatureGenerator(bool genearteWordAndClassFeature)
                {
                  this->generateWordAndClassFeature = genearteWordAndClassFeature;
                }

                void TokenClassFeatureGenerator::createFeatures(std::vector<std::string> &features, std::string tokens[], int index, std::string preds[])
                {
                  std::string wordClass = FeatureGeneratorUtil::tokenFeature(tokens[index]);
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
