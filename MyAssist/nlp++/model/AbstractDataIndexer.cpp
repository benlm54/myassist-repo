#include "AbstractDataIndexer.h"
#include "model/ComparableEvent.h"

namespace opennlp
{
    namespace model
    {

        int **AbstractDataIndexer::getContexts()
        {
          return contexts;
        }

        int *AbstractDataIndexer::getNumTimesEventsSeen()
        {
          return numTimesEventsSeen;
        }

        int *AbstractDataIndexer::getOutcomeList()
        {
          return outcomeList;
        }

        std::string *AbstractDataIndexer::getPredLabels()
        {
          return predLabels;
        }

        std::string *AbstractDataIndexer::getOutcomeLabels()
        {
          return outcomeLabels;
        }

        int *AbstractDataIndexer::getPredCounts()
        {
          return predCounts;
        }

        int AbstractDataIndexer::sortAndMerge(std::vector eventsToCompare, bool sort)
        {
          int numUniqueEvents = 1;
          numEvents = eventsToCompare.size();
          if (sort)
          {
            Collections::sort(eventsToCompare);
            if (numEvents <= 1)
            {
              return numUniqueEvents; // nothing to do; edge case (see assertion)
            }

            ComparableEvent *ce = static_cast<ComparableEvent*>(eventsToCompare[0]);
            for (int i = 1; i < numEvents; i++)
            {
              ComparableEvent *ce2 = static_cast<ComparableEvent*>(eventsToCompare[i]);

              if (ce->compare(ce2) == 0)
              {
                ce->seen++; // increment the seen count
                eventsToCompare[i] = 0; // kill the duplicate
              }
              else
              {
                ce = ce2; // a new champion emerges...
                numUniqueEvents++; // increment the # of unique events
              }
            }
          }
          else
          {
            numUniqueEvents = eventsToCompare.size();
          }
          if (sort)
              std::cout << "done. Reduced " + numEvents + " events to " + numUniqueEvents + "." << std::endl;

          contexts = new int[numUniqueEvents][];
          outcomeList = new int[numUniqueEvents];
          numTimesEventsSeen = new int[numUniqueEvents];

          for (int i = 0, j = 0; i < numEvents; i++)
          {
            ComparableEvent *evt = static_cast<ComparableEvent*>(eventsToCompare[i]);
            if (0 == evt)
            {
              continue; // this was a dupe, skip over it.
            }
            numTimesEventsSeen[j] = evt->seen;
            outcomeList[j] = evt->outcome;
            contexts[j] = evt->predIndexes;
            ++j;
          }
          return numUniqueEvents;
        }

        int AbstractDataIndexer::getNumEvents()
        {
          return numEvents;
        }

        void AbstractDataIndexer::update(std::string ec[], Set *predicateSet, Map<std::string, int> *counter, int cutoff)
        {
         for (int j = 0; j < sizeof(ec) / sizeof(ec[0]); j++)
         {
           int i = counter->get(ec[j]);
           if (i == 0)
           {
             counter->put(ec[j], 1);
           }
           else
           {
             counter->put(ec[j], i + 1);
           }
           if (!predicateSet->contains(ec[j]) && counter->get(ec[j]) >= cutoff)
           {
             predicateSet->add(ec[j]);
           }
         }
        }

        std::string *AbstractDataIndexer::toIndexedStringArray(Map<std::string, int> *labelToIndexMap)
        {
          const std::string array_Renamed[labelToIndexMap->size()];
          for (Map<std::string, int>::const_iterator label = labelToIndexMap->begin(); label != labelToIndexMap->end(); ++label)
          {
            array_Renamed[labelToIndexMap->get(label->first)] = label->first;
          }
          return array_Renamed;
        }

        float **AbstractDataIndexer::getValues()
        {
          return 0;
        }
    }
}
