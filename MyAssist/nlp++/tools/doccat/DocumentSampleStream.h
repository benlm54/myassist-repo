#ifndef DOCUMENTSAMPLESTREAM
#define DOCUMENTSAMPLESTREAM

#include "DocumentSample.h"
#include "../tools/util/FilterObjectStream.h"
#include "../tools/util/ObjectStream.h"
#include "FilterObjectStream<String, DocumentSample>.h"
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
        namespace doccat
        {


            using opennlp::tools::tokenize::WhitespaceTokenizer;
            using opennlp::tools::util::FilterObjectStream;
            using opennlp::tools::util::ObjectStream;

            /// <summary>
            /// This class reads in string encoded training samples, parses them and outputs <seealso cref="DocumentSample"/> objects.
            /// <p>
            /// Format:<br>
            /// Each line contains one sample document.<br>
            /// The category is the first string in the line followed by a tab and whitespace separated document tokens.<br>
            /// Sample line: category-string tab-char whitespace-separated-tokens line-break-char(s)<br>
            /// </summary>
            class DocumentSampleStream : public FilterObjectStream<std::string, DocumentSample*>
            {

          public:
              DocumentSampleStream(ObjectStream<std::string> *samples);

              virtual DocumentSample *read() throw(IOException);
            };

        }
    }
}


#endif	//#ifndef DOCUMENTSAMPLESTREAM
