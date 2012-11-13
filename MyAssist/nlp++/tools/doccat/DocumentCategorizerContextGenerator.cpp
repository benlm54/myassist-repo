#include "DocumentCategorizerContextGenerator.h"

namespace opennlp
{
    namespace tools
    {
        namespace doccat
        {

            DocumentCategorizerContextGenerator::DocumentCategorizerContextGenerator(...)
            {
              mFeatureGenerators = featureGenerators;
            }

            std::string *DocumentCategorizerContextGenerator::getContext(std::string text[])
            {

              Collection<std::string> *context = std::list<std::string>();

              for (int i = 0; i < mFeatureGenerators->length; i++)
              {
                Collection<std::string> *extractedFeatures = mFeatureGenerators[i]->extractFeatures(text);
                context->addAll(extractedFeatures);
              }

              return context->toArray(new std::string[context->size()]);
            }
        }
    }
}
