#include "SentenceFeatureGenerator.h"

namespace opennlp
{
    namespace tools
    {
        namespace util
        {
            namespace featuregen
            {

                SentenceFeatureGenerator::SentenceFeatureGenerator(bool isGenerateFirstWordFeature, bool isGenerateLastWordFeature) : isGenerateFirstWordFeature(isGenerateFirstWordFeature), isGenerateLastWordFeature(isGenerateLastWordFeature)
                {
                }

                void SentenceFeatureGenerator::createFeatures(std::vector<std::string> &features, std::string tokens[], int index, std::string previousOutcomes[])
                {

                  if (isGenerateFirstWordFeature && index == 0)
                  {
                    features.push_back("S=begin");
                  }

                  if (isGenerateLastWordFeature && sizeof(tokens) / sizeof(tokens[0]) == index + 1)
                  {
                    features.push_back("S=end");
                  }
                }
            }
        }
    }
}
