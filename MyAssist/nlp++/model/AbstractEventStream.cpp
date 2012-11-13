#include "AbstractEventStream.h"

namespace opennlp
{
    namespace model
    {

        AbstractEventStream::AbstractEventStream()
        {
        }

        void AbstractEventStream::remove()
        {
          throw UnsupportedOperationException();
        }
    }
}
