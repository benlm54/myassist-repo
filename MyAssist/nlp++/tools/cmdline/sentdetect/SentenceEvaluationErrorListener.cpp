#include "SentenceEvaluationErrorListener.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace sentdetect
            {
                using opennlp::tools::cmdline::EvaluationErrorPrinter;
                using opennlp::tools::sentdetect::SentenceDetectorEvaluationMonitor;
                using opennlp::tools::sentdetect::SentenceSample;
                using opennlp::tools::util::eval::EvaluationMonitor;

                SentenceEvaluationErrorListener::SentenceEvaluationErrorListener() : opennlp.tools.cmdline.EvaluationErrorPrinter<opennlp.tools.sentdetect.SentenceSample>(System.err)
                {
                }

                SentenceEvaluationErrorListener::SentenceEvaluationErrorListener(OutputStream *outputStream) : opennlp.tools.cmdline.EvaluationErrorPrinter<opennlp.tools.sentdetect.SentenceSample>(outputStream)
                {
                }

                void SentenceEvaluationErrorListener::missclassified(SentenceSample *reference, SentenceSample *prediction)
                {
                  printError(reference->getSentences(), prediction->getSentences(), reference, prediction, reference->getDocument());
                }
            }
        }
    }
}
