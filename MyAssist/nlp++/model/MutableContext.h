#ifndef MUTABLECONTEXT
#define MUTABLECONTEXT

#include "Context.h"

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
        /// Class used to store parameters or expected values associated with this context which
        /// can be updated or assigned. 
        /// </summary>
        class MutableContext : public Context
        {

          /// <summary>
          /// Creates a new parameters object with the specified parameters associated with the specified
          /// outcome pattern.
          /// </summary>
          /// <param name="outcomePattern"> Array of outcomes for which parameters exists for this context. </param>
          /// <param name="parameters"> Parameters for the outcomes specified. </param>
      public:
          MutableContext(int outcomePattern[], double parameters[]);

          /// <summary>
          /// Assigns the parameter or expected value at the specified outcomeIndex the specified value. 
          /// </summary>
          /// <param name="outcomeIndex"> The index of the parameter or expected value to be updated. </param>
          /// <param name="value"> The value to be assigned. </param>
          virtual void setParameter(int outcomeIndex, double value);

          /// <summary>
          /// Updated the parameter or expected value at the specified outcomeIndex by adding the specified value to its current value.
          /// </summary>
          /// <param name="outcomeIndex"> The index of the parameter or expected value to be updated. </param>
          /// <param name="value"> The value to be added. </param>
          virtual void updateParameter(int outcomeIndex, double value);

          virtual bool contains(int outcome);
        };

    }
}


#endif	//#ifndef MUTABLECONTEXT
