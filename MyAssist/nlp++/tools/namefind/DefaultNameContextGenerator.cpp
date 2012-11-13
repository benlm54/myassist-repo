#include "DefaultNameContextGenerator.h"
#include "tools/namefind/NameFinderME.h"
#include "tools/util/featuregen/FeatureGeneratorUtil.h"

namespace opennlp
{
    namespace tools
    {
        namespace namefind
        {
            using opennlp::tools::util::featuregen::AdaptiveFeatureGenerator;
            using opennlp::tools::util::featuregen::BigramNameFeatureGenerator;
            using opennlp::tools::util::featuregen::CachedFeatureGenerator;
            using opennlp::tools::util::featuregen::FeatureGeneratorUtil;
            using opennlp::tools::util::featuregen::OutcomePriorFeatureGenerator;
            using opennlp::tools::util::featuregen::PreviousMapFeatureGenerator;
            using opennlp::tools::util::featuregen::TokenClassFeatureGenerator;
            using opennlp::tools::util::featuregen::TokenFeatureGenerator;
            using opennlp::tools::util::featuregen::WindowFeatureGenerator;

            DefaultNameContextGenerator::DefaultNameContextGenerator()
            {
            }

            DefaultNameContextGenerator::DefaultNameContextGenerator(...)
            {

              if (featureGenerators != 0)
              {
                this->featureGenerators = featureGenerators;
              }
              else
              {
                // use defaults

                this->featureGenerators = new AdaptiveFeatureGenerator[]{windowFeatures, new PreviousMapFeatureGenerator()};
              }
            }

            void DefaultNameContextGenerator::addFeatureGenerator(AdaptiveFeatureGenerator *generator)
            {
//ORIGINAL LINE: opennlp.tools.util.featuregen.AdaptiveFeatureGenerator generators[] = featureGenerators;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                AdaptiveFeatureGenerator *generators = featureGenerators;

                featureGenerators = new AdaptiveFeatureGenerator[featureGenerators->length + 1];

                System::arraycopy(generators, 0, featureGenerators, 0, generators->length);

                featureGenerators[featureGenerators->length - 1] = generator;
            }

            void DefaultNameContextGenerator::updateAdaptiveData(std::string tokens[], std::string outcomes[])
            {

              if (tokens != 0 && outcomes != 0 && sizeof(tokens) / sizeof(tokens[0]) != sizeof(outcomes) / sizeof(outcomes[0]))
              {
                  throw IllegalArgumentException("The tokens and outcome arrays MUST have the same size!");
              }

              for (int i = 0; i < featureGenerators->length; i++)
              {
                featureGenerators[i]->updateAdaptiveData(tokens, outcomes);
              }
            }

            void DefaultNameContextGenerator::clearAdaptiveData()
            {
              for (int i = 0; i < featureGenerators->length; i++)
              {
                featureGenerators[i]->clearAdaptiveData();
              }
            }

            std::string *DefaultNameContextGenerator::getContext(int index, std::string tokens[], std::string preds[], Object additionalContext[])
            {
              std::vector<std::string> features = std::vector<std::string>();

              for (int i = 0; i < featureGenerators->length; i++)
              {
                featureGenerators[i]->createFeatures(features, tokens, index, preds);
              }

              //previous outcome features
              std::string po = NameFinderME::OTHER;
              std::string ppo = NameFinderME::OTHER;

              if (index > 1)
              {
                ppo = preds[index - 2];
              }

              if (index > 0)
              {
                po = preds[index - 1];
              }
              features.push_back("po=" + po);
              features.push_back("pow=" + po + "," + tokens[index]);
              features.push_back("powf=" + po + "," + FeatureGeneratorUtil::tokenFeature(tokens[index]));
              features.push_back("ppo=" + ppo);

              return features.toArray(new std::string[features.size()]);
            }
        }
    }
}
