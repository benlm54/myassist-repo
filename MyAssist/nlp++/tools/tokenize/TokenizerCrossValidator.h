#ifndef TOKENIZERCROSSVALIDATOR
#define TOKENIZERCROSSVALIDATOR

#include "../tools/util/TrainingParameters.h"
#include "../tools/dictionary/Dictionary.h"
#include "../tools/util/eval/FMeasure.h"
#include "TokenizerEvaluationMonitor.h"
#include "TokenSample.h"
#include "../tools/util/ObjectStream.h"
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
        namespace tokenize
        {


            using opennlp::tools::dictionary::Dictionary;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::TrainingParameters;
            using opennlp::tools::util::eval::CrossValidationPartitioner;
            using opennlp::tools::util::eval::FMeasure;
            using opennlp::tools::util::model::ModelUtil;

            class TokenizerCrossValidator
            {

          private:
              const std::string language;
              const bool alphaNumericOptimization;

              TrainingParameters *const params;

              Dictionary *const abbreviations;

              FMeasure *fmeasure;
//ORIGINAL LINE: private TokenizerEvaluationMonitor[] listeners;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              TokenizerEvaluationMonitor *listeners;

          public:
//ORIGINAL LINE: public TokenizerCrossValidator(String language, opennlp.tools.dictionary.Dictionary abbreviations, boolean alphaNumericOptimization, opennlp.tools.util.TrainingParameters params, TokenizerEvaluationMonitor... listeners)
//JAVA TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
              TokenizerCrossValidator(const std::string &language, Dictionary *abbreviations, bool alphaNumericOptimization, TrainingParameters *params, ...);

              /// @deprecated use <seealso cref="#TokenizerCrossValidator(String, boolean, TrainingParameters, TokenizerEvaluationMonitor...)"/>
              /// instead and pass in a TrainingParameters object. 
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              TokenizerCrossValidator(const std::string &language, bool alphaNumericOptimization, int cutoff, int iterations); //this(language, alphaNumericOptimization, ModelUtil.createTrainingParameters(iterations, cutoff));

//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              TokenizerCrossValidator(const std::string &language, bool alphaNumericOptimization); //this(language, alphaNumericOptimization, ModelUtil.createTrainingParameters(100, 5));

//ORIGINAL LINE: public TokenizerCrossValidator(String language, boolean alphaNumericOptimization, opennlp.tools.util.TrainingParameters params, TokenizerEvaluationMonitor... listeners)
//JAVA TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              TokenizerCrossValidator(const std::string &language, bool alphaNumericOptimization, TrainingParameters *params, ...); //this(language, nullptr, alphaNumericOptimization, params, listeners);


              /// <summary>
              /// Starts the evaluation.
              /// </summary>
              /// <param name="samples">
              ///          the data to train and test </param>
              /// <param name="nFolds">
              ///          number of folds
              /// </param>
              /// <exception cref="IOException"> </exception>
              virtual void evaluate(ObjectStream<TokenSample*> *samples, int nFolds) throw(IOException);

              virtual FMeasure *getFMeasure();

            private:
                void InitializeInstanceFields();
            };

        }
    }
}


#endif	//#ifndef TOKENIZERCROSSVALIDATOR
