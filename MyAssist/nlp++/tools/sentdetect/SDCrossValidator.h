#ifndef SDCROSSVALIDATOR
#define SDCROSSVALIDATOR

#include "../tools/dictionary/Dictionary.h"
#include "../tools/util/TrainingParameters.h"
#include "../tools/util/eval/FMeasure.h"
#include "SentenceDetectorEvaluationMonitor.h"
#include "SentenceSample.h"
#include "../tools/util/ObjectStream.h"
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
        namespace sentdetect
        {


            using opennlp::tools::dictionary::Dictionary;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::TrainingParameters;
            using opennlp::tools::util::eval::CrossValidationPartitioner;
            using opennlp::tools::util::eval::FMeasure;
            using opennlp::tools::util::model::ModelUtil;

            /// 
            class SDCrossValidator
            {

          private:
              const std::string languageCode;

              Dictionary *const abbreviations;

              TrainingParameters *const params;

              FMeasure *fmeasure;

//ORIGINAL LINE: private SentenceDetectorEvaluationMonitor[] listeners;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              SentenceDetectorEvaluationMonitor *listeners;

          public:
//ORIGINAL LINE: public SDCrossValidator(String languageCode, opennlp.tools.util.TrainingParameters params, opennlp.tools.dictionary.Dictionary abbreviations, SentenceDetectorEvaluationMonitor... listeners)
//JAVA TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
              SDCrossValidator(const std::string &languageCode, TrainingParameters *params, Dictionary *abbreviations, ...);

              /// @deprecated use <seealso cref="#SDCrossValidator(String, TrainingParameters)"/>
              /// instead and pass in a TrainingParameters object. 
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              SDCrossValidator(const std::string &languageCode, int cutoff, int iterations); //this(languageCode, ModelUtil.createTrainingParameters(cutoff, iterations));

//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              SDCrossValidator(const std::string &languageCode, TrainingParameters *params); //this(languageCode, params, (Dictionary)nullptr);

              /// @deprecated use <seealso cref="#SDCrossValidator(String, TrainingParameters, Dictionary, SentenceDetectorEvaluationMonitor...)"/>
              /// instead and pass in a TrainingParameters object. 
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated("use <seealso cref="#SDCrossValidator(String, opennlp.tools.util.TrainingParameters, opennlp.tools.dictionary.Dictionary, SentenceDetectorEvaluationMonitor...)"/>") public SDCrossValidator(String languageCode, int cutoff, int iterations, opennlp.tools.dictionary.Dictionary abbreviations)
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              SDCrossValidator(const std::string &languageCode, int cutoff, int iterations, Dictionary *abbreviations); //this(languageCode, ModelUtil.createTrainingParameters(cutoff, iterations), abbreviations);

//ORIGINAL LINE: public SDCrossValidator(String languageCode, opennlp.tools.util.TrainingParameters params, SentenceDetectorEvaluationMonitor... listeners)
//JAVA TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              SDCrossValidator(const std::string &languageCode, TrainingParameters *params, ...); //this(languageCode, params, nullptr, listeners);

//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              SDCrossValidator(const std::string &languageCode); //this(languageCode, 5, 100);

              /// <summary>
              /// Starts the evaluation.
              /// </summary>
              /// <param name="samples">
              ///          the data to train and test </param>
              /// <param name="nFolds">
              ///          number of folds
              /// </param>
              /// <exception cref="IOException"> </exception>
              virtual void evaluate(ObjectStream<SentenceSample*> *samples, int nFolds) throw(IOException);

              virtual FMeasure *getFMeasure();

            private:
                void InitializeInstanceFields();
            };

        }
    }
}


#endif	//#ifndef SDCROSSVALIDATOR
