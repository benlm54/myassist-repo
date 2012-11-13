#include "TrainUtil.h"
#include "model/HashSumEventStream.h"
#include "model/DataIndexer.h"
#include "model/OnePassDataIndexer.h"
#include "model/TwoPassDataIndexer.h"
#include "maxent/GIS.h"
#include "perceptron/PerceptronTrainer.h"
#include "perceptron/SimplePerceptronSequenceTrainer.h"
#include "NumberFormatException.h"

namespace opennlp
{
    namespace model
    {
        using opennlp::perceptron::PerceptronTrainer;
        using opennlp::perceptron::SimplePerceptronSequenceTrainer;
const std::string TrainUtil::ALGORITHM_PARAM = "Algorithm";
const std::string TrainUtil::MAXENT_VALUE = "MAXENT";
const std::string TrainUtil::PERCEPTRON_VALUE = "PERCEPTRON";
const std::string TrainUtil::PERCEPTRON_SEQUENCE_VALUE = "PERCEPTRON_SEQUENCE";
const std::string TrainUtil::CUTOFF_PARAM = "Cutoff";
const std::string TrainUtil::ITERATIONS_PARAM = "Iterations";
const std::string TrainUtil::DATA_INDEXER_PARAM = "DataIndexer";
const std::string TrainUtil::DATA_INDEXER_ONE_PASS_VALUE = "OnePass";
const std::string TrainUtil::DATA_INDEXER_TWO_PASS_VALUE = "TwoPass";

        std::string TrainUtil::getStringParam(Map<std::string, std::string> *trainParams, const std::string &key, const std::string &defaultValue, Map<std::string, std::string> *reportMap)
        {

          std::string valueString = trainParams->get(key);

          if (valueString == "")
            valueString = defaultValue;

          if (reportMap != 0)
            reportMap->put(key, valueString);

          return valueString;
        }

        int TrainUtil::getIntParam(Map<std::string, std::string> *trainParams, const std::string &key, int defaultValue, Map<std::string, std::string> *reportMap)
        {

          std::string valueString = trainParams->get(key);

          if (valueString != "")
            return StringConverterHelper::fromString<int>(valueString);
          else
            return defaultValue;
        }

        double TrainUtil::getDoubleParam(Map<std::string, std::string> *trainParams, const std::string &key, double defaultValue, Map<std::string, std::string> *reportMap)
        {

          std::string valueString = trainParams->get(key);

          if (valueString != "")
            return StringConverterHelper::fromString<double>(valueString);
          else
            return defaultValue;
        }

        bool TrainUtil::getBooleanParam(Map<std::string, std::string> *trainParams, const std::string &key, bool defaultValue, Map<std::string, std::string> *reportMap)
        {

          std::string valueString = trainParams->get(key);

          if (valueString != "")
            return StringConverterHelper::fromString<bool>(valueString);
          else
            return defaultValue;
        }

        bool TrainUtil::isValid(Map<std::string, std::string> *trainParams)
        {

          // TODO: Need to validate all parameters correctly ... error prone?!

          std::string algorithmName = trainParams->get(ALGORITHM_PARAM);

          if (algorithmName != "" && !(MAXENT_VALUE == algorithmName || PERCEPTRON_VALUE == algorithmName || PERCEPTRON_SEQUENCE_VALUE == algorithmName))
          {
            return false;
          }

          try
          {
            std::string cutoffString = trainParams->get(CUTOFF_PARAM);
            if (cutoffString != "")
                StringConverterHelper::fromString<int>(cutoffString);

            std::string iterationsString = trainParams->get(ITERATIONS_PARAM);
            if (iterationsString != "")
                StringConverterHelper::fromString<int>(iterationsString);
          }
          catch (NumberFormatException e)
          {
            return false;
          }

          std::string dataIndexer = trainParams->get(DATA_INDEXER_PARAM);

          if (dataIndexer != "")
          {
            if (!((std::string("OnePass")) == dataIndexer || (std::string("TwoPass")) == dataIndexer))
            {
              return false;
            }
          }

          // TODO: Check data indexing ... 

          return true;
        }

        opennlp::model::AbstractModel *TrainUtil::train(EventStream *events, Map<std::string, std::string> *trainParams, Map<std::string, std::string> *reportMap) throw(IOException)
        {

          if (!isValid(trainParams))
              throw IllegalArgumentException("trainParams are not valid!");

          if (isSequenceTraining(trainParams))
            throw IllegalArgumentException("sequence training is not supported by this method!");

          std::string algorithmName = getStringParam(trainParams, ALGORITHM_PARAM, MAXENT_VALUE, reportMap);

          int iterations = getIntParam(trainParams, ITERATIONS_PARAM, ITERATIONS_DEFAULT, reportMap);

          int cutoff = getIntParam(trainParams, CUTOFF_PARAM, CUTOFF_DEFAULT, reportMap);

          bool sortAndMerge;

          if (MAXENT_VALUE == algorithmName)
              sortAndMerge = true;
          else if (PERCEPTRON_VALUE == algorithmName)
            sortAndMerge = false;
          else
            throw IllegalStateException("Unexpected algorihtm name: " + algorithmName);

          HashSumEventStream *hses = new HashSumEventStream(events);

          std::string dataIndexerName = getStringParam(trainParams, DATA_INDEXER_PARAM, DATA_INDEXER_TWO_PASS_VALUE, reportMap);

          DataIndexer *indexer = 0;

          if (DATA_INDEXER_ONE_PASS_VALUE == dataIndexerName)
          {
            indexer = new OnePassDataIndexer(hses, cutoff, sortAndMerge);
          }
          else if (DATA_INDEXER_TWO_PASS_VALUE == dataIndexerName)
          {
            indexer = new TwoPassDataIndexer(hses, cutoff, sortAndMerge);
          }
          else
          {
            throw IllegalStateException("Unexpected data indexer name: " + dataIndexerName);
          }

          AbstractModel *model;
          if (MAXENT_VALUE == algorithmName)
          {

            int threads = getIntParam(trainParams, "Threads", 1, reportMap);

            model = opennlp::maxent::GIS::trainModel(iterations, indexer, true, false, 0, 0, threads);
          }
          else if (PERCEPTRON_VALUE == algorithmName)
          {
            bool useAverage = getBooleanParam(trainParams, "UseAverage", true, reportMap);

            bool useSkippedAveraging = getBooleanParam(trainParams, "UseSkippedAveraging", false, reportMap);

            // overwrite otherwise it might not work
            if (useSkippedAveraging)
              useAverage = true;

            double stepSizeDecrease = getDoubleParam(trainParams, "StepSizeDecrease", 0, reportMap);

            double tolerance = getDoubleParam(trainParams, "Tolerance", PerceptronTrainer::TOLERANCE_DEFAULT, reportMap);

            PerceptronTrainer *perceptronTrainer = new PerceptronTrainer();
            perceptronTrainer->setSkippedAveraging(useSkippedAveraging);

            if (stepSizeDecrease > 0)
              perceptronTrainer->setStepSizeDecrease(stepSizeDecrease);

            perceptronTrainer->setTolerance(tolerance);

            model = perceptronTrainer->trainModel(iterations, indexer, cutoff, useAverage);
          }
          else
          {
            throw IllegalStateException("Algorithm not supported: " + algorithmName);
          }

          if (reportMap != 0)
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              reportMap->put("Training-Eventhash", hses->calculateHashSum()->toString(16));

          return model;
        }

        bool TrainUtil::isSequenceTraining(Map<std::string, std::string> *trainParams)
        {
          return PERCEPTRON_SEQUENCE_VALUE == trainParams->get(ALGORITHM_PARAM);
        }

        opennlp::model::AbstractModel *TrainUtil::train(SequenceStream *events, Map<std::string, std::string> *trainParams, Map<std::string, std::string> *reportMap) throw(IOException)
        {

          if (!isValid(trainParams))
            throw IllegalArgumentException("trainParams are not valid!");

          if (!isSequenceTraining(trainParams))
            throw IllegalArgumentException("Algorithm must be a sequence algorithm!");

          int iterations = getIntParam(trainParams, ITERATIONS_PARAM, ITERATIONS_DEFAULT, reportMap);
          int cutoff = getIntParam(trainParams, CUTOFF_PARAM, CUTOFF_DEFAULT, reportMap);

          bool useAverage = getBooleanParam(trainParams, "UseAverage", true, reportMap);

          return (new SimplePerceptronSequenceTrainer())->trainModel(iterations, events, cutoff,useAverage);
        }
    }
}
