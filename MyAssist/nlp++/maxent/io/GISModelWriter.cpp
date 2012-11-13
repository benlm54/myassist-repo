#include "GISModelWriter.h"
#include "model/IndexHashTable.h"

namespace opennlp
{
    namespace maxent
    {
        namespace io
        {
            using opennlp::model::AbstractModel;
            using opennlp::model::AbstractModelWriter;
            using opennlp::model::ComparablePredicate;
            using opennlp::model::Context;
            using opennlp::model::IndexHashTable;

            GISModelWriter::GISModelWriter(AbstractModel *model)
            {

//ORIGINAL LINE: Object[] data = model.getDataStructures();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              void *data = model->getDataStructures();

              PARAMS = static_cast<Context[]>(data[0]);
              IndexHashTable<std::string> *pmap = static_cast<IndexHashTable<std::string>*>(data[1]);
              OUTCOME_LABELS = static_cast<std::string[]>(data[2]);
              CORRECTION_CONSTANT = (static_cast<int>(data[3]));
              CORRECTION_PARAM = (static_cast<double>(data[4]));

              PRED_LABELS = new std::string[pmap->size()];
              pmap->toArray(PRED_LABELS);
            }

            void GISModelWriter::persist() throw(IOException)
            {

              // the type of model (GIS)
              writeUTF("GIS");

              // the value of the correction constant
              writeInt(CORRECTION_CONSTANT);

              // the value of the correction constant
              writeDouble(CORRECTION_PARAM);

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
              std::vector compressed = compressOutcomes(sorted);

              writeInt(compressed.size());

              for (int i = 0; i < compressed.size(); i++)
              {
                std::vector a = static_cast<std::vector>(compressed[i]);
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                writeUTF(a.size() + (static_cast<ComparablePredicate*>(a[0]))->toString());
              }

              // the mapping from predicate names to their integer indexes
              writeInt(PARAMS->length);

              for (int i = 0; i < sorted->length; i++)
                writeUTF(sorted[i]->name);

              // write out the parameters
              for (int i = 0; i < sorted->length; i++)
                for (int j = 0; j < sorted[i]->params->length; j++)
                  writeDouble(sorted[i]->params[j]);

              close();
            }

            ComparablePredicate *GISModelWriter::sortValues()
            {

              ComparablePredicate sortPreds[PARAMS->length];

              int numParams = 0;
              for (int pid = 0; pid < PARAMS->length; pid++)
              {
//ORIGINAL LINE: int[] predkeys = PARAMS[pid].getOutcomes();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                int *predkeys = PARAMS[pid]->getOutcomes();
                // Arrays.sort(predkeys);
                int numActive = predkeys->length;
//ORIGINAL LINE: int[] activeOutcomes = predkeys;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                int *activeOutcomes = predkeys;
//ORIGINAL LINE: double[] activeParams = PARAMS[pid].getParameters();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                double *activeParams = PARAMS[pid]->getParameters();

                numParams += numActive;
                /*
                 * double[] activeParams = new double[numActive];
                 * 
                 * int id = 0; for (int i=0; i < predkeys.length; i++) { int oid =
                 * predkeys[i]; activeOutcomes[id] = oid; activeParams[id] =
                 * PARAMS[pid].getParams(oid); id++; }
                 */
                sortPreds[pid] = new ComparablePredicate(PRED_LABELS[pid], activeOutcomes, activeParams);
              }

              Arrays::sort(sortPreds);
              return sortPreds;
            }

            std::vector GISModelWriter::compressOutcomes(ComparablePredicate sorted[])
            {
              ComparablePredicate *cp = sorted[0];
              std::vector outcomePatterns = std::vector();
              std::vector newGroup = std::vector();
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
                  newGroup = std::vector();
                  newGroup.push_back(sorted[i]);
                }
              }
              outcomePatterns.push_back(newGroup);
              return outcomePatterns;
            }
        }
    }
}
