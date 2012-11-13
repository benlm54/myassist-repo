#include "Event.h"
#include "StringBuffer.h"

namespace opennlp
{
    namespace model
    {

        Event::Event(const std::string &outcome, std::string context[])
        {
        }

        Event::Event(const std::string &outcome, std::string context[], float values[])
        {
          this->outcome = outcome;
          this->context = context;
          this->values = values;
        }

        std::string Event::getOutcome()
        {
          return outcome;
        }

        std::string *Event::getContext()
        {
          return context;
        }

        float *Event::getValues()
        {
          return values;
        }

        std::string Event::ToString()
        {
          StringBuffer *sb = new StringBuffer();
          sb->append(outcome)->append(" [");
          if (context->length > 0)
          {
            sb->append(context[0]);
            if (values != 0)
            {
              sb->append("=" + values[0]);
            }
          }
          for (int ci = 1;ci < context->length;ci++)
          {
            sb->append(" ")->append(context[ci]);
            if (values != 0)
            {
              sb->append("=" + values[ci]);
            }
          }
          sb->append("]");
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
          return sb->toString();
        }
    }
}
