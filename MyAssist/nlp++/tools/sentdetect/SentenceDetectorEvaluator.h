#ifndef SENTENCEDETECTOREVALUATOR
#define SENTENCEDETECTOREVALUATOR

#include "SentenceSample.h"
#include "../tools/util/eval/Evaluator.h"
#include "../tools/util/eval/FMeasure.h"
#include "SentenceDetector.h"
#include "Evaluator<SentenceSample>.h"

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
            using opennlp::tools::util::eval::Evaluator;
            using opennlp::tools::util::eval::FMeasure;

            /// <summary>
            /// The <seealso cref="SentenceDetectorEvaluator"/> measures the performance of
            /// the given <seealso cref="SentenceDetector"/> with the provided reference
            /// <seealso cref="SentenceSample"/>s.
            /// </summary>
            /// <seealso cref= Evaluator </seealso>
            /// <seealso cref= SentenceDetector </seealso>
            /// <seealso cref= SentenceSample </seealso>
            class SentenceDetectorEvaluator : public Evaluator<SentenceSample*>
            {

          private:
              FMeasure *fmeasure;

              /// <summary>
              /// The <seealso cref="SentenceDetector"/> used to predict sentences.
              /// </summary>
              SentenceDetector *sentenceDetector;

              /// <summary>
              /// Initializes the current instance.
              /// </summary>
              /// <param name="sentenceDetector"> </param>
              /// <param name="listeners"> evaluation sample listeners </param>
          public:
//ORIGINAL LINE: public SentenceDetectorEvaluator(SentenceDetector sentenceDetector, SentenceDetectorEvaluationMonitor... listeners)
//JAVA TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
              SentenceDetectorEvaluator(SentenceDetector *sentenceDetector, ...);

          protected:
              virtual SentenceSample *processSample(SentenceSample *sample);

          public:
              virtual FMeasure *getFMeasure();

            private:
                void InitializeInstanceFields();
            };

        }
    }
}


#endif	//#ifndef SENTENCEDETECTOREVALUATOR
