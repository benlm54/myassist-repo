#include "DoccatModel.h"

namespace opennlp
{
    namespace tools
    {
        namespace doccat
        {
            using opennlp::model::AbstractModel;
            using opennlp::tools::util::InvalidFormatException;
            using opennlp::tools::util::model::BaseModel;
const std::string DoccatModel::COMPONENT_NAME = "DocumentCategorizerME";
const std::string DoccatModel::DOCCAT_MODEL_ENTRY_NAME = "doccat.model";

            DoccatModel::DoccatModel(const std::string &languageCode, AbstractModel *doccatModel, Map<std::string, std::string> *manifestInfoEntries) : opennlp.tools.util.model.BaseModel(COMPONENT_NAME, languageCode, manifestInfoEntries)
            {

              artifactMap->put(DOCCAT_MODEL_ENTRY_NAME, doccatModel);

              checkArtifactMap();
            }

            DoccatModel::DoccatModel(const std::string &languageCode, AbstractModel *doccatModel)
            {
            }

            DoccatModel::DoccatModel(InputStream *in_Renamed) throw(IOException, InvalidFormatException) : opennlp.tools.util.model.BaseModel(COMPONENT_NAME, in)
            {
            }

            void DoccatModel::validateArtifactMap() throw(InvalidFormatException)
            {
              BaseModel::validateArtifactMap();

              if (!(dynamic_cast<AbstractModel*>(artifactMap->get(DOCCAT_MODEL_ENTRY_NAME)) != 0))
              {
                throw InvalidFormatException("Doccat model is incomplete!");
              }
            }

            opennlp::model::AbstractModel *DoccatModel::getChunkerModel()
            {
              return static_cast<AbstractModel*>(artifactMap->get(DOCCAT_MODEL_ENTRY_NAME));
            }
        }
    }
}
