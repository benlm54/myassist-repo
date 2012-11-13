#ifndef FILTEROBJECTSTREAM
#define FILTEROBJECTSTREAM

#include "ObjectStream.h"
#include "ObjectStream<T>.h"

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
            /// Abstract base class for filtering <seealso cref="ObjectStream"/>s.
            /// <p>
            /// Filtering streams take an existing stream and convert 
            /// its output to something else.
            /// </summary>
            /// @param <S> the type of the source/input stream </param>
            /// @param <T> the type of this stream </param>
            template<typename S, typename T>
            class FilterObjectStream : public ObjectStream<T>
            {

          protected:
              ObjectStream<S> *const samples;

              FilterObjectStream(ObjectStream<S> *samples) : samples(samples)
              {
                if (samples == 0)
                  throw IllegalArgumentException("samples must not be null!");

              }

          public:
              virtual void reset() throw(IOException, UnsupportedOperationException)
              {
                samples->reset();
              }

              virtual void close() throw(IOException)
              {
                samples->close();
              }
            };

        }
    }
}


#endif	//#ifndef FILTEROBJECTSTREAM
