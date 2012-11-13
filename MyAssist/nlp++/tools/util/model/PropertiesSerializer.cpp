#include "PropertiesSerializer.h"

namespace opennlp
{
    namespace tools
    {
        namespace util
        {
            namespace model
            {
                using opennlp::tools::util::InvalidFormatException;

                Properties *PropertiesSerializer::create(InputStream *in_Renamed) throw(IOException, InvalidFormatException)
                {
                  Properties *properties = new Properties();
                  properties->load(in_Renamed);

                  return properties;
                }

                void PropertiesSerializer::serialize(Properties *properties, OutputStream *out) throw(IOException)
                {
                  properties->store(out, "");
                }

                void PropertiesSerializer::register_Renamed(Map<std::string, ArtifactSerializer*> *factories)
                {
                  factories->put("properties", new PropertiesSerializer());
                }
            }
        }
    }
}
