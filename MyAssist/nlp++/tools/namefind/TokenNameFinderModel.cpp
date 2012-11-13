#include "TokenNameFinderModel.h"
#include "tools/util/model/ModelUtil.h"
#include "tools/util/featuregen/GeneratorFactory.h"
#include "tools/namefind/NameFinderME.h"
#include "Throwable.h"

namespace opennlp
{
    namespace tools
    {
        namespace namefind
        {
            using opennlp::model::AbstractModel;
            using opennlp::model::MaxentModel;
            using opennlp::tools::util::InvalidFormatException;
            using opennlp::tools::util::featuregen::AdaptiveFeatureGenerator;
            using opennlp::tools::util::featuregen::AggregatedFeatureGenerator;
            using opennlp::tools::util::featuregen::FeatureGeneratorResourceProvider;
            using opennlp::tools::util::featuregen::GeneratorFactory;
            using opennlp::tools::util::model::ArtifactSerializer;
            using opennlp::tools::util::model::BaseModel;
            using opennlp::tools::util::model::ModelUtil;

            TokenNameFinderModel::FeatureGeneratorCreationError::FeatureGeneratorCreationError(Throwable *t) : RuntimeException(t)
            {
            }

            char *TokenNameFinderModel::ByteArraySerializer::create(InputStream *in_Renamed) throw(IOException, InvalidFormatException)
            {

              return ModelUtil::read(in_Renamed);
            }

            void TokenNameFinderModel::ByteArraySerializer::serialize(char artifact[], OutputStream *out) throw(IOException)
            {
              out->write(artifact);
            }

const std::string TokenNameFinderModel::COMPONENT_NAME = "NameFinderME";
const std::string TokenNameFinderModel::MAXENT_MODEL_ENTRY_NAME = "nameFinder.model";
const std::string TokenNameFinderModel::GENERATOR_DESCRIPTOR_ENTRY_NAME = "generator.featuregen";

            TokenNameFinderModel::TokenNameFinderModel(const std::string &languageCode, AbstractModel *nameFinderModel, char generatorDescriptor[], Map<std::string, void*> *resources, Map<std::string, std::string> *manifestInfoEntries) : opennlp.tools.util.model.BaseModel(COMPONENT_NAME, languageCode, manifestInfoEntries)
            {


              if (!isModelValid(nameFinderModel))
              {
                throw IllegalArgumentException("Model not compatible with name finder!");
              }

              artifactMap->put(MAXENT_MODEL_ENTRY_NAME, nameFinderModel);

              // TODO: Null check ?!
              if (generatorDescriptor != 0 && sizeof(generatorDescriptor) / sizeof(generatorDescriptor[0]) > 0)
                artifactMap->put(GENERATOR_DESCRIPTOR_ENTRY_NAME, generatorDescriptor);

              // The resource map must not contain key which are already taken
              // like the name finder maxent model name
              if (resources->containsKey(MAXENT_MODEL_ENTRY_NAME) || resources->containsKey(GENERATOR_DESCRIPTOR_ENTRY_NAME))
              {
                throw IllegalArgumentException();
              }

              // TODO: Add checks to not put resources where no serializer exists,
              // make that case fail here, should be done in the BaseModel
              artifactMap->putAll(resources);

              checkArtifactMap();
            }

            TokenNameFinderModel::TokenNameFinderModel(const std::string &languageCode, AbstractModel *nameFinderModel, Map<std::string, void*> *resources, Map<std::string, std::string> *manifestInfoEntries)
            {
            }

            TokenNameFinderModel::TokenNameFinderModel(InputStream *in_Renamed) throw(IOException, InvalidFormatException) : opennlp.tools.util.model.BaseModel(COMPONENT_NAME, in)
            {
            }

            opennlp::model::AbstractModel *TokenNameFinderModel::getNameFinderModel()
            {
              return static_cast<AbstractModel*>(artifactMap->get(MAXENT_MODEL_ENTRY_NAME));
            }

            opennlp::tools::util::featuregen::AdaptiveFeatureGenerator *TokenNameFinderModel::createFeatureGenerators()
            {

//ORIGINAL LINE: byte descriptorBytes[] = (byte[]) artifactMap.get(GENERATOR_DESCRIPTOR_ENTRY_NAME);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              char *descriptorBytes = static_cast<char[]>(artifactMap->get(GENERATOR_DESCRIPTOR_ENTRY_NAME));

              if (descriptorBytes != 0)
              {
                InputStream *descriptorIn = new ByteArrayInputStream(descriptorBytes);

                AdaptiveFeatureGenerator *generator = 0;
                try
                {
                  generator = GeneratorFactory::create(descriptorIn, new FeatureGeneratorResourceProviderAnonymousInnerClassHelper();
                }
                catch (InvalidFormatException e)
                {
                  // It is assumed that the creation of the feature generation does not
                  // fail after it succeeded once during model loading.

                  // But it might still be possible that such an exception is thrown,
                  // in this case the caller should not be forced to handle the exception
                  // and a Runtime Exception is thrown instead.

                  // If the re-creation of the feature generation fails it is assumed
                  // that this can only be caused by a programming mistake and therefore
                  // throwing a Runtime Exception is reasonable

                  throw FeatureGeneratorCreationError(e);
                }
                catch (IOException e)
                {
                  throw IllegalStateException("Reading from mem cannot result in an I/O error");
                }

                return generator;
              }
              else
              {
                return 0;
              }
            }

            void *TokenNameFinderModel::FeatureGeneratorResourceProviderAnonymousInnerClassHelper::getResource(const std::string &key)
            {
              return outerInstance->artifactMap->get(key);
            }

            opennlp::tools::namefind::TokenNameFinderModel *TokenNameFinderModel::updateFeatureGenerator(char descriptor[])
            {

              TokenNameFinderModel *model = new TokenNameFinderModel(getLanguage(), getNameFinderModel(), descriptor, Collections::emptyMap<std::string, void*>(), Collections::emptyMap<std::string, std::string>());

              // TODO: Not so nice!
              model->artifactMap->clear();
              model->artifactMap->putAll(artifactMap);
              model->artifactMap->put(GENERATOR_DESCRIPTOR_ENTRY_NAME, descriptor);

              return model;
            }

            void TokenNameFinderModel::createArtifactSerializers(Map<std::string, ArtifactSerializer*> *serializers)
            {
              BaseModel::createArtifactSerializers(serializers);

              serializers->put("featuregen", new ByteArraySerializer());
            }

            Map<std::string, ArtifactSerializer*> *TokenNameFinderModel::createArtifactSerializers()
            {

              // TODO: Not so nice, because code cannot really be reused by the other create serializer method
              //       Has to be redesigned, we need static access to default serializers
              //       and these should be able to extend during runtime ?! 

              Map<std::string, ArtifactSerializer*> *serializers = BaseModel::createArtifactSerializers();

              serializers->put("featuregen", new ByteArraySerializer());

              return serializers;
            }

            bool TokenNameFinderModel::isModelValid(MaxentModel *model)
            {

              // We should have *optionally* one outcome named "other", some named xyz-start and sometimes 
              // they have a pair xyz-cont. We should not have any other outcome
              // To validate the model we check if we have one outcome named "other", at least
              // one outcome with suffix start. After that we check if all outcomes that ends with
              // "cont" have a pair that ends with "start".
              std::vector<std::string> start = std::vector<std::string>();
              std::vector<std::string> cont = std::vector<std::string>();

              for (int i = 0; i < model->getNumOutcomes(); i++)
              {
                std::string outcome = model->getOutcome(i);
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'endsWith' method:
                if (outcome.endsWith(NameFinderME::START))
                {
                  start.push_back(outcome.substr(0, outcome.length() - NameFinderME::START.length()));
                }
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'endsWith' method:
                else if (outcome.endsWith(NameFinderME::CONTINUE))
                {
                  cont.push_back(outcome.substr(0, outcome.length() - NameFinderME::CONTINUE.length()));
                }
                else if (outcome == NameFinderME::OTHER)
                {
                  // don't fail anymore if couldn't find outcome named OTHER
                }
                else
                {
                  // got unexpected outcome
                  return false;
                }
              }

              if (start.empty())
              {
                return false;
              }
              else
              {
                for (std::vector<std::string>::const_iterator contPreffix = cont.begin(); contPreffix != cont.end(); ++contPreffix)
                {
                  if (!std::find(start.begin(), start.end(), *contPreffix) != start.end())
                  {
                    return false;
                  }
                }
              }

              return true;
            }

            void TokenNameFinderModel::validateArtifactMap() throw(InvalidFormatException)
            {
              BaseModel::validateArtifactMap();

              if (dynamic_cast<AbstractModel*>(artifactMap->get(MAXENT_MODEL_ENTRY_NAME)) != 0)
              {
                AbstractModel *model = static_cast<AbstractModel*>(artifactMap->get(MAXENT_MODEL_ENTRY_NAME));
                isModelValid(model);
              }
              else
              {
                throw InvalidFormatException("Token Name Finder model is incomplete!");
              }
            }
        }
    }
}
