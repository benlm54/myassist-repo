#ifndef PLAINTEXTBYLINESTREAM
#define PLAINTEXTBYLINESTREAM

#include "ObjectStream.h"
#include "ObjectStream<String>.h"
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
            /// Reads a plain text file and return each line as a <code>String</code> object.
            /// </summary>
            class PlainTextByLineStream : public ObjectStream<std::string>
            {

          private:
              FileChannel *const channel;
              const std::string encoding;

              BufferedReader *in_Renamed;

              /// <summary>
              /// Initializes the current instance.
              /// </summary>
              /// <param name="in"> </param>
          public:
//JAVA TO C++ CONVERTER WARNING: Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
              PlainTextByLineStream(Reader *in_Renamed);

//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              PlainTextByLineStream(InputStream *in_Renamed, const std::string &charsetName) throw(UnsupportedEncodingException); //this(new InputStreamReader(in, charsetName));

//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              PlainTextByLineStream(InputStream *in_Renamed, Charset *charset); //this(new InputStreamReader(in, charset));

              PlainTextByLineStream(FileChannel *channel, const std::string &charsetName);

//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              PlainTextByLineStream(FileChannel *channel, Charset *encoding); //this(channel, encoding.name());

              virtual std::string read() throw(IOException);

              virtual void reset() throw(IOException);

              virtual void close() throw(IOException);
            };

        }
    }
}


#endif	//#ifndef PLAINTEXTBYLINESTREAM
