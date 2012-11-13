#ifndef SENTENCECONTEXTGENERATOR
#define SENTENCECONTEXTGENERATOR

#include "../tools/sentdetect/DefaultSDContextGenerator.h"
#include <string>
#include <cmath>

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
            namespace lang
            {
                namespace th
                {

                    using opennlp::tools::sentdetect::DefaultSDContextGenerator;

                    /// <summary>
                    /// Creates contexts/features for end-of-sentence detection in Thai text.
                    /// </summary>
                    class SentenceContextGenerator : public DefaultSDContextGenerator
                    {

                  public:
                      static const char eosCharacters[2];

                      SentenceContextGenerator();

                  protected:
                      virtual void collectFeatures(const std::string &prefix, const std::string &suffix, const std::string &previous, const std::string &next);
                    };

                }
            }
        }
    }
}


#endif	//#ifndef SENTENCECONTEXTGENERATOR
