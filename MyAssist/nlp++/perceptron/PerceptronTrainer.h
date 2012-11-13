#ifndef PERCEPTRONTRAINER
#define PERCEPTRONTRAINER

#include "../model/AbstractModel.h"
#include "../model/DataIndexer.h"
#include "../model/MutableContext.h"
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
    namespace perceptron
    {

        using opennlp::model::AbstractModel;
        using opennlp::model::DataIndexer;
        using opennlp::model::EvalParameters;
        using opennlp::model::MutableContext;

        /// <summary>
        /// Trains models using the perceptron algorithm.  Each outcome is represented as
        /// a binary perceptron classifier.  This supports standard (integer) weighting as well
        /// average weighting as described in:
        /// Discriminative Training Methods for Hidden Markov Models: Theory and Experiments
        /// with the Perceptron Algorithm. Michael Collins, EMNLP 2002.
        /// 
        /// </summary>
        class PerceptronTrainer
        {

      public:
          static const double TOLERANCE_DEFAULT;

          /// <summary>
          /// Number of unique events which occurred in the event set. </summary>
      private:
          int numUniqueEvents;
          /// <summary>
          /// Number of events in the event set. </summary>
          int numEvents;

          /// <summary>
          /// Number of predicates. </summary>
          int numPreds;
          /// <summary>
          /// Number of outcomes. </summary>
          int numOutcomes;
          /// <summary>
          /// Records the array of predicates seen in each event. </summary>
//ORIGINAL LINE: private int[][] contexts;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          int **contexts;

          /// <summary>
          /// The value associates with each context. If null then context values are assumes to be 1. </summary>
//ORIGINAL LINE: private float[][] values;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          float **values;

          /// <summary>
          /// List of outcomes for each event i, in context[i]. </summary>
//ORIGINAL LINE: private int[] outcomeList;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          int *outcomeList;

          /// <summary>
          /// Records the num of times an event has been seen for each event i, in context[i]. </summary>
//ORIGINAL LINE: private int[] numTimesEventsSeen;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          int *numTimesEventsSeen;

          /// <summary>
          /// Stores the String names of the outcomes.  The GIS only tracks outcomes
          /// as ints, and so this array is needed to save the model to disk and
          /// thereby allow users to know what the outcome was in human
          /// understandable terms. 
          /// </summary>
//ORIGINAL LINE: private String[] outcomeLabels;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          std::string *outcomeLabels;

          /// <summary>
          /// Stores the String names of the predicates. The GIS only tracks
          /// predicates as ints, and so this array is needed to save the model to
          /// disk and thereby allow users to know what the outcome was in human
          /// understandable terms. 
          /// </summary>
//ORIGINAL LINE: private String[] predLabels;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          std::string *predLabels;

          bool printMessages;

          double tolerance;

          double stepSizeDecrease;

          bool useSkippedlAveraging;

          /// <summary>
          /// Specifies the tolerance. If the change in training set accuracy
          /// is less than this, stop iterating.
          /// </summary>
          /// <param name="tolerance"> </param>
      public:
          virtual void setTolerance(double tolerance);

          /// <summary>
          /// Enables and sets step size decrease. The step size is
          /// decreased every iteration by the specified value.
          /// </summary>
          /// <param name="decrease"> - step size decrease in percent </param>
          virtual void setStepSizeDecrease(double decrease);

          /// <summary>
          /// Enables skipped averaging, this flag changes the standard
          /// averaging to special averaging instead.
          /// <p>
          /// If we are doing averaging, and the current iteration is one
          /// of the first 20 or it is a perfect square, then updated the
          /// summed parameters. 
          /// <p>
          /// The reason we don't take all of them is that the parameters change
          /// less toward the end of training, so they drown out the contributions
          /// of the more volatile early iterations. The use of perfect
          /// squares allows us to sample from successively farther apart iterations.
          /// </summary>
          /// <param name="averaging">
          /// 
          /// @return </param>
          virtual void setSkippedAveraging(bool averaging);

          virtual AbstractModel *trainModel(int iterations, DataIndexer *di, int cutoff);

          virtual AbstractModel *trainModel(int iterations, DataIndexer *di, int cutoff, bool useAverage);

      private:
          MutableContext *findParameters(int iterations, bool useAverage);

          double trainingStats(EvalParameters *evalParams);


          int maxIndex(double values[]);

          void display(const std::string &s);

          void displayIteration(int i);

          // See whether a number is a perfect square. Inefficient, but fine
          // for our purposes.
          static bool isPerfectSquare(int n);


        private:
            void InitializeInstanceFields();

public:
            PerceptronTrainer()
            {
                InitializeInstanceFields();
            }
        };

    }
}


#endif	//#ifndef PERCEPTRONTRAINER
