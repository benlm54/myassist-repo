#ifndef MAXENTMODEL
#define MAXENTMODEL

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
        /// Interface for maximum entropy models.
        /// 
        /// </summary>
        class MaxentModel
        {

          /// <summary>
          /// Evaluates a context.
          /// </summary>
          /// <param name="context"> A list of String names of the contextual predicates
          ///                which are to be evaluated together. </param>
          /// <returns> an array of the probabilities for each of the different
          ///         outcomes, all of which sum to 1.
          /// 
          ///  </returns>
      public:
          virtual double *eval(std::string context[]) = 0;

          /// <summary>
          /// Evaluates a context.
          /// </summary>
          /// <param name="context"> A list of String names of the contextual predicates
          ///                which are to be evaluated together. </param>
          /// <param name="probs"> An array which is populated with the probabilities for each of the different
          ///         outcomes, all of which sum to 1. </param>
          /// <returns> an array of the probabilities for each of the different outcomes, all of which sum to 1. 
          ///    </returns>
          virtual double *eval(std::string context[], double probs[]) = 0;

          /// <summary>
          /// Evaluates a contexts with the specified context values. </summary>
          /// <param name="context"> A list of String names of the contextual predicates
          ///                which are to be evaluated together. </param>
          /// <param name="values"> The values associated with each context. </param>
          /// <returns> an array of the probabilities for each of the different outcomes, all of which sum to 1. </returns>
          virtual double *eval(std::string context[], float values[]) = 0;

          /// <summary>
          /// Simple function to return the outcome associated with the index
          /// containing the highest probability in the double[].
          /// </summary>
          /// <param name="outcomes"> A <code>double[]</code> as returned by the
          ///            <code>eval(String[] context)</code>
          ///            method. </param>
          /// <returns> the String name of the best outcome
          ///  </returns>
          virtual std::string getBestOutcome(double outcomes[]) = 0;

          /// <summary>
          /// Return a string matching all the outcome names with all the
          /// probabilities produced by the <code>eval(String[]
          /// context)</code> method.
          /// </summary>
          /// <param name="outcomes"> A <code>double[]</code> as returned by the
          ///            <code>eval(String[] context)</code>
          ///            method. </param>
          /// <returns>    String containing outcome names paired with the normalized
          ///            probability (contained in the <code>double[] ocs</code>)
          ///            for each one.
          ///  </returns>
          virtual std::string getAllOutcomes(double outcomes[]) = 0;

          /// <summary>
          /// Gets the String name of the outcome associated with the index
          /// i.
          /// </summary>
          /// <param name="i"> the index for which the name of the associated outcome is
          ///          desired. </param>
          /// <returns> the String name of the outcome
          ///  </returns>
          virtual std::string getOutcome(int i) = 0;

          /// <summary>
          /// Gets the index associated with the String name of the given
          /// outcome.
          /// </summary>
          /// <param name="outcome"> the String name of the outcome for which the
          ///          index is desired </param>
          /// <returns> the index if the given outcome label exists for this
          /// model, -1 if it does not.
          ///  </returns>
          virtual int getIndex(const std::string &outcome) = 0;

          /// <summary>
          /// Returns the data structures relevant to storing the model.
          /// 
          /// </summary>
          virtual void *getDataStructures() = 0;

          /// <summary>
          /// Returns the number of outcomes for this model. </summary>
          ///  <returns> The number of outcomes.
          ///  </returns>
          virtual int getNumOutcomes() = 0;

        };

    }
}


#endif	//#ifndef MAXENTMODEL
