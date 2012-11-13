#ifndef DEFAULTCHUNKERCONTEXTGENERATOR
#define DEFAULTCHUNKERCONTEXTGENERATOR

#include "ChunkerContextGenerator.h"
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

            /// <summary>
            /// Features based on chunking model described in Fei Sha and Fernando Pereira. Shallow
            ///  parsing with conditional random fields. In Proceedings of HLT-NAACL 2003. Association
            ///  for Computational Linguistics, 2003.
            /// </summary>
            class DefaultChunkerContextGenerator : public ChunkerContextGenerator
            {

              /// <summary>
              /// Creates the default context generator a chunker.
              /// </summary>
          public:
              DefaultChunkerContextGenerator();

              virtual std::string *getContext(int index, std::string sequence[], std::string priorDecisions[], Object additionalContext[]);

              virtual std::string *getContext(int i, std::string toks[], std::string tags[], std::string preds[]);
            };

        }
    }
}


#endif	//#ifndef DEFAULTCHUNKERCONTEXTGENERATOR
