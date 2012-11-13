#include "BaseModel.h"
#include "tools/util/model/GenericModelSerializer.h"
#include "tools/util/model/PropertiesSerializer.h"
#include "tools/util/model/DictionarySerializer.h"
#include "Properties.h"
#include "NumberFormatException.h"

namespace opennlp
{
    namespace tools
    {
        namespace util
        {
            namespace model
            {
                using opennlp::tools::util::InvalidFormatException;
                using opennlp::tools::util::Version;
const std::string BaseModel::MANIFEST_ENTRY = "manifest.properties";
const std::string BaseModel::MANIFEST_VERSION_PROPERTY = "Manifest-Version";
const std::string BaseModel::COMPONENT_NAME_PROPERTY = "Component-Name";
const std::string BaseModel::VERSION_PROPERTY = "OpenNLP-Version";
const std::string BaseModel::TIMESTAMP_PROPERTY = "Timestamp";
const std::string BaseModel::LANGUAGE_PROPERTY = "Language";
const std::string BaseModel::TRAINING_CUTOFF_PROPERTY = "Training-Cutoff";
const std::string BaseModel::TRAINING_ITERATIONS_PROPERTY = "Training-Iterations";
const std::string BaseModel::TRAINING_EVENTHASH_PROPERTY = "Training-Eventhash";

                BaseModel::BaseModel(const std::string &componentName, const std::string &languageCode, Map<std::string, std::string> *manifestInfoEntries) : artifactMap(std::map<std::string, void*>()), componentName(componentName)
                {

                  InitializeInstanceFields();
                  if (componentName == "")
                      throw IllegalArgumentException("componentName must not be null!");

                  if (languageCode == "")
                      throw IllegalArgumentException("languageCode must not be null!");



                  createArtifactSerializers(artifactSerializers);

                  Properties *manifest = new Properties();
                  manifest->setProperty(MANIFEST_VERSION_PROPERTY, "1.0");
                  manifest->setProperty(LANGUAGE_PROPERTY, languageCode);
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                  manifest->setProperty(VERSION_PROPERTY, Version::currentVersion()->toString());
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                  manifest->setProperty(TIMESTAMP_PROPERTY, long long::toString(System::currentTimeMillis()));
                  manifest->setProperty(COMPONENT_NAME_PROPERTY, componentName);

                  if (manifestInfoEntries != 0)
                  {
                    for (Map<std::string, std::string>::const_iterator entry = manifestInfoEntries->begin(); entry != manifestInfoEntries->end(); ++entry)
                    {
                      manifest->setProperty((*entry)->getKey(), (*entry)->getValue());
                    }
                  }

                  artifactMap->put(MANIFEST_ENTRY, manifest);
                }

                BaseModel::BaseModel(const std::string &componentName, InputStream *in_Renamed) throw(IOException, InvalidFormatException) : artifactMap(Collections::unmodifiableMap(artifactMap)), componentName(componentName)
                {

                  InitializeInstanceFields();
                  if (componentName == "")
                    throw IllegalArgumentException("componentName must not be null!");

                  if (in_Renamed == 0)
                      throw IllegalArgumentException("in must not be null!");


                  Map<std::string, void*> *artifactMap = std::map<std::string, void*>();

                  createArtifactSerializers(artifactSerializers);

                  ZipInputStream * const zip = new ZipInputStream(in_Renamed);

                  ZipEntry *entry;
                  while ((entry = zip->getNextEntry()) != 0)
                  {

                    std::string extension = getEntryExtension(entry->getName());

                    ArtifactSerializer *factory = artifactSerializers->get(extension);

                    if (factory == 0)
                    {
                      throw InvalidFormatException("Unkown artifact format: " + extension);
                    }

                    artifactMap->put(entry->getName(), factory->create(zip));

                    zip->closeEntry();
                  }


                  validateArtifactMap();
                }

                std::string BaseModel::getEntryExtension(const std::string &entry) throw(InvalidFormatException)
                {
                  int extensionIndex = entry.rfind('.') + 1;

                  if (extensionIndex == -1 || extensionIndex >= entry.length())
                      throw InvalidFormatException("Entry name must have type extension: " + entry);

                  return entry.substr(extensionIndex);
                }

                opennlp::tools::util::model::ArtifactSerializer *BaseModel::getArtifactSerializer(const std::string &resoruceName)
                {
                  std::string extension = "";
                  try
                  {
                    extension = getEntryExtension(resoruceName);
                  }
                  catch (InvalidFormatException e)
                  {
                    throw IllegalStateException(e);
                  }

                  return artifactSerializers->get(extension);
                }

                Map<std::string, ArtifactSerializer*> *BaseModel::createArtifactSerializers()
                {
                  Map<std::string, ArtifactSerializer*> *serializers = std::map<std::string, ArtifactSerializer*>();

                  GenericModelSerializer::register_Renamed(serializers);
                  PropertiesSerializer::register_Renamed(serializers);
                  DictionarySerializer::register_Renamed(serializers);

                  return serializers;
                }

                void BaseModel::createArtifactSerializers(Map<std::string, ArtifactSerializer*> *serializers)
                {
                  serializers->putAll(createArtifactSerializers());
                }

                void BaseModel::validateArtifactMap() throw(InvalidFormatException)
                {
                  if (!(dynamic_cast<Properties*>(artifactMap->get(MANIFEST_ENTRY)) != 0))
                    throw InvalidFormatException("Missing the " + MANIFEST_ENTRY + "!");

                  // First check version, everything else might change in the future
                  std::string versionString = getManifestProperty(VERSION_PROPERTY);

                  if (versionString != "")
                  {
                    Version *version;

                    try
                    {
                      version = Version::parse(versionString);
                    }
                    catch (NumberFormatException e)
                    {
                      throw InvalidFormatException("Unable to parse model version!, e");
                    }

                    // Major and minor version must match, revision might be 
                    if (Version::currentVersion()->getMajor() != version->getMajor() || Version::currentVersion()->getMinor() != version->getMinor())
                    {
                      throw InvalidFormatException("Model version " + version + " is not supported by this (" + Version::currentVersion() + ") version of OpenNLP!");
                    }

                    // Reject loading a snapshot model with a non-snapshot version
                    if (!Version::currentVersion()->isSnapshot() && version->isSnapshot())
                    {
                      throw InvalidFormatException("Model is a snapshot models are not" + "supported by release versions!");
                    }
                  }
                  else
                  {
                    throw InvalidFormatException("Missing " + VERSION_PROPERTY + " property in " + MANIFEST_ENTRY + "!");
                  }

                  if (getManifestProperty(COMPONENT_NAME_PROPERTY) == "")
                    throw InvalidFormatException("Missing " + COMPONENT_NAME_PROPERTY + " property in " + MANIFEST_ENTRY + "!");

                  if (getManifestProperty(COMPONENT_NAME_PROPERTY) != componentName)
                      throw InvalidFormatException("The " + componentName + " cannot load a model for the " + getManifestProperty(COMPONENT_NAME_PROPERTY) + "!");

                  if (getManifestProperty(LANGUAGE_PROPERTY) == "")
                    throw InvalidFormatException("Missing " + LANGUAGE_PROPERTY + " property in " + MANIFEST_ENTRY + "!");
                }

                void BaseModel::checkArtifactMap()
                {
                  try
                  {
                    validateArtifactMap();
                  }
                  catch (InvalidFormatException e)
                  {
                    throw IllegalArgumentException(e->getMessage());
                  }
                }

                std::string BaseModel::getManifestProperty(const std::string &key)
                {
                  Properties *manifest = static_cast<Properties*>(artifactMap->get(MANIFEST_ENTRY));

                  return manifest->getProperty(key);
                }

                void BaseModel::setManifestProperty(const std::string &key, const std::string &value)
                {
                  Properties *manifest = static_cast<Properties*>(artifactMap->get(MANIFEST_ENTRY));

                  manifest->setProperty(key, value);
                }

                std::string BaseModel::getLanguage()
                {
                  return getManifestProperty(LANGUAGE_PROPERTY);
                }

                opennlp::tools::util::Version *BaseModel::getVersion()
                {
                  std::string version = getManifestProperty(VERSION_PROPERTY);

                  return Version::parse(version);
                }

                void BaseModel::serialize(OutputStream *out) throw(IOException)
                {
                  ZipOutputStream *zip = new ZipOutputStream(out);

                  for (Map<std::string, void*>::const_iterator name = artifactMap->begin(); name != artifactMap->end(); ++name)
                  {
                    zip->putNextEntry(new ZipEntry(name->first));

                    ArtifactSerializer *serializer = getArtifactSerializer(name->first);

                    if (serializer == 0)
                    {
                      throw IllegalStateException("Missing serializer for " + name->first);
                    }

                    serializer->serialize(artifactMap->get(name->first), zip);

                    zip->closeEntry();
                  }

                  zip->finish();
                  zip->flush();
                }

                void BaseModel::InitializeInstanceFields()
                {
                    artifactSerializers = std::map<std::string, ArtifactSerializer*>();
                }
            }
        }
    }
}
