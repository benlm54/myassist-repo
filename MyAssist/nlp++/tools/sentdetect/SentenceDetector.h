#ifndef SENTENCEDETECTOR
#define SENTENCEDETECTOR

#include "../tools/util/Span.h"

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

            using opennlp::tools::util::Span;

            /// <summary>
            /// The interface for sentence detectors, which find the sentence boundaries in
            /// a text.
            /// </summary>
            class SentenceDetector
            {

                /// <summary>
                /// Sentence detect a string.
                /// </summary>
                /// <param name="s"> The string to be sentence detected. </param>
                /// <returns>  The String[] with the individual sentences as the array
                ///          elements. </returns>
            public:
                virtual std::string *sentDetect(const std::string &s) = 0;

                /// <summary>
                /// Sentence detect a string.
                /// </summary>
                /// <param name="s"> The string to be sentence detected.
                /// </param>
                /// <returns> The Span[] with the spans (offsets into s) for each
                /// detected sentence as the individuals array elements. </returns>
                virtual opennlp::tools::util::Span *sentPosDetect(const std::string &s) = 0;
            };

        }
    }
}


#endif	//#ifndef SENTENCEDETECTOR
