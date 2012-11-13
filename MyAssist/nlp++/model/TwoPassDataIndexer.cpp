#include "TwoPassDataIndexer.h"
#include "model/FileEventStream.h"
#include "model/Event.h"
#include "model/ComparableEvent.h"

namespace opennlp
{
    namespace model
    {

        TwoPassDataIndexer::TwoPassDataIndexer(EventStream *eventStream) throw(IOException)
        {
        }

        TwoPassDataIndexer::TwoPassDataIndexer(EventStream *eventStream, int cutoff) throw(IOException)
        {
        }

        TwoPassDataIndexer::TwoPassDataIndexer(EventStream *eventStream, int cutoff, bool sort) throw(IOException)
        {
          Map<std::string, int> *predicateIndex = std::map<std::string, int>();
          std::vector eventsToCompare;

          std::cout << "Indexing events using cutoff of " + cutoff + "\n" << std::endl;

          std::cout << "\tComputing event counts...  ";
          try
          {
            File *tmp = File::createTempFile("events", 0);
            tmp->deleteOnExit();
            Writer *osw = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(tmp),"UTF8"));
            int numEvents = computeEventCounts(eventStream, osw, predicateIndex, cutoff);
            std::cout << "done. " + numEvents + " events" << std::endl;

            std::cout << "\tIndexing...  ";

            eventsToCompare = index(numEvents, new FileEventStream(tmp), predicateIndex);
            // done with predicates
//JAVA TO C++ CONVERTER WARNING: Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
            delete predicateIndex;
            tmp->delete();
            std::cout << "done." << std::endl;

            if (sort)
            {
              std::cout << "Sorting and merging events... ";
            }
            else
            {
              std::cout << "Collecting events... ";
            }
            sortAndMerge(eventsToCompare,sort);
            std::cout << "Done indexing." << std::endl;
          }
          catch (IOException e)
          {
            System::err::println(e);
          }
        }

        int TwoPassDataIndexer::computeEventCounts(EventStream *eventStream, Writer *eventStore, Map<std::string, int> *predicatesInOut, int cutoff) throw(IOException)
        {
          Map<std::string, int> *counter = std::map<std::string, int>();
          int eventCount = 0;
          Set *predicateSet = std::set();
          while (eventStream->hasNext())
          {
            Event *ev = eventStream->next();
            eventCount++;
            eventStore->write(FileEventStream::toLine(ev));
//ORIGINAL LINE: String[] ec = ev.getContext();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
            std::string *ec = ev->getContext();
            update(ec,predicateSet,counter,cutoff);
              eventStream++;
          }
          predCounts = new int[predicateSet->size()];
          int index = 0;
//JAVA TO C++ CONVERTER TODO TASK: Java iterators are only converted within the context of 'while' and 'for' loops:
          for (Set::const_iterator pi = predicateSet->begin();pi->hasNext();index++)
          {
//JAVA TO C++ CONVERTER TODO TASK: Java iterators are only converted within the context of 'while' and 'for' loops:
            std::string predicate = static_cast<std::string>(pi->next());
            predCounts[index] = counter->get(predicate);
            predicatesInOut->put(predicate,index);
          }
          eventStore->close();
          return eventCount;
        }

        std::vector TwoPassDataIndexer::index(int numEvents, EventStream *es, Map<std::string, int> *predicateIndex) throw(IOException)
        {
          Map<std::string, int> *omap = std::map<std::string, int>();
          int outcomeCount = 0;
          std::vector eventsToCompare = std::vector(numEvents);
          std::vector<int> indexedContext = std::vector<int>();
          while (es->hasNext())
          {
            Event *ev = es->next();
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
              for (int ci = 0;ci < sizeof(cons) / sizeof(cons[0]);ci++)
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
              es++;
          }
          outcomeLabels = toIndexedStringArray(omap);
          predLabels = toIndexedStringArray(predicateIndex);
          return eventsToCompare;
        }
    }
}
