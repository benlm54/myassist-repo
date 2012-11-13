#include "AdditionalContextFeatureGenerator.h"

namespace opennlp
{
    namespace tools
    {
        namespace util
        {
            namespace featuregen
            {

                void AdditionalContextFeatureGenerator::createFeatures(std::vector<std::string> &features, std::string tokens[], int index, std::string preds[])
                {

                  if (additionalContext != 0 && additionalContext->length != 0)
                  {

//ORIGINAL LINE: String[] context = additionalContext[index];
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                    std::string *context = additionalContext[index];

                    for (int i = 0; i < context->length; i++)
                    {
                      features.push_back("ne=" + context[i]);
                    }
                  }
                }

                void AdditionalContextFeatureGenerator::setCurrentContext(std::string context[][])
                {
                  additionalContext = context;
                }
            }
        }
    }
}
