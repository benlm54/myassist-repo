#include "DefaultChunkerSequenceValidator.h"

namespace opennlp
{
    namespace tools
    {
        namespace chunker
        {
            using opennlp::tools::util::SequenceValidator;

            bool DefaultChunkerSequenceValidator::validOutcome(const std::string &outcome, const std::string &prevOutcome)
            {
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'startsWith' method:
              if (outcome.startsWith("I-"))
              {
                if (prevOutcome == "")
                {
                  return (false);
                }
                else
                {
                  if (prevOutcome == "O")
                  {
                    return (false);
                  }
                  if (!prevOutcome.substr(2)->equals(outcome.substr(2)))
                  {
                    return (false);
                  }
                }
              }
              return true;
            }

            bool DefaultChunkerSequenceValidator::validOutcome(const std::string &outcome, std::string sequence[])
            {
              std::string prevOutcome = "";
              if (sizeof(sequence) / sizeof(sequence[0]) > 0)
              {
                prevOutcome = sequence[sizeof(sequence) / sizeof(sequence[0]) - 1];
              }
              return validOutcome(outcome,prevOutcome);
            }

            bool DefaultChunkerSequenceValidator::validSequence(int i, std::string sequence[], std::string s[], const std::string &outcome)
            {
              return validOutcome(outcome, s);
            }
        }
    }
}
