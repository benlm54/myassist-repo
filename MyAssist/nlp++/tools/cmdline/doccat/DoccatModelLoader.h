#ifndef DOCCATMODELLOADER
#define DOCCATMODELLOADER

#include "../tools/cmdline/ModelLoader.h"
#include "../tools/doccat/DoccatModel.h"
#include "../tools/util/InvalidFormatException.h"
#include "DoccatModel>.h"

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
        namespace cmdline
        {
            namespace doccat
            {


                using opennlp::tools::cmdline::ModelLoader;
                using opennlp::tools::doccat::DoccatModel;
                using opennlp::tools::util::InvalidFormatException;

                /// <summary>
                /// Loads a Document Categorizer Model for the command line tools.
                /// <p>
                /// <b>Note:</b> Do not use this class, internal use only!
                /// </summary>
                class DoccatModelLoader : public ModelLoader<DoccatModel*>
                {

              public:
                  DoccatModelLoader();

              protected:
                  virtual DoccatModel *loadModel(InputStream *modelIn) throw(IOException, InvalidFormatException);

                };

            }
        }
    }
}


#endif	//#ifndef DOCCATMODELLOADER
