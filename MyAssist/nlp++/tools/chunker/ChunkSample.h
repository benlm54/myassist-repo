#ifndef CHUNKSAMPLE
#define CHUNKSAMPLE

#include "../tools/util/Span.h"
#include "StringBuilder.h"
#include <string>
#include <vector>

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


            using opennlp::tools::util::Span;

            /// <summary>
            /// Class for holding chunks for a single unit of text.
            /// </summary>
            class ChunkSample
            {

          private:
              const std::vector<std::string> sentence;
              const std::vector<std::string> tags;
              const std::vector<std::string> preds;

              /// <summary>
              /// Initializes the current instance.
              /// </summary>
              /// <param name="sentence">
              ///          training sentence </param>
              /// <param name="tags">
              ///          POS Tags for the sentence </param>
              /// <param name="preds">
              ///          Chunk tags in B-* I-* notation </param>
          public:
              ChunkSample(std::string sentence[], std::string tags[], std::string preds[]);

              /// <summary>
              /// Initializes the current instance.
              /// </summary>
              /// <param name="sentence">
              ///          training sentence </param>
              /// <param name="tags">
              ///          POS Tags for the sentence </param>
              /// <param name="preds">
              ///          Chunk tags in B-* I-* notation </param>
              ChunkSample(std::vector<std::string> &sentence, std::vector<std::string> &tags, std::vector<std::string> &preds);

              /// <summary>
              /// Gets the training sentence </summary>
              virtual std::string *getSentence();

              /// <summary>
              /// Gets the POS Tags for the sentence </summary>
              virtual std::string *getTags();

              /// <summary>
              /// Gets the Chunk tags in B-* I-* notation </summary>
              virtual std::string *getPreds();

              /// <summary>
              /// Gets the phrases as an array of spans </summary>
              virtual Span *getPhrasesAsSpanList();

              /// <summary>
              /// Static method to create arrays of spans of phrases
              /// </summary>
              /// <param name="aSentence">
              ///          training sentence </param>
              /// <param name="aTags">
              ///          POS Tags for the sentence </param>
              /// <param name="aPreds">
              ///          Chunk tags in B-* I-* notation
              /// </param>
              /// <returns> the phrases as an array of spans </returns>
              static Span *phrasesAsSpanList(std::string aSentence[], std::string aTags[], std::string aPreds[]);

          private:
              static void validateArguments(int sentenceSize, int tagsSize, int predsSize) throw(IllegalArgumentException);

              /// <summary>
              /// Creates a nice to read string for the phrases formatted as following: <br>
              /// <code>
              /// [NP Rockwell_NNP ] [VP said_VBD ] [NP the_DT agreement_NN ] [VP calls_VBZ ] [SBAR for_IN ] [NP it_PRP ] [VP to_TO supply_VB ] [NP 200_CD additional_JJ so-called_JJ shipsets_NNS ] [PP for_IN ] [NP the_DT planes_NNS ] ._.
              /// </code>
              /// </summary>
              /// <returns> a nice to read string representation of the chunk phases </returns>
          public:
              virtual std::string nicePrint();

              virtual std::string ToString();

              virtual bool Equals(void *obj);

            };

        }
    }
}


#endif	//#ifndef CHUNKSAMPLE
