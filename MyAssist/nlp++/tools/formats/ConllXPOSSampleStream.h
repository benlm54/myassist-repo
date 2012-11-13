#ifndef CONLLXPOSSAMPLESTREAM
#define CONLLXPOSSAMPLESTREAM

#include "../tools/postag/POSSample.h"
#include "../tools/util/FilterObjectStream.h"
#include "../tools/util/ObjectStream.h"
#include "POSSample>.h"
#include "S.h"
#include <string>
#include <vector>

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
            using opennlp::tools::util::FilterObjectStream;
            using opennlp::tools::util::InvalidFormatException;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::ParagraphStream;
            using opennlp::tools::util::PlainTextByLineStream;

            /// <summary>
            /// Parses the data from the CONLL 06 shared task into POS Samples.
            /// <p>
            /// More information about the data format can be found here:<br>
            /// http://www.cnts.ua.ac.be/conll2006/
            /// <p>
            /// <b>Note:</b> Do not use this class, internal use only!
            /// </summary>
            class ConllXPOSSampleStream : public FilterObjectStream<std::string, POSSample*>
            {

          public:
              ConllXPOSSampleStream(ObjectStream<std::string> *lineStream);

              ConllXPOSSampleStream(Reader *in_Renamed) throw(IOException);

              virtual POSSample *read() throw(IOException);
            };

        }
    }
}


#endif	//#ifndef CONLLXPOSSAMPLESTREAM
