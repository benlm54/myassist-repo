#ifndef TOKENIZERMODELLOADER
#define TOKENIZERMODELLOADER

#include "../tools/cmdline/ModelLoader.h"
#include "../tools/tokenize/TokenizerModel.h"
#include "../tools/util/InvalidFormatException.h"
#include "TokenizerModel>.h"

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
            namespace tokenizer
            {


                using opennlp::tools::cmdline::ModelLoader;
                using opennlp::tools::tokenize::TokenizerModel;
                using opennlp::tools::util::InvalidFormatException;

                /// <summary>
                /// Loads a Tokenizer Model for the command line tools.
                /// <p>
                /// <b>Note:</b> Do not use this class, internal use only!
                /// </summary>
                class TokenizerModelLoader : public ModelLoader<TokenizerModel*>
                {

              public:
                  TokenizerModelLoader();

              protected:
                  TokenizerModel *loadModel(InputStream *modelIn) throw(IOException, InvalidFormatException);
                };

            }
        }
    }
}


#endif	//#ifndef TOKENIZERMODELLOADER