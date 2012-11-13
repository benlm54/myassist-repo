#ifndef NAMEFINDERCENSUS90NAMESTREAM
#define NAMEFINDERCENSUS90NAMESTREAM

#include "../tools/util/ObjectStream.h"
#include "../tools/util/StringList.h"
#include "StringList>.h"
#include <string>

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


            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::PlainTextByLineStream;
            using opennlp::tools::util::StringList;
            using opennlp::tools::util::StringUtil;

            /// <summary>
            /// This class helps to read the US Census data from the files to build a
            /// StringList for each dictionary entry in the name-finder dictionary.
            /// The entries in the source file are as follows:
            /// <p>
            ///      SMITH          1.006  1.006      1
            /// <p>
            /// <ul>
            /// <li>The first field is the name (in ALL CAPS).
            /// <li>The next field is a frequency in percent.
            /// <li>The next is a cumulative frequency in percent.
            /// <li>The last is a ranking.
            /// </ul>
            /// <p>
            /// <b>Note:</b> Do not use this class, internal use only!
            /// </summary>
            class NameFinderCensus90NameStream : public ObjectStream<StringList*>
            {

          private:
              Locale *const locale;
              Charset *const encoding;
              ObjectStream<std::string> *const lineStream;

              /// <summary>
              /// This constructor takes an ObjectStream and initializes the class to handle
              /// the stream.
              /// </summary>
              /// <param name="lineStream">  an <code>ObjectSteam<String></code> that represents the
              ///                    input file to be attached to this class. </param>
          public:
              NameFinderCensus90NameStream(ObjectStream<std::string> *lineStream);

              /// <summary>
              /// This constructor takes an <code>InputStream</code> and a <code>Charset</code>
              /// and opens an associated stream object with the specified encoding specified.
              /// </summary>
              /// <param name="in">  an <code>InputStream</code> for the input file. </param>
              /// <param name="encoding">  the <code>Charset</code> to apply to the input stream. </param>
              NameFinderCensus90NameStream(InputStream *in_Renamed, Charset *encoding);

              virtual StringList *read() throw(IOException);

              virtual void reset() throw(IOException, UnsupportedOperationException);

              virtual void close() throw(IOException);

            };

        }
    }
}


#endif	//#ifndef NAMEFINDERCENSUS90NAMESTREAM
