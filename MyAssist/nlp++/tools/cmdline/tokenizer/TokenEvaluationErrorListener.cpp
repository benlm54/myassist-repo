#include "TokenEvaluationErrorListener.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace tokenizer
            {
                using opennlp::tools::cmdline::EvaluationErrorPrinter;
                using opennlp::tools::tokenize::TokenSample;
                using opennlp::tools::tokenize::TokenizerEvaluationMonitor;
                using opennlp::tools::util::eval::EvaluationMonitor;

                TokenEvaluationErrorListener::TokenEvaluationErrorListener() : opennlp.tools.cmdline.EvaluationErrorPrinter<opennlp.tools.tokenize.TokenSample>(System.err)
                {
                }

                TokenEvaluationErrorListener::TokenEvaluationErrorListener(OutputStream *outputStream) : opennlp.tools.cmdline.EvaluationErrorPrinter<opennlp.tools.tokenize.TokenSample>(outputStream)
                {
                }

                void TokenEvaluationErrorListener::missclassified(TokenSample *reference, TokenSample *prediction)
                {
                  printError(reference->getTokenSpans(), prediction->getTokenSpans(), reference, prediction, reference->getText());
                }
            }
        }
    }
}
