#include "UncloseableInputStream.h"

namespace opennlp
{
    namespace tools
    {
        namespace util
        {
            namespace model
            {

                UncloseableInputStream::UncloseableInputStream(InputStream *in_Renamed) : java.io.FilterInputStream(in)
                {
                }

                void UncloseableInputStream::close() throw(IOException)
                {
                }
            }
        }
    }
}
