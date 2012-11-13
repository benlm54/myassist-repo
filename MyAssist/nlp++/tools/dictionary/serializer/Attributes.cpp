#include "Attributes.h"

namespace opennlp
{
    namespace tools
    {
        namespace dictionary
        {
            namespace serializer
            {

                std::string Attributes::getValue(const std::string &key)
                {
                  return mNameValueMap->get(key);
                }

                void Attributes::setValue(const std::string &key, const std::string &value)
                {

                  if (key == "" || value == "")
                  {
                    throw IllegalArgumentException("null parameters are not allowwd!");
                  }

                  mNameValueMap->put(key, value);
                }

                Iterator<std::string> *Attributes::iterator()
                {
                  return mNameValueMap->keySet()->begin();
                }

                void Attributes::InitializeInstanceFields()
                {
                    mNameValueMap = std::map<std::string, std::string>();
                }
            }
        }
    }
}
