#include "SequenceStreamEventStream.h"

namespace opennlp
{
    namespace model
    {

        SequenceStreamEventStream::SequenceStreamEventStream(SequenceStream *sequenceStream)
        {
          InitializeInstanceFields();
          this->sequenceIterator = sequenceStream->begin();
        }

        bool SequenceStreamEventStream::hasNext()
        {
          if (events != 0 && eventIndex < events->length)
          {
            return true;
          }
          else
          {
            if (sequenceIterator->hasNext())
            {
              Sequence *s = sequenceIterator->next();
              eventIndex = 0;
              events = s->getEvents();
              return true;
            }
            else
            {
              return false;
            }
          }
        }

        opennlp::model::Event *SequenceStreamEventStream::next()
        {
          return events[eventIndex++];
        }

        void SequenceStreamEventStream::remove()
        {
          throw UnsupportedOperationException();
        }

        void SequenceStreamEventStream::InitializeInstanceFields()
        {
            eventIndex = -1;
        }
    }
}
