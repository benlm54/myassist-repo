#include "NameEvaluationErrorListener.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace namefind
            {
                using opennlp::tools::cmdline::EvaluationErrorPrinter;
                using opennlp::tools::namefind::NameSample;
                using opennlp::tools::namefind::TokenNameFinderEvaluationMonitor;
                using opennlp::tools::util::eval::EvaluationMonitor;

                NameEvaluationErrorListener::NameEvaluationErrorListener() : opennlp.tools.cmdline.EvaluationErrorPrinter<opennlp.tools.namefind.NameSample>(System.err)
                {
                }

                NameEvaluationErrorListener::NameEvaluationErrorListener(OutputStream *outputStream) : opennlp.tools.cmdline.EvaluationErrorPrinter<opennlp.tools.namefind.NameSample>(outputStream)
                {
                }

                void NameEvaluationErrorListener::missclassified(NameSample *reference, NameSample *prediction)
                {
                  printError(reference->getNames(), prediction->getNames(), reference, prediction, reference->getSentence());
                }
            }
        }
    }
}
