#ifndef ABSTRACTDATAINDEXER
#define ABSTRACTDATAINDEXER

#include "DataIndexer.h"
#include <string>
#include <vector>

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
        /// Abstract class for collecting event and context counts used in training. 
        /// 
        /// </summary>
        class AbstractDataIndexer : public DataIndexer
        {

      private:
          int numEvents;
          /// <summary>
          /// The integer contexts associated with each unique event. </summary>
      protected:
//ORIGINAL LINE: protected int[][] contexts;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          int **contexts;
          /// <summary>
          /// The integer outcome associated with each unique event. </summary>
//ORIGINAL LINE: protected int[] outcomeList;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          int *outcomeList;
          /// <summary>
          /// The number of times an event occured in the training data. </summary>
//ORIGINAL LINE: protected int[] numTimesEventsSeen;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          int *numTimesEventsSeen;
          /// <summary>
          /// The predicate/context names. </summary>
//ORIGINAL LINE: protected String[] predLabels;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          std::string *predLabels;
          /// <summary>
          /// The names of the outcomes. </summary>
//ORIGINAL LINE: protected String[] outcomeLabels;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          std::string *outcomeLabels;
          /// <summary>
          /// The number of times each predicate occured. </summary>
//ORIGINAL LINE: protected int[] predCounts;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          int *predCounts;

      public:
          virtual int **getContexts();

          virtual int *getNumTimesEventsSeen();

          virtual int *getOutcomeList();

          virtual std::string *getPredLabels();

          virtual std::string *getOutcomeLabels();



          virtual int *getPredCounts();

          /// <summary>
          /// Sorts and uniques the array of comparable events and return the number of unique events.
          /// This method will alter the eventsToCompare array -- it does an in place
          /// sort, followed by an in place edit to remove duplicates.
          /// </summary>
          /// <param name="eventsToCompare"> a <code>ComparableEvent[]</code> value </param>
          /// <returns> The number of unique events in the specified list.
          /// @since maxent 1.2.6 </returns>
      protected:
          virtual int sortAndMerge(std::vector eventsToCompare, bool sort);


      public:
          virtual int getNumEvents();

          /// <summary>
          /// Updates the set of predicated and counter with the specified event contexts and cutoff. </summary>
          /// <param name="ec"> The contexts/features which occur in a event. </param>
          /// <param name="predicateSet"> The set of predicates which will be used for model building. </param>
          /// <param name="counter"> The predicate counters. </param>
          /// <param name="cutoff"> The cutoff which determines whether a predicate is included. </param>
       protected:
           static void update(std::string ec[], Set *predicateSet, Map<std::string, int> *counter, int cutoff);

          /// <summary>
          /// Utility method for creating a String[] array from a map whose
          /// keys are labels (Strings) to be stored in the array and whose
          /// values are the indices (Integers) at which the corresponding
          /// labels should be inserted.
          /// </summary>
          /// <param name="labelToIndexMap"> a <code>TObjectIntHashMap</code> value </param>
          /// <returns> a <code>String[]</code> value
          /// @since maxent 1.2.6 </returns>
          static std::string *toIndexedStringArray(Map<std::string, int> *labelToIndexMap);

      public:
          virtual float **getValues();


        };

    }
}


#endif	//#ifndef ABSTRACTDATAINDEXER
