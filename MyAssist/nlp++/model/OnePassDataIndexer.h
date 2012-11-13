#ifndef ONEPASSDATAINDEXER
#define ONEPASSDATAINDEXER

#include "AbstractDataIndexer.h"
#include "EventStream.h"
#include "Event.h"
#include <string>
#include <map>
#include <vector>
#include <list>
#include <set>

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
        /// An indexer for maxent model data which handles cutoffs for uncommon
        /// contextual predicates and provides a unique integer index for each of the
        /// predicates.
        /// </summary>
        class OnePassDataIndexer : public AbstractDataIndexer
        {

          /// <summary>
          /// One argument constructor for DataIndexer which calls the two argument
          /// constructor assuming no cutoff.
          /// </summary>
          /// <param name="eventStream">
          ///          An Event[] which contains the a list of all the Events seen in the
          ///          training data. </param>
      public:
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
          OnePassDataIndexer(EventStream *eventStream) throw(IOException); //this(eventStream, 0);

//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
          OnePassDataIndexer(EventStream *eventStream, int cutoff) throw(IOException); //this(eventStream, cutoff, true);

          /// <summary>
          /// Two argument constructor for DataIndexer.
          /// </summary>
          /// <param name="eventStream">
          ///          An Event[] which contains the a list of all the Events seen in the
          ///          training data. </param>
          /// <param name="cutoff">
          ///          The minimum number of times a predicate must have been observed in
          ///          order to be included in the model. </param>
          OnePassDataIndexer(EventStream *eventStream, int cutoff, bool sort) throw(IOException);

          /// <summary>
          /// Reads events from <tt>eventStream</tt> into a linked list. The predicates
          /// associated with each event are counted and any which occur at least
          /// <tt>cutoff</tt> times are added to the <tt>predicatesInOut</tt> map along
          /// with a unique integer index.
          /// </summary>
          /// <param name="eventStream">
          ///          an <code>EventStream</code> value </param>
          /// <param name="predicatesInOut">
          ///          a <code>TObjectIntHashMap</code> value </param>
          /// <param name="cutoff">
          ///          an <code>int</code> value </param>
          /// <returns> a <code>TLinkedList</code> value </returns>
      private:
          std::list<Event*> computeEventCounts(EventStream *eventStream, Map<std::string, int> *predicatesInOut, int cutoff) throw(IOException);

      protected:
          virtual std::vector index(std::list<Event*> &events, Map<std::string, int> *predicateIndex);

        };

    }
}


#endif	//#ifndef ONEPASSDATAINDEXER
