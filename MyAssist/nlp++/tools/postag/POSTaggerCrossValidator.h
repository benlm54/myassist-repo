#ifndef POSTAGGERCROSSVALIDATOR
#define POSTAGGERCROSSVALIDATOR

#include "../tools/util/TrainingParameters.h"
#include "POSDictionary.h"
#include "../tools/dictionary/Dictionary.h"
#include "../tools/util/eval/Mean.h"
#include "POSTaggerEvaluationMonitor.h"
#include "../tools/util/model/ModelType.h"
#include "POSSample.h"
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
        namespace postag
        {


            using opennlp::tools::cmdline::CmdLineUtil;
            using opennlp::tools::cmdline::TerminateToolException;
            using opennlp::tools::dictionary::Dictionary;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::TrainingParameters;
            using opennlp::tools::util::eval::CrossValidationPartitioner;
            using opennlp::tools::util::eval::Mean;
            using opennlp::tools::util::model::ModelType;
            using opennlp::tools::util::model::ModelUtil;

            class POSTaggerCrossValidator
            {

          private:
              const std::string languageCode;

              TrainingParameters *const params;

              POSDictionary *tagDictionary;
              Dictionary *ngramDictionary;
              int ngramCutoff;

              Mean *wordAccuracy;
//ORIGINAL LINE: private POSTaggerEvaluationMonitor[] listeners;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              POSTaggerEvaluationMonitor *listeners;

              /// @deprecated use <seealso cref="#POSTaggerCrossValidator(String, TrainingParameters, POSDictionary, Dictionary, POSTaggerEvaluationMonitor...)"/>
              /// instead and pass in a TrainingParameters object. 
          public:
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated("use <seealso cref="#POSTaggerCrossValidator(String, opennlp.tools.util.TrainingParameters, POSDictionary, opennlp.tools.dictionary.Dictionary, POSTaggerEvaluationMonitor...)"/>") public POSTaggerCrossValidator(String languageCode, opennlp.tools.util.model.ModelType modelType, POSDictionary tagDictionary, opennlp.tools.dictionary.Dictionary ngramDictionary, int cutoff, int iterations)
              POSTaggerCrossValidator(const std::string &languageCode, ModelType modelType, POSDictionary *tagDictionary, Dictionary *ngramDictionary, int cutoff, int iterations);

//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              POSTaggerCrossValidator(const std::string &languageCode, ModelType modelType, POSDictionary *tagDictionary, Dictionary *ngramDictionary); //this(languageCode, modelType, tagDictionary, ngramDictionary, 5, 100);

//ORIGINAL LINE: public POSTaggerCrossValidator(String languageCode, opennlp.tools.util.TrainingParameters trainParam, POSDictionary tagDictionary, POSTaggerEvaluationMonitor... listeners)
//JAVA TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
              POSTaggerCrossValidator(const std::string &languageCode, TrainingParameters *trainParam, POSDictionary *tagDictionary, ...);

//ORIGINAL LINE: public POSTaggerCrossValidator(String languageCode, opennlp.tools.util.TrainingParameters trainParam, POSDictionary tagDictionary, Integer ngramCutoff, POSTaggerEvaluationMonitor... listeners)
//JAVA TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
              POSTaggerCrossValidator(const std::string &languageCode, TrainingParameters *trainParam, POSDictionary *tagDictionary, int ngramCutoff, ...);

//ORIGINAL LINE: public POSTaggerCrossValidator(String languageCode, opennlp.tools.util.TrainingParameters trainParam, POSDictionary tagDictionary, opennlp.tools.dictionary.Dictionary ngramDictionary, POSTaggerEvaluationMonitor... listeners)
//JAVA TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
              POSTaggerCrossValidator(const std::string &languageCode, TrainingParameters *trainParam, POSDictionary *tagDictionary, Dictionary *ngramDictionary, ...);

              /// <summary>
              /// Starts the evaluation.
              /// </summary>
              /// <param name="samples">
              ///          the data to train and test </param>
              /// <param name="nFolds">
              ///          number of folds
              /// </param>
              /// <exception cref="IOException"> </exception>
              virtual void evaluate(ObjectStream<POSSample*> *samples, int nFolds) throw(IOException, IOException);

              /// <summary>
              /// Retrieves the accuracy for all iterations.
              /// </summary>
              /// <returns> the word accuracy </returns>
              virtual double getWordAccuracy();

              /// <summary>
              /// Retrieves the number of words which where validated
              /// over all iterations. The result is the amount of folds
              /// multiplied by the total number of words.
              /// </summary>
              /// <returns> the word count </returns>
              virtual long long getWordCount();

            private:
                void InitializeInstanceFields();
            };

        }
    }
}


#endif	//#ifndef POSTAGGERCROSSVALIDATOR
