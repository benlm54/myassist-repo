#ifndef PARSERMODEL
#define PARSERMODEL

#include "../tools/util/model/BaseModel.h"
#include "../tools/postag/POSModel.h"
#include "../tools/util/model/ArtifactSerializer.h"
#include "../tools/util/InvalidFormatException.h"
#include "../tools/chunker/ChunkerModel.h"
#include "lang/en/HeadRules.h"
#include "../model/AbstractModel.h"
#include "ParserType.h"
#include "POSModel>.h"
#include "ChunkerModel>.h"
#include "HeadRules>.h"
#include <string>

/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreemnets.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


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

            /// <summary>
            /// This is an abstract base class for <seealso cref="ParserModel"/> implementations.
            /// </summary>
            // TODO: Model should validate the artifact map
            class ParserModel : public BaseModel
            {

          private:
              class POSModelSerializer : public ArtifactSerializer<POSModel*>
              {

            public:
                virtual POSModel *create(InputStream *in_Renamed) throw(IOException, InvalidFormatException);

                virtual void serialize(POSModel *artifact, OutputStream *out) throw(IOException);
              };

          private:
              class ChunkerModelSerializer : public ArtifactSerializer<ChunkerModel*>
              {

            public:
                virtual ChunkerModel *create(InputStream *in_Renamed) throw(IOException, InvalidFormatException);

                virtual void serialize(ChunkerModel *artifact, OutputStream *out) throw(IOException);
              };

          private:
              class HeadRulesSerializer : public ArtifactSerializer<opennlp::tools::parser::lang::en::HeadRules*>
              {

            public:
                virtual opennlp::tools::parser::lang::en::HeadRules *create(InputStream *in_Renamed) throw(IOException, InvalidFormatException);

                virtual void serialize(opennlp::tools::parser::lang::en::HeadRules *artifact, OutputStream *out) throw(IOException);
              };

          private:
              static const std::string COMPONENT_NAME;

              static const std::string BUILD_MODEL_ENTRY_NAME;

              static const std::string CHECK_MODEL_ENTRY_NAME;

              static const std::string ATTACH_MODEL_ENTRY_NAME;

              static const std::string PARSER_TAGGER_MODEL_ENTRY_NAME;

              static const std::string CHUNKER_TAGGER_MODEL_ENTRY_NAME;

              static const std::string HEAD_RULES_MODEL_ENTRY_NAME;

              static const std::string PARSER_TYPE;

          public:
              ParserModel(const std::string &languageCode, AbstractModel *buildModel, AbstractModel *checkModel, AbstractModel *attachModel, POSModel *parserTagger, ChunkerModel *chunkerTagger, opennlp::tools::parser::lang::en::HeadRules *headRules, ParserType modelType, Map<std::string, std::string> *manifestInfoEntries);

//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              ParserModel(const std::string &languageCode, AbstractModel *buildModel, AbstractModel *checkModel, AbstractModel *attachModel, POSModel *parserTagger, ChunkerModel *chunkerTagger, opennlp::tools::parser::lang::en::HeadRules *headRules, ParserType modelType); //this(languageCode, buildModel, checkModel, attachModel, parserTagger, chunkerTagger, headRules, modelType, nullptr);

//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              ParserModel(const std::string &languageCode, AbstractModel *buildModel, AbstractModel *checkModel, POSModel *parserTagger, ChunkerModel *chunkerTagger, opennlp::tools::parser::lang::en::HeadRules *headRules, ParserType type, Map<std::string, std::string> *manifestInfoEntries); //this(languageCode, buildModel, checkModel, nullptr, parserTagger, chunkerTagger, headRules, type, manifestInfoEntries);

              ParserModel(InputStream *in_Renamed) throw(IOException, InvalidFormatException);

          protected:
              virtual void createArtifactSerializers(Map<std::string, ArtifactSerializer*> *serializers);

          public:
              virtual ParserType getParserType();

              virtual AbstractModel *getBuildModel();

              virtual AbstractModel *getCheckModel();

              virtual AbstractModel *getAttachModel();

              virtual POSModel *getParserTaggerModel();

              virtual ChunkerModel *getParserChunkerModel();

              virtual opennlp::tools::parser::lang::en::HeadRules *getHeadRules();

              // TODO: Update model methods should make sure properties are copied correctly ...
              virtual ParserModel *updateBuildModel(AbstractModel *buildModel);

              virtual ParserModel *updateCheckModel(AbstractModel *checkModel);

              virtual ParserModel *updateTaggerModel(POSModel *taggerModel);

              virtual ParserModel *updateChunkerModel(ChunkerModel *chunkModel);

          protected:
              virtual void validateArtifactMap() throw(InvalidFormatException);
            };
        }
    }
}


#endif	//#ifndef PARSERMODEL
