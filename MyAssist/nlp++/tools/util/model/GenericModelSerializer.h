#ifndef GENERICMODELSERIALIZER
#define GENERICMODELSERIALIZER

#include "../model/AbstractModel.h"
#include "ArtifactSerializer.h"
#include "../tools/util/InvalidFormatException.h"
#include "AbstractModel>.h"
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
        namespace util
        {
            namespace model
            {


                using opennlp::model::AbstractModel;
                using opennlp::model::BinaryFileDataReader;
                using opennlp::model::GenericModelReader;
                using opennlp::tools::util::InvalidFormatException;

                class GenericModelSerializer : public ArtifactSerializer<AbstractModel*>
                {

              public:
                  virtual AbstractModel *create(InputStream *in_Renamed) throw(IOException, InvalidFormatException);

                  virtual void serialize(AbstractModel *artifact, OutputStream *out) throw(IOException);

                  static void register_Renamed(Map<std::string, ArtifactSerializer*> *factories);
                };

            }
        }
    }
}


#endif	//#ifndef GENERICMODELSERIALIZER
