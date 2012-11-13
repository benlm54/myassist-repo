#include "SentenceDetectorEvaluator.h"
#include "tools/util/Span.h"

namespace opennlp
{
    namespace tools
    {
        namespace sentdetect
        {
            using opennlp::tools::util::Span;
            using opennlp::tools::util::eval::Evaluator;
            using opennlp::tools::util::eval::FMeasure;

            SentenceDetectorEvaluator::SentenceDetectorEvaluator(SentenceDetector *sentenceDetector, ...) : opennlp.tools.util.eval.Evaluator<SentenceSample>(listeners)
            {
              InitializeInstanceFields();
              this->sentenceDetector = sentenceDetector;
            }

            opennlp::tools::sentdetect::SentenceSample *SentenceDetectorEvaluator::processSample(SentenceSample *sample)
            {
//ORIGINAL LINE: opennlp.tools.util.Span predictions[] = sentenceDetector.sentPosDetect(sample.getDocument());
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              Span *predictions = sentenceDetector->sentPosDetect(sample->getDocument());
//ORIGINAL LINE: opennlp.tools.util.Span[] references = sample.getSentences();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              Span *references = sample->getSentences();

              fmeasure->updateScores(references, predictions);

              return new SentenceSample(sample->getDocument(), predictions);
            }

            opennlp::tools::util::eval::FMeasure *SentenceDetectorEvaluator::getFMeasure()
            {
              return fmeasure;
            }

            void SentenceDetectorEvaluator::InitializeInstanceFields()
            {
                fmeasure = new opennlp::tools::util::eval::FMeasure();
            }
        }
    }
}
