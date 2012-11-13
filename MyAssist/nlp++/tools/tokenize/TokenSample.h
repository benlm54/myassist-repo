#ifndef TOKENSAMPLE
#define TOKENSAMPLE

#include "../tools/util/Span.h"
#include "Detokenizer.h"
#include "StringBuilder.h"
#include "DetokenizationOperation.h"
#include "const_iterator.h"
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
        namespace tokenize
        {


            using opennlp::tools::tokenize::Detokenizer::DetokenizationOperation;
            using opennlp::tools::util::Span;

            /// <summary>
            /// A <seealso cref="TokenSample"/> is text with token spans.
            /// </summary>
            class TokenSample
            {

          public:
              static const std::string DEFAULT_SEPARATOR_CHARS;

          private:
              const std::string separatorChars;

              const std::string text;

              const std::vector<Span*> tokenSpans;

              /// <summary>
              /// Initializes the current instance.
              /// </summary>
              /// <param name="text"> the text which contains the tokens. </param>
              /// <param name="tokenSpans"> the spans which mark the begin and end of the tokens. </param>
          public:
              TokenSample(const std::string &text, Span tokenSpans[]) : separatorChars(DEFAULT_SEPARATOR_CHARS);

//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              TokenSample(Detokenizer *detokenizer, std::string tokens[]) : separatorChars(DEFAULT_SEPARATOR_CHARS);

              /// <summary>
              /// Retrieves the text.
              /// </summary>
              virtual std::string getText();

              /// <summary>
              /// Retrieves the token spans.
              /// </summary>
              virtual Span *getTokenSpans();

              virtual std::string ToString();

          private:
              static void addToken(StringBuilder *sample, std::vector<Span*> &tokenSpans, const std::string &token, bool isNextMerged);

          public:
              static TokenSample *parse(const std::string &sampleString, const std::string &separatorChars);

              virtual bool Equals(void *obj);
            };

        }
    }
}


#endif	//#ifndef TOKENSAMPLE
