#ifndef NAMESAMPLE
#define NAMESAMPLE

#include "../tools/util/Span.h"
#include "StringBuilder.h"
#include <string>
#include <vector>

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
        namespace namefind
        {


            using opennlp::tools::tokenize::WhitespaceTokenizer;
            using opennlp::tools::util::Span;

            /// <summary>
            /// Class for holding names for a single unit of text.
            /// </summary>
            class NameSample
            {

          private:
              const std::vector<std::string> sentence;
              const std::vector<Span*> names;
//ORIGINAL LINE: private final String[][] additionalContext;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              const std::string **additionalContext;
              const bool isClearAdaptiveData;

              /// <summary>
              /// Initializes the current instance.
              /// </summary>
              /// <param name="sentence"> training sentence </param>
              /// <param name="names"> </param>
              /// <param name="additionalContext"> </param>
              /// <param name="clearAdaptiveData"> if true the adaptive data of the 
              ///     feature generators is cleared </param>
          public:
              NameSample(std::string sentence[], Span names[], std::string additionalContext[][], bool clearAdaptiveData);

//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              NameSample(std::string sentence[], Span names[], bool clearAdaptiveData); //this(sentence, names, nullptr, clearAdaptiveData);

              virtual std::string *getSentence();

              virtual Span *getNames();

              virtual std::string **getAdditionalContext();

              virtual bool isClearAdaptiveDataSet();

              virtual bool Equals(void *obj);

              virtual std::string ToString();

          private:
              static std::string errorTokenWithContext(std::string sentence[], int index);

              static Pattern *const START_TAG_PATTERN;

          public:
              static NameSample *parse(const std::string &taggedTokens, bool isClearAdaptiveData) throw(IOException);
            };

        }
    }
}


#endif	//#ifndef NAMESAMPLE
