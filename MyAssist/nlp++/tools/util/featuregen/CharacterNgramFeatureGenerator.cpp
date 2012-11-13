#include "CharacterNgramFeatureGenerator.h"
#include "tools/ngram/NGramModel.h"
#include "tools/util/StringList.h"
#include "const_iterator.h"

namespace opennlp
{
    namespace tools
    {
        namespace util
        {
            namespace featuregen
            {
                using opennlp::tools::ngram::NGramModel;
                using opennlp::tools::util::StringList;

                CharacterNgramFeatureGenerator::CharacterNgramFeatureGenerator(int minLength, int maxLength) : minLength(minLength), maxLength(maxLength)
                {
                }

                CharacterNgramFeatureGenerator::CharacterNgramFeatureGenerator()
                {
                }

                void CharacterNgramFeatureGenerator::createFeatures(std::vector<std::string> &features, std::string tokens[], int index, std::string preds[])
                {

                  NGramModel *model = new NGramModel();
                  model->add(tokens[index], minLength, maxLength);

//JAVA TO C++ CONVERTER TODO TASK: Java iterators are only converted within the context of 'while' and 'for' loops:
                  for (NGramModel::const_iterator it = model->begin(); it->hasNext();)
                  {

//JAVA TO C++ CONVERTER TODO TASK: Java iterators are only converted within the context of 'while' and 'for' loops:
                    StringList *tokenList = it->next();

                    if (tokenList->size() > 0)
                    {
                      features.push_back("ng=" + tokenList->getToken(0).toLowerCase());
                    }
                  }
                }
            }
        }
    }
}
