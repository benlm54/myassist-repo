#ifndef TOKENIZEREVALUATOR
#define TOKENIZEREVALUATOR

#include "TokenSample.h"
#include "../tools/util/eval/Evaluator.h"
#include "../tools/util/eval/FMeasure.h"
#include "Tokenizer.h"
#include "Evaluator<TokenSample>.h"

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
        namespace tokenize
        {

            using opennlp::tools::util::Span;
            using opennlp::tools::util::eval::Evaluator;
            using opennlp::tools::util::eval::FMeasure;

            /// <summary>
            /// The <seealso cref="TokenizerEvaluator"/> measures the performance of
            /// the given <seealso cref="Tokenizer"/> with the provided reference
            /// <seealso cref="TokenSample"/>s.
            /// </summary>
            /// <seealso cref= Evaluator </seealso>
            /// <seealso cref= Tokenizer </seealso>
            /// <seealso cref= TokenSample </seealso>
            class TokenizerEvaluator : public Evaluator<TokenSample*>
            {

          private:
              FMeasure *fmeasure;

              /// <summary>
              /// The <seealso cref="Tokenizer"/> used to create the
              /// predicted tokens.
              /// </summary>
              Tokenizer *tokenizer;

              /// <summary>
              /// Initializes the current instance with the
              /// given <seealso cref="Tokenizer"/>.
              /// </summary>
              /// <param name="tokenizer"> the <seealso cref="Tokenizer"/> to evaluate. </param>
              /// <param name="listeners"> evaluation sample listeners </param>
          public:
//ORIGINAL LINE: public TokenizerEvaluator(Tokenizer tokenizer, TokenizerEvaluationMonitor... listeners)
//JAVA TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
              TokenizerEvaluator(Tokenizer *tokenizer, ...);

          protected:
              virtual TokenSample *processSample(TokenSample *reference);

          public:
              virtual FMeasure *getFMeasure();

            private:
                void InitializeInstanceFields();
            };

        }
    }
}


#endif	//#ifndef TOKENIZEREVALUATOR
