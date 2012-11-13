#ifndef CHUNKEREVENTSTREAM
#define CHUNKEREVENTSTREAM

#include "../model/AbstractEventStream.h"
#include "ChunkerContextGenerator.h"
#include "ChunkSample.h"
#include "../tools/util/ObjectStream.h"
#include "../model/Event.h"
#include <string>
#include <stdexcept>

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


            using opennlp::model::Event;
            using opennlp::tools::util::ObjectStream;

            /// <summary>
            /// Class for creating an event stream out of data files for training a chunker.
            /// </summary>
            class ChunkerEventStream : public opennlp::model::AbstractEventStream
            {

          private:
              ChunkerContextGenerator *cg;
              ObjectStream<ChunkSample*> *data;
//ORIGINAL LINE: private opennlp.model.Event[] events;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              Event *events;
              int ei;


              /// <summary>
              /// Creates a new event stream based on the specified data stream using the specified context generator. </summary>
              /// <param name="d"> The data stream for this event stream. </param>
              /// <param name="cg"> The context generator which should be used in the creation of events for this event stream. </param>
          public:
              ChunkerEventStream(ObjectStream<ChunkSample*> *d, ChunkerContextGenerator *cg);

              /// <summary>
              /// Creates a new event stream based on the specified data stream. </summary>
              /// <param name="d"> The data stream for this event stream. </param>
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              ChunkerEventStream(ObjectStream<ChunkSample*> *d); //this(d, new DefaultChunkerContextGenerator());

              virtual Event *next();

              virtual bool hasNext();

          private:
              void addNewEvents();
            };

        }
    }
}


#endif	//#ifndef CHUNKEREVENTSTREAM
