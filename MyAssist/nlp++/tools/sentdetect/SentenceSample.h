#ifndef SENTENCESAMPLE
#define SENTENCESAMPLE

#include "../tools/util/Span.h"
#include "../tools/tokenize/Detokenizer.h"
#include "StringBuilder.h"
#include "DetokenizationOperation.h"
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
        namespace sentdetect
        {


            using opennlp::tools::cmdline::tokenizer::DictionaryDetokenizerTool;
            using opennlp::tools::tokenize::Detokenizer;
            using opennlp::tools::tokenize::Detokenizer::DetokenizationOperation;
            using opennlp::tools::util::Span;

            /// <summary>
            /// A <seealso cref="SentenceSample"/> contains a document with
            /// begin indexes of the individual sentences.
            /// </summary>
            class SentenceSample
            {

          private:
              const std::string document;

              const std::vector<Span*> sentences;

              /// <summary>
              /// Initializes the current instance.
              /// </summary>
              /// <param name="document"> </param>
              /// <param name="sentences"> </param>
          public:
//ORIGINAL LINE: public SentenceSample(String document, opennlp.tools.util.Span... sentences)
//JAVA TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
              SentenceSample(const std::string &document, ...);

//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              SentenceSample(Detokenizer *detokenizer, std::string sentences[][]);

              /// <summary>
              /// Retrieves the document.
              /// </summary>
              /// <returns> the document </returns>
              virtual std::string getDocument();

              /// <summary>
              /// Retrieves the sentences.
              /// </summary>
              /// <returns> the begin indexes of the sentences
              /// in the document. </returns>
              virtual Span *getSentences();

              virtual std::string ToString();

              virtual bool Equals(void *obj);
            };

        }
    }
}


#endif	//#ifndef SENTENCESAMPLE
