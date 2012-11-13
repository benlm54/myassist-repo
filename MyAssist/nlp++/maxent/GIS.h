#ifndef GIS
#define GIS

#include "GISModel.h"
#include "../model/EventStream.h"
#include "../model/DataIndexer.h"
#include "../model/Prior.h"

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
        using opennlp::model::EventStream;
        using opennlp::model::Prior;
        using opennlp::model::UniformPrior;

        /// <summary>
        /// A Factory class which uses instances of GISTrainer to create and train
        /// GISModels.
        /// </summary>
        class GIS
        {
          /// <summary>
          /// Set this to false if you don't want messages about the progress of model
          /// training displayed. Alternately, you can use the overloaded version of
          /// trainModel() to conditionally enable progress messages.
          /// </summary>
      public:
          static bool PRINT_MESSAGES;

          /// <summary>
          /// If we are using smoothing, this is used as the "number" of times we want
          /// the trainer to imagine that it saw a feature that it actually didn't see.
          /// Defaulted to 0.1.
          /// </summary>
          static double SMOOTHING_OBSERVATION;

          /// <summary>
          /// Train a model using the GIS algorithm, assuming 100 iterations and no
          /// cutoff.
          /// </summary>
          /// <param name="eventStream">
          ///          The EventStream holding the data on which this model will be
          ///          trained. </param>
          /// <returns> The newly trained model, which can be used immediately or saved to
          ///         disk using an opennlp.maxent.io.GISModelWriter object. </returns>
          static GISModel *trainModel(EventStream *eventStream) throw(IOException);

          /// <summary>
          /// Train a model using the GIS algorithm, assuming 100 iterations and no
          /// cutoff.
          /// </summary>
          /// <param name="eventStream">
          ///          The EventStream holding the data on which this model will be
          ///          trained. </param>
          /// <param name="smoothing">
          ///          Defines whether the created trainer will use smoothing while
          ///          training the model. </param>
          /// <returns> The newly trained model, which can be used immediately or saved to
          ///         disk using an opennlp.maxent.io.GISModelWriter object. </returns>
          static GISModel *trainModel(EventStream *eventStream, bool smoothing) throw(IOException);

          /// <summary>
          /// Train a model using the GIS algorithm.
          /// </summary>
          /// <param name="eventStream">
          ///          The EventStream holding the data on which this model will be
          ///          trained. </param>
          /// <param name="iterations">
          ///          The number of GIS iterations to perform. </param>
          /// <param name="cutoff">
          ///          The number of times a feature must be seen in order to be relevant
          ///          for training. </param>
          /// <returns> The newly trained model, which can be used immediately or saved to
          ///         disk using an opennlp.maxent.io.GISModelWriter object. </returns>
          static GISModel *trainModel(EventStream *eventStream, int iterations, int cutoff) throw(IOException);

          /// <summary>
          /// Train a model using the GIS algorithm.
          /// </summary>
          /// <param name="eventStream">
          ///          The EventStream holding the data on which this model will be
          ///          trained. </param>
          /// <param name="iterations">
          ///          The number of GIS iterations to perform. </param>
          /// <param name="cutoff">
          ///          The number of times a feature must be seen in order to be relevant
          ///          for training. </param>
          /// <param name="smoothing">
          ///          Defines whether the created trainer will use smoothing while
          ///          training the model. </param>
          /// <param name="printMessagesWhileTraining">
          ///          Determines whether training status messages are written to STDOUT. </param>
          /// <returns> The newly trained model, which can be used immediately or saved to
          ///         disk using an opennlp.maxent.io.GISModelWriter object. </returns>
          static GISModel *trainModel(EventStream *eventStream, int iterations, int cutoff, bool smoothing, bool printMessagesWhileTraining) throw(IOException);

          /// <summary>
          /// Train a model using the GIS algorithm.
          /// </summary>
          /// <param name="eventStream">
          ///          The EventStream holding the data on which this model will be
          ///          trained. </param>
          /// <param name="iterations">
          ///          The number of GIS iterations to perform. </param>
          /// <param name="cutoff">
          ///          The number of times a feature must be seen in order to be relevant
          ///          for training. </param>
          /// <param name="sigma">
          ///          The standard deviation for the gaussian smoother. </param>
          /// <returns> The newly trained model, which can be used immediately or saved to
          ///         disk using an opennlp.maxent.io.GISModelWriter object. </returns>
          static GISModel *trainModel(EventStream *eventStream, int iterations, int cutoff, double sigma) throw(IOException);

          /// <summary>
          /// Train a model using the GIS algorithm.
          /// </summary>
          /// <param name="iterations">
          ///          The number of GIS iterations to perform. </param>
          /// <param name="indexer">
          ///          The object which will be used for event compilation. </param>
          /// <param name="smoothing">
          ///          Defines whether the created trainer will use smoothing while
          ///          training the model. </param>
          /// <returns> The newly trained model, which can be used immediately or saved to
          ///         disk using an opennlp.maxent.io.GISModelWriter object. </returns>
          static GISModel *trainModel(int iterations, DataIndexer *indexer, bool smoothing);

          /// <summary>
          /// Train a model using the GIS algorithm.
          /// </summary>
          /// <param name="iterations">
          ///          The number of GIS iterations to perform. </param>
          /// <param name="indexer">
          ///          The object which will be used for event compilation. </param>
          /// <returns> The newly trained model, which can be used immediately or saved to
          ///         disk using an opennlp.maxent.io.GISModelWriter object. </returns>
          static GISModel *trainModel(int iterations, DataIndexer *indexer);

          /// <summary>
          /// Train a model using the GIS algorithm with the specified number of
          /// iterations, data indexer, and prior.
          /// </summary>
          /// <param name="iterations">
          ///          The number of GIS iterations to perform. </param>
          /// <param name="indexer">
          ///          The object which will be used for event compilation. </param>
          /// <param name="modelPrior">
          ///          The prior distribution for the model. </param>
          /// <returns> The newly trained model, which can be used immediately or saved to
          ///         disk using an opennlp.maxent.io.GISModelWriter object. </returns>
          static GISModel *trainModel(int iterations, DataIndexer *indexer, Prior *modelPrior, int cutoff);

          /// <summary>
          /// Train a model using the GIS algorithm.
          /// </summary>
          /// <param name="iterations">
          ///          The number of GIS iterations to perform. </param>
          /// <param name="indexer">
          ///          The object which will be used for event compilation. </param>
          /// <param name="printMessagesWhileTraining">
          ///          Determines whether training status messages are written to STDOUT. </param>
          /// <param name="smoothing">
          ///          Defines whether the created trainer will use smoothing while
          ///          training the model. </param>
          /// <param name="modelPrior">
          ///          The prior distribution for the model. </param>
          /// <param name="cutoff">
          ///          The number of times a predicate must occur to be used in a model. </param>
          /// <returns> The newly trained model, which can be used immediately or saved to
          ///         disk using an opennlp.maxent.io.GISModelWriter object. </returns>
          static GISModel *trainModel(int iterations, DataIndexer *indexer, bool printMessagesWhileTraining, bool smoothing, Prior *modelPrior, int cutoff);

          /// <summary>
          /// Train a model using the GIS algorithm.
          /// </summary>
          /// <param name="iterations">
          ///          The number of GIS iterations to perform. </param>
          /// <param name="indexer">
          ///          The object which will be used for event compilation. </param>
          /// <param name="printMessagesWhileTraining">
          ///          Determines whether training status messages are written to STDOUT. </param>
          /// <param name="smoothing">
          ///          Defines whether the created trainer will use smoothing while
          ///          training the model. </param>
          /// <param name="modelPrior">
          ///          The prior distribution for the model. </param>
          /// <param name="cutoff">
          ///          The number of times a predicate must occur to be used in a model. </param>
          /// <returns> The newly trained model, which can be used immediately or saved to
          ///         disk using an opennlp.maxent.io.GISModelWriter object. </returns>
          static GISModel *trainModel(int iterations, DataIndexer *indexer, bool printMessagesWhileTraining, bool smoothing, Prior *modelPrior, int cutoff, int threads);
        };




    }
}


#endif	//#ifndef GIS
