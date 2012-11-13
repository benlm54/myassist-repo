#include "CachedFeatureGenerator.h"

namespace opennlp
{
    namespace tools
    {
        namespace util
        {
            namespace featuregen
            {
                using opennlp::tools::util::Cache;

                CachedFeatureGenerator::CachedFeatureGenerator(...) : generator(new AggregatedFeatureGenerator(generators))
                {
                  contextsCache = new Cache(100);
                }

                void CachedFeatureGenerator::createFeatures(std::vector<std::string> &features, std::string tokens[], int index, std::string previousOutcomes[])
                {

                  std::vector<std::string> cacheFeatures;

                  if (tokens == prevTokens)
                  {
                    cacheFeatures = static_cast<std::vector<std::string>>(contextsCache->get_Renamed(index));

                    if (cacheFeatures.size() > 0)
                    {
                      numberOfCacheHits++;
                      features.addAll(cacheFeatures);
                      return;
                    }

                  }
                  else
                  {
                    contextsCache->clear();
                    prevTokens = tokens;
                  }

                  cacheFeatures = std::vector<std::string>();

                  numberOfCacheMisses++;

                  generator->createFeatures(cacheFeatures, tokens, index, previousOutcomes);

                  contextsCache->put(index, cacheFeatures);
                  features.addAll(cacheFeatures);
                }

                void CachedFeatureGenerator::updateAdaptiveData(std::string tokens[], std::string outcomes[])
                {
                  generator->updateAdaptiveData(tokens, outcomes);
                }

                void CachedFeatureGenerator::clearAdaptiveData()
                {
                  generator->clearAdaptiveData();
                }

                long long CachedFeatureGenerator::getNumberOfCacheHits()
                {
                  return numberOfCacheHits;
                }

                long long CachedFeatureGenerator::getNumberOfCacheMisses()
                {
                  return numberOfCacheMisses;
                }

                std::string CachedFeatureGenerator::ToString()
                {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                  return __super::toString() + ": hits=" + numberOfCacheHits + " misses=" + numberOfCacheMisses + " hit%" + (numberOfCacheHits > 0 ? static_cast<double>(numberOfCacheHits) / (numberOfCacheMisses + numberOfCacheHits) : 0);
                }
            }
        }
    }
}
