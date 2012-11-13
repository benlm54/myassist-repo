#ifndef POSTAGGER
#define POSTAGGER

#include "../tools/util/Sequence.h"

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
        namespace postag
        {


            using opennlp::tools::util::Sequence;

            /// <summary>
            /// The interface for part of speech taggers.
            /// </summary>
            class POSTagger
            {

              /// <summary>
              /// Assigns the sentence of tokens pos tags.
              /// </summary>
              /// <param name="sentence">
              ///          The sentence of tokens to be tagged. </param>
              /// <returns> a list of pos tags for each token provided in sentence.
              /// </returns>
              /// @deprecated call <code> tag(String[]) </code> instead 
          public:
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated("call <code> tag(String[]) </code> instead") public java.util.List<String> tag(java.util.List<String> sentence);
              virtual std::vector<std::string> tag(std::vector<std::string> &sentence) = 0;

              /// <summary>
              /// Assigns the sentence of tokens pos tags. </summary>
              /// <param name="sentence"> The sentece of tokens to be tagged. </param>
              /// <returns> an array of pos tags for each token provided in sentence. </returns>
              virtual std::string *tag(std::string sentence[]) = 0;

              /// <summary>
              /// Assigns the sentence of space-delimied tokens pos tags. </summary>
              /// <param name="sentence"> The sentece of space-delimited tokens to be tagged. </param>
              /// <returns> a string of space-delimited pos tags for each token provided in sentence.
              /// </returns>
              /// @deprecated call <code> tag(String[]) instead </code> use WhiteSpaceTokenizer.INSTANCE.tokenize
              /// to obtain the String array. 
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated("call <code> tag(String[]) instead </code> use WhiteSpaceTokenizer.INSTANCE.tokenize") public String tag(String sentence);
              virtual std::string tag(const std::string &sentence) = 0;

              /// @deprecated call <code> topKSequences(String[]) </code> instead 
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated("call <code> topKSequences(String[]) </code> instead") public opennlp.tools.util.Sequence[] topKSequences(java.util.List<String> sentence);
              virtual opennlp::tools::util::Sequence *topKSequences(std::vector<std::string> &sentence) = 0;

              virtual opennlp::tools::util::Sequence *topKSequences(std::string sentence[]) = 0;
            };

        }
    }
}


#endif	//#ifndef POSTAGGER
