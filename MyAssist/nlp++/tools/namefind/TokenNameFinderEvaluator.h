#ifndef TOKENNAMEFINDEREVALUATOR
#define TOKENNAMEFINDEREVALUATOR

#include "NameSample.h"
#include "../tools/util/eval/Evaluator.h"
#include "../tools/util/eval/FMeasure.h"
#include "TokenNameFinder.h"
#include "../tools/util/InvalidFormatException.h"
#include "../tools/util/ObjectStream.h"
#include "Evaluator<NameSample>.h"
#include "ObjectStream<NameSample>.h"
#include <string>

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
        namespace namefind
        {


            using opennlp::tools::cmdline::PerformanceMonitor;
            using opennlp::tools::util::InvalidFormatException;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::PlainTextByLineStream;
            using opennlp::tools::util::Span;
            using opennlp::tools::util::eval::Evaluator;
            using opennlp::tools::util::eval::FMeasure;

            /// <summary>
            /// The <seealso cref="TokenNameFinderEvaluator"/> measures the performance
            /// of the given <seealso cref="TokenNameFinder"/> with the provided
            /// reference <seealso cref="NameSample"/>s.
            /// </summary>
            /// <seealso cref= Evaluator </seealso>
            /// <seealso cref= TokenNameFinder </seealso>
            /// <seealso cref= NameSample </seealso>
            class TokenNameFinderEvaluator : public Evaluator<NameSample*>
            {

          private:
              FMeasure *fmeasure;

              /// <summary>
              /// The <seealso cref="TokenNameFinder"/> used to create the predicted
              /// <seealso cref="NameSample"/> objects.
              /// </summary>
              TokenNameFinder *nameFinder;

              /// <summary>
              /// Initializes the current instance with the given
              /// <seealso cref="TokenNameFinder"/>.
              /// </summary>
              /// <param name="nameFinder"> the <seealso cref="TokenNameFinder"/> to evaluate. </param>
              /// <param name="listeners"> evaluation sample listeners  </param>
          public:
//ORIGINAL LINE: public TokenNameFinderEvaluator(TokenNameFinder nameFinder, TokenNameFinderEvaluationMonitor... listeners)
//JAVA TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
              TokenNameFinderEvaluator(TokenNameFinder *nameFinder, ...);

              /// <summary>
              /// Evaluates the given reference <seealso cref="NameSample"/> object.
              /// 
              /// This is done by finding the names with the
              /// <seealso cref="TokenNameFinder"/> in the sentence from the reference
              /// <seealso cref="NameSample"/>. The found names are then used to
              /// calculate and update the scores.
              /// </summary>
              /// <param name="reference"> the reference <seealso cref="NameSample"/>.
              /// </param>
              /// <returns> the predicted <seealso cref="NameSample"/>. </returns>
          protected:
              virtual NameSample *processSample(NameSample *reference);

          public:
              virtual FMeasure *getFMeasure();

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated public static void main(String[] args) throws java.io.IOException, opennlp.tools.util.InvalidFormatException
              static void main(std::string args[]) throw(IOException, InvalidFormatException);

                    private:
                        class ObjectStreamAnonymousInnerClassHelper : public ObjectStream<NameSample*>
                        {

                        public:
                            virtual NameSample *read() throw(IOException);

                            virtual void reset() throw(IOException);

                            virtual void close() throw(IOException);
                        };

            private:
                void InitializeInstanceFields();
            };

        }
    }
}


#endif	//#ifndef TOKENNAMEFINDEREVALUATOR
