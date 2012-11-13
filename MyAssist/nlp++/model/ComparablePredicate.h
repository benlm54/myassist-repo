#ifndef COMPARABLEPREDICATE
#define COMPARABLEPREDICATE

#include "Comparable<ComparablePredicate>.h"
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
        /// A maxent predicate representation which we can use to sort based on the
        /// outcomes. This allows us to make the mapping of features to their parameters
        /// much more compact.
        /// </summary>
        class ComparablePredicate : public Comparable<ComparablePredicate*>
        {
      public:
          std::string name;
//ORIGINAL LINE: public int[] outcomes;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          int *outcomes;
//ORIGINAL LINE: public double[] params;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          double *params;

          ComparablePredicate(const std::string &n, int ocs[], double ps[]);

          virtual int compareTo(ComparablePredicate *cp);

          virtual std::string ToString();

        };


    }
}


#endif	//#ifndef COMPARABLEPREDICATE
