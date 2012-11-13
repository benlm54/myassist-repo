#ifndef DOCCATMODEL
#define DOCCATMODEL

#include "../tools/util/model/BaseModel.h"
#include "../model/AbstractModel.h"
#include "../tools/util/InvalidFormatException.h"
#include <string>

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
        namespace doccat
        {


            using opennlp::model::AbstractModel;
            using opennlp::tools::util::InvalidFormatException;
            using opennlp::tools::util::model::BaseModel;

            class DoccatModel : public BaseModel
            {

          private:
              static const std::string COMPONENT_NAME;
              static const std::string DOCCAT_MODEL_ENTRY_NAME;

          protected:
              DoccatModel(const std::string &languageCode, AbstractModel *doccatModel, Map<std::string, std::string> *manifestInfoEntries);

          public:
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              DoccatModel(const std::string &languageCode, AbstractModel *doccatModel); //this(languageCode, doccatModel, nullptr);

              DoccatModel(InputStream *in_Renamed) throw(IOException, InvalidFormatException);

          protected:
              virtual void validateArtifactMap() throw(InvalidFormatException);

          public:
              virtual AbstractModel *getChunkerModel();
            };

        }
    }
}


#endif	//#ifndef DOCCATMODEL
