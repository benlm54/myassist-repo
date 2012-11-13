#include "DictionaryDetokenizer.h"
#include "DetokenizationOperation.h"

namespace opennlp
{
    namespace tools
    {
        namespace tokenize
        {

            DictionaryDetokenizer::DictionaryDetokenizer(DetokenizationDictionary *dict) : dict(dict)
            {
            }

            DetokenizationOperation *DictionaryDetokenizer::detokenize(std::string tokens[])
            {

              DetokenizationOperation operations[sizeof(tokens) / sizeof(tokens[0])];

              Set<std::string> *matchingTokens = std::set<std::string>();

              for (int i = 0; i < sizeof(tokens) / sizeof(tokens[0]); i++)
              {
                DetokenizationDictionary::Operation dictOperation = dict->getOperation(tokens[i]);

                if (dictOperation == 0)
                {
                  operations[i] = Detokenizer::DetokenizationOperation::NO_OPERATION;
                }
                else if (DetokenizationDictionary::MOVE_LEFT::equals(dictOperation))
                {
                  operations[i] = Detokenizer::DetokenizationOperation::MERGE_TO_LEFT;
                }
                else if (DetokenizationDictionary::MOVE_RIGHT::equals(dictOperation))
                {
                  operations[i] = Detokenizer::DetokenizationOperation::MERGE_TO_RIGHT;
                }
                else if (DetokenizationDictionary::RIGHT_LEFT_MATCHING::equals(dictOperation))
                {

                  if (matchingTokens->contains(tokens[i]))
                  {
                    // The token already occurred once, move it to the left
                    // and clear the occurrence flag
                    operations[i] = Detokenizer::DetokenizationOperation::MERGE_TO_LEFT;
                    matchingTokens->remove(tokens[i]);
                  }
                  else
                  {
                    // First time this token is seen, move it to the right
                    // and remember it
                    operations[i] = Detokenizer::DetokenizationOperation::MERGE_TO_RIGHT;
                    matchingTokens->add(tokens[i]);
                  }
                }
                else
                {
                  throw IllegalStateException("Unkown operation: " + dictOperation);
                }
              }

              return operations;
            }
        }
    }
}
