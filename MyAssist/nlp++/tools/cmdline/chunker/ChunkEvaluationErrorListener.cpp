#include "ChunkEvaluationErrorListener.h"

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
                using opennlp::tools::cmdline::EvaluationErrorPrinter;
                using opennlp::tools::util::eval::EvaluationMonitor;

                ChunkEvaluationErrorListener::ChunkEvaluationErrorListener() : opennlp.tools.cmdline.EvaluationErrorPrinter<opennlp.tools.chunker.ChunkSample>(System.err)
                {
                }

                ChunkEvaluationErrorListener::ChunkEvaluationErrorListener(OutputStream *outputStream) : opennlp.tools.cmdline.EvaluationErrorPrinter<opennlp.tools.chunker.ChunkSample>(outputStream)
                {
                }

                void ChunkEvaluationErrorListener::missclassified(ChunkSample *reference, ChunkSample *prediction)
                {
                  printError(reference->getPhrasesAsSpanList(), prediction->getPhrasesAsSpanList(), reference, prediction, reference->getSentence());
                }
            }
        }
    }
}
