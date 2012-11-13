#include "TrainingParameters.h"

namespace opennlp
{
    namespace tools
    {
        namespace util
        {

const std::string TrainingParameters::ALGORITHM_PARAM = "Algorithm";
const std::string TrainingParameters::ITERATIONS_PARAM = "Iterations";
const std::string TrainingParameters::CUTOFF_PARAM = "Cutoff";

            TrainingParameters::TrainingParameters()
            {
                InitializeInstanceFields();
            }

            TrainingParameters::TrainingParameters(InputStream *in_Renamed) throw(IOException)
            {

              InitializeInstanceFields();
              Properties *properties = new Properties();
              properties->load(in_Renamed);

              for (Properties::const_iterator entry = properties->begin(); entry != properties->end(); ++entry)
              {
                parameters->put(static_cast<std::string>(entry->getKey()), static_cast<std::string>(entry->getValue()));
              }
            }

            std::string TrainingParameters::algorithm(const std::string &namespace_Renamed)
            {
              return parameters->get(namespace_Renamed + "." + ALGORITHM_PARAM);
            }

            std::string TrainingParameters::algorithm()
            {
              return parameters->get(ALGORITHM_PARAM);
            }

            Map<std::string, std::string> *TrainingParameters::getSettings(const std::string &namespace_Renamed)
            {

              Map<std::string, std::string> *trainingParams = std::map<std::string, std::string>();

              for (Map<std::string, std::string>::const_iterator entry = parameters->begin(); entry != parameters->end(); ++entry)
              {
                std::string key = (*entry)->getKey();

                if (namespace_Renamed != "")
                {
                  std::string prefix = namespace_Renamed + ".";

//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'startsWith' method:
                  if (key.startsWith(prefix))
                  {
                    trainingParams->put(key.substr(prefix.length()), (*entry)->getValue());
                  }
                }
                else
                {
                  if (!key.find(".") != string::npos)
                  {
                    trainingParams->put(key, (*entry)->getValue());
                  }
                }
              }

              return Collections::unmodifiableMap(trainingParams);
            }

            Map<std::string, std::string> *TrainingParameters::getSettings()
            {
              return getSettings(0);
            }

            opennlp::tools::util::TrainingParameters *TrainingParameters::getParameters(const std::string &namespace_Renamed)
            {

              TrainingParameters *params = new TrainingParameters();

              for (Map<std::string, std::string>::const_iterator entry = getSettings(namespace_Renamed)->begin(); entry != getSettings(namespace_Renamed)->end(); ++entry)
              {
                params->put((*entry)->getKey(), (*entry)->getValue());
              }

              return params;
            }

            void TrainingParameters::put(const std::string &namespace_Renamed, const std::string &key, const std::string &value)
            {

              if (namespace_Renamed == "")
              {
                parameters->put(key, value);
              }
              else
              {
                parameters->put(namespace_Renamed + "." + key, value);
              }
            }

            void TrainingParameters::put(const std::string &key, const std::string &value)
            {
              put(0, key, value);
            }

            void TrainingParameters::serialize(OutputStream *out) throw(IOException)
            {
              Properties *properties = new Properties();

              for (Map<std::string, std::string>::const_iterator entry = parameters->begin(); entry != parameters->end(); ++entry)
              {
                properties->put((*entry)->getKey(), (*entry)->getValue());
              }

              properties->store(out, 0);
            }

            void TrainingParameters::InitializeInstanceFields()
            {
                parameters = std::map<std::string, std::string>();
            }
        }
    }
}
