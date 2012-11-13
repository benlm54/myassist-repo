#ifndef SEQUENCESTREAMEVENTSTREAM
#define SEQUENCESTREAMEVENTSTREAM

#include "EventStream.h"
#include "Sequence.h"
#include "Event.h"
#include "SequenceStream.h"

/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

namespace opennlp
{
    namespace model
    {


        /// <summary>
        /// Class which turns a sequence stream into an event stream. 
        /// 
        /// </summary>
        class SequenceStreamEventStream : public EventStream
        {

      private:
          Iterator<Sequence*> *sequenceIterator;
      public:
          int eventIndex;
//ORIGINAL LINE: Event[] events;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          Event *events;

          SequenceStreamEventStream(SequenceStream *sequenceStream);

          virtual bool hasNext();

          virtual Event *next();

          virtual void remove();


        private:
            void InitializeInstanceFields();
        };

    }
}


#endif	//#ifndef SEQUENCESTREAMEVENTSTREAM
