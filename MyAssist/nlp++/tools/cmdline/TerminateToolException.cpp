#include "TerminateToolException.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {

            TerminateToolException::TerminateToolException(int code, const std::string &message) : code(code), message(message)
            {
            }

            TerminateToolException::TerminateToolException(int code)
            {
            }

            int TerminateToolException::getCode()
            {
              return code;
            }

            std::string TerminateToolException::getMessage()
            {
              return message;
            }
        }
    }
}
