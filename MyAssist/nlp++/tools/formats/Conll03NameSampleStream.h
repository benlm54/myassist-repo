#ifndef CONLL03NAMESAMPLESTREAM
#define CONLL03NAMESAMPLESTREAM

#include "../tools/namefind/NameSample.h"
#include "../tools/util/ObjectStream.h"
#include "Conll02NameSampleStream.h"
#include "NameSample>.h"
#include <string>
#include <vector>

/*
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 * 
 *       http://www.apache.org/licenses/LICENSE-2.0
 * 
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *  under the License.
 */

namespace opennlp
{
    namespace tools
    {
        namespace formats
        {

//JAVA TO C++ CONVERTER TODO TASK: The Java 'import static' statement cannot be converted to C++:
            import static opennlp.tools.formats.Conll02NameSampleStream.extract;


            using opennlp::tools::namefind::NameSample;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::PlainTextByLineStream;
            using opennlp::tools::util::Span;
            using opennlp::tools::util::StringUtil;

            /// <summary>
            /// An import stream which can parse the CONLL03 data.
            /// </summary>
            class Conll03NameSampleStream : public ObjectStream<NameSample*>
            {

          public:
              enum LANGUAGE
              {
                EN,
                DE
              };

          private:
              const LANGUAGE lang;
              ObjectStream<std::string> *const lineStream;

              const int types;

              /// 
              /// <param name="lang"> </param>
              /// <param name="lineStream"> </param>
              /// <param name="types"> </param>
          public:
              Conll03NameSampleStream(LANGUAGE lang, ObjectStream<std::string> *lineStream, int types);

              /// 
              /// <param name="lang"> </param>
              /// <param name="in"> </param>
              /// <param name="types"> </param>
              Conll03NameSampleStream(LANGUAGE lang, InputStream *in_Renamed, int types);

              virtual NameSample *read() throw(IOException);

              virtual void reset() throw(IOException, UnsupportedOperationException);

              virtual void close() throw(IOException);

            };

        }
    }
}


#endif	//#ifndef CONLL03NAMESAMPLESTREAM
