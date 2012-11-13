#ifndef ABSTRACTEVENTSTREAM
#define ABSTRACTEVENTSTREAM

#include "ObjectStream.h"
#include "../model/Event.h"
#include "T.h"

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
        namespace util
        {


            using opennlp::model::Event;
            using opennlp::model::EventStream;

            /// <summary>
            /// This is a base class for <seealso cref="EventStream"/> classes.
            /// It takes an <seealso cref="Iterator"/> of sample objects as input and
            /// outputs the events creates by a subclass.
            /// </summary>
            template<typename T>
            class AbstractEventStream : public opennlp::model::AbstractEventStream
            {

          private:
              ObjectStream<T> *samples;

              Iterator<Event*> *events;

              /// <summary>
              /// Initializes the current instance with a sample <seealso cref="Iterator"/>.
              /// </summary>
              /// <param name="samples"> the sample <seealso cref="Iterator"/>. </param>
          public:
              AbstractEventStream(ObjectStream<T> *samples)
              {
                InitializeInstanceFields();
                this->samples = samples;
              }

              /// <summary>
              /// Creates events for the provided sample.
              /// </summary>
              /// <param name="sample"> the sample for which training <seealso cref="Event"/>s
              /// are be created.
              /// </param>
              /// <returns> an <seealso cref="Iterator"/> of training events or
              /// an empty <seealso cref="Iterator"/>. </returns>
          protected:
              virtual Iterator<Event*> *createEvents(T sample) = 0;

              /// <summary>
              /// Checks if there are more training events available.
              /// 
              /// </summary>
          public:
              bool hasNext() throw(IOException)
              {

                if (events->hasNext())
                {
                  return true;
                }
                else
                {
                  // search next event iterator which is not empty
                  T sample = 0;
                  while (!events->hasNext() && (sample = samples->read()) != 0)
                  {
                    events = createEvents(sample);
                  }

                  return events->hasNext();
                }
              }

              Event *next()
              {
                return events->next();
              }

            private:
                void InitializeInstanceFields()
                {
                    events = java::util::Collections::emptyList<opennlp::model::Event*>()->begin();
                }
            };

        }
    }
}


#endif	//#ifndef ABSTRACTEVENTSTREAM
