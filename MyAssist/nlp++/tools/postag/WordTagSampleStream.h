#ifndef WORDTAGSAMPLESTREAM
#define WORDTAGSAMPLESTREAM

#include "POSSample.h"
#include "../tools/util/FilterObjectStream.h"
#include "../tools/util/ObjectStream.h"
#include "FilterObjectStream<String, POSSample>.h"
#include "S.h"
#include <string>

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
        namespace postag
        {


            using opennlp::tools::util::FilterObjectStream;
            using opennlp::tools::util::InvalidFormatException;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::PlainTextByLineStream;

            /// <summary>
            /// A stream filter which reads a sentence per line which contains
            /// words and tags in word_tag format and outputs a <seealso cref="POSSample"/> objects.
            /// </summary>
            class WordTagSampleStream : public FilterObjectStream<std::string, POSSample*>
            {

          private:
              static Logger *logger;

              /// <summary>
              /// Initializes the current instance.
              /// </summary>
              /// <param name="sentences"> </param>
          public:
              WordTagSampleStream(Reader *sentences) throw(IOException);

              WordTagSampleStream(ObjectStream<std::string> *sentences);

              /// <summary>
              /// Parses the next sentence and return the next
              /// <seealso cref="POSSample"/> object.
              /// 
              /// If an error occurs an empty <seealso cref="POSSample"/> object is returned
              /// and an warning message is logged. Usually it does not matter if one
              /// of many sentences is ignored.
              /// 
              /// TODO: An exception in error case should be thrown.
              /// </summary>
              virtual POSSample *read() throw(IOException);
            };

        }
    }
}


#endif	//#ifndef WORDTAGSAMPLESTREAM
