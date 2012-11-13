#ifndef POSMODEL
#define POSMODEL

#include "../tools/util/model/BaseModel.h"
#include "POSDictionary.h"
#include "../tools/util/model/ArtifactSerializer.h"
#include "../tools/util/InvalidFormatException.h"
#include "../model/AbstractModel.h"
#include "../tools/dictionary/Dictionary.h"
#include "ArtifactSerializer<POSDictionary>.h"
#include "const_iterator.h"
#include <string>
#include <set>

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
        namespace postag
        {


            using opennlp::model::AbstractModel;
            using opennlp::tools::dictionary::Dictionary;
            using opennlp::tools::util::InvalidFormatException;
            using opennlp::tools::util::model::ArtifactSerializer;
            using opennlp::tools::util::model::BaseModel;
            using opennlp::tools::util::model::UncloseableInputStream;

            /// <summary>
            /// The <seealso cref="POSModel"/> is the model used
            /// by a learnable <seealso cref="POSTagger"/>.
            /// </summary>
            /// <seealso cref= POSTaggerME </seealso>
            class POSModel : public BaseModel
            {

          public:
              class POSDictionarySerializer : public ArtifactSerializer<POSDictionary*>
              {

            public:
                virtual POSDictionary *create(InputStream *in_Renamed) throw(IOException, InvalidFormatException);

                virtual void serialize(POSDictionary *artifact, OutputStream *out) throw(IOException);

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @SuppressWarnings("unchecked") static void register(java.util.Map<String, opennlp.tools.util.model.ArtifactSerializer> factories)
                static void register_Renamed(Map<std::string, ArtifactSerializer*> *factories);
              };

          private:
              static const std::string COMPONENT_NAME;

              static const std::string POS_MODEL_ENTRY_NAME;
              static const std::string TAG_DICTIONARY_ENTRY_NAME;
              static const std::string NGRAM_DICTIONARY_ENTRY_NAME;

          public:
              POSModel(const std::string &languageCode, AbstractModel *posModel, POSDictionary *tagDictionary, Dictionary *ngramDict, Map<std::string, std::string> *manifestInfoEntries);

//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              POSModel(const std::string &languageCode, AbstractModel *posModel, POSDictionary *tagDictionary, Dictionary *ngramDict); //this(languageCode, posModel, tagDictionary, ngramDict, nullptr);

              POSModel(InputStream *in_Renamed) throw(IOException, InvalidFormatException);

          protected:
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Override @SuppressWarnings("unchecked") protected void createArtifactSerializers(java.util.Map<String, opennlp.tools.util.model.ArtifactSerializer> serializers)
              virtual void createArtifactSerializers(Map<std::string, ArtifactSerializer*> *serializers);

              virtual void validateArtifactMap() throw(InvalidFormatException);

          public:
              AbstractModel *getPosModel();

              /// <summary>
              /// Retrieves the tag dictionary.
              /// </summary>
              /// <returns> tag dictionary or null if not used </returns>
              POSDictionary *getTagDictionary();

              /// <summary>
              /// Retrieves the ngram dictionary.
              /// </summary>
              /// <returns> ngram dictionary or null if not used </returns>
              Dictionary *getNgramDictionary();
            };

        }
    }
}


#endif	//#ifndef POSMODEL
