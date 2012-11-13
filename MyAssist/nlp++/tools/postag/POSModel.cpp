#include "POSModel.h"
#include "tools/util/model/UncloseableInputStream.h"
#include "const_iterator.h"

namespace opennlp
{
    namespace tools
    {
        namespace postag
        {
            using opennlp::model::AbstractModel;
            using opennlp::tools::dictionary::Dictionary;
            using opennlp::tools::util::InvalidFormatException;
            using opennlp::tools::util::model::ArtifactSerializer;
            using opennlp::tools::util::model::BaseModel;
            using opennlp::tools::util::model::UncloseableInputStream;

            opennlp::tools::postag::POSDictionary *POSModel::POSDictionarySerializer::create(InputStream *in_Renamed) throw(IOException, InvalidFormatException)
            {
              return POSDictionary::create(new UncloseableInputStream(in_Renamed));
            }

            void POSModel::POSDictionarySerializer::serialize(POSDictionary *artifact, OutputStream *out) throw(IOException)
            {
              artifact->serialize(out);
            }

            void POSModel::POSDictionarySerializer::register_Renamed(Map<std::string, ArtifactSerializer*> *factories)
            {
              factories->put("tagdict", new POSDictionarySerializer());
            }

const std::string POSModel::COMPONENT_NAME = "POSTaggerME";
const std::string POSModel::POS_MODEL_ENTRY_NAME = "pos.model";
const std::string POSModel::TAG_DICTIONARY_ENTRY_NAME = "tags.tagdict";
const std::string POSModel::NGRAM_DICTIONARY_ENTRY_NAME = "ngram.dictionary";

            POSModel::POSModel(const std::string &languageCode, AbstractModel *posModel, POSDictionary *tagDictionary, Dictionary *ngramDict, Map<std::string, std::string> *manifestInfoEntries) : opennlp.tools.util.model.BaseModel(COMPONENT_NAME, languageCode, manifestInfoEntries)
            {


              if (posModel == 0)
                  throw IllegalArgumentException("The maxentPosModel param must not be null!");

              artifactMap->put(POS_MODEL_ENTRY_NAME, posModel);

              if (tagDictionary != 0)
                artifactMap->put(TAG_DICTIONARY_ENTRY_NAME, tagDictionary);

              if (ngramDict != 0)
                artifactMap->put(NGRAM_DICTIONARY_ENTRY_NAME, ngramDict);

              checkArtifactMap();
            }

            POSModel::POSModel(const std::string &languageCode, AbstractModel *posModel, POSDictionary *tagDictionary, Dictionary *ngramDict)
            {
            }

            POSModel::POSModel(InputStream *in_Renamed) throw(IOException, InvalidFormatException) : opennlp.tools.util.model.BaseModel(COMPONENT_NAME, in)
            {
            }

            void POSModel::createArtifactSerializers(Map<std::string, ArtifactSerializer*> *serializers)
            {

              BaseModel::createArtifactSerializers(serializers);

              POSDictionarySerializer::register_Renamed(serializers);
            }

            void POSModel::validateArtifactMap() throw(InvalidFormatException)
            {
              BaseModel::validateArtifactMap();

              if (!(dynamic_cast<AbstractModel*>(artifactMap->get(POS_MODEL_ENTRY_NAME)) != 0))
              {
                throw InvalidFormatException("POS model is incomplete!");
              }

              // Ensure that the tag dictionary is compatible with the model
              void *tagdictEntry = artifactMap->get(TAG_DICTIONARY_ENTRY_NAME);

              if (tagdictEntry != 0)
              {
                if (dynamic_cast<POSDictionary*>(tagdictEntry) != 0)
                {
                  POSDictionary *posDict = static_cast<POSDictionary*>(tagdictEntry);

                  Set<std::string> *dictTags = std::set<std::string>();

                  for (opennlp::tools::postag::POSDictionary::const_iterator word = posDict->begin(); word != posDict->end(); ++word)
                  {
                    Collections::addAll(dictTags, posDict->getTags(word));
                  }

                  Set<std::string> *modelTags = std::set<std::string>();

                  AbstractModel *posModel = getPosModel();

                  for (int i = 0; i < posModel->getNumOutcomes(); i++)
                  {
                    modelTags->add(posModel->getOutcome(i));
                  }

                  if (!modelTags->containsAll(dictTags))
                  {
                    throw InvalidFormatException("Tag dictioinary contains tags " + "which are unkown by the model!");
                  }
                }
                else
                {
                  throw InvalidFormatException("Abbreviations dictionary has wrong type!");
                }
              }

              void *ngramDictEntry = artifactMap->get(NGRAM_DICTIONARY_ENTRY_NAME);

              if (ngramDictEntry != 0 && !(dynamic_cast<Dictionary*>(ngramDictEntry) != 0))
              {
                throw InvalidFormatException("NGram dictionary has wrong type!");
              }
            }

            opennlp::model::AbstractModel *POSModel::getPosModel()
            {
              return static_cast<AbstractModel*>(artifactMap->get(POS_MODEL_ENTRY_NAME));
            }

            opennlp::tools::postag::POSDictionary *POSModel::getTagDictionary()
            {
              return static_cast<POSDictionary*>(artifactMap->get(TAG_DICTIONARY_ENTRY_NAME));
            }

            opennlp::tools::dictionary::Dictionary *POSModel::getNgramDictionary()
            {
              return static_cast<Dictionary*>(artifactMap->get(NGRAM_DICTIONARY_ENTRY_NAME));
            }
        }
    }
}
