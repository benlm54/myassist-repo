#ifndef ATTACHCONTEXTGENERATOR
#define ATTACHCONTEXTGENERATOR

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
            namespace treeinsert
            {


                using opennlp::tools::parser::AbstractContextGenerator;
                using opennlp::tools::parser::Cons;
                using opennlp::tools::parser::Parse;

                class AttachContextGenerator : public AbstractContextGenerator
                {


              public:
                  AttachContextGenerator(Set<std::string> *punctSet);

                  virtual std::string *getContext(void *o);

              private:
                  bool containsPunct(Collection<Parse*> *puncts, const std::string &punct);

                  /// 
                  /// <param name="constituents"> The constituents as they have been constructed so far. </param>
                  /// <param name="index"> The constituent index of the node being attached. </param>
                  /// <param name="rightFrontier"> The nodes which have been not attach to so far. </param>
                  /// <returns> A set of contextual features about this attachment. </returns>
              public:
                  virtual std::string *getContext(Parse constituents[], int index, std::vector<Parse*> &rightFrontier, int rfi);
                };

            }
        }
    }
}


#endif	//#ifndef ATTACHCONTEXTGENERATOR
