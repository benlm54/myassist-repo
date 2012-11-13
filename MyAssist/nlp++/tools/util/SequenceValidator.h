#ifndef SEQUENCEVALIDATOR
#define SEQUENCEVALIDATOR

#include "T.h"

/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreemnets.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

namespace opennlp
{
    namespace tools
    {
        namespace util
        {

            template<typename T>
            class SequenceValidator
            {

              /// <summary>
              /// Determines whether a particular continuation of a sequence is valid.
              /// This is used to restrict invalid sequences such as those used in start/continue tag-based chunking
              /// or could be used to implement tag dictionary restrictions.
              /// </summary>
              /// <param name="i"> The index in the input sequence for which the new outcome is being proposed. </param>
              /// <param name="inputSequence"> The input sequence. </param>
              /// <param name="outcomesSequence"> The outcomes so far in this sequence. </param>
              /// <param name="outcome"> The next proposed outcome for the outcomes sequence.
              /// </param>
              /// <returns> true is the sequence would still be valid with the new outcome, false otherwise. </returns>
          public:
              virtual bool validSequence(int i, T inputSequence[], std::string outcomesSequence[], const std::string &outcome) = 0;
            };

        }
    }
}


#endif	//#ifndef SEQUENCEVALIDATOR
