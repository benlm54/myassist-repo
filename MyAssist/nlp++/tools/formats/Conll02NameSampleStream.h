#ifndef CONLL02NAMESAMPLESTREAM
#define CONLL02NAMESAMPLESTREAM

#include "../tools/namefind/NameSample.h"
#include "../tools/util/ObjectStream.h"
#include "Conll03NameSampleStream.h"
#include "../tools/util/InvalidFormatException.h"
#include "../tools/util/Span.h"
#include "NameSample>.h"
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


            using opennlp::tools::namefind::NameSample;
            using opennlp::tools::util::InvalidFormatException;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::PlainTextByLineStream;
            using opennlp::tools::util::Span;
            using opennlp::tools::util::StringUtil;

            /// <summary>
            /// Parser for the dutch and spanish ner training files of the CONLL 2002 shared task.
            /// <p>
            /// The dutch data has a -DOCSTART- tag to mark article boundaries,
            /// adaptive data in the feature generators will be cleared before every article.<br>
            /// The spanish data does not contain article boundaries,
            /// adaptive data will be cleared for every sentence.
            /// <p>
            /// The data contains four named entity types: Person, Organization, Location and Misc.<br>
            /// <p>
            /// Data can be found on this web site:<br>
            /// http://www.cnts.ua.ac.be/conll2002/ner/
            /// <p>
            /// <b>Note:</b> Do not use this class, internal use only!
            /// </summary>
            class Conll02NameSampleStream : public ObjectStream<NameSample*>
            {

          public:
              enum LANGUAGE
              {
                NL,
                ES
              };

          public:
              static const int GENERATE_PERSON_ENTITIES = 0x01;
              static const int GENERATE_ORGANIZATION_ENTITIES = 0x01 << 1;
              static const int GENERATE_LOCATION_ENTITIES = 0x01 << 2;
              static const int GENERATE_MISC_ENTITIES = 0x01 << 3;

              static const std::string DOCSTART;

          private:
              const LANGUAGE lang;
              ObjectStream<std::string> *const lineStream;

              const int types;

          public:
              Conll02NameSampleStream(LANGUAGE lang, ObjectStream<std::string> *lineStream, int types);

              /// <param name="lang"> </param>
              /// <param name="in"> an Input Stream to read data. </param>
              /// <exception cref="IOException">  </exception>
              Conll02NameSampleStream(LANGUAGE lang, InputStream *in_Renamed, int types);

              static Span *extract(int begin, int end, const std::string &beginTag) throw(InvalidFormatException);


              virtual NameSample *read() throw(IOException);

              virtual void reset() throw(IOException, UnsupportedOperationException);

              virtual void close() throw(IOException);
            };

        }
    }
}


#endif	//#ifndef CONLL02NAMESAMPLESTREAM
