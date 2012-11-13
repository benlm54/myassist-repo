#include "WindowFeatureGenerator.h"

namespace opennlp
{
    namespace tools
    {
        namespace util
        {
            namespace featuregen
            {

const std::string WindowFeatureGenerator::PREV_PREFIX = "p";
const std::string WindowFeatureGenerator::NEXT_PREFIX = "n";

                WindowFeatureGenerator::WindowFeatureGenerator(AdaptiveFeatureGenerator *generator, int prevWindowSize, int nextWindowSize) : generator(generator), prevWindowSize(prevWindowSize), nextWindowSize(nextWindowSize)
                {
                }

                WindowFeatureGenerator::WindowFeatureGenerator(int prevWindowSize, int nextWindowSize, ...)
                {
                }

                WindowFeatureGenerator::WindowFeatureGenerator(AdaptiveFeatureGenerator *generator)
                {
                }

                WindowFeatureGenerator::WindowFeatureGenerator(...)
                {
                }

                void WindowFeatureGenerator::createFeatures(std::vector<std::string> &features, std::string tokens[], int index, std::string preds[])
                {
                  // current features
                  generator->createFeatures(features, tokens, index, preds);

                  // previous features
                  for (int i = 1; i < prevWindowSize + 1; i++)
                  {
                    if (index - i >= 0)
                    {

                      std::vector<std::string> prevFeatures = std::vector<std::string>();

                      generator->createFeatures(prevFeatures, tokens, index - i, preds);

                      for (std::vector<std::string>::const_iterator it = prevFeatures.begin(); it != prevFeatures.end(); ++it)
                      {
                        features.push_back(PREV_PREFIX + i + *it);
                      }
                    }
                  }

                  // next features
                  for (int i = 1; i < nextWindowSize + 1; i++)
                  {
                    if (i + index < sizeof(tokens) / sizeof(tokens[0]))
                    {

                      std::vector<std::string> nextFeatures = std::vector<std::string>();

                      generator->createFeatures(nextFeatures, tokens, index + i, preds);

                      for (std::vector<std::string>::const_iterator it = nextFeatures.begin(); it != nextFeatures.end(); ++it)
                      {
                        features.push_back(NEXT_PREFIX + i + *it);
                      }
                    }
                  }
                }

                void WindowFeatureGenerator::updateAdaptiveData(std::string tokens[], std::string outcomes[])
                {
                  generator->updateAdaptiveData(tokens, outcomes);
                }

                void WindowFeatureGenerator::clearAdaptiveData()
                {
                    generator->clearAdaptiveData();
                }

                std::string WindowFeatureGenerator::ToString()
                {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                  return __super::toString() + ": Prev windwow size: " + prevWindowSize + ", Next window size: " + nextWindowSize;
                }
            }
        }
    }
}
