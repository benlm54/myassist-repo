#ifndef COLLECTIONOBJECTSTREAM
#define COLLECTIONOBJECTSTREAM

#include "ObjectStream.h"
#include "ObjectStream<E>.h"

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


            template<typename E>
            class CollectionObjectStream : public ObjectStream<E>
            {
          private:
              Collection<E> *collection;

              Iterator<E> *iterator;

          public:
              CollectionObjectStream(Collection<E> *collection)
              {
                this->collection = collection;

                reset();
              }

              virtual E read()
              {
                if (iterator->hasNext())
                  return iterator->next();
                else
                  return 0;
              }

              virtual void reset()
              {
                this->iterator = collection->begin();
              }

              virtual void close()
              {
              }
            };
        }
    }
}


#endif	//#ifndef COLLECTIONOBJECTSTREAM
