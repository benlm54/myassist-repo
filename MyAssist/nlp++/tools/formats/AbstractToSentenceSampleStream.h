#ifndef ABSTRACTTOSENTENCESAMPLESTREAM
#define ABSTRACTTOSENTENCESAMPLESTREAM

#include "../tools/sentdetect/SentenceSample.h"
#include "../tools/util/FilterObjectStream.h"
#include "../tools/tokenize/Detokenizer.h"
#include "../tools/util/ObjectStream.h"
#include "SentenceSample>.h"
#include "S.h"
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
        namespace formats
        {


            using opennlp::tools::sentdetect::SentenceSample;
            using opennlp::tools::tokenize::Detokenizer;
            using opennlp::tools::util::FilterObjectStream;
            using opennlp::tools::util::ObjectStream;

            template<typename T>
            class AbstractToSentenceSampleStream : public FilterObjectStream<T, SentenceSample*>
            {

          private:
              Detokenizer *const detokenizer;

              const int chunkSize;

          public:
              AbstractToSentenceSampleStream(Detokenizer *detokenizer, ObjectStream<T> *samples, int chunkSize) : FilterObjectStream<T, SentenceSample>(samples), detokenizer(detokenizer), chunkSize(chunkSize)
              {

                if (detokenizer == 0)
                  throw IllegalArgumentException("detokenizer must not be null!");


                if (chunkSize < 0)
                  throw IllegalArgumentException("chunkSize must be zero or larger!");

                if (chunkSize > 0)
                else
                  this->chunkSize = int::MAX_VALUE;
              }

          protected:
              virtual std::string *toSentence(T sample) = 0;

          public:
              virtual SentenceSample *read() throw(IOException)
              {
                std::vector<std::string[]> sentences = std::vector<std::string[]>();

                T posSample;
                int chunks = 0;
                while ((posSample = samples->read()) != 0 && chunks < chunkSize)
                {
                  sentences.push_back(toSentence(posSample));
                  chunks++;
                }

                if (sentences.size() > 0)
                  return new SentenceSample(detokenizer, sentences.toArray(new std::string[sentences.size()][]));
                else if (posSample != 0)
                  return read(); // filter out empty line
                else
                {
                  return 0; // last sample was read
                }
              }
            };

        }
    }
}


#endif	//#ifndef ABSTRACTTOSENTENCESAMPLESTREAM
