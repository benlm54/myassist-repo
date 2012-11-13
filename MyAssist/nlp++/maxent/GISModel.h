#ifndef GISMODEL
#define GISMODEL

#include "../model/AbstractModel.h"
#include "../model/Context.h"
#include "../model/Prior.h"
#include "../model/EvalParameters.h"
#include <string>
#include <cmath>

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


        using opennlp::model::AbstractModel;
        using opennlp::model::Context;
        using opennlp::model::EvalParameters;
        using opennlp::model::Prior;
        using opennlp::model::UniformPrior;

        /// <summary>
        /// A maximum entropy model which has been trained using the Generalized
        /// Iterative Scaling procedure (implemented in GIS.java).
        /// </summary>
        class GISModel : public AbstractModel
        {

          /// <summary>
          /// Creates a new model with the specified parameters, outcome names, and
          /// predicate/feature labels.
          /// </summary>
          /// <param name="params">
          ///          The parameters of the model. </param>
          /// <param name="predLabels">
          ///          The names of the predicates used in this model. </param>
          /// <param name="outcomeNames">
          ///          The names of the outcomes this model predicts. </param>
          /// <param name="correctionConstant">
          ///          The maximum number of active features which occur in an event. </param>
          /// <param name="correctionParam">
          ///          The parameter associated with the correction feature. </param>
      public:
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
          GISModel(Context params[], std::string predLabels[], std::string outcomeNames[], int correctionConstant, double correctionParam); //this(params, predLabels, outcomeNames, correctionConstant, correctionParam, new UniformPrior());

          /// <summary>
          /// Creates a new model with the specified parameters, outcome names, and
          /// predicate/feature labels.
          /// </summary>
          /// <param name="params">
          ///          The parameters of the model. </param>
          /// <param name="predLabels">
          ///          The names of the predicates used in this model. </param>
          /// <param name="outcomeNames">
          ///          The names of the outcomes this model predicts. </param>
          /// <param name="correctionConstant">
          ///          The maximum number of active features which occur in an event. </param>
          /// <param name="correctionParam">
          ///          The parameter associated with the correction feature. </param>
          /// <param name="prior">
          ///          The prior to be used with this model. </param>
          GISModel(Context params[], std::string predLabels[], std::string outcomeNames[], int correctionConstant, double correctionParam, Prior *prior);

          /// <summary>
          /// Use this model to evaluate a context and return an array of the likelihood
          /// of each outcome given that context.
          /// </summary>
          /// <param name="context">
          ///          The names of the predicates which have been observed at the
          ///          present decision point. </param>
          /// <returns> The normalized probabilities for the outcomes given the context.
          ///         The indexes of the double[] are the outcome ids, and the actual
          ///         string representation of the outcomes can be obtained from the
          ///         method getOutcome(int i). </returns>
          double *eval(std::string context[]);

          double *eval(std::string context[], float values[]);

          double *eval(std::string context[], double outsums[]);

          /// <summary>
          /// Use this model to evaluate a context and return an array of the likelihood
          /// of each outcome given that context.
          /// </summary>
          /// <param name="context">
          ///          The names of the predicates which have been observed at the
          ///          present decision point. </param>
          /// <param name="outsums">
          ///          This is where the distribution is stored. </param>
          /// <returns> The normalized probabilities for the outcomes given the context.
          ///         The indexes of the double[] are the outcome ids, and the actual
          ///         string representation of the outcomes can be obtained from the
          ///         method getOutcome(int i). </returns>
          double *eval(std::string context[], float values[], double outsums[]);


          /// <summary>
          /// Use this model to evaluate a context and return an array of the likelihood
          /// of each outcome given the specified context and the specified parameters.
          /// </summary>
          /// <param name="context">
          ///          The integer values of the predicates which have been observed at
          ///          the present decision point. </param>
          /// <param name="prior">
          ///          The prior distribution for the specified context. </param>
          /// <param name="model">
          ///          The set of parametes used in this computation. </param>
          /// <returns> The normalized probabilities for the outcomes given the context.
          ///         The indexes of the double[] are the outcome ids, and the actual
          ///         string representation of the outcomes can be obtained from the
          ///         method getOutcome(int i). </returns>
          static double *eval(int context[], double prior[], EvalParameters *model);

          /// <summary>
          /// Use this model to evaluate a context and return an array of the likelihood
          /// of each outcome given the specified context and the specified parameters.
          /// </summary>
          /// <param name="context">
          ///          The integer values of the predicates which have been observed at
          ///          the present decision point. </param>
          /// <param name="values">
          ///          The values for each of the parameters. </param>
          /// <param name="prior">
          ///          The prior distribution for the specified context. </param>
          /// <param name="model">
          ///          The set of parametes used in this computation. </param>
          /// <returns> The normalized probabilities for the outcomes given the context.
          ///         The indexes of the double[] are the outcome ids, and the actual
          ///         string representation of the outcomes can be obtained from the
          ///         method getOutcome(int i). </returns>
          static double *eval(int context[], float values[], double prior[], EvalParameters *model);

          static void main(std::string args[]) throw(java::io::IOException);
        };
    }
}


#endif	//#ifndef GISMODEL
