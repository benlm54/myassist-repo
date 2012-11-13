#ifndef GISTRAINER
#define GISTRAINER

#include "../model/MutableContext.h"
#include "../model/Prior.h"
#include "../model/EvalParameters.h"
#include "GISModel.h"
#include "../model/EventStream.h"
#include "../model/DataIndexer.h"
#include "synchronized.h"
#include "InterruptedException.h"
#include <string>
#include <vector>
#include <cmath>
#include <stdexcept>

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


        using opennlp::model::DataIndexer;
        using opennlp::model::EvalParameters;
        using opennlp::model::EventStream;
        using opennlp::model::MutableContext;
        using opennlp::model::OnePassDataIndexer;
        using opennlp::model::Prior;
        using opennlp::model::UniformPrior;


        /// <summary>
        /// An implementation of Generalized Iterative Scaling.  The reference paper
        /// for this implementation was Adwait Ratnaparkhi's tech report at the
        /// University of Pennsylvania's Institute for Research in Cognitive Science,
        /// and is available at <a href ="ftp://ftp.cis.upenn.edu/pub/ircs/tr/97-08.ps.Z"><code>ftp://ftp.cis.upenn.edu/pub/ircs/tr/97-08.ps.Z</code></a>. 
        /// 
        /// The slack parameter used in the above implementation has been removed by default
        /// from the computation and a method for updating with Gaussian smoothing has been
        /// added per Investigating GIS and Smoothing for Maximum Entropy Taggers, Clark and Curran (2002).  
        /// <a href="http://acl.ldc.upenn.edu/E/E03/E03-1071.pdf"><code>http://acl.ldc.upenn.edu/E/E03/E03-1071.pdf</code></a>
        /// The slack parameter can be used by setting <code>useSlackParameter</code> to true.
        /// Gaussian smoothing can be used by setting <code>useGaussianSmoothing</code> to true. 
        /// 
        /// A prior can be used to train models which converge to the distribution which minimizes the
        /// relative entropy between the distribution specified by the empirical constraints of the training
        /// data and the specified prior.  By default, the uniform distribution is used as the prior.
        /// </summary>
        class GISTrainer
        {
      private:
          class ModelExpactationComputeTask : public Callable<ModelExpactationComputeTask*>
          {
              private:
                  GISTrainer *const outerInstance;


            const int startIndex;
            const int length;

            double loglikelihood;

            int numEvents;
            int numCorrect;

            const int threadIndex;

            // startIndex to compute, number of events to compute
        public:
            ModelExpactationComputeTask(GISTrainer *outerInstance, int threadIndex, int startIndex, int length);

            virtual ModelExpactationComputeTask *call();

            virtual int getNumEvents();

            virtual int getNumCorrect();

            virtual double getLoglikelihood();

          private:
              void InitializeInstanceFields();
          };


          /// <summary>
          /// Specifies whether unseen context/outcome pairs should be estimated as occur very infrequently.
          /// </summary>
      private:
          bool useSimpleSmoothing;

          /// <summary>
          /// Specified whether parameter updates should prefer a distribution of parameters which
          /// is gaussian.
          /// </summary>
          bool useGaussianSmoothing;

          double sigma;

          // If we are using smoothing, this is used as the "number" of
          // times we want the trainer to imagine that it saw a feature that it
          // actually didn't see.  Defaulted to 0.1.
          double _smoothingObservation;

          const bool printMessages;

          /// <summary>
          /// Number of unique events which occured in the event set. 
          /// </summary>
          int numUniqueEvents;

          /// <summary>
          /// Number of predicates. 
          /// </summary>
          int numPreds;

          /// <summary>
          /// Number of outcomes. 
          /// </summary>
          int numOutcomes;

          /// <summary>
          /// Records the array of predicates seen in each event.
          /// </summary>
//ORIGINAL LINE: private int[][] contexts;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          int **contexts;

          /// <summary>
          /// The value associated with each context. If null then context values are assumes to be 1.
          /// </summary>
//ORIGINAL LINE: private float[][] values;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          float **values;

          /// <summary>
          /// List of outcomes for each event i, in context[i].
          /// </summary>
//ORIGINAL LINE: private int[] outcomeList;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          int *outcomeList;

          /// <summary>
          /// Records the num of times an event has been seen for each event i, in context[i].
          /// </summary>
//ORIGINAL LINE: private int[] numTimesEventsSeen;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          int *numTimesEventsSeen;

          /// <summary>
          /// The number of times a predicate occured in the training data.
          /// </summary>
//ORIGINAL LINE: private int[] predicateCounts;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          int *predicateCounts;

          int cutoff;

          /// <summary>
          /// Stores the String names of the outcomes. The GIS only tracks outcomes as
          /// ints, and so this array is needed to save the model to disk and thereby
          /// allow users to know what the outcome was in human understandable terms.
          /// </summary>
//ORIGINAL LINE: private String[] outcomeLabels;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          std::string *outcomeLabels;

          /// <summary>
          /// Stores the String names of the predicates. The GIS only tracks predicates
          /// as ints, and so this array is needed to save the model to disk and thereby
          /// allow users to know what the outcome was in human understandable terms.
          /// </summary>
//ORIGINAL LINE: private String[] predLabels;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          std::string *predLabels;

          /// <summary>
          /// Stores the observed expected values of the features based on training data.
          /// </summary>
//ORIGINAL LINE: private opennlp.model.MutableContext[] observedExpects;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          MutableContext *observedExpects;

          /// <summary>
          /// Stores the estimated parameter value of each predicate during iteration
          /// </summary>
//ORIGINAL LINE: private opennlp.model.MutableContext[] params;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          MutableContext *params;

          /// <summary>
          /// Stores the expected values of the features based on the current models 
          /// </summary>
//ORIGINAL LINE: private opennlp.model.MutableContext[][] modelExpects;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          MutableContext **modelExpects;

          /// <summary>
          /// This is the prior distribution that the model uses for training.
          /// </summary>
          Prior *prior;

          static const double LLThreshold;

          /// <summary>
          /// Initial probability for all outcomes.
          /// </summary>
          EvalParameters *evalParams;

          /// <summary>
          /// Creates a new <code>GISTrainer</code> instance which does not print
          /// progress messages about training to STDOUT.
          /// 
          /// </summary>
      public:
          GISTrainer();

          /// <summary>
          /// Creates a new <code>GISTrainer</code> instance.
          /// </summary>
          /// <param name="printMessages"> sends progress messages about training to
          ///                      STDOUT when true; trains silently otherwise. </param>
          GISTrainer(bool printMessages);

          /// <summary>
          /// Sets whether this trainer will use smoothing while training the model.
          /// This can improve model accuracy, though training will potentially take
          /// longer and use more memory.  Model size will also be larger.
          /// </summary>
          /// <param name="smooth"> true if smoothing is desired, false if not </param>
          virtual void setSmoothing(bool smooth);

          /// <summary>
          /// Sets whether this trainer will use smoothing while training the model.
          /// This can improve model accuracy, though training will potentially take
          /// longer and use more memory.  Model size will also be larger.
          /// </summary>
          /// <param name="timesSeen"> the "number" of times we want the trainer to imagine
          ///                  it saw a feature that it actually didn't see </param>
          virtual void setSmoothingObservation(double timesSeen);

          /// <summary>
          /// Sets whether this trainer will use smoothing while training the model.
          /// This can improve model accuracy, though training will potentially take
          /// longer and use more memory.  Model size will also be larger.
          /// </summary>
          /// <param name="smooth"> true if smoothing is desired, false if not </param>
          virtual void setGaussianSigma(double sigmaValue);

          /// <summary>
          /// Trains a GIS model on the event in the specified event stream, using the specified number
          /// of iterations and the specified count cutoff. </summary>
          /// <param name="eventStream"> A stream of all events. </param>
          /// <param name="iterations"> The number of iterations to use for GIS. </param>
          /// <param name="cutoff"> The number of times a feature must occur to be included. </param>
          /// <returns> A GIS model trained with specified  </returns>
          virtual GISModel *trainModel(EventStream *eventStream, int iterations, int cutoff) throw(IOException);

          /// <summary>
          /// Train a model using the GIS algorithm.
          /// </summary>
          /// <param name="iterations">  The number of GIS iterations to perform. </param>
          /// <param name="di"> The data indexer used to compress events in memory. </param>
          /// <returns> The newly trained model, which can be used immediately or saved
          ///         to disk using an opennlp.maxent.io.GISModelWriter object. </returns>
          virtual GISModel *trainModel(int iterations, DataIndexer *di, int cutoff);

          /// <summary>
          /// Train a model using the GIS algorithm.
          /// </summary>
          /// <param name="iterations">  The number of GIS iterations to perform. </param>
          /// <param name="di"> The data indexer used to compress events in memory. </param>
          /// <param name="modelPrior"> The prior distribution used to train this model. </param>
          /// <returns> The newly trained model, which can be used immediately or saved
          ///         to disk using an opennlp.maxent.io.GISModelWriter object. </returns>
          virtual GISModel *trainModel(int iterations, DataIndexer *di, Prior *modelPrior, int cutoff, int threads);

          /* Estimate and return the model parameters. */
      private:
          void findParameters(int iterations, double correctionConstant);

          //modeled on implementation in  Zhang Le's maxent kit
          double gaussianUpdate(int predicate, int oid, int n, double correctionConstant);

          /* Compute one iteration of GIS and retutn log-likelihood.*/
          double nextIteration(double correctionConstant);

          void display(const std::string &s);

        private:
            void InitializeInstanceFields();
        };

    }
}


#endif	//#ifndef GISTRAINER
