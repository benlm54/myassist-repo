#include "UniformPrior.h"

namespace opennlp
{
    namespace model
    {

        void UniformPrior::logPrior(double dist[], int context[], float values[])
        {
          for (int oi = 0;oi < numOutcomes;oi++)
          {
            dist[oi] = r;
          }
        }

        void UniformPrior::logPrior(double dist[], int context[])
        {
          logPrior(dist,context,0);
        }

        void UniformPrior::setLabels(std::string outcomeLabels[], std::string contextLabels[])
        {
          this->numOutcomes = sizeof(outcomeLabels) / sizeof(outcomeLabels[0]);
          r = log(1.0 / numOutcomes);
        }
    }
}
