#include "DocumentCategorizerME.h"
#include "tools/tokenize/SimpleTokenizer.h"
#include "tools/tokenize/Tokenizer.h"
#include "maxent/GIS.h"
#include "model/TwoPassDataIndexer.h"
#include "model/TrainUtil.h"
#include "tools/util/model/ModelUtil.h"

namespace opennlp
{
    namespace tools
    {
        namespace doccat
        {
            using opennlp::maxent::GIS;
            using opennlp::model::AbstractModel;
            using opennlp::model::MaxentModel;
            using opennlp::model::TrainUtil;
            using opennlp::model::TwoPassDataIndexer;
            using opennlp::tools::tokenize::SimpleTokenizer;
            using opennlp::tools::tokenize::Tokenizer;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::TrainingParameters;
            using opennlp::tools::util::model::ModelUtil;
FeatureGenerator *DocumentCategorizerME::defaultFeatureGenerator = new BagOfWordsFeatureGenerator();

            DocumentCategorizerME::DocumentCategorizerME(DoccatModel *model, ...)
            {
              this->model = model->getChunkerModel();
              this->mContextGenerator = new DocumentCategorizerContextGenerator(featureGenerators);
            }

            DocumentCategorizerME::DocumentCategorizerME(DoccatModel *model)
            {
            }

            DocumentCategorizerME::DocumentCategorizerME(MaxentModel *model)
            {
            }

            DocumentCategorizerME::DocumentCategorizerME(MaxentModel *model, ...)
            {

              this->model = model;
              mContextGenerator = new DocumentCategorizerContextGenerator(featureGenerators);
            }

            double *DocumentCategorizerME::categorize(std::string text[])
            {
              return model->eval(mContextGenerator->getContext(text));
            }

            double *DocumentCategorizerME::categorize(const std::string &documentText)
            {
              Tokenizer *tokenizer = SimpleTokenizer::INSTANCE;
              return categorize(tokenizer->tokenize(documentText));
            }

            std::string DocumentCategorizerME::getBestCategory(double outcome[])
            {
              return model->getBestOutcome(outcome);
            }

            int DocumentCategorizerME::getIndex(const std::string &category)
            {
              return model->getIndex(category);
            }

            std::string DocumentCategorizerME::getCategory(int index)
            {
              return model->getOutcome(index);
            }

            int DocumentCategorizerME::getNumberOfCategories()
            {
              return model->getNumOutcomes();
            }

            std::string DocumentCategorizerME::getAllResults(double results[])
            {
              return model->getAllOutcomes(results);
            }

            opennlp::model::AbstractModel *DocumentCategorizerME::train(DocumentCategorizerEventStream *eventStream) throw(IOException)
            {
             return GIS::trainModel(100, new TwoPassDataIndexer(eventStream, 5));
            }

            opennlp::tools::doccat::DoccatModel *DocumentCategorizerME::train(const std::string &languageCode, ObjectStream<DocumentSample*> *samples, TrainingParameters *mlParams, ...) throw(IOException)
            {

              Map<std::string, std::string> *manifestInfoEntries = std::map<std::string, std::string>();

              AbstractModel *model = TrainUtil::train(new DocumentCategorizerEventStream(samples, featureGenerators), mlParams->getSettings(), manifestInfoEntries);

              return new DoccatModel(languageCode, model, manifestInfoEntries);
            }

            opennlp::tools::doccat::DoccatModel *DocumentCategorizerME::train(const std::string &languageCode, ObjectStream<DocumentSample*> *samples, int cutoff, int iterations, ...) throw(IOException)
            {
              return train(languageCode, samples, ModelUtil::createTrainingParameters(iterations, cutoff), featureGenerators);
            }

            opennlp::tools::doccat::DoccatModel *DocumentCategorizerME::train(const std::string &languageCode, ObjectStream<DocumentSample*> *samples, int cutoff, int iterations) throw(IOException)
            {
              return train(languageCode, samples, cutoff, iterations, defaultFeatureGenerator);
            }

            opennlp::tools::doccat::DoccatModel *DocumentCategorizerME::train(const std::string &languageCode, ObjectStream<DocumentSample*> *samples) throw(IOException)
            {
              return train(languageCode, samples, 5, 100, defaultFeatureGenerator);
            }
        }
    }
}
