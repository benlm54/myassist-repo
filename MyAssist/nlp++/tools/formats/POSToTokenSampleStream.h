#ifndef POSTOTOKENSAMPLESTREAM
#define POSTOTOKENSAMPLESTREAM

#include "../tools/postag/POSSample.h"
#include "../tools/tokenize/TokenSample.h"
#include "../tools/util/FilterObjectStream.h"
#include "../tools/tokenize/Detokenizer.h"
#include "../tools/util/ObjectStream.h"
#include "TokenSample>.h"
#include "S.h"

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


            using opennlp::tools::postag::POSSample;
            using opennlp::tools::tokenize::Detokenizer;
            using opennlp::tools::tokenize::TokenSample;
            using opennlp::tools::util::FilterObjectStream;
            using opennlp::tools::util::ObjectStream;

            /// <summary>
            /// <b>Note:</b> Do not use this class, internal use only!
            /// </summary>
            class POSToTokenSampleStream : public FilterObjectStream<POSSample*, TokenSample*>
            {

          private:
              Detokenizer *const detokenizer;

          public:
              POSToTokenSampleStream(Detokenizer *detokenizer, ObjectStream<POSSample*> *samples);

              virtual TokenSample *read() throw(IOException);
            };

        }
    }
}


#endif	//#ifndef POSTOTOKENSAMPLESTREAM
