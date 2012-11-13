#include "ChunkerCrossValidator.h"
#include "tools/util/eval/CrossValidationPartitioner.h"
#include "tools/chunker/ChunkerME.h"
#include "tools/chunker/ChunkerModel.h"
#include "tools/chunker/DefaultChunkerContextGenerator.h"
#include "tools/chunker/ChunkerEvaluator.h"
#include "tools/chunker/DefaultChunkerSequenceValidator.h"

namespace opennlp
{
    namespace tools
    {
        namespace chunker
        {
            using opennlp::tools::util::InvalidFormatException;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::TrainingParameters;
            using opennlp::tools::util::eval::CrossValidationPartitioner;
            using opennlp::tools::util::eval::FMeasure;
            using opennlp::tools::util::model::ModelUtil;

            ChunkerCrossValidator::ChunkerCrossValidator(const std::string &languageCode, int cutoff, int iterations) : languageCode(languageCode), params(ModelUtil::createTrainingParameters(iterations, cutoff))
            {

              InitializeInstanceFields();

//JAVA TO C++ CONVERTER WARNING: Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
              delete[] listeners;
            }

            ChunkerCrossValidator::ChunkerCrossValidator(const std::string &languageCode, TrainingParameters *params, ...) : languageCode(languageCode), params(params)
            {

              InitializeInstanceFields();
              this->listeners = listeners;
            }

            void ChunkerCrossValidator::evaluate(ObjectStream<ChunkSample*> *samples, int nFolds) throw(IOException, InvalidFormatException, IOException)
            {
              CrossValidationPartitioner<ChunkSample*> *partitioner = new CrossValidationPartitioner<ChunkSample*>(samples, nFolds);

              while (partitioner->hasNext())
              {

                CrossValidationPartitioner::TrainingSampleStream<ChunkSample*> *trainingSampleStream = partitioner->next();

                ChunkerModel *model = ChunkerME::train(languageCode, trainingSampleStream, new DefaultChunkerContextGenerator(), params);

                // do testing
                ChunkerEvaluator *evaluator = new ChunkerEvaluator(new ChunkerME(model, ChunkerME::DEFAULT_BEAM_SIZE, new DefaultChunkerSequenceValidator()), listeners);

                evaluator->evaluate(trainingSampleStream->getTestSampleStream());

                fmeasure->mergeInto(evaluator->getFMeasure());
                  partitioner++;
              }
            }

            opennlp::tools::util::eval::FMeasure *ChunkerCrossValidator::getFMeasure()
            {
              return fmeasure;
            }

            void ChunkerCrossValidator::InitializeInstanceFields()
            {
                fmeasure = new opennlp::tools::util::eval::FMeasure();
            }
        }
    }
}
