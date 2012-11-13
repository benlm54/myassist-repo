#ifndef SENTENCEDETECTORCONVERTERTOOL
#define SENTENCEDETECTORCONVERTERTOOL

#include "../tools/cmdline/AbstractConverterTool.h"
#include "../tools/sentdetect/SentenceSample.h"
#include "../tools/cmdline/ObjectStreamFactory.h"
#include "SentenceSample>.h"
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
            namespace sentdetect
            {


                using opennlp::tools::cmdline::AbstractConverterTool;
                using opennlp::tools::cmdline::ObjectStreamFactory;
                using opennlp::tools::formats::ConllXSentenceSampleStreamFactory;
                using opennlp::tools::formats::NameToSentenceSampleStreamFactory;
                using opennlp::tools::formats::POSToSentenceSampleStreamFactory;
                using opennlp::tools::sentdetect::SentenceSample;

                class SentenceDetectorConverterTool : public AbstractConverterTool<SentenceSample*>
                {

              private:
                  static Map<std::string, ObjectStreamFactory<SentenceSample*>*> *const streamFactories;

//JAVA TO C++ CONVERTER TODO TASK: Static constructors are not allowed in native C++:
                  static SentenceDetectorConverterTool();

              public:
                  virtual std::string getName();

                  virtual std::string getShortDescription();

              protected:
                  virtual ObjectStreamFactory<SentenceSample*> *createStreamFactory(const std::string &format);
                };

            }
        }
    }
}


#endif	//#ifndef SENTENCEDETECTORCONVERTERTOOL
