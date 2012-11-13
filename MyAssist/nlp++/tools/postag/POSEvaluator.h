#ifndef POSEVALUATOR
#define POSEVALUATOR

#include "POSSample.h"
#include "../tools/util/eval/Evaluator.h"
#include "POSTagger.h"
#include "../tools/util/eval/Mean.h"
#include "Evaluator<POSSample>.h"
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
        namespace postag
        {

            using opennlp::tools::util::eval::Evaluator;
            using opennlp::tools::util::eval::Mean;

            /// <summary>
            /// The <seealso cref="POSEvaluator"/> measures the performance of
            /// the given <seealso cref="POSTagger"/> with the provided reference
            /// <seealso cref="POSSample"/>s.
            /// </summary>
            class POSEvaluator : public Evaluator<POSSample*>
            {

          private:
              POSTagger *tagger;

              Mean *wordAccuracy;

              /// <summary>
              /// Initializes the current instance.
              /// </summary>
              /// <param name="tagger"> </param>
              /// <param name="listeners"> an array of evaluation listeners </param>
          public:
//ORIGINAL LINE: public POSEvaluator(POSTagger tagger, POSTaggerEvaluationMonitor... listeners)
//JAVA TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
              POSEvaluator(POSTagger *tagger, ...);

              /// <summary>
              /// Evaluates the given reference <seealso cref="POSSample"/> object.
              /// 
              /// This is done by tagging the sentence from the reference
              /// <seealso cref="POSSample"/> with the <seealso cref="POSTagger"/>. The
              /// tags are then used to update the word accuracy score.
              /// </summary>
              /// <param name="reference"> the reference <seealso cref="POSSample"/>.
              /// </param>
              /// <returns> the predicted <seealso cref="POSSample"/>. </returns>
          protected:
              virtual POSSample *processSample(POSSample *reference);

              /// <summary>
              /// Retrieves the word accuracy.
              /// 
              /// This is defined as:
              /// word accuracy = correctly detected tags / total words
              /// </summary>
              /// <returns> the word accuracy </returns>
          public:
              virtual double getWordAccuracy();

              /// <summary>
              /// Retrieves the total number of words considered
              /// in the evaluation.
              /// </summary>
              /// <returns> the word count </returns>
              virtual long long getWordCount();

              /// <summary>
              /// Represents this objects as human readable <seealso cref="String"/>.
              /// </summary>
              virtual std::string ToString();


            private:
                void InitializeInstanceFields();
            };

        }
    }
}


#endif	//#ifndef POSEVALUATOR
