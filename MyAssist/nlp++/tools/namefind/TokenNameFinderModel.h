#ifndef TOKENNAMEFINDERMODEL
#define TOKENNAMEFINDERMODEL

#include "../tools/util/model/BaseModel.h"
#include "../tools/util/model/ArtifactSerializer.h"
#include "../tools/util/InvalidFormatException.h"
#include "../model/AbstractModel.h"
#include "../tools/util/featuregen/AdaptiveFeatureGenerator.h"
#include "../tools/util/featuregen/FeatureGeneratorResourceProvider.h"
#include "../model/MaxentModel.h"
#include "RuntimeException.h"
#include "ArtifactSerializer<byte[]>.h"
#include "Throwable.h"
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
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

            /// <summary>
            /// The <seealso cref="TokenNameFinderModel"/> is the model used
            /// by a learnable <seealso cref="TokenNameFinder"/>.
            /// </summary>
            /// <seealso cref= NameFinderME </seealso>
            class TokenNameFinderModel : public BaseModel
            {

          public:
              class FeatureGeneratorCreationError : public std::exception
              {
            public:
                FeatureGeneratorCreationError(Throwable *t);
              };

          private:
              class ByteArraySerializer : public ArtifactSerializer<char[]>
              {

            public:
                virtual char *create(InputStream *in_Renamed) throw(IOException, InvalidFormatException);

                virtual void serialize(char artifact[], OutputStream *out) throw(IOException);
              };

          private:
              static const std::string COMPONENT_NAME;
              static const std::string MAXENT_MODEL_ENTRY_NAME;

              static const std::string GENERATOR_DESCRIPTOR_ENTRY_NAME;

          public:
              TokenNameFinderModel(const std::string &languageCode, AbstractModel *nameFinderModel, char generatorDescriptor[], Map<std::string, void*> *resources, Map<std::string, std::string> *manifestInfoEntries);

//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              TokenNameFinderModel(const std::string &languageCode, AbstractModel *nameFinderModel, Map<std::string, void*> *resources, Map<std::string, std::string> *manifestInfoEntries); //this(languageCode, nameFinderModel, nullptr, resources, manifestInfoEntries);

              TokenNameFinderModel(InputStream *in_Renamed) throw(IOException, InvalidFormatException);

              /// <summary>
              /// Retrieves the <seealso cref="TokenNameFinder"/> model.
              /// </summary>
              /// <returns> the classification model </returns>
              virtual AbstractModel *getNameFinderModel();

              /// <summary>
              /// Creates the <seealso cref="AdaptiveFeatureGenerator"/>. Usually this
              /// is a set of generators contained in the <seealso cref="AggregatedFeatureGenerator"/>.
              /// 
              /// Note:
              /// The generators are created on every call to this method.
              /// </summary>
              /// <returns> the feature generator or null if there is no descriptor in the model </returns>
              virtual AdaptiveFeatureGenerator *createFeatureGenerators();

                    private:
                        class FeatureGeneratorResourceProviderAnonymousInnerClassHelper : public FeatureGeneratorResourceProvider
                        {

                        public:
                            virtual void *getResource(const std::string &key);
                        };

          public:
              virtual TokenNameFinderModel *updateFeatureGenerator(char descriptor[]);

          protected:
              virtual void createArtifactSerializers(Map<std::string, ArtifactSerializer*> *serializers);

          public:
              static Map<std::string, ArtifactSerializer*> *createArtifactSerializers();

              // TODO: Write test for this method
              static bool isModelValid(MaxentModel *model);

          protected:
              virtual void validateArtifactMap() throw(InvalidFormatException);
            };

        }
    }
}


#endif	//#ifndef TOKENNAMEFINDERMODEL
