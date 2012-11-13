#ifndef TOKENIZERCONVERTERTOOL
#define TOKENIZERCONVERTERTOOL

#include "../tools/cmdline/AbstractConverterTool.h"
#include "../tools/tokenize/TokenSample.h"
#include "../tools/cmdline/ObjectStreamFactory.h"
#include "TokenSample>.h"
#include <string>
#include <map>

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


                using opennlp::tools::cmdline::AbstractConverterTool;
                using opennlp::tools::cmdline::ObjectStreamFactory;
                using opennlp::tools::formats::ConllXTokenSampleStreamFactory;
                using opennlp::tools::formats::NameToTokenSampleStreamFactory;
                using opennlp::tools::formats::POSToTokenSampleStreamFactory;
                using opennlp::tools::tokenize::TokenSample;

                class TokenizerConverterTool : public AbstractConverterTool<TokenSample*>
                {

              private:
                  static Map<std::string, ObjectStreamFactory<TokenSample*>*> *const streamFactories;

//JAVA TO C++ CONVERTER TODO TASK: Static constructors are not allowed in native C++:
                  static TokenizerConverterTool();


              public:
                  virtual std::string getName();

                  virtual std::string getShortDescription();

              protected:
                  virtual ObjectStreamFactory<TokenSample*> *createStreamFactory(const std::string &format);

                };

            }
        }
    }
}


#endif	//#ifndef TOKENIZERCONVERTERTOOL
