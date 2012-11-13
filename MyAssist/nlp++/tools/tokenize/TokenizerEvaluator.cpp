#include "TokenizerEvaluator.h"
#include "tools/util/Span.h"

namespace opennlp
{
    namespace tools
    {
        namespace tokenize
        {
            using opennlp::tools::util::Span;
            using opennlp::tools::util::eval::Evaluator;
            using opennlp::tools::util::eval::FMeasure;

            TokenizerEvaluator::TokenizerEvaluator(Tokenizer *tokenizer, ...) : opennlp.tools.util.eval.Evaluator<TokenSample>(listeners)
            {
              InitializeInstanceFields();
              this->tokenizer = tokenizer;
            }

            opennlp::tools::tokenize::TokenSample *TokenizerEvaluator::processSample(TokenSample *reference)
            {
//ORIGINAL LINE: opennlp.tools.util.Span predictions[] = tokenizer.tokenizePos(reference.getText());
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              Span *predictions = tokenizer->tokenizePos(reference->getText());
              fmeasure->updateScores(reference->getTokenSpans(), predictions);

              return new TokenSample(reference->getText(), predictions);
            }

            opennlp::tools::util::eval::FMeasure *TokenizerEvaluator::getFMeasure()
            {
              return fmeasure;
            }

            void TokenizerEvaluator::InitializeInstanceFields()
            {
                fmeasure = new opennlp::tools::util::eval::FMeasure();
            }
        }
    }
}
