#include "PreviousMapFeatureGenerator.h"

namespace opennlp
{
    namespace tools
    {
        namespace util
        {
            namespace featuregen
            {

                void PreviousMapFeatureGenerator::createFeatures(std::vector<std::string> &features, std::string tokens[], int index, std::string preds[])
                {
                  features.push_back("pd=" + previousMap->get(tokens[index]));
                }

                void PreviousMapFeatureGenerator::updateAdaptiveData(std::string tokens[], std::string outcomes[])
                {

                  for (int i = 0; i < sizeof(tokens) / sizeof(tokens[0]); i++)
                  {
                    previousMap->put(tokens[i], outcomes[i]);
                  }
                }

                void PreviousMapFeatureGenerator::clearAdaptiveData()
                {
                  previousMap->clear();
                }

                void PreviousMapFeatureGenerator::InitializeInstanceFields()
                {
                    previousMap = std::map<std::string, std::string>();
                }
            }
        }
    }
}
