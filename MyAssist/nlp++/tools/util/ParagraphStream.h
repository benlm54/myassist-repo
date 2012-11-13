#ifndef PARAGRAPHSTREAM
#define PARAGRAPHSTREAM

#include "FilterObjectStream.h"
#include "ObjectStream.h"
#include "FilterObjectStream<String, String>.h"
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
        namespace util
        {


            /// <summary>
            /// Stream filter which merges text lines into paragraphs. The boundary of paragraph is defined
            /// by an empty text line. If the last paragraph in the stream is not terminated by an empty line
            /// the left over is assumed to be a paragraph.
            /// </summary>
            class ParagraphStream : public FilterObjectStream<std::string, std::string>
            {

          public:
              ParagraphStream(ObjectStream<std::string> *lineStream);

              virtual std::string read() throw(IOException);
            };

        }
    }
}


#endif	//#ifndef PARAGRAPHSTREAM
