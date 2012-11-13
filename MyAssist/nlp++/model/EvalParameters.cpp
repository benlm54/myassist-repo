#include "EvalParameters.h"

namespace opennlp
{
    namespace model
    {

        EvalParameters::EvalParameters(Context params[], double correctionParam, double correctionConstant, int numOutcomes) : numOutcomes(numOutcomes), constantInverse(1.0 / correctionConstant)
        {
          this->params = params;
          this->correctionParam = correctionParam;
          this->correctionConstant = correctionConstant;
        }

        EvalParameters::EvalParameters(Context params[], int numOutcomes)
        {
        }

        Context *EvalParameters::getParams()
        {
          return params;
        }

        int EvalParameters::getNumOutcomes()
        {
          return numOutcomes;
        }

        double EvalParameters::getCorrectionConstant()
        {
          return correctionConstant;
        }

        double EvalParameters::getConstantInverse()
        {
          return constantInverse;
        }

        double EvalParameters::getCorrectionParam()
        {
          return correctionParam;
        }

        void EvalParameters::setCorrectionParam(double correctionParam)
        {
          this->correctionParam = correctionParam;
        }
    }
}
