#ifndef CHECKCONTEXTGENERATOR
#define CHECKCONTEXTGENERATOR

#include "../tools/parser/AbstractContextGenerator.h"
#include "../tools/parser/Parse.h"
#include "StringBuffer.h"
#include <string>
#include <vector>

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
        namespace parser
        {
            namespace chunking
            {


                using opennlp::tools::parser::AbstractContextGenerator;
                using opennlp::tools::parser::Parse;

                /// <summary>
                /// Class for generating predictive context for deciding when a constituent is complete.
                /// </summary>
                class CheckContextGenerator : public AbstractContextGenerator
                {

                  /// <summary>
                  /// Creates a new context generator for generating predictive context for deciding when a constituent is complete.
                  /// </summary>
              public:
                  CheckContextGenerator();

                  virtual std::string *getContext(void *o);

                  /// <summary>
                  /// Returns predictive context for deciding whether the specified constituents between the specified start and end index
                  /// can be combined to form a new constituent of the specified type. </summary>
                  /// <param name="constituents"> The constituents which have yet to be combined into new constituents. </param>
                  /// <param name="type"> The type of the new constituent proposed. </param>
                  /// <param name="start"> The first constituent of the proposed constituent. </param>
                  /// <param name="end"> The last constituent of the proposed constituent. </param>
                  /// <returns> The predictive context for deciding whether a new constituent should be created. </returns>
                  virtual std::string *getContext(Parse constituents[], const std::string &type, int start, int end);
                };

            }
        }
    }
}


#endif	//#ifndef CHECKCONTEXTGENERATOR
