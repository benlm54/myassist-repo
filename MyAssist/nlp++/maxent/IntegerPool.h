#ifndef INTEGERPOOL
#define INTEGERPOOL

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
    namespace maxent
    {

        /// <summary>
        /// A pool of read-only, unsigned Integer objects within a fixed,
        /// non-sparse range.  Use this class for operations in which a large
        /// number of Integer wrapper objects will be created.
        /// </summary>
        class IntegerPool
        {
        private:
//ORIGINAL LINE: private Integer[] _table;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
            int *_table;

          /// <summary>
          /// Creates an IntegerPool with 0..size Integer objects.
          /// </summary>
          /// <param name="size">
          ///          the size of the pool. </param>
      public:
          IntegerPool(int size);

          /// <summary>
          /// Returns the shared Integer wrapper for <tt>value</tt> if it is inside the
          /// range managed by this pool. if <tt>value</tt> is outside the range, a new
          /// Integer instance is returned.
          /// </summary>
          /// <param name="value">
          ///          an <code>int</code> value </param>
          /// <returns> an <code>Integer</code> value </returns>
          virtual int get_Renamed(int value);
        };

    }
}


#endif	//#ifndef INTEGERPOOL
