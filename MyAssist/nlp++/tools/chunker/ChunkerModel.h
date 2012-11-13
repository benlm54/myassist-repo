#ifndef CHUNKERMODEL
#define CHUNKERMODEL

#include "../tools/util/model/BaseModel.h"
#include "../model/AbstractModel.h"
#include "../tools/util/InvalidFormatException.h"
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
        namespace chunker
        {


            using opennlp::model::AbstractModel;
            using opennlp::model::BinaryFileDataReader;
            using opennlp::model::GenericModelReader;
            using opennlp::tools::util::InvalidFormatException;
            using opennlp::tools::util::model::BaseModel;

            /// <summary>
            /// The <seealso cref="ChunkerModel"/> is the model used
            /// by a learnable <seealso cref="Chunker"/>.
            /// </summary>
            /// <seealso cref= ChunkerME </seealso>
            class ChunkerModel : public BaseModel
            {

          private:
              static const std::string COMPONENT_NAME;
              static const std::string CHUNKER_MODEL_ENTRY_NAME;

          public:
              ChunkerModel(const std::string &languageCode, AbstractModel *chunkerModel, Map<std::string, std::string> *manifestInfoEntries);

//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              ChunkerModel(const std::string &languageCode, AbstractModel *chunkerModel); //this(languageCode, chunkerModel, nullptr);

              ChunkerModel(InputStream *in_Renamed) throw(IOException, InvalidFormatException);

          protected:
              virtual void validateArtifactMap() throw(InvalidFormatException);

          public:
              virtual AbstractModel *getChunkerModel();

              static void main(std::string args[]) throw(FileNotFoundException, IOException);
            };

        }
    }
}


#endif	//#ifndef CHUNKERMODEL
