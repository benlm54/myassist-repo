#ifndef SENTENCESAMPLESTREAM
#define SENTENCESAMPLESTREAM

#include "SentenceSample.h"
#include "../tools/util/FilterObjectStream.h"
#include "../tools/util/ObjectStream.h"
#include "FilterObjectStream<String, SentenceSample>.h"
#include "StringBuilder.h"
#include "S.h"
#include <string>
#include <vector>
#include <list>

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


            using opennlp::tools::util::FilterObjectStream;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::Span;

            /// <summary>
            /// This class is a stream filter which reads a sentence by line samples from
            /// a <code>Reader</code> and converts them into <seealso cref="SentenceSample"/> objects.
            /// </summary>
            class SentenceSampleStream : public FilterObjectStream<std::string, SentenceSample*>
            {

          public:
              SentenceSampleStream(ObjectStream<std::string> *sentences);

              virtual SentenceSample *read() throw(IOException);
            };

        }
    }
}


#endif	//#ifndef SENTENCESAMPLESTREAM
