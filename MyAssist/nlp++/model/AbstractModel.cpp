#include "AbstractModel.h"
#include "StringBuffer.h"

namespace opennlp
{
    namespace model
    {

        AbstractModel::AbstractModel(Context params[], std::string predLabels[], IndexHashTable<std::string> *pmap, std::string outcomeNames[])
        {
          this->pmap = pmap;
          this->outcomeNames = outcomeNames;
          this->evalParams = new EvalParameters(params,sizeof(outcomeNames) / sizeof(outcomeNames[0]));
        }

        AbstractModel::AbstractModel(Context params[], std::string predLabels[], std::string outcomeNames[])
        {
          init(predLabels,outcomeNames);
          this->evalParams = new EvalParameters(params,sizeof(outcomeNames) / sizeof(outcomeNames[0]));
        }

        AbstractModel::AbstractModel(Context params[], std::string predLabels[], std::string outcomeNames[], int correctionConstant, double correctionParam)
        {
          init(predLabels,outcomeNames);
          this->evalParams = new EvalParameters(params,correctionParam,correctionConstant,sizeof(outcomeNames) / sizeof(outcomeNames[0]));
        }

        void AbstractModel::init(std::string predLabels[], std::string outcomeNames[])
        {
          this->pmap = new IndexHashTable<std::string>(predLabels, 0.7);
          this->outcomeNames = outcomeNames;
        }

        std::string AbstractModel::getBestOutcome(double ocs[])
        {
            int best = 0;
            for (int i = 1; i < sizeof(ocs) / sizeof(ocs[0]); i++)
                if (ocs[i] > ocs[best])
                    best = i;
            return outcomeNames[best];
        }

        opennlp::model::AbstractModel::ModelType AbstractModel::getModelType()
        {
          return modelType;
        }

        std::string AbstractModel::getAllOutcomes(double ocs[])
        {
            if (sizeof(ocs) / sizeof(ocs[0]) != outcomeNames->length)
            {
                return "The double array sent as a parameter to GISModel.getAllOutcomes() must not have been produced by this model.";
            }
            else
            {
              DecimalFormat *df = new DecimalFormat("0.0000");
              StringBuffer *sb = new StringBuffer(sizeof(ocs) / sizeof(ocs[0])*2);
              sb->append(outcomeNames[0])->append("[")->append(df->format(ocs[0]))->append("]");
              for (int i = 1; i < sizeof(ocs) / sizeof(ocs[0]); i++)
              {
                sb->append("  ")->append(outcomeNames[i])->append("[")->append(df->format(ocs[i]))->append("]");
              }
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              return sb->toString();
            }
        }

        std::string AbstractModel::getOutcome(int i)
        {
            return outcomeNames[i];
        }

        int AbstractModel::getIndex(const std::string &outcome)
        {
            for (int i = 0; i < outcomeNames->length; i++)
            {
                if (outcomeNames[i] == outcome)
                    return i;
            }
            return -1;
        }

        int AbstractModel::getNumOutcomes()
        {
          return (evalParams->getNumOutcomes());
        }

        void *AbstractModel::getDataStructures()
        {
            Object data[5];
            data[0] = evalParams->getParams();
            data[1] = pmap;
            data[2] = outcomeNames;
            data[3] = int(static_cast<int>(evalParams->getCorrectionConstant()));
            data[4] = double(evalParams->getCorrectionParam());
            return data;
        }
    }
}
