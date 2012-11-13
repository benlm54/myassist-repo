#include "ParserModel.h"
#include "tools/util/model/UncloseableInputStream.h"
#include "tools/parser/HeadRules.h"

namespace opennlp
{
    namespace tools
    {
        namespace parser
        {
            using opennlp::model::AbstractModel;
            using opennlp::tools::chunker::ChunkerModel;
            using opennlp::tools::postag::POSModel;
            using opennlp::tools::util::InvalidFormatException;
            using opennlp::tools::util::model::ArtifactSerializer;
            using opennlp::tools::util::model::BaseModel;
            using opennlp::tools::util::model::UncloseableInputStream;

            opennlp::tools::postag::POSModel *ParserModel::POSModelSerializer::create(InputStream *in_Renamed) throw(IOException, InvalidFormatException)
            {
              return new POSModel(new UncloseableInputStream(in_Renamed));
            }

            void ParserModel::POSModelSerializer::serialize(POSModel *artifact, OutputStream *out) throw(IOException)
            {
              artifact->serialize(out);
            }

            opennlp::tools::chunker::ChunkerModel *ParserModel::ChunkerModelSerializer::create(InputStream *in_Renamed) throw(IOException, InvalidFormatException)
            {
              return new ChunkerModel(new UncloseableInputStream(in_Renamed));
            }

            void ParserModel::ChunkerModelSerializer::serialize(ChunkerModel *artifact, OutputStream *out) throw(IOException)
            {
              artifact->serialize(out);
            }

            opennlp::tools::parser::lang::en::HeadRules *ParserModel::HeadRulesSerializer::create(InputStream *in_Renamed) throw(IOException, InvalidFormatException)
            {
              return new opennlp::tools::parser::lang::en::HeadRules(new BufferedReader(new InputStreamReader(in_Renamed, "UTF-8")));
            }

            void ParserModel::HeadRulesSerializer::serialize(opennlp::tools::parser::lang::en::HeadRules *artifact, OutputStream *out) throw(IOException)
            {
              artifact->serialize(new OutputStreamWriter(out, "UTF-8"));
            }

const std::string ParserModel::COMPONENT_NAME = "Parser";
const std::string ParserModel::BUILD_MODEL_ENTRY_NAME = "build.model";
const std::string ParserModel::CHECK_MODEL_ENTRY_NAME = "check.model";
const std::string ParserModel::ATTACH_MODEL_ENTRY_NAME = "attach.model";
const std::string ParserModel::PARSER_TAGGER_MODEL_ENTRY_NAME = "parsertager.postagger";
const std::string ParserModel::CHUNKER_TAGGER_MODEL_ENTRY_NAME = "parserchunker.chunker";
const std::string ParserModel::HEAD_RULES_MODEL_ENTRY_NAME = "head-rules.headrules";
const std::string ParserModel::PARSER_TYPE = "parser-type";

            ParserModel::ParserModel(const std::string &languageCode, AbstractModel *buildModel, AbstractModel *checkModel, AbstractModel *attachModel, POSModel *parserTagger, ChunkerModel *chunkerTagger, opennlp::tools::parser::lang::en::HeadRules *headRules, ParserType modelType, Map<std::string, std::string> *manifestInfoEntries) : opennlp.tools.util.model.BaseModel(COMPONENT_NAME, languageCode, manifestInfoEntries)
            {


              setManifestProperty(PARSER_TYPE, modelType::name());

              artifactMap->put(BUILD_MODEL_ENTRY_NAME, buildModel);

              artifactMap->put(CHECK_MODEL_ENTRY_NAME, checkModel);

              if (CHUNKING::equals(modelType))
              {
                if (attachModel != 0)
                    throw IllegalArgumentException("attachModel must be null for chunking parser!");
              }
              else if (TREEINSERT::equals(modelType))
              {
                if (attachModel == 0)
                  throw IllegalArgumentException("attachModel must not be null!");

                artifactMap->put(ATTACH_MODEL_ENTRY_NAME, attachModel);
              }
              else
              {
                throw IllegalStateException("Unkown ParserType!");
              }

              artifactMap->put(PARSER_TAGGER_MODEL_ENTRY_NAME, parserTagger);

              artifactMap->put(CHUNKER_TAGGER_MODEL_ENTRY_NAME, chunkerTagger);

              artifactMap->put(HEAD_RULES_MODEL_ENTRY_NAME, headRules);

              checkArtifactMap();
            }

            ParserModel::ParserModel(const std::string &languageCode, AbstractModel *buildModel, AbstractModel *checkModel, AbstractModel *attachModel, POSModel *parserTagger, ChunkerModel *chunkerTagger, opennlp::tools::parser::lang::en::HeadRules *headRules, ParserType modelType)
            {
            }

            ParserModel::ParserModel(const std::string &languageCode, AbstractModel *buildModel, AbstractModel *checkModel, POSModel *parserTagger, ChunkerModel *chunkerTagger, opennlp::tools::parser::lang::en::HeadRules *headRules, ParserType type, Map<std::string, std::string> *manifestInfoEntries)
            {
            }

            ParserModel::ParserModel(InputStream *in_Renamed) throw(IOException, InvalidFormatException) : opennlp.tools.util.model.BaseModel(COMPONENT_NAME, in)
            {
            }

            void ParserModel::createArtifactSerializers(Map<std::string, ArtifactSerializer*> *serializers)
            {

              BaseModel::createArtifactSerializers(serializers);

              serializers->put("postagger", new POSModelSerializer());
              serializers->put("chunker", new ChunkerModelSerializer());
              serializers->put("headrules", new HeadRulesSerializer());

            }

            opennlp::tools::parser::ParserType ParserModel::getParserType()
            {
              return PARSE(getManifestProperty(PARSER_TYPE));
            }

            opennlp::model::AbstractModel *ParserModel::getBuildModel()
            {
              return static_cast<AbstractModel*>(artifactMap->get(BUILD_MODEL_ENTRY_NAME));
            }

            opennlp::model::AbstractModel *ParserModel::getCheckModel()
            {
              return static_cast<AbstractModel*>(artifactMap->get(CHECK_MODEL_ENTRY_NAME));
            }

            opennlp::model::AbstractModel *ParserModel::getAttachModel()
            {
              return static_cast<AbstractModel*>(artifactMap->get(ATTACH_MODEL_ENTRY_NAME));
            }

            opennlp::tools::postag::POSModel *ParserModel::getParserTaggerModel()
            {
              return static_cast<POSModel*>(artifactMap->get(PARSER_TAGGER_MODEL_ENTRY_NAME));
            }

            opennlp::tools::chunker::ChunkerModel *ParserModel::getParserChunkerModel()
            {
              return static_cast<ChunkerModel*>(artifactMap->get(CHUNKER_TAGGER_MODEL_ENTRY_NAME));
            }

            opennlp::tools::parser::lang::en::HeadRules *ParserModel::getHeadRules()
            {
              return static_cast<opennlp::tools::parser::lang::en::HeadRules*>(artifactMap->get(HEAD_RULES_MODEL_ENTRY_NAME));
            }

            opennlp::tools::parser::ParserModel *ParserModel::updateBuildModel(AbstractModel *buildModel)
            {
              return new ParserModel(getLanguage(), buildModel, getCheckModel(), getAttachModel(), getParserTaggerModel(), getParserChunkerModel(), getHeadRules(), getParserType());
            }

            opennlp::tools::parser::ParserModel *ParserModel::updateCheckModel(AbstractModel *checkModel)
            {
              return new ParserModel(getLanguage(), getBuildModel(), checkModel, getAttachModel(), getParserTaggerModel(), getParserChunkerModel(), getHeadRules(), getParserType());
            }

            opennlp::tools::parser::ParserModel *ParserModel::updateTaggerModel(POSModel *taggerModel)
            {
              return new ParserModel(getLanguage(), getBuildModel(), getCheckModel(), getAttachModel(), taggerModel, getParserChunkerModel(), getHeadRules(), getParserType());
            }

            opennlp::tools::parser::ParserModel *ParserModel::updateChunkerModel(ChunkerModel *chunkModel)
            {
              return new ParserModel(getLanguage(), getBuildModel(), getCheckModel(), getAttachModel(), getParserTaggerModel(), chunkModel, getHeadRules(), getParserType());
            }

            void ParserModel::validateArtifactMap() throw(InvalidFormatException)
            {
              BaseModel::validateArtifactMap();

              if (!(dynamic_cast<AbstractModel*>(artifactMap->get(BUILD_MODEL_ENTRY_NAME)) != 0))
              {
                throw InvalidFormatException("Missing the build model!");
              }

              ParserType modelType = getParserType();

              if (modelType != 0)
              {
                if (CHUNKING::equals(modelType))
                {
                  if (artifactMap->get(ATTACH_MODEL_ENTRY_NAME) != 0)
                      throw InvalidFormatException("attachModel must be null for chunking parser!");
                }
                else if (TREEINSERT::equals(modelType))
                {
                  if (!(dynamic_cast<AbstractModel*>(artifactMap->get(ATTACH_MODEL_ENTRY_NAME)) != 0))
                    throw InvalidFormatException("attachModel must not be null!");
                }
                else
                {
                  throw InvalidFormatException("Unkown ParserType!");
                }
              }
              else
              {
                throw InvalidFormatException("Missing the parser type property!");
              }

              if (!(dynamic_cast<AbstractModel*>(artifactMap->get(CHECK_MODEL_ENTRY_NAME)) != 0))
              {
                throw InvalidFormatException("Missing the check model!");
              }

              if (!(dynamic_cast<POSModel*>(artifactMap->get(PARSER_TAGGER_MODEL_ENTRY_NAME)) != 0))
              {
                throw InvalidFormatException("Missing the tagger model!");
              }

              if (!(dynamic_cast<ChunkerModel*>(artifactMap->get(CHUNKER_TAGGER_MODEL_ENTRY_NAME)) != 0))
              {
                throw InvalidFormatException("Missing the chunker model!");
              }

              if (!(dynamic_cast<HeadRules*>(artifactMap->get(HEAD_RULES_MODEL_ENTRY_NAME)) != 0))
              {
                throw InvalidFormatException("Missing the head rules!");
              }
            }
        }
    }
}
