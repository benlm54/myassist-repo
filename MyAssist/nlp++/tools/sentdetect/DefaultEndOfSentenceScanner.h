#ifndef DEFAULTENDOFSENTENCESCANNER
#define DEFAULTENDOFSENTENCESCANNER

#include "EndOfSentenceScanner.h"
#include "../maxent/IntegerPool.h"
#include "StringBuffer.h"
#include <string>
#include <vector>

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
        namespace sentdetect
        {


            using opennlp::maxent::IntegerPool;

            /// <summary>
            /// Default implementation of the <seealso cref="EndOfSentenceScanner"/>.
            /// It uses an character array with possible end of sentence chars
            /// to identify potential sentence endings.
            /// </summary>
            class DefaultEndOfSentenceScanner : public EndOfSentenceScanner
            {

          protected:
              static IntegerPool *const INT_POOL;

          private:
//ORIGINAL LINE: private char eosCharacters[];
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              char *eosCharacters;

              /// <summary>
              /// Initializes the current instance.
              /// </summary>
              /// <param name="eosCharacters"> </param>
          public:
              DefaultEndOfSentenceScanner(char eosCharacters[]);

              virtual std::vector<int> getPositions(const std::string &s);

              virtual std::vector<int> getPositions(StringBuffer *buf);

              virtual std::vector<int> getPositions(char cbuf[]);

              virtual char *getEndOfSentenceCharacters();
            };

        }
    }
}


#endif	//#ifndef DEFAULTENDOFSENTENCESCANNER
