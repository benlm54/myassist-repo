#ifndef DEFAULTPOSCONTEXTGENERATOR
#define DEFAULTPOSCONTEXTGENERATOR

#include "POSContextGenerator.h"
#include "../tools/util/Cache.h"
#include "../tools/dictionary/Dictionary.h"
#include <string>
#include <vector>
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
        namespace postag
        {


            using opennlp::tools::dictionary::Dictionary;
            using opennlp::tools::util::Cache;
            using opennlp::tools::util::StringList;

            /// <summary>
            /// A context generator for the POS Tagger.
            /// </summary>
            class DefaultPOSContextGenerator : public POSContextGenerator
            {

          protected:
              const std::string SE;
              const std::string SB;
          private:
              static const int PREFIX_LENGTH = 4;
              static const int SUFFIX_LENGTH = 4;

              static Pattern *hasCap;
              static Pattern *hasNum;

              Cache *contextsCache;
              void *wordsKey;

              Dictionary *dict;
//ORIGINAL LINE: private String[] dictGram;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              std::string *dictGram;

              /// <summary>
              /// Initializes the current instance.
              /// </summary>
              /// <param name="dict"> </param>
          public:
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              DefaultPOSContextGenerator(Dictionary *dict) : SE("*SE*"), SB("*SB*"); //this(0,dict);

              /// <summary>
              /// Initializes the current instance.
              /// </summary>
              /// <param name="cacheSize"> </param>
              /// <param name="dict"> </param>
              DefaultPOSContextGenerator(int cacheSize, Dictionary *dict) : SE("*SE*"), SB("*SB*");
          protected:
              static std::string *getPrefixes(const std::string &lex);

              static std::string *getSuffixes(const std::string &lex);

          public:
              virtual std::string *getContext(int index, std::string sequence[], std::string priorDecisions[], Object additionalContext[]);

              /// <summary>
              /// Returns the context for making a pos tag decision at the specified token index given the specified tokens and previous tags. </summary>
              /// <param name="index"> The index of the token for which the context is provided. </param>
              /// <param name="tokens"> The tokens in the sentence. </param>
              /// <param name="tags"> The tags assigned to the previous words in the sentence. </param>
              /// <returns> The context for making a pos tag decision at the specified token index given the specified tokens and previous tags. </returns>
              virtual std::string *getContext(int index, Object tokens[], std::string tags[]);

            };

        }
    }
}


#endif	//#ifndef DEFAULTPOSCONTEXTGENERATOR
