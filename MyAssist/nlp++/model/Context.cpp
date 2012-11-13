#include "Context.h"

namespace opennlp
{
    namespace model
    {

        Context::Context(int outcomePattern[], double parameters[])
        {
          this->outcomes = outcomePattern;
          this->parameters = parameters;
        }

        int *Context::getOutcomes()
        {
          return outcomes;
        }

        double *Context::getParameters()
        {
          return parameters;
        }
    }
}
