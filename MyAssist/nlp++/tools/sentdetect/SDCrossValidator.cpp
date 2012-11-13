#include "SDCrossValidator.h"
#include "tools/util/eval/CrossValidationPartitioner.h"
#include "tools/sentdetect/SentenceModel.h"
#include "tools/sentdetect/SentenceDetectorME.h"
#include "tools/sentdetect/SentenceDetectorEvaluator.h"

namespace opennlp
{
    namespace tools
    {
        namespace sentdetect
        {
            using opennlp::tools::dictionary::Dictionary;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::TrainingParameters;
            using opennlp::tools::util::eval::CrossValidationPartitioner;
            using opennlp::tools::util::eval::FMeasure;
            using opennlp::tools::util::model::ModelUtil;

            SDCrossValidator::SDCrossValidator(const std::string &languageCode, TrainingParameters *params, Dictionary *abbreviations, ...) : languageCode(languageCode), abbreviations(abbreviations), params(params)
            {
              InitializeInstanceFields();
              this->listeners = listeners;
            }

            SDCrossValidator::SDCrossValidator(const std::string &languageCode, int cutoff, int iterations)
            {
              InitializeInstanceFields();
            }

            SDCrossValidator::SDCrossValidator(const std::string &languageCode, TrainingParameters *params)
            {
              InitializeInstanceFields();
            }

            SDCrossValidator::SDCrossValidator(const std::string &languageCode, int cutoff, int iterations, Dictionary *abbreviations)
            {
              InitializeInstanceFields();
            }

            SDCrossValidator::SDCrossValidator(const std::string &languageCode, TrainingParameters *params, ...)
            {
              InitializeInstanceFields();
            }

            SDCrossValidator::SDCrossValidator(const std::string &languageCode)
            {
              InitializeInstanceFields();
            }

            void SDCrossValidator::evaluate(ObjectStream<SentenceSample*> *samples, int nFolds) throw(IOException)
            {

              CrossValidationPartitioner<SentenceSample*> *partitioner = new CrossValidationPartitioner<SentenceSample*>(samples, nFolds);

             while (partitioner->hasNext())
             {

               CrossValidationPartitioner::TrainingSampleStream<SentenceSample*> *trainingSampleStream = partitioner->next();

                SentenceModel *model;

                model = SentenceDetectorME::train(languageCode, trainingSampleStream, true, abbreviations, params);

                // do testing
                SentenceDetectorEvaluator *evaluator = new SentenceDetectorEvaluator(new SentenceDetectorME(model), listeners);

                evaluator->evaluate(trainingSampleStream->getTestSampleStream());

                fmeasure->mergeInto(evaluator->getFMeasure());
                 partitioner++;
             }
            }

            opennlp::tools::util::eval::FMeasure *SDCrossValidator::getFMeasure()
            {
              return fmeasure;
            }

            void SDCrossValidator::InitializeInstanceFields()
            {
                fmeasure = new opennlp::tools::util::eval::FMeasure();
            }
        }
    }
}
