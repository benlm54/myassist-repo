#include "OnePassDataIndexer.h"
#include "model/ComparableEvent.h"

namespace opennlp
{
    namespace model
    {

        OnePassDataIndexer::OnePassDataIndexer(EventStream *eventStream) throw(IOException)
        {
        }

        OnePassDataIndexer::OnePassDataIndexer(EventStream *eventStream, int cutoff) throw(IOException)
        {
        }

        OnePassDataIndexer::OnePassDataIndexer(EventStream *eventStream, int cutoff, bool sort) throw(IOException)
        {
          Map<std::string, int> *predicateIndex = std::map<std::string, int>();
          std::list<Event*> events;
          std::vector eventsToCompare;

          std::cout << "Indexing events using cutoff of " + cutoff + "\n" << std::endl;

          std::cout << "\tComputing event counts...  ";
          events = computeEventCounts(eventStream, predicateIndex, cutoff);
          std::cout << "done. " + events.size() + " events" << std::endl;

          std::cout << "\tIndexing...  ";
          eventsToCompare = index(events, predicateIndex);
          // done with event list
          events.clear();
          // done with predicates
//JAVA TO C++ CONVERTER WARNING: Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
          delete predicateIndex;

          std::cout << "done." << std::endl;

          std::cout << "Sorting and merging events... ";
          sortAndMerge(eventsToCompare, sort);
          std::cout << "Done indexing." << std::endl;
        }

        std::list<Event*> OnePassDataIndexer::computeEventCounts(EventStream *eventStream, Map<std::string, int> *predicatesInOut, int cutoff) throw(IOException)
        {
          Set *predicateSet = std::set();
          Map<std::string, int> *counter = std::map<std::string, int>();
          std::list<Event*> events = std::list<Event*>();
          while (eventStream->hasNext())
          {
            Event *ev = eventStream->next();
            events.push_back(ev);
            update(ev->getContext(), predicateSet, counter, cutoff);
              eventStream++;
          }
          predCounts = new int[predicateSet->size()];
          int index = 0;
//JAVA TO C++ CONVERTER TODO TASK: Java iterators are only converted within the context of 'while' and 'for' loops:
          for (Set::const_iterator pi = predicateSet->begin(); pi->hasNext(); index++)
          {
//JAVA TO C++ CONVERTER TODO TASK: Java iterators are only converted within the context of 'while' and 'for' loops:
            std::string predicate = static_cast<std::string>(pi->next());
            predCounts[index] = counter->get(predicate);
            predicatesInOut->put(predicate, index);
          }
          return events;
        }

        std::vector OnePassDataIndexer::index(std::list<Event*> &events, Map<std::string, int> *predicateIndex)
        {
          Map<std::string, int> *omap = std::map<std::string, int>();

          int numEvents = events.size();
          int outcomeCount = 0;
          std::vector eventsToCompare = std::vector(numEvents);
          std::vector<int> indexedContext = std::vector<int>();

          for (int eventIndex = 0; eventIndex < numEvents; eventIndex++)
          {
            Event *ev = static_cast<Event*>(events.pop_front());
//ORIGINAL LINE: String[] econtext = ev.getContext();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
            std::string *econtext = ev->getContext();
            ComparableEvent *ce;

            int ocID;
            std::string oc = ev->getOutcome();

            if (omap->containsKey(oc))
            {
              ocID = omap->get(oc);
            }
            else
            {
              ocID = outcomeCount++;
              omap->put(oc, ocID);
            }

            for (int i = 0; i < econtext->length; i++)
            {
              std::string pred = econtext[i];
              if (predicateIndex->containsKey(pred))
              {
                indexedContext.push_back(predicateIndex->get(pred));
              }
            }

            // drop events with no active features
            if (indexedContext.size() > 0)
            {
              int cons[indexedContext.size()];
              for (int ci = 0; ci < sizeof(cons) / sizeof(cons[0]); ci++)
              {
                cons[ci] = indexedContext[ci];
              }
              ce = new ComparableEvent(ocID, cons);
              eventsToCompare.push_back(ce);
            }
            else
            {
              System::err::println("Dropped event " + ev->getOutcome() + ":" + Arrays::asList(ev->getContext()));
            }
            // recycle the TIntArrayList
            indexedContext.clear();
          }
          outcomeLabels = toIndexedStringArray(omap);
          predLabels = toIndexedStringArray(predicateIndex);
          return eventsToCompare;
        }
    }
}
