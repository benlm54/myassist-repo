#include "InSpanGenerator.h"

namespace opennlp
{
    namespace tools
    {
        namespace util
        {
            namespace featuregen
            {
                using opennlp::tools::namefind::TokenNameFinder;
                using opennlp::tools::util::Span;

                InSpanGenerator::InSpanGenerator(const std::string &prefix, TokenNameFinder *finder) : prefix(prefix), finder(finder)
                {

                  if (prefix == "")
                      throw IllegalArgumentException("prefix must not be null!");


                  if (finder == 0)
                      throw IllegalArgumentException("finder must not be null!");

                }

                void InSpanGenerator::createFeatures(std::vector<std::string> &features, std::string tokens[], int index, std::string preds[])
                {
                  // cache results for sentence
                  if (currentSentence != tokens)
                  {
                    currentSentence = tokens;
                    currentNames = finder->find(tokens);
                  }

                  // iterate over names and check if a span is contained
                  for (int i = 0; i < currentNames->length; i++)
                  {
                    if (currentNames[i]->contains(index))
                    {
                      // found a span for the current token
                      features.push_back(prefix + ":w=dic");
                      features.push_back(prefix + ":w=dic=" + tokens[index]);

                      // TODO: consider generation start and continuation features

                      break;
                    }
                  }
                }
            }
        }
    }
}
