#ifndef BUILDCONTEXTGENERATOR
#define BUILDCONTEXTGENERATOR

#include "../tools/parser/AbstractContextGenerator.h"
#include "../tools/parser/Parse.h"
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
            namespace treeinsert
            {


                using opennlp::tools::parser::AbstractContextGenerator;
                using opennlp::tools::parser::Cons;
                using opennlp::tools::parser::Parse;

                /// <summary>
                /// Creates the features or contexts for the building phase of parsing.
                /// This phase builds constituents from the left-most node of these
                /// constituents.
                /// </summary>
                class BuildContextGenerator : public AbstractContextGenerator
                {

              private:
//ORIGINAL LINE: private opennlp.tools.parser.Parse[] leftNodes;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                  Parse *leftNodes;

              public:
                  BuildContextGenerator();

                  virtual std::string *getContext(void *o);

                  /// <summary>
                  /// Returns the contexts/features for the decision to build a new constituent for the specified parse
                  /// at the specified index. </summary>
                  /// <param name="constituents"> The constituents of the parse so far. </param>
                  /// <param name="index"> The index of the constituent where a build decision is being made. </param>
                  /// <returns> the contexts/features for the decision to build a new constituent. </returns>
                  virtual std::string *getContext(Parse constituents[], int index);

                };

            }
        }
    }
}


#endif	//#ifndef BUILDCONTEXTGENERATOR
