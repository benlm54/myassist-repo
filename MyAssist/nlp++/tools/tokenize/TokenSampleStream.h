#ifndef TOKENSAMPLESTREAM
#define TOKENSAMPLESTREAM

#include "TokenSample.h"
#include "../tools/util/FilterObjectStream.h"
#include "../tools/util/ObjectStream.h"
#include "FilterObjectStream<String, TokenSample>.h"
#include "S.h"
#include <string>

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
        namespace tokenize
        {


            using opennlp::tools::util::FilterObjectStream;
            using opennlp::tools::util::ObjectStream;

            /// <summary>
            /// This class is a stream filter which reads in string encoded samples and creates
            /// <seealso cref="TokenSample"/>s out of them. The input string sample is tokenized if a
            /// whitespace or the special separator chars occur.
            /// <p>
            /// Sample:<br>
            /// "token1 token2 token3<SPLIT>token4"<br>
            /// The tokens token1 and token2 are separated by a whitespace, token3 and token3
            /// are separated by the special character sequence, in this case the default
            /// split sequence.
            /// <p>
            /// The sequence must be unique in the input string and is not escaped.
            /// </summary>
            class TokenSampleStream : public FilterObjectStream<std::string, TokenSample*>
            {

          private:
              const std::string separatorChars;


          public:
              TokenSampleStream(ObjectStream<std::string> *sampleStrings, const std::string &separatorChars);

//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              TokenSampleStream(ObjectStream<std::string> *sentences); //this(sentences, TokenSample.DEFAULT_SEPARATOR_CHARS);

              virtual TokenSample *read() throw(IOException);
            };

        }
    }
}


#endif	//#ifndef TOKENSAMPLESTREAM
