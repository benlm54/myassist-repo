#ifndef ABSTRACTMODEL
#define ABSTRACTMODEL

#include "MaxentModel.h"
#include "IndexHashTable.h"
#include "EvalParameters.h"
#include "Prior.h"
#include "Context.h"
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


        class AbstractModel : public MaxentModel
        {
      public:
          enum ModelType
          {
              MAXENT,
              PERCEPTRON
          };


          /// <summary>
          /// Mapping between predicates/contexts and an integer representing them. </summary>
      protected:
          IndexHashTable<std::string> *pmap;
          /// <summary>
          /// The names of the outcomes. </summary>
//ORIGINAL LINE: protected String[] outcomeNames;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          std::string *outcomeNames;
          /// <summary>
          /// Parameters for the model. </summary>
          EvalParameters *evalParams;
          /// <summary>
          /// Prior distribution for this model. </summary>
          Prior *prior;

          /// <summary>
          /// The type of the model. </summary>
          ModelType modelType;

      public:
          AbstractModel(Context params[], std::string predLabels[], IndexHashTable<std::string> *pmap, std::string outcomeNames[]);

          AbstractModel(Context params[], std::string predLabels[], std::string outcomeNames[]);

          AbstractModel(Context params[], std::string predLabels[], std::string outcomeNames[], int correctionConstant, double correctionParam);

      private:
          void init(std::string predLabels[], std::string outcomeNames[]);


          /// <summary>
          /// Return the name of the outcome corresponding to the highest likelihood
          /// in the parameter ocs.
          /// </summary>
          /// <param name="ocs"> A double[] as returned by the eval(String[] context)
          ///            method. </param>
          /// <returns>    The name of the most likely outcome. </returns>
      public:
          std::string getBestOutcome(double ocs[]);

          virtual ModelType getModelType();

          /// <summary>
          /// Return a string matching all the outcome names with all the
          /// probabilities produced by the <code>eval(String[] context)</code>
          /// method.
          /// </summary>
          /// <param name="ocs"> A <code>double[]</code> as returned by the
          ///            <code>eval(String[] context)</code>
          ///            method. </param>
          /// <returns>    String containing outcome names paired with the normalized
          ///            probability (contained in the <code>double[] ocs</code>)
          ///            for each one. </returns>
          std::string getAllOutcomes(double ocs[]);

          /// <summary>
          /// Return the name of an outcome corresponding to an int id.
          /// </summary>
          /// <param name="i"> An outcome id. </param>
          /// <returns>  The name of the outcome associated with that id. </returns>
          std::string getOutcome(int i);

          /// <summary>
          /// Gets the index associated with the String name of the given outcome.
          /// </summary>
          /// <param name="outcome"> the String name of the outcome for which the
          ///          index is desired </param>
          /// <returns> the index if the given outcome label exists for this
          /// model, -1 if it does not.
          ///  </returns>
          virtual int getIndex(const std::string &outcome);

          virtual int getNumOutcomes();

          /// <summary>
          /// Provides the fundamental data structures which encode the maxent model
          /// information.  This method will usually only be needed by
          /// GISModelWriters.  The following values are held in the Object array
          /// which is returned by this method:
          /// 
          /// <li>index 0: opennlp.maxent.Context[] containing the model
          ///            parameters  
          /// <li>index 1: java.util.Map containing the mapping of model predicates
          ///            to unique integers
          /// <li>index 2: java.lang.String[] containing the names of the outcomes,
          ///            stored in the index of the array which represents their
          /// 	          unique ids in the model.
          /// <li>index 3: java.lang.Integer containing the value of the models
          ///            correction constant
          /// <li>index 4: java.lang.Double containing the value of the models
          ///            correction parameter
          /// </summary>
          /// <returns> An Object[] with the values as described above. </returns>
          void *getDataStructures();
        };

    }
}


#endif	//#ifndef ABSTRACTMODEL
