#ifndef WHITESPACETOKENSTREAM
#define WHITESPACETOKENSTREAM

#include "TokenSample.h"
#include "../tools/util/FilterObjectStream.h"
#include "../tools/util/ObjectStream.h"
#include "FilterObjectStream<TokenSample, String>.h"
#include "S.h"
#include "StringBuilder.h"
#include "const_iterator.h"
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
            using opennlp::tools::util::Span;

            /// <summary>
            /// This stream formats a <seealso cref="TokenSample"/>s into whitespace
            /// separated token strings.
            /// </summary>
            class WhitespaceTokenStream : public FilterObjectStream<TokenSample*, std::string>
            {

          public:
              WhitespaceTokenStream(ObjectStream<TokenSample*> *tokens);

              virtual std::string read() throw(IOException);
            };

        }
    }
}


#endif	//#ifndef WHITESPACETOKENSTREAM
