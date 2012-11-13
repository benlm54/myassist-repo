#include "BinaryGISModelReader.h"

namespace opennlp
{
    namespace maxent
    {
        namespace io
        {
            using opennlp::model::BinaryFileDataReader;

            BinaryGISModelReader::BinaryGISModelReader(DataInputStream *dis) : GISModelReader(new BinaryFileDataReader(dis))
            {
            }
        }
    }
}
