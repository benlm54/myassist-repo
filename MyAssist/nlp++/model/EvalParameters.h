#ifndef EVALPARAMETERS
#define EVALPARAMETERS

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
         /// This class encapsulates the varibales used in producing probabilities from a model 
         /// and facilitaes passing these variables to the eval method.
         /// </summary>
        class EvalParameters
        {

         /// <summary>
         /// Mapping between outcomes and paramater values for each context. 
         /// The integer representation of the context can be found using <code>pmap</code>.
         /// </summary>
      private:
//ORIGINAL LINE: private Context[] params;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          Context *params;
          /// <summary>
          /// The number of outcomes being predicted. </summary>
          const int numOutcomes;
          /// <summary>
          /// The maximum number of feattures fired in an event. Usually refered to a C.
          /// This is used to normalize the number of features which occur in an event. 
          /// </summary>
          double correctionConstant;

          /// <summary>
          ///  Stores inverse of the correction constant, 1/C. </summary>
          const double constantInverse;
          /// <summary>
          /// The correction parameter of the model. </summary>
          double correctionParam;

          /// <summary>
          /// Creates a set of paramters which can be evaulated with the eval method. </summary>
          /// <param name="params"> The parameters of the model. </param>
          /// <param name="correctionParam"> The correction paramter. </param>
          /// <param name="correctionConstant"> The correction constant. </param>
          /// <param name="numOutcomes"> The number of outcomes. </param>
      public:
          EvalParameters(Context params[], double correctionParam, double correctionConstant, int numOutcomes);

//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
          EvalParameters(Context params[], int numOutcomes); //this(params,0,0,numOutcomes);

          /* (non-Javadoc)
           * @see opennlp.model.EvalParameters#getParams()
           */
          virtual Context *getParams();

          /* (non-Javadoc)
           * @see opennlp.model.EvalParameters#getNumOutcomes()
           */
          virtual int getNumOutcomes();

          virtual double getCorrectionConstant();

          virtual double getConstantInverse();

          virtual double getCorrectionParam();

          virtual void setCorrectionParam(double correctionParam);
        };
    }
}


#endif	//#ifndef EVALPARAMETERS
