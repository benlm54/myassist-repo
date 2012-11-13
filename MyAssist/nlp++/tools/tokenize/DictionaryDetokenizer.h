#ifndef DICTIONARYDETOKENIZER
#define DICTIONARYDETOKENIZER

#include "Detokenizer.h"
#include "DetokenizationDictionary.h"
#include "DetokenizationOperation.h"
#include <string>
#include <set>

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
        namespace tokenize
        {


            /// <summary>
            /// A rule based detokenizer. Simple rules which indicate in which direction a token should be
            /// moved are looked up in a <seealso cref="DetokenizationDictionary"/> object.
            /// </summary>
            /// <seealso cref= Detokenizer </seealso>
            /// <seealso cref= DetokenizationDictionary </seealso>
            class DictionaryDetokenizer : public Detokenizer
            {

          private:
              DetokenizationDictionary *const dict;

          public:
              DictionaryDetokenizer(DetokenizationDictionary *dict);

              virtual DetokenizationOperation *detokenize(std::string tokens[]);
            };

        }
    }
}


#endif	//#ifndef DICTIONARYDETOKENIZER
