#include "PerceptronModelWriter.h"
#include "model/IndexHashTable.h"

namespace opennlp
{
    namespace perceptron
    {
        using opennlp::model::AbstractModel;
        using opennlp::model::AbstractModelWriter;
        using opennlp::model::ComparablePredicate;
        using opennlp::model::Context;
        using opennlp::model::IndexHashTable;

        PerceptronModelWriter::PerceptronModelWriter(AbstractModel *model)
        {

//ORIGINAL LINE: Object[] data = model.getDataStructures();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          void *data = model->getDataStructures();
          this->numOutcomes = model->getNumOutcomes();
          PARAMS = static_cast<Context[]>(data[0]);
          IndexHashTable<std::string> *pmap = static_cast<IndexHashTable<std::string>*>(data[1]);
          OUTCOME_LABELS = static_cast<std::string[]>(data[2]);

          PRED_LABELS = new std::string[pmap->size()];
          pmap->toArray(PRED_LABELS);
        }

        ComparablePredicate *PerceptronModelWriter::sortValues()
        {
//ORIGINAL LINE: opennlp.model.ComparablePredicate[] sortPreds;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          ComparablePredicate *sortPreds;
          ComparablePredicate tmpPreds[PARAMS->length];
          int tmpOutcomes[numOutcomes];
          double tmpParams[numOutcomes];
          int numPreds = 0;
          //remove parameters with 0 weight and predicates with no parameters 
          for (int pid = 0; pid < PARAMS->length; pid++)
          {
            int numParams = 0;
//ORIGINAL LINE: double[] predParams = PARAMS[pid].getParameters();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
            double *predParams = PARAMS[pid]->getParameters();
//ORIGINAL LINE: int[] outcomePattern = PARAMS[pid].getOutcomes();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
            int *outcomePattern = PARAMS[pid]->getOutcomes();
            for (int pi = 0;pi < predParams->length;pi++)
            {
              if (predParams[pi] != 0)
              {
                tmpOutcomes[numParams] = outcomePattern[pi];
                tmpParams[numParams] = predParams[pi];
                numParams++;
              }
            }

            int activeOutcomes[numParams];
            double activeParams[numParams];

            for (int pi = 0;pi < numParams;pi++)
            {
              activeOutcomes[pi] = tmpOutcomes[pi];
              activeParams[pi] = tmpParams[pi];
            }
            if (numParams != 0)
            {
              tmpPreds[numPreds] = new ComparablePredicate(PRED_LABELS[pid],activeOutcomes,activeParams);
              numPreds++;
            }
          }
          System::err::println("Compressed " + PARAMS->length + " parameters to " + numPreds);
          sortPreds = new ComparablePredicate[numPreds];
          for (int pid = 0;pid < numPreds;pid++)
          {
            sortPreds[pid] = tmpPreds[pid];
          }
          Arrays::sort(sortPreds);
          return sortPreds;
        }

        std::vector<std::vector<ComparablePredicate*>> PerceptronModelWriter::computeOutcomePatterns(ComparablePredicate sorted[])
        {
          ComparablePredicate *cp = sorted[0];
          std::vector<std::vector<ComparablePredicate*>> outcomePatterns = std::vector<std::vector<ComparablePredicate*>>();
          std::vector<ComparablePredicate*> newGroup = std::vector<ComparablePredicate*>();
          for (int i = 0; i < sizeof(sorted) / sizeof(sorted[0]); i++)
          {
            if (cp->compare(sorted[i]) == 0)
            {
              newGroup.push_back(sorted[i]);
            }
            else
            {
              cp = sorted[i];
              outcomePatterns.push_back(newGroup);
              newGroup = std::vector<ComparablePredicate*>();
              newGroup.push_back(sorted[i]);
            }
          }
          outcomePatterns.push_back(newGroup);
          System::err::println(outcomePatterns.size() + " outcome patterns");
          return outcomePatterns;
        }

        void PerceptronModelWriter::persist() throw(IOException)
        {

          // the type of model (Perceptron)
          writeUTF("Perceptron");

          // the mapping from outcomes to their integer indexes
          writeInt(OUTCOME_LABELS->length);

          for (int i = 0; i < OUTCOME_LABELS->length; i++)
            writeUTF(OUTCOME_LABELS[i]);

          // the mapping from predicates to the outcomes they contributed to.
          // The sorting is done so that we actually can write this out more
          // compactly than as the entire list.
//ORIGINAL LINE: opennlp.model.ComparablePredicate[] sorted = sortValues();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          ComparablePredicate *sorted = sortValues();
          std::vector<std::vector<ComparablePredicate*>> compressed = computeOutcomePatterns(sorted);

          writeInt(compressed.size());

          for (int i = 0; i < compressed.size(); i++)
          {
            std::vector<ComparablePredicate*> a = compressed[i];
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
            writeUTF(a.size() + a[0]->toString());
          }

          // the mapping from predicate names to their integer indexes
          writeInt(sorted->length);

          for (int i = 0; i < sorted->length; i++)
            writeUTF(sorted[i]->name);

          // write out the parameters
          for (int i = 0; i < sorted->length; i++)
            for (int j = 0; j < sorted[i]->params->length; j++)
              writeDouble(sorted[i]->params[j]);

          close();
        }
    }
}
