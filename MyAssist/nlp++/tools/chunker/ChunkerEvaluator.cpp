#include "ChunkerEvaluator.h"

namespace opennlp
{
    namespace tools
    {
        namespace chunker
        {
            using opennlp::tools::util::eval::Evaluator;
            using opennlp::tools::util::eval::FMeasure;

            ChunkerEvaluator::ChunkerEvaluator(Chunker *chunker, ...) : opennlp.tools.util.eval.Evaluator<ChunkSample>(listeners)
            {
              InitializeInstanceFields();
              this->chunker = chunker;
            }

            opennlp::tools::chunker::ChunkSample *ChunkerEvaluator::processSample(ChunkSample *reference)
            {
//ORIGINAL LINE: String[] preds = chunker.chunk(reference.getSentence(), reference.getTags());
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              std::string *preds = chunker->chunk(reference->getSentence(), reference->getTags());
              ChunkSample *result = new ChunkSample(reference->getSentence(), reference->getTags(), preds);

              fmeasure->updateScores(reference->getPhrasesAsSpanList(), result->getPhrasesAsSpanList());

              return result;
            }

            opennlp::tools::util::eval::FMeasure *ChunkerEvaluator::getFMeasure()
            {
              return fmeasure;
            }

            void ChunkerEvaluator::InitializeInstanceFields()
            {
                fmeasure = new opennlp::tools::util::eval::FMeasure();
            }
        }
    }
}
