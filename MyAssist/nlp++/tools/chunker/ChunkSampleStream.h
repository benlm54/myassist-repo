#ifndef CHUNKSAMPLESTREAM
#define CHUNKSAMPLESTREAM

#include "ChunkSample.h"
#include "../tools/util/FilterObjectStream.h"
#include "../tools/util/ObjectStream.h"
#include "FilterObjectStream<String, ChunkSample>.h"
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
        namespace chunker
        {


            using opennlp::tools::util::FilterObjectStream;
            using opennlp::tools::util::ObjectStream;

            /// <summary>
            /// Parses the conll 2000 shared task shallow parser training data.
            /// <p>
            /// Data format is specified on the conll page:<br>
            /// <a hraf="http://www.cnts.ua.ac.be/conll2000/chunking/">
            /// http://www.cnts.ua.ac.be/conll2000/chunking/</a>
            /// </summary>
            class ChunkSampleStream : public FilterObjectStream<std::string, ChunkSample*>
            {

              /// <summary>
              /// Initializes the current instance.
              /// </summary>
              /// <param name="samples"> a plain text line stream </param>
          public:
              ChunkSampleStream(ObjectStream<std::string> *samples);

              virtual ChunkSample *read() throw(IOException);
            };

        }
    }
}


#endif	//#ifndef CHUNKSAMPLESTREAM
