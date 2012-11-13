#include "GIS.h"
#include "maxent/GISTrainer.h"
#include "model/UniformPrior.h"

namespace opennlp
{
    namespace maxent
    {
        using opennlp::model::DataIndexer;
        using opennlp::model::EventStream;
        using opennlp::model::Prior;
        using opennlp::model::UniformPrior;
bool GIS::PRINT_MESSAGES = true;
double GIS::SMOOTHING_OBSERVATION = 0.1;

        opennlp::maxent::GISModel *GIS::trainModel(EventStream *eventStream) throw(IOException)
        {
          return trainModel(eventStream, 100, 0, false, PRINT_MESSAGES);
        }

        opennlp::maxent::GISModel *GIS::trainModel(EventStream *eventStream, bool smoothing) throw(IOException)
        {
          return trainModel(eventStream, 100, 0, smoothing, PRINT_MESSAGES);
        }

        opennlp::maxent::GISModel *GIS::trainModel(EventStream *eventStream, int iterations, int cutoff) throw(IOException)
        {
          return trainModel(eventStream, iterations, cutoff, false, PRINT_MESSAGES);
        }

        opennlp::maxent::GISModel *GIS::trainModel(EventStream *eventStream, int iterations, int cutoff, bool smoothing, bool printMessagesWhileTraining) throw(IOException)
        {
          GISTrainer *trainer = new GISTrainer(printMessagesWhileTraining);
          trainer->setSmoothing(smoothing);
          trainer->setSmoothingObservation(SMOOTHING_OBSERVATION);
          return trainer->trainModel(eventStream, iterations, cutoff);
        }

        opennlp::maxent::GISModel *GIS::trainModel(EventStream *eventStream, int iterations, int cutoff, double sigma) throw(IOException)
        {
          GISTrainer *trainer = new GISTrainer(PRINT_MESSAGES);
          if (sigma > 0)
            trainer->setGaussianSigma(sigma);
          return trainer->trainModel(eventStream, iterations, cutoff);
        }

        opennlp::maxent::GISModel *GIS::trainModel(int iterations, DataIndexer *indexer, bool smoothing)
        {
          return trainModel(iterations, indexer, true, smoothing, 0, 0);
        }

        opennlp::maxent::GISModel *GIS::trainModel(int iterations, DataIndexer *indexer)
        {
          return trainModel(iterations, indexer, true, false, 0, 0);
        }

        opennlp::maxent::GISModel *GIS::trainModel(int iterations, DataIndexer *indexer, Prior *modelPrior, int cutoff)
        {
          return trainModel(iterations, indexer, true, false, modelPrior, cutoff);
        }

        opennlp::maxent::GISModel *GIS::trainModel(int iterations, DataIndexer *indexer, bool printMessagesWhileTraining, bool smoothing, Prior *modelPrior, int cutoff)
        {
          return trainModel(iterations, indexer, printMessagesWhileTraining, smoothing, modelPrior, cutoff, 1);
        }

        opennlp::maxent::GISModel *GIS::trainModel(int iterations, DataIndexer *indexer, bool printMessagesWhileTraining, bool smoothing, Prior *modelPrior, int cutoff, int threads)
        {
          GISTrainer *trainer = new GISTrainer(printMessagesWhileTraining);
          trainer->setSmoothing(smoothing);
          trainer->setSmoothingObservation(SMOOTHING_OBSERVATION);
          if (modelPrior == 0)
          {
            modelPrior = new UniformPrior();
          }

          return trainer->trainModel(iterations, indexer, modelPrior, cutoff, threads);
        }
    }
}
