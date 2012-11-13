#ifndef COMPARABLEEVENT
#define COMPARABLEEVENT

#include "Comparable.h"
#include "StringBuffer.h"
#include <string>

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
        /// A maxent event representation which we can use to sort based on the
        /// predicates indexes contained in the events.
        /// </summary>
        class ComparableEvent : public Comparable
        {
      public:
          int outcome;
//ORIGINAL LINE: public int[] predIndexes;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          int *predIndexes;
          int seen; // the number of times this event
                               // has been seen.

//ORIGINAL LINE: public float[] values;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          float *values;

          ComparableEvent(int oc, int pids[], float values[]);

//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
          ComparableEvent(int oc, int pids[]); //this(oc, pids, nullptr);

          virtual int compareTo(void *o);

          virtual std::string ToString();

      private:
          void sort(int pids[], float values[]);

        private:
            void InitializeInstanceFields();
        };


    }
}


#endif	//#ifndef COMPARABLEEVENT
