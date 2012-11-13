#include "TokenizerCrossValidator.h"
#include "tools/util/eval/CrossValidationPartitioner.h"
#include "tools/tokenize/TokenizerModel.h"
#include "tools/tokenize/TokenizerME.h"
#include "tools/tokenize/TokenizerEvaluator.h"

namespace opennlp
{
    namespace tools
    {
        namespace tokenize
        {
            using opennlp::tools::dictionary::Dictionary;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::TrainingParameters;
            using opennlp::tools::util::eval::CrossValidationPartitioner;
            using opennlp::tools::util::eval::FMeasure;
            using opennlp::tools::util::model::ModelUtil;

            TokenizerCrossValidator::TokenizerCrossValidator(const std::string &language, Dictionary *abbreviations, bool alphaNumericOptimization, TrainingParameters *params, ...) : language(language), alphaNumericOptimization(alphaNumericOptimization), params(params), abbreviations(abbreviations)
            {
              InitializeInstanceFields();
              this->listeners = listeners;
            }

            TokenizerCrossValidator::TokenizerCrossValidator(const std::string &language, bool alphaNumericOptimization, int cutoff, int iterations)
            {
              InitializeInstanceFields();
            }

            TokenizerCrossValidator::TokenizerCrossValidator(const std::string &language, bool alphaNumericOptimization)
            {
              InitializeInstanceFields();
            }

            TokenizerCrossValidator::TokenizerCrossValidator(const std::string &language, bool alphaNumericOptimization, TrainingParameters *params, ...)
            {
              InitializeInstanceFields();
            }

            void TokenizerCrossValidator::evaluate(ObjectStream<TokenSample*> *samples, int nFolds) throw(IOException)
            {

              CrossValidationPartitioner<TokenSample*> *partitioner = new CrossValidationPartitioner<TokenSample*>(samples, nFolds);

               while (partitioner->hasNext())
               {

                 CrossValidationPartitioner::TrainingSampleStream<TokenSample*> *trainingSampleStream = partitioner->next();

                 // Maybe throws IOException if temporary file handling fails ...
                 TokenizerModel *model;

                model = TokenizerME::train(language, trainingSampleStream, abbreviations, alphaNumericOptimization, params);

                 TokenizerEvaluator *evaluator = new TokenizerEvaluator(new TokenizerME(model), listeners);

                 evaluator->evaluate(trainingSampleStream->getTestSampleStream());
                 fmeasure->mergeInto(evaluator->getFMeasure());
                   partitioner++;
               }
            }

            opennlp::tools::util::eval::FMeasure *TokenizerCrossValidator::getFMeasure()
            {
              return fmeasure;
            }

            void TokenizerCrossValidator::InitializeInstanceFields()
            {
                fmeasure = new opennlp::tools::util::eval::FMeasure();
            }
        }
    }
}
