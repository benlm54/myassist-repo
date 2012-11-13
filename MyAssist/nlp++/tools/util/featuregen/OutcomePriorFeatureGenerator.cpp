#include "OutcomePriorFeatureGenerator.h"

namespace opennlp
{
    namespace tools
    {
        namespace util
        {
            namespace featuregen
            {

const std::string OutcomePriorFeatureGenerator::OUTCOME_PRIOR_FEATURE = "def";

                void OutcomePriorFeatureGenerator::createFeatures(std::vector<std::string> &features, std::string tokens[], int index, std::string previousOutcomes[])
                {
                  features.push_back(OUTCOME_PRIOR_FEATURE);
                }
            }
        }
    }
}
