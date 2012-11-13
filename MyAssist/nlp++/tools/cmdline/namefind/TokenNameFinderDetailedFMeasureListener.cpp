#include "TokenNameFinderDetailedFMeasureListener.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace namefind
            {
                using opennlp::tools::cmdline::DetailedFMeasureListener;
                using opennlp::tools::namefind::NameSample;
                using opennlp::tools::namefind::TokenNameFinderEvaluationMonitor;
                using opennlp::tools::util::Span;

                Span *TokenNameFinderDetailedFMeasureListener::asSpanArray(NameSample *sample)
                {
                  return sample->getNames();
                }
            }
        }
    }
}
