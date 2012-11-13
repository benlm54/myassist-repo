#include "FeatureGeneratorUtil.h"
#include "tools/util/featuregen/FastTokenClassFeatureGenerator.h"

namespace opennlp
{
    namespace tools
    {
        namespace util
        {
            namespace featuregen
            {

                std::string FeatureGeneratorUtil::tokenFeature(const std::string &token)
                {
                  return FastTokenClassFeatureGenerator::tokenFeature(token);
                }
            }
        }
    }
}
