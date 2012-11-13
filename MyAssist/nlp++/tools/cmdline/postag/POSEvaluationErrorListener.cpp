#include "POSEvaluationErrorListener.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace postag
            {
                using opennlp::tools::cmdline::EvaluationErrorPrinter;
                using opennlp::tools::postag::POSSample;
                using opennlp::tools::postag::POSTaggerEvaluationMonitor;
                using opennlp::tools::util::eval::EvaluationMonitor;

                POSEvaluationErrorListener::POSEvaluationErrorListener() : opennlp.tools.cmdline.EvaluationErrorPrinter<opennlp.tools.postag.POSSample>(System.err)
                {
                }

                POSEvaluationErrorListener::POSEvaluationErrorListener(OutputStream *outputStream) : opennlp.tools.cmdline.EvaluationErrorPrinter<opennlp.tools.postag.POSSample>(outputStream)
                {
                }

                void POSEvaluationErrorListener::missclassified(POSSample *reference, POSSample *prediction)
                {
                  printError(reference->getTags(), prediction->getTags(), reference, prediction, reference->getSentence());
                }
            }
        }
    }
}
