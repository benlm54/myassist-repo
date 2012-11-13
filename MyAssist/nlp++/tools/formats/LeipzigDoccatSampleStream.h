#ifndef LEIPZIGDOCCATSAMPLESTREAM
#define LEIPZIGDOCCATSAMPLESTREAM

#include "../tools/doccat/DocumentSample.h"
#include "../tools/util/FilterObjectStream.h"
#include "DocumentSample>.h"
#include "StringBuilder.h"
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
        namespace formats
        {


            using opennlp::tools::doccat::DocumentSample;
            using opennlp::tools::tokenize::SimpleTokenizer;
            using opennlp::tools::util::FilterObjectStream;
            using opennlp::tools::util::PlainTextByLineStream;

            /// <summary>
            /// Stream filter to produce document samples out of a Leipzig sentences.txt file.
            /// In the Leipzig corpus the encoding of the various senences.txt file is defined by
            /// the language. The language must be specified to produce the category tags and is used
            /// to determine the correct input encoding.
            /// <p>
            /// The input text is tokenized with the <seealso cref="SimpleTokenizer"/>. The input text classified
            /// by the language model must also be tokenized by the <seealso cref="SimpleTokenizer"/> to produce
            /// exactly the same tokenization during testing and training.
            /// </summary>
            class LeipzigDoccatSampleStream : public FilterObjectStream<std::string, DocumentSample*>
            {

          private:
              const std::string language;
              const int sentencesPerDocument;

              /// <summary>
              /// Creates a new LeipzigDoccatSampleStream with the specified parameters.
              /// </summary>
              /// <param name="language"> the Leipzig input sentences.txt file </param>
              /// <param name="sentencesPerDocument"> the number of sentences which should be grouped into once <seealso cref="DocumentSample"/> </param>
              /// <param name="in"> the InputStream pointing to the contents of the sentences.txt input file </param>
          public:
              LeipzigDoccatSampleStream(const std::string &language, int sentencesPerDocument, InputStream *in_Renamed) throw(IOException);

              virtual DocumentSample *read() throw(IOException);
            };

        }
    }
}


#endif	//#ifndef LEIPZIGDOCCATSAMPLESTREAM
