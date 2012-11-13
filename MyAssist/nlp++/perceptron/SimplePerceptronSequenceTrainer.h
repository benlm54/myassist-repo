#ifndef SIMPLEPERCEPTRONSEQUENCETRAINER
#define SIMPLEPERCEPTRONSEQUENCETRAINER

#include "../model/SequenceStream.h"
#include "../model/MutableContext.h"
#include "../model/IndexHashTable.h"
#include "../model/AbstractModel.h"
#include "const_iterator.h"
#include <string>
#include <map>

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
        using opennlp::model::Event;
        using opennlp::model::IndexHashTable;
        using opennlp::model::MutableContext;
        using opennlp::model::OnePassDataIndexer;
        using opennlp::model::Sequence;
        using opennlp::model::SequenceStream;
        using opennlp::model::SequenceStreamEventStream;
        using opennlp::model::TwoPassDataIndexer;

        /// <summary>
        /// Trains models for sequences using the perceptron algorithm.  Each outcome is represented as
        /// a binary perceptron classifier.  This supports standard (integer) weighting as well
        /// average weighting.  Sequence information is used in a simplified was to that described in:
        /// Discriminative Training Methods for Hidden Markov Models: Theory and Experiments
        /// with the Perceptron Algorithm. Michael Collins, EMNLP 2002.
        /// Specifically only updates are applied to tokens which were incorrectly tagged by a sequence tagger
        /// rather than to all feature across the sequence which differ from the training sequence.
        /// </summary>
        class SimplePerceptronSequenceTrainer
        {

      private:
          bool printMessages;
          int iterations;
          SequenceStream *sequenceStream;
          /// <summary>
          /// Number of events in the event set. </summary>
          int numEvents;

          /// <summary>
          /// Number of predicates. </summary>
          int numPreds;
          int numOutcomes;

          /// <summary>
          /// List of outcomes for each event i, in context[i]. </summary>
//ORIGINAL LINE: private int[] outcomeList;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          int *outcomeList;

//ORIGINAL LINE: private String[] outcomeLabels;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          std::string *outcomeLabels;

      public:
//ORIGINAL LINE: double[] modelDistribution;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          double *modelDistribution;

          /// <summary>
          /// Stores the average parameter values of each predicate during iteration. </summary>
      private:
//ORIGINAL LINE: private opennlp.model.MutableContext[] averageParams;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          MutableContext *averageParams;

          /// <summary>
          /// Mapping between context and an integer </summary>
          IndexHashTable<std::string> *pmap;

          Map<std::string, int> *omap;

          /// <summary>
          /// Stores the estimated parameter value of each predicate during iteration. </summary>
//ORIGINAL LINE: private opennlp.model.MutableContext[] params;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          MutableContext *params;
          bool useAverage;
//ORIGINAL LINE: private int[][][] updates;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          int ***updates;
          int VALUE;
          int ITER;
          int EVENT;

//ORIGINAL LINE: private int[] allOutcomesPattern;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          int *allOutcomesPattern;
//ORIGINAL LINE: private String[] predLabels;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          std::string *predLabels;
      public:
          int numSequences;

          virtual AbstractModel *trainModel(int iterations, SequenceStream *sequenceStream, int cutoff, bool useAverage) throw(IOException);

      private:
          void findParameters(int iterations);

          void display(const std::string &s);

      public:
          virtual void nextIteration(int iteration);

      private:
          void trainingStats(MutableContext params[]);

        private:
            void InitializeInstanceFields();

public:
            SimplePerceptronSequenceTrainer()
            {
                InitializeInstanceFields();
            }
        };

    }
}


#endif	//#ifndef SIMPLEPERCEPTRONSEQUENCETRAINER
