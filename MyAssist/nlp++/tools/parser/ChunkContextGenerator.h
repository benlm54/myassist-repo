#ifndef CHUNKCONTEXTGENERATOR
#define CHUNKCONTEXTGENERATOR

#include "../tools/chunker/ChunkerContextGenerator.h"
#include "../tools/util/Cache.h"
#include "StringBuffer.h"
#include <string>
#include <vector>

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
        namespace parser
        {


            using opennlp::tools::chunker::ChunkerContextGenerator;
            using opennlp::tools::util::Cache;

            /// <summary>
            /// Creates predivtive context for the pre-chunking phases of parsing.
            /// </summary>
            class ChunkContextGenerator : public ChunkerContextGenerator
            {

          private:
              static const std::string EOS;
              Cache *contextsCache;
              void *wordsKey;


          public:
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              ChunkContextGenerator(); //this(0);

//JAVA TO C++ CONVERTER TODO TASK: No base class can be determined:
              ChunkContextGenerator(int cacheSize); //super();

              virtual std::string *getContext(void *o);

              virtual std::string *getContext(int i, std::string words[], std::string prevDecisions[], Object ac[]);

              virtual std::string *getContext(int i, std::string words[], std::string tags[], std::string preds[]);

          private:
              std::string chunkandpostag(int i, const std::string &tok, const std::string &tag, const std::string &chunk);

              std::string chunkandpostagbo(int i, const std::string &tag, const std::string &chunk);
            };

        }
    }
}


#endif	//#ifndef CHUNKCONTEXTGENERATOR
