#include "ParserChunkerSequenceValidator.h"
#include "tools/parser/chunking/Parser.h"

namespace opennlp
{
    namespace tools
    {
        namespace parser
        {
            using opennlp::tools::chunker::ChunkerModel;
            using opennlp::tools::parser::chunking::Parser;
            using opennlp::tools::util::SequenceValidator;

            ParserChunkerSequenceValidator::ParserChunkerSequenceValidator(ChunkerModel *model)
            {

              continueStartMap = std::map<std::string, std::string>(model->getChunkerModel()->getNumOutcomes());
              for (int oi = 0, on = model->getChunkerModel()->getNumOutcomes(); oi < on; oi++)
              {
                std::string outcome = model->getChunkerModel()->getOutcome(oi);
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'startsWith' method:
                if (outcome.startsWith(Parser::CONT))
                {
                  continueStartMap->put(outcome,Parser::START + outcome.substr(Parser::CONT.length()));
                }
              }
            }

            bool ParserChunkerSequenceValidator::validSequence(int i, std::string inputSequence[], std::string tagList[], const std::string &outcome)
            {
              if (continueStartMap->containsKey(outcome))
              {
                int lti = sizeof(tagList) / sizeof(tagList[0]) - 1;

                if (lti == -1)
                {
                  return false;
                }
                else
                {
                  std::string lastTag = tagList[lti];

                  if (lastTag == outcome)
                  {
                     return true;
                  }

                  if (lastTag == continueStartMap->get(outcome))
                  {
                    return true;
                  }

                  if (lastTag == Parser::OTHER)
                  {
                    return false;
                  }
                  return false;
                }
              }
              return true;
            }
        }
    }
}
