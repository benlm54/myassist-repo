#include "GenericModelSerializer.h"
#include "model/BinaryFileDataReader.h"
#include "model/GenericModelReader.h"
#include "tools/util/model/ModelUtil.h"

namespace opennlp
{
    namespace tools
    {
        namespace util
        {
            namespace model
            {
                using opennlp::model::AbstractModel;
                using opennlp::model::BinaryFileDataReader;
                using opennlp::model::GenericModelReader;
                using opennlp::tools::util::InvalidFormatException;

                opennlp::model::AbstractModel *GenericModelSerializer::create(InputStream *in_Renamed) throw(IOException, InvalidFormatException)
                {
                  return (new GenericModelReader(new BinaryFileDataReader(in_Renamed)))->getModel();
                }

                void GenericModelSerializer::serialize(AbstractModel *artifact, OutputStream *out) throw(IOException)
                {
                  ModelUtil::writeModel(artifact, out);
                }

                void GenericModelSerializer::register_Renamed(Map<std::string, ArtifactSerializer*> *factories)
                {
                 factories->put("model", new GenericModelSerializer());
                }
            }
        }
    }
}
