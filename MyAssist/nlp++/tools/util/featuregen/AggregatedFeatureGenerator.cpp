#include "AggregatedFeatureGenerator.h"

namespace opennlp
{
    namespace tools
    {
        namespace util
        {
            namespace featuregen
            {

                AggregatedFeatureGenerator::AggregatedFeatureGenerator(...)
                {

                  for (Collection<AdaptiveFeatureGenerator*>::const_iterator generator = generators->begin(); generator != generators->end(); ++generator)
                  {
                    if (*generator == 0)
                      throw IllegalArgumentException("null values in generators are not permitted!");
                  }

                  this->generators = std::vector<AdaptiveFeatureGenerator*>(generators->length);

                  Collections::addAll(this->generators, generators);

                  this->generators = Collections::unmodifiableCollection(this->generators);
                }

                AggregatedFeatureGenerator::AggregatedFeatureGenerator(Collection<AdaptiveFeatureGenerator*> *generators)
                {
                }

                void AggregatedFeatureGenerator::clearAdaptiveData()
                {

                  for (Collection<AdaptiveFeatureGenerator*>::const_iterator generator = generators->begin(); generator != generators->end(); ++generator)
                  {
                    (*generator)->clearAdaptiveData();
                  }
                }

                void AggregatedFeatureGenerator::createFeatures(std::vector<std::string> &features, std::string tokens[], int index, std::string previousOutcomes[])
                {

                  for (Collection<AdaptiveFeatureGenerator*>::const_iterator generator = generators->begin(); generator != generators->end(); ++generator)
                  {
                    (*generator)->createFeatures(features, tokens, index, previousOutcomes);
                  }
                }

                void AggregatedFeatureGenerator::updateAdaptiveData(std::string tokens[], std::string outcomes[])
                {

                  for (Collection<AdaptiveFeatureGenerator*>::const_iterator generator = generators->begin(); generator != generators->end(); ++generator)
                  {
                    (*generator)->updateAdaptiveData(tokens, outcomes);
                  }
                }

                Collection<AdaptiveFeatureGenerator*> *AggregatedFeatureGenerator::getGenerators()
                {
                  return generators;
                }
            }
        }
    }
}
