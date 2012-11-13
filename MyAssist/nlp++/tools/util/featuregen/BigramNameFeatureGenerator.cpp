#include "BigramNameFeatureGenerator.h"
#include "tools/util/featuregen/FeatureGeneratorUtil.h"

namespace opennlp
{
    namespace tools
    {
        namespace util
        {
            namespace featuregen
            {

                void BigramNameFeatureGenerator::createFeatures(std::vector<std::string> &features, std::string tokens[], int index, std::string previousOutcomes[])
                {
                  std::string wc = FeatureGeneratorUtil::tokenFeature(tokens[index]);
                  //bi-gram features 
                  if (index > 0)
                  {
                    features.push_back("pw,w=" + tokens[index - 1] + "," + tokens[index]);
                    std::string pwc = FeatureGeneratorUtil::tokenFeature(tokens[index - 1]);
                    features.push_back("pwc,wc=" + pwc + "," + wc);
                  }
                  if (index + 1 < sizeof(tokens) / sizeof(tokens[0]))
                  {
                    features.push_back("w,nw=" + tokens[index] + "," + tokens[index + 1]);
                    std::string nwc = FeatureGeneratorUtil::tokenFeature(tokens[index + 1]);
                    features.push_back("wc,nc=" + wc + "," + nwc);
                  }
                }
            }
        }
    }
}
