#include "DictionaryFeatureGenerator.h"
#include "tools/namefind/DictionaryNameFinder.h"

namespace opennlp
{
    namespace tools
    {
        namespace util
        {
            namespace featuregen
            {
                using opennlp::tools::dictionary::Dictionary;
                using opennlp::tools::namefind::DictionaryNameFinder;

                DictionaryFeatureGenerator::DictionaryFeatureGenerator(Dictionary *dict)
                {
                }

                DictionaryFeatureGenerator::DictionaryFeatureGenerator(const std::string &prefix, Dictionary *dict)
                {
                  setDictionary(prefix,dict);
                }

                void DictionaryFeatureGenerator::setDictionary(Dictionary *dict)
                {
                  setDictionary("",dict);
                }

                void DictionaryFeatureGenerator::setDictionary(const std::string &name, Dictionary *dict)
                {
                  isg = new InSpanGenerator(name, new DictionaryNameFinder(dict));
                }

                void DictionaryFeatureGenerator::createFeatures(std::vector<std::string> &features, std::string tokens[], int index, std::string previousOutcomes[])
                {
                  isg->createFeatures(features, tokens, index, previousOutcomes);
                }
            }
        }
    }
}
