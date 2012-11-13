#ifndef CHUNKER
#define CHUNKER

#include "../tools/util/Span.h"
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
        namespace chunker
        {


            using opennlp::tools::util::Sequence;
            using opennlp::tools::util::Span;

            /// <summary>
            /// The interface for chunkers which provide chunk tags for a sequence of tokens.
            /// </summary>
            class Chunker
            {

              /// <summary>
              /// Generates chunk tags for the given sequence returning the result in a list.
              /// </summary>
              /// <param name="toks"> a list of the tokens or words of the sequence. </param>
              /// <param name="tags"> a list of the pos tags of the sequence.
              /// </param>
              /// <returns> a list of chunk tags for each token in the sequence.
              /// </returns>
              /// @deprecated please use <seealso cref="#chunk(String[], String[])"/> instead. 
          public:
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated("please use <seealso cref="#chunk(String[] , String[])"/> instead.") public java.util.List<String> chunk(java.util.List<String> toks, java.util.List<String> tags);
              virtual std::vector<std::string> chunk(std::vector<std::string> &toks, std::vector<std::string> &tags) = 0;

              /// <summary>
              /// Generates chunk tags for the given sequence returning the result in an array.
              /// </summary>
              /// <param name="toks"> an array of the tokens or words of the sequence. </param>
              /// <param name="tags"> an array of the pos tags of the sequence.
              /// </param>
              /// <returns> an array of chunk tags for each token in the sequence. </returns>
              virtual std::string *chunk(std::string toks[], std::string tags[]) = 0;

              /// <summary>
              /// Generates tagged chunk spans for the given sequence returning the result in a span array.
              /// </summary>
              /// <param name="toks"> an array of the tokens or words of the sequence. </param>
              /// <param name="tags"> an array of the pos tags of the sequence.
              /// </param>
              /// <returns> an array of spans with chunk tags for each chunk in the sequence. </returns>
              virtual opennlp::tools::util::Span *chunkAsSpans(std::string toks[], std::string tags[]) = 0;

              /// <summary>
              /// Returns the top k chunk sequences for the specified sentence with the specified pos-tags </summary>
              /// <param name="sentence"> The tokens of the sentence. </param>
              /// <param name="tags"> The pos-tags for the specified sentence.
              /// </param>
              /// <returns> the top k chunk sequences for the specified sentence.
              /// </returns>
              /// @deprecated please use <seealso cref="#topKSequences(String[], String[])"/> instead. 
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated("please use <seealso cref="#topKSequences(String[] , String[])"/> instead.") public opennlp.tools.util.Sequence[] topKSequences(java.util.List<String> sentence, java.util.List<String> tags);
              virtual opennlp::tools::util::Sequence *topKSequences(std::vector<std::string> &sentence, std::vector<std::string> &tags) = 0;


              /// <summary>
              /// Returns the top k chunk sequences for the specified sentence with the specified pos-tags </summary>
              /// <param name="sentence"> The tokens of the sentence. </param>
              /// <param name="tags"> The pos-tags for the specified sentence.
              /// </param>
              /// <returns> the top k chunk sequences for the specified sentence. </returns>
              virtual opennlp::tools::util::Sequence *topKSequences(std::string sentence[], std::string tags[]) = 0;

              /// <summary>
              /// Returns the top k chunk sequences for the specified sentence with the specified pos-tags </summary>
              /// <param name="sentence"> The tokens of the sentence. </param>
              /// <param name="tags"> The pos-tags for the specified sentence. </param>
              /// <param name="minSequenceScore"> A lower bound on the score of a returned sequence.
              /// </param>
              /// <returns> the top k chunk sequences for the specified sentence. </returns>
              virtual opennlp::tools::util::Sequence *topKSequences(std::string sentence[], std::string tags[], double minSequenceScore) = 0;
            };

        }
    }
}


#endif	//#ifndef CHUNKER
