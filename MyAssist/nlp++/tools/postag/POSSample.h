#ifndef POSSAMPLE
#define POSSAMPLE

#include "../tools/util/InvalidFormatException.h"
#include "StringBuilder.h"
#include <string>
#include <vector>
#include <algorithm>

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
        namespace postag
        {


            using opennlp::tools::tokenize::WhitespaceTokenizer;
            using opennlp::tools::util::InvalidFormatException;

            /// <summary>
            /// Represents an pos-tagged sentence.
            /// </summary>
            class POSSample
            {

          private:
              std::vector<std::string> sentence;

              std::vector<std::string> tags;

          public:
              POSSample(std::string sentence[], std::string tags[]);

              POSSample(std::vector<std::string> &sentence, std::vector<std::string> &tags);

          private:
              void checkArguments();

          public:
              virtual std::string *getSentence();

              virtual std::string *getTags();

              virtual std::string ToString();

              static POSSample *parse(const std::string &sentenceString) throw(InvalidFormatException);

              virtual bool Equals(void *obj);
            };

        }
    }
}


#endif	//#ifndef POSSAMPLE
