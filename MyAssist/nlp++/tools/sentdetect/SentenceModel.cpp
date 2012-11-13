#include "SentenceModel.h"
#include "tools/sentdetect/SentenceDetectorME.h"
#include "tools/util/model/ModelUtil.h"
#include "model/GenericModelReader.h"

namespace opennlp
{
    namespace tools
    {
        namespace sentdetect
        {
            using opennlp::model::AbstractModel;
            using opennlp::model::GenericModelReader;
            using opennlp::tools::dictionary::Dictionary;
            using opennlp::tools::util::InvalidFormatException;
            using opennlp::tools::util::model::BaseModel;
            using opennlp::tools::util::model::ModelUtil;
const std::string SentenceModel::COMPONENT_NAME = "SentenceDetectorME";
const std::string SentenceModel::MAXENT_MODEL_ENTRY_NAME = "sent.model";
const std::string SentenceModel::ABBREVIATIONS_ENTRY_NAME = "abbreviations.dictionary";
const std::string SentenceModel::TOKEN_END_PROPERTY = "useTokenEnd";

            SentenceModel::SentenceModel(const std::string &languageCode, AbstractModel *sentModel, bool useTokenEnd, Dictionary *abbreviations, Map<std::string, std::string> *manifestInfoEntries) : opennlp.tools.util.model.BaseModel(COMPONENT_NAME, languageCode, manifestInfoEntries)
            {


              artifactMap->put(MAXENT_MODEL_ENTRY_NAME, sentModel);

//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              setManifestProperty(TOKEN_END_PROPERTY, bool::toString(useTokenEnd));

              // Abbreviations are optional
              if (abbreviations != 0)
                  artifactMap->put(ABBREVIATIONS_ENTRY_NAME, abbreviations);

              checkArtifactMap();
            }

            SentenceModel::SentenceModel(const std::string &languageCode, AbstractModel *sentModel, bool useTokenEnd, Dictionary *abbreviations)
            {
            }

            SentenceModel::SentenceModel(InputStream *in_Renamed) throw(IOException, InvalidFormatException) : opennlp.tools.util.model.BaseModel(COMPONENT_NAME, in)
            {
            }

            void SentenceModel::validateArtifactMap() throw(InvalidFormatException)
            {
              BaseModel::validateArtifactMap();

              if (!(dynamic_cast<AbstractModel*>(artifactMap->get(MAXENT_MODEL_ENTRY_NAME)) != 0))
              {
                throw InvalidFormatException("Unable to find " + MAXENT_MODEL_ENTRY_NAME + " maxent model!");
              }

              if (!ModelUtil::validateOutcomes(getMaxentModel(), SentenceDetectorME::SPLIT, SentenceDetectorME::NO_SPLIT))
              {
                throw InvalidFormatException("The maxent model is not compatible " + "with the sentence detector!");
              }

              if (getManifestProperty(TOKEN_END_PROPERTY) == "")
                throw InvalidFormatException(TOKEN_END_PROPERTY + " is a mandatory property!");

              void *abbreviationsEntry = artifactMap->get(ABBREVIATIONS_ENTRY_NAME);

              if (abbreviationsEntry != 0 && !(dynamic_cast<Dictionary*>(abbreviationsEntry) != 0))
              {
                throw InvalidFormatException("Abbreviations dictionary has wrong type!");
              }
            }

            opennlp::model::AbstractModel *SentenceModel::getMaxentModel()
            {
              return static_cast<AbstractModel*>(artifactMap->get(MAXENT_MODEL_ENTRY_NAME));
            }

            opennlp::tools::dictionary::Dictionary *SentenceModel::getAbbreviations()
            {
              return static_cast<Dictionary*>(artifactMap->get(ABBREVIATIONS_ENTRY_NAME));
            }

            bool SentenceModel::useTokenEnd()
            {
              return StringConverterHelper::fromString<bool>(getManifestProperty(TOKEN_END_PROPERTY));
            }

            void SentenceModel::main(std::string args[]) throw(FileNotFoundException, IOException, InvalidFormatException)
            {
              if (sizeof(args) / sizeof(args[0]) < 3)
              {
                System::err::println("SentenceModel [-abbreviationsDictionary] [-useTokenEnd] languageCode packageName modelName");
                exit(1);
              }

              int ai = 0;

              Dictionary *abbreviations = 0;
              if ((std::string("-abbreviationsDictionary")) == args[ai])
              {
                ai++;
                abbreviations = new Dictionary(new FileInputStream(args[ai++]));
              }

              bool useTokenEnd = false;
              if ((std::string("-useTokenEnd")) == args[ai])
              {
                useTokenEnd = true;
                ai++;
              }

              std::string languageCode = args[ai++];
              std::string packageName = args[ai++];
              std::string modelName = args[ai];

              AbstractModel *model = (new GenericModelReader(new File(modelName)))->getModel();
              SentenceModel *packageModel = new SentenceModel(languageCode, model, useTokenEnd, abbreviations);
              packageModel->serialize(new FileOutputStream(packageName));
            }
        }
    }
}
