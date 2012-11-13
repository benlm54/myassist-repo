#ifndef DEFAULTSDCONTEXTGENERATOR
#define DEFAULTSDCONTEXTGENERATOR

#include "SDContextGenerator.h"
#include "StringBuffer.h"
#include "CharSequence.h"
#include "StringBuilder.h"
#include <string>
#include <vector>
#include <cctype>

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
        namespace sentdetect
        {


            using opennlp::tools::util::StringUtil;

            /// <summary>
            /// Generate event contexts for maxent decisions for sentence detection.
            /// 
            /// </summary>
            class DefaultSDContextGenerator : public SDContextGenerator
            {

              /// <summary>
              /// String buffer for generating features.
              /// </summary>
          protected:
              StringBuffer *buf;

              /// <summary>
              /// List for holding features as they are generated.
              /// </summary>
              std::vector<std::string> collectFeats;

          private:
              Set<std::string> *inducedAbbreviations;

//ORIGINAL LINE: private char[] eosCharacters;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              char *eosCharacters;

              /// <summary>
              /// Creates a new <code>SDContextGenerator</code> instance with
              /// no induced abbreviations.
              /// </summary>
              /// <param name="eosCharacters"> </param>
          public:
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              DefaultSDContextGenerator(char eosCharacters[]); //this(Collections.emptySet<String>(), eosCharacters);

              /// <summary>
              /// Creates a new <code>SDContextGenerator</code> instance which uses
              /// the set of induced abbreviations.
              /// </summary>
              /// <param name="inducedAbbreviations"> a <code>Set</code> of Strings
              /// representing induced abbreviations in the training data.
              /// Example: &quot;Mr.&quot;
              /// </param>
              /// <param name="eosCharacters"> </param>
              DefaultSDContextGenerator(Set<std::string> *inducedAbbreviations, char eosCharacters[]);

              /* (non-Javadoc)
               * @see opennlp.tools.sentdetect.SDContextGenerator#getContext(java.lang.StringBuffer, int)
               */
              virtual std::string *getContext(CharSequence *sb, int position);

              /// <summary>
              /// Determines some of the features for the sentence detector and adds them to list features.
              /// </summary>
              /// <param name="prefix"> String preceeding the eos character in the eos token. </param>
              /// <param name="suffix"> String following the eos character in the eos token. </param>
              /// <param name="previous"> Space delimited token preceeding token containing eos character. </param>
              /// <param name="next"> Space delimited token following token containsing eos character. </param>
          protected:
              virtual void collectFeatures(const std::string &prefix, const std::string &suffix, const std::string &previous, const std::string &next);

          private:
              static bool isFirstUpper(const std::string &s);

              /// <summary>
              /// Finds the index of the nearest space before a specified index which is not itself preceded by a space.
              /// </summary>
              /// <param name="sb">   The string buffer which contains the text being examined. </param>
              /// <param name="seek"> The index to begin searching from. </param>
              /// <returns> The index which contains the nearest space. </returns>
              static int previousSpaceIndex(CharSequence *sb, int seek);

              /// <summary>
              /// Finds the index of the nearest space after a specified index.
              /// </summary>
              /// <param name="sb"> The string buffer which contains the text being examined. </param>
              /// <param name="seek"> The index to begin searching from. </param>
              /// <param name="lastIndex"> The highest index of the StringBuffer sb. </param>
              /// <returns> The index which contains the nearest space. </returns>
              static int nextSpaceIndex(CharSequence *sb, int seek, int lastIndex);
            };

        }
    }
}


#endif	//#ifndef DEFAULTSDCONTEXTGENERATOR
