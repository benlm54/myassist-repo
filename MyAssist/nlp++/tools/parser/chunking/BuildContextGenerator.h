#ifndef BUILDCONTEXTGENERATOR
#define BUILDCONTEXTGENERATOR

#include "../tools/parser/AbstractContextGenerator.h"
#include "../tools/dictionary/Dictionary.h"
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
            namespace chunking
            {


                using opennlp::tools::dictionary::Dictionary;
                using opennlp::tools::parser::AbstractContextGenerator;
                using opennlp::tools::parser::Cons;
                using opennlp::tools::parser::Parse;
                using opennlp::tools::util::StringList;

                /// <summary>
                /// Class to generator predictive contexts for deciding how constituents should be combined together.
                /// </summary>
                class BuildContextGenerator : public AbstractContextGenerator
                {

              private:
                  Dictionary *dict;
//ORIGINAL LINE: private String[] unigram;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                  std::string *unigram;
//ORIGINAL LINE: private String[] bigram;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                  std::string *bigram;
//ORIGINAL LINE: private String[] trigram;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                  std::string *trigram;

                  /// <summary>
                  /// Creates a new context generator for making decisions about combining constitients togehter.
                  /// 
                  /// </summary>
              public:
                  BuildContextGenerator();

//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
                  BuildContextGenerator(Dictionary *dict); //this();

                  virtual std::string *getContext(void *o);

                  /// <summary>
                  /// Returns the predictive context used to determine how constituent at the specified index
                  /// should be combined with other contisuents. </summary>
                  /// <param name="constituents"> The constituents which have yet to be combined into new constituents. </param>
                  /// <param name="index"> The index of the constituent whcihi is being considered. </param>
                  /// <returns> the context for building constituents at the specified index. </returns>
                  virtual std::string *getContext(Parse constituents[], int index);
                };

            }
        }
    }
}


#endif	//#ifndef BUILDCONTEXTGENERATOR
