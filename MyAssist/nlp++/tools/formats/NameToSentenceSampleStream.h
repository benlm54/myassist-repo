#ifndef NAMETOSENTENCESAMPLESTREAM
#define NAMETOSENTENCESAMPLESTREAM

#include "AbstractToSentenceSampleStream.h"
#include "../tools/namefind/NameSample.h"
#include "../tools/tokenize/Detokenizer.h"
#include "../tools/util/ObjectStream.h"
#include "NameSample>.h"
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

            using opennlp::tools::namefind::NameSample;
            using opennlp::tools::tokenize::Detokenizer;
            using opennlp::tools::util::ObjectStream;

            /// <summary>
            /// <b>Note:</b> Do not use this class, internal use only!
            /// </summary>
            class NameToSentenceSampleStream : public AbstractToSentenceSampleStream<NameSample*>
            {

          public:
              NameToSentenceSampleStream(Detokenizer *detokenizer, ObjectStream<NameSample*> *samples, int chunkSize);

          protected:
              virtual std::string *toSentence(NameSample *sample);
            };

        }
    }
}


#endif	//#ifndef NAMETOSENTENCESAMPLESTREAM
