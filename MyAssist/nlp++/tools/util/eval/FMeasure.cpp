#include "FMeasure.h"

namespace opennlp
{
    namespace tools
    {
        namespace util
        {
            namespace eval
            {

                double FMeasure::getPrecisionScore()
                {
                  return selected > 0 ? static_cast<double>(truePositive) / static_cast<double>(selected): 0;
                }

                double FMeasure::getRecallScore()
                {
                  return target > 0 ? static_cast<double>(truePositive) / static_cast<double>(target): 0;
                }

                double FMeasure::getFMeasure()
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

                void FMeasure::updateScores(Object references[], Object predictions[])
                {

                    truePositive += countTruePositives(references, predictions);
                    selected += sizeof(predictions) / sizeof(predictions[0]);
                    target += sizeof(references) / sizeof(references[0]);
                }

                void FMeasure::mergeInto(FMeasure *measure)
                {
                  this->selected += measure->selected;
                  this->target += measure->target;
                  this->truePositive += measure->truePositive;
                }

                std::string FMeasure::ToString()
                {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                  return "Precision: " + double::toString(getPrecisionScore()) + "\n" + "Recall: " + double::toString(getRecallScore()) + "\n" + "F-Measure: " + double::toString(getFMeasure());
                }

                int FMeasure::countTruePositives(Object references[], Object predictions[])
                {

                  int truePositives = 0;

                  // Note: Maybe a map should be used to improve performance
                  for (int referenceIndex = 0; referenceIndex < sizeof(references) / sizeof(references[0]); referenceIndex++)
                  {

                    void *referenceName = references[referenceIndex];

                    for (int predictedIndex = 0; predictedIndex < sizeof(predictions) / sizeof(predictions[0]); predictedIndex++)
                    {
                      if (referenceName->equals(predictions[predictedIndex]))
                      {
                        truePositives++;
                      }
                    }
                  }

                  return truePositives;
                }

                double FMeasure::precision(Object references[], Object predictions[])
                {

                  if (sizeof(predictions) / sizeof(predictions[0]) > 0)
                  {
                    return countTruePositives(references, predictions) / static_cast<double>(sizeof(predictions) / sizeof(predictions[0]));
                  }
                  else
                  {
                    return double::NaN;
                  }
                }

                double FMeasure::recall(Object references[], Object predictions[])
                {

                  if (sizeof(references) / sizeof(references[0]) > 0)
                  {
                    return countTruePositives(references, predictions) / static_cast<double>(sizeof(references) / sizeof(references[0]));
                  }
                  else
                  {
                      return double::NaN;
                  }
                }
            }
        }
    }
}
