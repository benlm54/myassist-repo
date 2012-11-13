#ifndef PORTUGUESECONTRACTIONUTILITY
#define PORTUGUESECONTRACTIONUTILITY

#include "StringBuilder.h"
#include <string>
#include <map>

/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
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
        namespace formats
        {
            namespace ad
            {


                /// <summary>
                /// Utility class to handle Portuguese contractions.
                /// <p>
                /// Some Corpora splits contractions in its parts, for example, "da" > "de" +
                /// "a", but according to the fase of language processing, NER for instance, we
                /// can't decide if to split a contraction or not, specially because contractions
                /// inside names are not separated, but outside are.
                /// 
                /// <p>
                /// <b>Note:</b> Do not use this class, internal use only!
                /// </summary>
                class PortugueseContractionUtility
                {

              private:
                  static Map<std::string, std::string> *const CONTRACTIONS;
//JAVA TO C++ CONVERTER TODO TASK: Static constructors are not allowed in native C++:
                  static PortugueseContractionUtility();

                  /// <summary>
                  /// Merges a contraction
                  /// </summary>
                  /// <param name="left">
                  ///          the left component </param>
                  /// <param name="right">
                  ///          the right component </param>
                  /// <returns> the merged contraction </returns>
              public:
                  static std::string toContraction(const std::string &left, const std::string &right);
                };

            }
        }
    }
}


#endif	//#ifndef PORTUGUESECONTRACTIONUTILITY
