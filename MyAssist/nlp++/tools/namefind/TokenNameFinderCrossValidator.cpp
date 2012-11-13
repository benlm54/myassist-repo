#include "TokenNameFinderCrossValidator.h"
#include "tools/util/eval/CrossValidationPartitioner.h"
#include "tools/namefind/NameFinderME.h"
#include "tools/namefind/TokenNameFinderModel.h"
#include "tools/namefind/TokenNameFinderEvaluator.h"

namespace opennlp
{
    namespace tools
    {
        namespace namefind
        {
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::TrainingParameters;
            using opennlp::tools::util::eval::CrossValidationPartitioner;
            using opennlp::tools::util::eval::FMeasure;
            using opennlp::tools::util::featuregen::AdaptiveFeatureGenerator;
            using opennlp::tools::util::model::ModelUtil;

            TokenNameFinderCrossValidator::TokenNameFinderCrossValidator(const std::string &languageCode, int cutoff, int iterations)
            {
              InitializeInstanceFields();
            }

            TokenNameFinderCrossValidator::TokenNameFinderCrossValidator(const std::string &languageCode, const std::string &type, int cutoff, int iterations) : languageCode(languageCode), params(ModelUtil::createTrainingParameters(iterations, cutoff)), type(type), featureGeneratorBytes(delete[] this->featureGeneratorBytes), resources(Collections::emptyMap<std::string, void*>())
            {
              InitializeInstanceFields();

            }

            TokenNameFinderCrossValidator::TokenNameFinderCrossValidator(const std::string &languageCode, const std::string &type, char featureGeneratorBytes[], Map<std::string, void*> *resources, int iterations, int cutoff) : languageCode(languageCode), params(ModelUtil::createTrainingParameters(iterations, cutoff)), type(type), featureGeneratorBytes(featureGeneratorBytes), resources(resources)
            {
              InitializeInstanceFields();

            }

            TokenNameFinderCrossValidator::TokenNameFinderCrossValidator(const std::string &languageCode, const std::string &type, TrainingParameters *trainParams, char featureGeneratorBytes[], Map<std::string, void*> *resources, ...) : languageCode(languageCode), params(trainParams), type(type), featureGeneratorBytes(featureGeneratorBytes), resources(resources)
            {

              InitializeInstanceFields();


              this->listeners = listeners;
            }

            void TokenNameFinderCrossValidator::evaluate(ObjectStream<NameSample*> *samples, int nFolds) throw(IOException)
            {
              CrossValidationPartitioner<NameSample*> *partitioner = new CrossValidationPartitioner<NameSample*>(samples, nFolds);

              while (partitioner->hasNext())
              {

                CrossValidationPartitioner::TrainingSampleStream<NameSample*> *trainingSampleStream = partitioner->next();

                TokenNameFinderModel *model = opennlp::tools::namefind::NameFinderME::train(languageCode, type, trainingSampleStream, params, featureGeneratorBytes, resources);

                // do testing
                TokenNameFinderEvaluator *evaluator = new TokenNameFinderEvaluator(new NameFinderME(model), listeners);

                evaluator->evaluate(trainingSampleStream->getTestSampleStream());

                fmeasure->mergeInto(evaluator->getFMeasure());
                  partitioner++;
              }
            }

            opennlp::tools::util::eval::FMeasure *TokenNameFinderCrossValidator::getFMeasure()
            {
              return fmeasure;
            }

            void TokenNameFinderCrossValidator::InitializeInstanceFields()
            {
                fmeasure = new opennlp::tools::util::eval::FMeasure();
            }
        }
    }
}
