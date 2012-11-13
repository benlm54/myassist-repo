#include "NameFinderSequenceValidator.h"
#include "tools/namefind/NameFinderME.h"

namespace opennlp
{
    namespace tools
    {
        namespace namefind
        {
            using opennlp::tools::util::SequenceValidator;

            bool NameFinderSequenceValidator::validSequence(int i, std::string inputSequence[], std::string outcomesSequence[], const std::string &outcome)
            {

              // outcome is formatted like "cont" or "sometype-cont", so we
              // can check if it ends with "cont".
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'endsWith' method:
              if (outcome.endsWith(NameFinderME::CONTINUE))
              {

                int li = sizeof(outcomesSequence) / sizeof(outcomesSequence[0]) - 1;

                if (li == -1)
                {
                  return false;
                }
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'endsWith' method:
                else if (outcomesSequence[li].endsWith(NameFinderME::OTHER))
                {
                  return false;
                }
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'endsWith' method:
                else if (outcomesSequence[li].endsWith(NameFinderME::CONTINUE))
                {
                  // if it is continue, we have to check if previous match was of the same type 
                  std::string previousNameType = NameFinderME::extractNameType(outcomesSequence[li]);
                  std::string nameType = NameFinderME::extractNameType(outcome);
                  if (previousNameType != "" || nameType != "")
                  {
                    if (nameType != "")
                    {
                      if (nameType == previousNameType)
                      {
                        return true;
                      }
                    }
                    return false; // outcomes types are not equal
                  }
                }
              }
              return true;
            }
        }
    }
}
