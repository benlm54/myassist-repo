#include "TokenizerModel.h"
#include "tools/tokenize/TokenizerME.h"
#include "tools/util/model/ModelUtil.h"
#include "maxent/io/BinaryGISModelReader.h"

namespace opennlp
{
    namespace tools
    {
        namespace tokenize
        {
            using opennlp::maxent::io::BinaryGISModelReader;
            using opennlp::model::AbstractModel;
            using opennlp::model::MaxentModel;
            using opennlp::tools::dictionary::Dictionary;
            using opennlp::tools::util::InvalidFormatException;
            using opennlp::tools::util::model::BaseModel;
            using opennlp::tools::util::model::ModelUtil;
const std::string TokenizerModel::COMPONENT_NAME = "TokenizerME";
const std::string TokenizerModel::TOKENIZER_MODEL_ENTRY = "token.model";
const std::string TokenizerModel::ABBREVIATIONS_ENTRY_NAME = "abbreviations.dictionary";
const std::string TokenizerModel::USE_ALPHA_NUMERIC_OPTIMIZATION = "useAlphaNumericOptimization";

            TokenizerModel::TokenizerModel(const std::string &language, AbstractModel *tokenizerMaxentModel, Dictionary *abbreviations, bool useAlphaNumericOptimization, Map<std::string, std::string> *manifestInfoEntries) : opennlp.tools.util.model.BaseModel(COMPONENT_NAME, language, manifestInfoEntries)
            {

              artifactMap->put(TOKENIZER_MODEL_ENTRY, tokenizerMaxentModel);

//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              setManifestProperty(USE_ALPHA_NUMERIC_OPTIMIZATION, bool::toString(useAlphaNumericOptimization));

              // Abbreviations are optional
              if (abbreviations != 0)
                artifactMap->put(ABBREVIATIONS_ENTRY_NAME, abbreviations);

              checkArtifactMap();
            }

            TokenizerModel::TokenizerModel(const std::string &language, AbstractModel *tokenizerMaxentModel, bool useAlphaNumericOptimization, Map<std::string, std::string> *manifestInfoEntries)
            {
            }

            TokenizerModel::TokenizerModel(const std::string &language, AbstractModel *tokenizerMaxentModel, bool useAlphaNumericOptimization)
            {
            }

            TokenizerModel::TokenizerModel(InputStream *in_Renamed) throw(IOException, InvalidFormatException) : opennlp.tools.util.model.BaseModel(COMPONENT_NAME, in)
            {
            }

            bool TokenizerModel::isModelCompatible(MaxentModel *model)
            {
              return ModelUtil::validateOutcomes(model, TokenizerME::SPLIT, TokenizerME::NO_SPLIT);
            }

            void TokenizerModel::validateArtifactMap() throw(InvalidFormatException)
            {
              BaseModel::validateArtifactMap();

              if (!(dynamic_cast<AbstractModel*>(artifactMap->get(TOKENIZER_MODEL_ENTRY)) != 0))
              {
                throw InvalidFormatException("Token model is incomplete!");
              }

              if (!isModelCompatible(getMaxentModel()))
              {
                throw InvalidFormatException("The maxent model is not compatible with the tokenizer!");
              }

              if (getManifestProperty(USE_ALPHA_NUMERIC_OPTIMIZATION) == "")
              {
                throw InvalidFormatException("The " + USE_ALPHA_NUMERIC_OPTIMIZATION + " parameter " + "cannot be found!");
              }

              void *abbreviationsEntry = artifactMap->get(ABBREVIATIONS_ENTRY_NAME);

              if (abbreviationsEntry != 0 && !(dynamic_cast<Dictionary*>(abbreviationsEntry) != 0))
              {
                throw InvalidFormatException("Abbreviations dictionary has wrong type!");
              }
            }

            opennlp::model::AbstractModel *TokenizerModel::getMaxentModel()
            {
              return static_cast<AbstractModel*>(artifactMap->get(TOKENIZER_MODEL_ENTRY));
            }

            opennlp::tools::dictionary::Dictionary *TokenizerModel::getAbbreviations()
            {
              return static_cast<Dictionary*>(artifactMap->get(ABBREVIATIONS_ENTRY_NAME));
            }

            bool TokenizerModel::useAlphaNumericOptimization()
            {
              std::string optimization = getManifestProperty(USE_ALPHA_NUMERIC_OPTIMIZATION);

              return StringConverterHelper::fromString<bool>(optimization);
            }

            void TokenizerModel::main(std::string args[]) throw(IOException)
            {
              if (sizeof(args) / sizeof(args[0]) < 3)
              {
                System::err::println("TokenizerModel [-alphaNumericOptimization] languageCode packageName modelName");
                exit(1);
              }

              int ai = 0;

              bool alphaNumericOptimization = false;

              if ((std::string("-alphaNumericOptimization")) == args[ai])
              {
                alphaNumericOptimization = true;
                ai++;
              }

              std::string languageCode = args[ai++];
              std::string packageName = args[ai++];
              std::string modelName = args[ai];

              AbstractModel *model = (new BinaryGISModelReader(new DataInputStream(new FileInputStream(modelName))))->getModel();

              TokenizerModel *packageModel = new TokenizerModel(languageCode, model, alphaNumericOptimization);

              OutputStream *out = 0;
              try
              {
                out = new FileOutputStream(packageName);
                packageModel->serialize(out);
              }
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
              finally
              {
                if (out != 0)
                  out->close();
              }
            }
        }
    }
}
