#include "DictionarySerializer.h"
#include "StringBuilder.h"
#include "Attributes.h"
#include "Locator.h"
#include "XMLReader.h"
#include "SAXException.h"
#include "StreamResult.h"
#include "SAXTransformerFactory.h"
#include "TransformerHandler.h"
#include "TransformerConfigurationException.h"
#include "Transformer.h"
#include "AttributesImpl.h"
#include "const_iterator.h"

namespace opennlp
{
    namespace tools
    {
        namespace util
        {
            namespace model
            {
                using opennlp::tools::dictionary::Dictionary;
                using opennlp::tools::util::InvalidFormatException;

                opennlp::tools::dictionary::Dictionary *DictionarySerializer::create(InputStream *in_Renamed) throw(IOException, InvalidFormatException)
                {
                  return new Dictionary(in_Renamed);
                }

                void DictionarySerializer::serialize(Dictionary *dictionary, OutputStream *out) throw(IOException)
                {
                  dictionary->serialize(out);
                }

                void DictionarySerializer::register_Renamed(Map<std::string, ArtifactSerializer*> *factories)
                {
                  factories->put("dictionary", new DictionarySerializer());
                }
            }
        }
    }
}
