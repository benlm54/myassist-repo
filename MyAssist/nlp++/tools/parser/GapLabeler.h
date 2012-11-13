#ifndef GAPLABELER
#define GAPLABELER

#include "Constituent.h"

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
        namespace parser
        {


            /// <summary>
            /// Interface for labeling nodes which contain traces so that these traces can be predicted
            /// by the parser.
            /// </summary>
            class GapLabeler
            {
              /// <summary>
              /// Labels the constituents found in the stack with gap labels if appropriate. </summary>
              /// <param name="stack"> The stack of un-completed constituents. </param>
          public:
              virtual void labelGaps(std::stack<Constituent*> &stack) = 0;
            };

        }
    }
}


#endif	//#ifndef GAPLABELER
