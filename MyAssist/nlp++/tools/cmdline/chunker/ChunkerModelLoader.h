#ifndef CHUNKERMODELLOADER
#define CHUNKERMODELLOADER

#include "../tools/chunker/ChunkerModel.h"
#include "../tools/cmdline/ModelLoader.h"
#include "../tools/util/InvalidFormatException.h"
#include "ChunkerModel>.h"

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
            namespace chunker
            {


                using opennlp::tools::chunker::ChunkerModel;
                using opennlp::tools::cmdline::ModelLoader;
                using opennlp::tools::util::InvalidFormatException;

                /// <summary>
                /// Loads a Chunker Model for the command line tools.
                /// <p>
                /// <b>Note:</b> Do not use this class, internal use only!
                /// </summary>
                class ChunkerModelLoader : public ModelLoader<ChunkerModel*>
                {

              public:
                  ChunkerModelLoader();

              protected:
                  virtual ChunkerModel *loadModel(InputStream *modelIn) throw(IOException, InvalidFormatException);

                };

            }
        }
    }
}


#endif	//#ifndef CHUNKERMODELLOADER
