#include "InvalidFormatException.h"
#include "Throwable.h"

namespace opennlp
{
    namespace tools
    {
        namespace util
        {

            InvalidFormatException::InvalidFormatException()
            {
            }

            InvalidFormatException::InvalidFormatException(const std::string &message) : java.io.IOException(message)
            {
            }

            InvalidFormatException::InvalidFormatException(Throwable *t) : java.io.IOException()
            {
              initCause(t);
            }

            InvalidFormatException::InvalidFormatException(const std::string &message, Throwable *t) : java.io.IOException(message)
            {
              initCause(t);
            }
        }
    }
}
