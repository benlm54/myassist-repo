#ifndef DICTIONARYNAMEFINDER
#define DICTIONARYNAMEFINDER

#include "TokenNameFinder.h"
#include "../tools/dictionary/Dictionary.h"
#include "../tools/dictionary/Index.h"
#include "../tools/util/Span.h"
#include <string>
#include <vector>
#include <list>

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
        namespace namefind
        {


            using opennlp::tools::dictionary::Dictionary;
            using opennlp::tools::dictionary::Index;
            using opennlp::tools::util::Span;
            using opennlp::tools::util::StringList;

            /// <summary>
            /// This is a dictionary based name finder, it scans text
            /// for names inside a dictionary.
            /// </summary>
            class DictionaryNameFinder : public TokenNameFinder
            {

          private:
              Dictionary *mDictionary;

              Index *mMetaDictionary;

              /// <summary>
              /// Initializes the current instance.
              /// </summary>
              /// <param name="dictionary"> </param>
          public:
              DictionaryNameFinder(Dictionary *dictionary);

              virtual Span *find(std::string tokenStrings[]);

              virtual void clearAdaptiveData();
            };

        }
    }
}


#endif	//#ifndef DICTIONARYNAMEFINDER
