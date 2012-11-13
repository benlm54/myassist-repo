#ifndef HASHSUMEVENTSTREAM
#define HASHSUMEVENTSTREAM

#include "EventStream.h"
#include "Event.h"

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
    namespace model
    {


        using opennlp::model::Event;
        using opennlp::model::EventStream;

        class HashSumEventStream : public EventStream
        {

      private:
          EventStream *const eventStream;

          MessageDigest *digest;

      public:
          HashSumEventStream(EventStream *eventStream);

          virtual bool hasNext() throw(IOException);

          virtual Event *next() throw(IOException);

          /// <summary>
          /// Calculates the hash sum of the stream. The method must be
          /// called after the stream is completely consumed.
          /// </summary>
          /// <returns> the hash sum </returns>
          /// <exception cref="IllegalStateException"> if the stream is not consumed completely,
          /// completely means that hasNext() returns false </exception>
          virtual BigInteger *calculateHashSum();

          virtual void remove();
        };

    }
}


#endif	//#ifndef HASHSUMEVENTSTREAM
