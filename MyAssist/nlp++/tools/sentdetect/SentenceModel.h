#ifndef SENTENCEMODEL
#define SENTENCEMODEL

#include "../tools/util/model/BaseModel.h"
#include "../model/AbstractModel.h"
#include "../tools/dictionary/Dictionary.h"
#include "../tools/util/InvalidFormatException.h"
#include <string>
#include "stringconverter.h"

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
        namespace sentdetect
        {


            using opennlp::model::AbstractModel;
            using opennlp::model::GenericModelReader;
            using opennlp::tools::dictionary::Dictionary;
            using opennlp::tools::util::InvalidFormatException;
            using opennlp::tools::util::model::BaseModel;
            using opennlp::tools::util::model::ModelUtil;

            /// <summary>
            /// The <seealso cref="SentenceModel"/> is the model used
            /// by a learnable <seealso cref="SentenceDetector"/>.
            /// </summary>
            /// <seealso cref= SentenceDetectorME </seealso>
            class SentenceModel : public BaseModel
            {

          private:
              static const std::string COMPONENT_NAME;

              static const std::string MAXENT_MODEL_ENTRY_NAME;
              static const std::string ABBREVIATIONS_ENTRY_NAME;

              static const std::string TOKEN_END_PROPERTY;

          public:
              SentenceModel(const std::string &languageCode, AbstractModel *sentModel, bool useTokenEnd, Dictionary *abbreviations, Map<std::string, std::string> *manifestInfoEntries);

//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              SentenceModel(const std::string &languageCode, AbstractModel *sentModel, bool useTokenEnd, Dictionary *abbreviations); //this(languageCode, sentModel, useTokenEnd, abbreviations, nullptr);

              SentenceModel(InputStream *in_Renamed) throw(IOException, InvalidFormatException);

          protected:
              virtual void validateArtifactMap() throw(InvalidFormatException);

          public:
              virtual AbstractModel *getMaxentModel();

              virtual Dictionary *getAbbreviations();

              virtual bool useTokenEnd();

              static void main(std::string args[]) throw(FileNotFoundException, IOException, InvalidFormatException);
            };

        }
    }
}


#endif	//#ifndef SENTENCEMODEL
