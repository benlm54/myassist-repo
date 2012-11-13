#include "SuffixSensitiveGISModelReader.h"
#include "model/AbstractModel.h"
#include "maxent/io/SuffixSensitiveGISModelWriter.h"

namespace opennlp
{
    namespace maxent
    {
        namespace io
        {
            using opennlp::model::AbstractModel;

            SuffixSensitiveGISModelReader::SuffixSensitiveGISModelReader(File *f) throw(IOException) : GISModelReader(f)
            {
            }

            void SuffixSensitiveGISModelReader::main(std::string args[]) throw(IOException)
            {
              AbstractModel *m = (new SuffixSensitiveGISModelReader(new File(args[0])))->getModel();
              (new SuffixSensitiveGISModelWriter(m, new File(args[1])))->persist();
            }
        }
    }
}
