#ifndef CHUNKERCONTEXTGENERATOR
#define CHUNKERCONTEXTGENERATOR

#include "../tools/util/BeamSearchContextGenerator.h"
#include <string>

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
        namespace chunker
        {

            using opennlp::tools::util::BeamSearchContextGenerator;

            /// <summary>
            /// Interface for the context generator used in syntactic chunking.
            /// </summary>
            class ChunkerContextGenerator : public BeamSearchContextGenerator<std::string>
            {

              /// <summary>
              /// Returns the contexts for chunking of the specified index. </summary>
              /// <param name="i"> The index of the token in the specified toks array for which the context should be constructed. </param>
              /// <param name="toks"> The tokens of the sentence.  The <code>toString</code> methods of these objects should return the token text. </param>
              /// <param name="tags"> The POS tags for the the specified tokens. </param>
              /// <param name="preds"> The previous decisions made in the taging of this sequence.  Only indices less than i will be examined. </param>
              /// <returns> An array of predictive contexts on which a model basis its decisions. </returns>
          public:
              virtual std::string *getContext(int i, std::string toks[], std::string tags[], std::string preds[]) = 0;
            };

        }
    }
}


#endif	//#ifndef CHUNKERCONTEXTGENERATOR
