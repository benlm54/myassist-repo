#ifndef DEFAULTCHUNKERSEQUENCEVALIDATOR
#define DEFAULTCHUNKERSEQUENCEVALIDATOR

#include "../tools/util/SequenceValidator.h"
#include "SequenceValidator<String>.h"
#include <string>

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
        namespace chunker
        {

            using opennlp::tools::util::SequenceValidator;

            class DefaultChunkerSequenceValidator : public SequenceValidator<std::string>
            {

          private:
              bool validOutcome(const std::string &outcome, const std::string &prevOutcome);

          protected:
              virtual bool validOutcome(const std::string &outcome, std::string sequence[]);

          public:
              virtual bool validSequence(int i, std::string sequence[], std::string s[], const std::string &outcome);

            };

        }
    }
}


#endif	//#ifndef DEFAULTCHUNKERSEQUENCEVALIDATOR
