#include "DetailedFMeasureListener.h"
#include "const_iterator.h"
#include "StringBuilder.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            using opennlp::tools::util::Span;
            using opennlp::tools::util::eval::EvaluationMonitor;

            DetailedFMeasureListener<T>::F1Comparator::F1Comparator(DetailedFMeasureListener *outerInstance) : outerInstance(outerInstance)
            {
            }

            int DetailedFMeasureListener<T>::F1Comparator::compare(const std::string &o1, const std::string &o2)
            {
              if (o1 == o2)
                return 0;
              double t1 = 0;
              double t2 = 0;

              if (outerInstance->statsForOutcome->containsKey(o1))
                t1 += outerInstance->statsForOutcome->get(o1)->getFMeasure();
              if (outerInstance->statsForOutcome->containsKey(o2))
                t2 += outerInstance->statsForOutcome->get(o2)->getFMeasure();

              t1 = outerInstance->zeroOrPositive(t1);
              t2 = outerInstance->zeroOrPositive(t2);

              if (t1 + t2 > 0)
              {
                if (t1 > t2)
                  return -1;
                return 1;
              }
              return o1.compare(o2);
            }

            DetailedFMeasureListener<T>::Stats::Stats(DetailedFMeasureListener *outerInstance) : outerInstance(outerInstance)
            {
                InitializeInstanceFields();
            }

            void DetailedFMeasureListener<T>::Stats::incrementFalsePositive()
            {
              falsePositiveCounter++;
            }

            void DetailedFMeasureListener<T>::Stats::incrementTruePositive()
            {
              truePositiveCounter++;
            }

            void DetailedFMeasureListener<T>::Stats::incrementTarget()
            {
              targetCounter++;
            }

            int DetailedFMeasureListener<T>::Stats::getFalsePositives()
            {
              return falsePositiveCounter;
            }

            int DetailedFMeasureListener<T>::Stats::getTruePositives()
            {
              return truePositiveCounter;
            }

            int DetailedFMeasureListener<T>::Stats::getTarget()
            {
              return targetCounter;
            }

            double DetailedFMeasureListener<T>::Stats::getPrecisionScore()
            {
              int tp = getTruePositives();
              int selected = tp + getFalsePositives();
              return selected > 0 ? static_cast<double>(tp) / static_cast<double>(selected): 0;
            }

            double DetailedFMeasureListener<T>::Stats::getRecallScore()
            {
              int target = getTarget();
              int tp = getTruePositives();
              return target > 0 ? static_cast<double>(tp) / static_cast<double>(target): 0;
            }

            double DetailedFMeasureListener<T>::Stats::getFMeasure()
            {

              if (getPrecisionScore() + getRecallScore() > 0)
              {
                return 2 * (getPrecisionScore() * getRecallScore()) / (getPrecisionScore() + getRecallScore());
              }
              else
              {
                // cannot divide by zero, return error code
                return -1;
              }
            }

            void DetailedFMeasureListener<T>::Stats::InitializeInstanceFields()
            {
                falsePositiveCounter = 0;
                truePositiveCounter = 0;
                targetCounter = 0;
            }
        }
    }
}
