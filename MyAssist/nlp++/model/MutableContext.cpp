#include "MutableContext.h"

namespace opennlp
{
    namespace model
    {

        MutableContext::MutableContext(int outcomePattern[], double parameters[]) : Context(outcomePattern, parameters)
        {
        }

        void MutableContext::setParameter(int outcomeIndex, double value)
        {
          parameters[outcomeIndex] = value;
        }

        void MutableContext::updateParameter(int outcomeIndex, double value)
        {
          parameters[outcomeIndex] += value;
        }

        bool MutableContext::contains(int outcome)
        {
          return (Arrays::binarySearch(outcomes,outcome) >= 0);
        }
    }
}
