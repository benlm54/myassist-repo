#ifndef CACHE
#define CACHE

#include <string>
#include <map>

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


            /// <summary>
            /// Provides fixed size, pre-allocated, least recently used replacement cache.
            /// </summary>
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @SuppressWarnings("unchecked") public class Cache implements java.util.Map
            class Cache : public Map
            {

              /// <summary>
              /// The element in the linked list which was most recently used. * </summary>
          private:
              DoubleLinkedListElement *first;
              /// <summary>
              /// The element in the linked list which was least recently used. * </summary>
              DoubleLinkedListElement *last;
              /// <summary>
              /// Temporary holder of the key of the least-recently-used element. </summary>
              void *lastKey;
              /// <summary>
              /// Temporary value used in swap. </summary>
              ObjectWrapper *temp;
              /// <summary>
              /// Holds the object wrappers which the keys are mapped to. </summary>
//ORIGINAL LINE: private ObjectWrapper[] wrappers;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              ObjectWrapper *wrappers;
              /// <summary>
              /// Map which stores the keys and values of the cache. </summary>
              Map *map;
              /// <summary>
              /// The size of the cache. </summary>
//JAVA TO C++ CONVERTER NOTE: The variable size was renamed since C++ does not allow variables with the same name as methods:
              int size_Renamed;

              /// <summary>
              /// Creates a new cache of the specified size. </summary>
              /// <param name="size"> The size of the cache. </param>
          public:
              Cache(int size);

              virtual void clear();

              virtual void *put(void *key, void *value);

              virtual void *get_Renamed(void *key);


              virtual bool containsKey(void *key);

              virtual bool containsValue(void *value);

              virtual Set *entrySet();

              virtual bool isEmpty();

              virtual Set *keySet();

              virtual void putAll(Map *t);

              virtual void *remove(void *key);

              virtual int size();

              virtual Collection *values();
            };

            class ObjectWrapper
            {

          public:
              void *object;
              DoubleLinkedListElement *listItem;

              ObjectWrapper(void *o, DoubleLinkedListElement *li);

              virtual void *getObject();

              virtual DoubleLinkedListElement *getListItem();

              virtual void setObject(void *o);

              virtual void setListItem(DoubleLinkedListElement *li);

              virtual bool eqauls(void *o);
            };

            class DoubleLinkedListElement
            {

          public:
              DoubleLinkedListElement *prev;
              DoubleLinkedListElement *next;
              void *object;

              DoubleLinkedListElement(DoubleLinkedListElement *p, DoubleLinkedListElement *n, void *o);
            };

            class DoubleLinkedList
            {

          public:
              DoubleLinkedListElement *first;
              DoubleLinkedListElement *last;
              DoubleLinkedListElement *current;

              DoubleLinkedList();

              virtual void addFirst(void *o);

              virtual void addLast(void *o);

              virtual void insert(void *o);

              virtual DoubleLinkedListElement *getFirst();

              virtual DoubleLinkedListElement *getLast();

              virtual DoubleLinkedListElement *getCurrent();

              virtual DoubleLinkedListElement *next();

              virtual DoubleLinkedListElement *prev();

              virtual std::string ToString();
            };

        }
    }
}


#endif	//#ifndef CACHE
