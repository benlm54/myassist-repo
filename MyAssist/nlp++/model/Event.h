#ifndef EVENT
#define EVENT

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
        /// The context of a decision point during training.  This includes
        /// contextual predicates and an outcome.
        /// </summary>
        class Event
        {
        private:
            std::string outcome;
//ORIGINAL LINE: private String[] context;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
            std::string *context;
//ORIGINAL LINE: private float[] values;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
            float *values;

        public:
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
            Event(const std::string &outcome, std::string context[]); //this(outcome,context,nullptr);

            Event(const std::string &outcome, std::string context[], float values[]);

            virtual std::string getOutcome();

            virtual std::string *getContext();

            virtual float *getValues();

            virtual std::string ToString();

        };

    }
}


#endif	//#ifndef EVENT
