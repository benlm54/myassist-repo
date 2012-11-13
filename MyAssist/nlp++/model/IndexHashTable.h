#ifndef INDEXHASHTABLE
#define INDEXHASHTABLE

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
        /// The <seealso cref="IndexHashTable"/> is a hash table which maps entries
        /// of an array to their index in the array. All entries in the array must
        /// be unique otherwise a well-defined mapping is not possible.
        /// <p>
        /// The entry objects must implement <seealso cref="Object#equals(Object)"/> and
        /// <seealso cref="Object#hashCode()"/> otherwise the behavior of this class is
        /// undefined.
        /// <p>
        /// The implementation uses a hash table with open addressing and linear probing.
        /// <p>
        /// The table is thread safe and can concurrently accessed by multiple threads,
        /// thread safety is achieved through immutability. Though its not strictly immutable
        /// which means, that the table must still be safely published to other threads.
        /// </summary>
        template<typename T>
        class IndexHashTable
        {

      private:
//ORIGINAL LINE: private final Object keys[];
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          const void *keys;
//ORIGINAL LINE: private final int values[];
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          const int *values;

//JAVA TO C++ CONVERTER NOTE: The variable size was renamed since C++ does not allow variables with the same name as methods:
          const int size_Renamed;

          /// <summary>
          /// Initializes the current instance. The specified array is copied into the
          /// table and later changes to the array do not affect this table in any way.
          /// </summary>
          /// <param name="mapping">
          ///          the values to be indexed, all values must be unique otherwise a
          ///          well-defined mapping of an entry to an index is not possible </param>
          /// <param name="loadfactor">
          ///          the load factor, usually 0.7
          /// </param>
          /// <exception cref="IllegalArgumentException">
          ///           if the entries are not unique </exception>
      public:
          IndexHashTable(T mapping[], double loadfactor) : keys(new Object[arraySize]), values(new int[arraySize]), size(sizeof(mapping) / sizeof(mapping[0]))
          {
            if (loadfactor <= 0 || loadfactor > 1)
              throw IllegalArgumentException("loadfactor must be larger than 0 " + "and equal to or smaller than 1!");

            int arraySize = static_cast<int>(sizeof(mapping) / sizeof(mapping[0]) / loadfactor) + 1;



            for (int i = 0; i < sizeof(mapping) / sizeof(mapping[0]); i++)
            {
              int startIndex = indexForHash(mapping[i]->hashCode(), keys->length);

              int index = searchKey(startIndex, 0, true);

              if (index == -1)
                throw IllegalArgumentException("Array must contain only unique keys!");

              keys[index] = mapping[i];
              values[index] = i;
            }
          }

      private:
          static int indexForHash(int h, int length)
          {
            return (h & 0x7fffffff) % length;
          }

          int searchKey(int startIndex, void *key, bool insert)
          {

            for (int index = startIndex; true; index = (index + 1) % keys->length)
            {

              // The keys array contains at least one null element, which guarantees
              // termination of the loop
              if (keys[index] == 0)
              {
                if (insert)
                  return index;
                else
                  return -1;
              }

              if (keys[index]->equals(key))
              {
                if (!insert)
                  return index;
                else
                  return -1;
              }
            }
          }

          /// <summary>
          /// Retrieves the index for the specified key.
          /// </summary>
          /// <param name="key"> </param>
          /// <returns> the index or -1 if there is no entry to the keys </returns>
      public:
          virtual int get_Renamed(T key)
          {

            int startIndex = indexForHash(key->hashCode(), keys->length);

            int index = searchKey(startIndex, key, false);

            if (index != -1)
            {
              return values[index];
            }
            else
            {
              return -1;
            }
          }

          /// <summary>
          /// Retrieves the size.
          /// </summary>
          /// <returns> the number of elements in this map. </returns>
          virtual int size()
          {
            return size_Renamed;
          }

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @SuppressWarnings("unchecked") public T[] toArray(T array[])
          virtual T *toArray(array_Renamed<T> *array_Renamed)
          {
            for (int i = 0; i < keys->length; i++)
            {
              if (keys[i] != 0)
                array_Renamed[values[i]] = static_cast<T>(keys[i]);
            }

            return array_Renamed;
          }
        };

    }
}


#endif	//#ifndef INDEXHASHTABLE
