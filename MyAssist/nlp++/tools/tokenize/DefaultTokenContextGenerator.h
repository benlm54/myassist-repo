#ifndef DEFAULTTOKENCONTEXTGENERATOR
#define DEFAULTTOKENCONTEXTGENERATOR

#include "TokenContextGenerator.h"
#include <string>
#include <vector>
#include <cctype>

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
        namespace tokenize
        {


            using opennlp::tools::util::StringUtil;

            /// <summary>
            /// Generate events for maxent decisions for tokenization.
            /// </summary>
            class DefaultTokenContextGenerator : public TokenContextGenerator
            {

          private:
              Set<std::string> *const inducedAbbreviations;

              /// <summary>
              /// Creates a default context generator for tokenizer.
              /// </summary>
          public:
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              DefaultTokenContextGenerator(); //this(Collections.emptySet<String>());

              /// <summary>
              /// Creates a default context generator for tokenizer.
              /// </summary>
              /// <param name="inducedAbbreviations"> the induced abbreviations </param>
              DefaultTokenContextGenerator(Set<std::string> *inducedAbbreviations);

              /* (non-Javadoc)
               * @see opennlp.tools.tokenize.TokenContextGenerator#getContext(java.lang.String, int)
               */
              virtual std::string *getContext(const std::string &sentence, int index);


              /// <summary>
              /// Helper function for getContext.
              /// </summary>
          private:
              void addCharPreds(const std::string &key, char c, std::vector<std::string> &preds);
            };

        }
    }
}


#endif	//#ifndef DEFAULTTOKENCONTEXTGENERATOR
