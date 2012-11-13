#include "ComparableEvent.h"
#include "StringBuffer.h"

namespace opennlp
{
    namespace model
    {

        ComparableEvent::ComparableEvent(int oc, int pids[], float values[])
        {
          InitializeInstanceFields();
          outcome = oc;
          if (values == 0)
          {
            Arrays::sort(pids);
          }
          else
          {
            sort(pids, values);
          }
          this->values = values; // needs to be sorted like pids
          predIndexes = pids;
        }

        ComparableEvent::ComparableEvent(int oc, int pids[])
        {
          InitializeInstanceFields();
        }

        int ComparableEvent::compareTo(void *o)
        {
          ComparableEvent *ce = static_cast<ComparableEvent*>(o);
          if (outcome < ce->outcome)
            return -1;
          else if (outcome > ce->outcome)
            return 1;

          int smallerLength = (predIndexes->length > ce->predIndexes->length ? ce->predIndexes->length : predIndexes->length);

          for (int i = 0; i < smallerLength; i++)
          {
            if (predIndexes[i] < ce->predIndexes[i])
              return -1;
            else if (predIndexes[i] > ce->predIndexes[i])
              return 1;
            if (values != 0 && ce->values != 0)
            {
              if (values[i] < ce->values[i])
                return -1;
              else if (values[i] > ce->values[i])
                return 1;
            }
            else if (values != 0)
            {
              if (values[i] < 1)
                return -1;
              else if (values[i] > 1)
                return 1;
            }
            else if (ce->values != 0)
            {
              if (1 < ce->values[i])
                return -1;
              else if (1 > ce->values[i])
                return 1;
            }
          }

          if (predIndexes->length < ce->predIndexes->length)
            return -1;
          else if (predIndexes->length > ce->predIndexes->length)
            return 1;

          return 0;
        }

        std::string ComparableEvent::ToString()
        {
          StringBuffer *s = (new StringBuffer())->append(outcome)->append(":");
          for (int i = 0; i < predIndexes->length; i++)
          {
            s->append(" ")->append(predIndexes[i]);
            if (values != 0)
            {
              s->append("=")->append(values[i]);
            }
          }
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
          return s->toString();
        }

        void ComparableEvent::sort(int pids[], float values[])
        {
          for (int mi = 0; mi < sizeof(pids) / sizeof(pids[0]); mi++)
          {
            int min = mi;
            for (int pi = mi + 1; pi < sizeof(pids) / sizeof(pids[0]); pi++)
            {
              if (pids[min] > pids[pi])
              {
                min = pi;
              }
            }
            int pid = pids[mi];
            pids[mi] = pids[min];
            pids[min] = pid;
            float val = values[mi];
            values[mi] = values[min];
            values[min] = val;
          }
        }

        void ComparableEvent::InitializeInstanceFields()
        {
            seen = 1;
        }
    }
}
