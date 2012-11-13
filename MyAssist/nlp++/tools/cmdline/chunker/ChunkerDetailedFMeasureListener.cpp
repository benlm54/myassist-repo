#include "ChunkerDetailedFMeasureListener.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace chunker
            {
                using opennlp::tools::chunker::ChunkSample;
                using opennlp::tools::chunker::ChunkerEvaluationMonitor;
                using opennlp::tools::cmdline::DetailedFMeasureListener;
                using opennlp::tools::util::Span;

                Span *ChunkerDetailedFMeasureListener::asSpanArray(ChunkSample *sample)
                {
                  return sample->getPhrasesAsSpanList();
                }
            }
        }
    }
}
