#ifndef TOKENNAMEFINDERCROSSVALIDATOR
#define TOKENNAMEFINDERCROSSVALIDATOR

#include "../tools/util/TrainingParameters.h"
#include "TokenNameFinderEvaluationMonitor.h"
#include "../tools/util/eval/FMeasure.h"
#include "NameSample.h"
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
        namespace namefind
        {


            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::TrainingParameters;
            using opennlp::tools::util::eval::CrossValidationPartitioner;
            using opennlp::tools::util::eval::FMeasure;
            using opennlp::tools::util::featuregen::AdaptiveFeatureGenerator;
            using opennlp::tools::util::model::ModelUtil;

            class TokenNameFinderCrossValidator
            {

          private:
              const std::string languageCode;
              TrainingParameters *const params;
              const std::string type;
//ORIGINAL LINE: private final byte[] featureGeneratorBytes;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              const char *featureGeneratorBytes;
              Map<std::string, void*> *const resources;
//ORIGINAL LINE: private TokenNameFinderEvaluationMonitor[] listeners;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              TokenNameFinderEvaluationMonitor *listeners;


              FMeasure *fmeasure;

              /// <summary>
              /// Name finder cross validator
              /// </summary>
              /// <param name="languageCode"> 
              ///          the language of the training data </param>
              /// <param name="cutoff"> </param>
              /// <param name="iterations">
              /// </param>
              /// @deprecated use <seealso cref="#TokenNameFinderCrossValidator(String, String, TrainingParameters, byte[], Map, TokenNameFinderEvaluationMonitor...)"/>
              /// instead and pass in a TrainingParameters object. 
          public:
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated("use <seealso cref="#TokenNameFinderCrossValidator(String, String, opennlp.tools.util.TrainingParameters, byte[] , java.util.Map, TokenNameFinderEvaluationMonitor...)"/>") public TokenNameFinderCrossValidator(String languageCode, int cutoff, int iterations)
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              TokenNameFinderCrossValidator(const std::string &languageCode, int cutoff, int iterations); //this(languageCode, nullptr, cutoff, iterations);

              /// <summary>
              /// Name finder cross validator
              /// </summary>
              /// <param name="languageCode">
              ///          the language of the training data </param>
              /// <param name="type">
              ///          null or an override type for all types in the training data </param>
              /// <param name="cutoff">
              ///          specifies the min number of times a feature must be seen </param>
              /// <param name="iterations">
              ///          the number of iterations
              /// </param>
              /// @deprecated use <seealso cref="#TokenNameFinderCrossValidator(String, String, TrainingParameters, byte[], Map, TokenNameFinderEvaluationMonitor...)"/>
              /// instead and pass in a TrainingParameters object. 
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated("use <seealso cref="#TokenNameFinderCrossValidator(String, String, opennlp.tools.util.TrainingParameters, byte[] , java.util.Map, TokenNameFinderEvaluationMonitor...)"/>") public TokenNameFinderCrossValidator(String languageCode, String type, int cutoff, int iterations)
//JAVA TO C++ CONVERTER WARNING: Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
              TokenNameFinderCrossValidator(const std::string &languageCode, const std::string &type, int cutoff, int iterations);

              /// <summary>
              /// Name finder cross validator
              /// </summary>
              /// <param name="languageCode">
              ///          the language of the training data </param>
              /// <param name="type">
              ///          null or an override type for all types in the training data </param>
              /// <param name="featureGeneratorBytes">
              ///          descriptor to configure the feature generation or null </param>
              /// <param name="resources">
              ///          the resources for the name finder or null if none </param>
              /// <param name="cutoff">
              ///          specifies the min number of times a feature must be seen </param>
              /// <param name="iterations">
              ///          the number of iterations
              /// </param>
              /// @deprecated use <seealso cref="#TokenNameFinderCrossValidator(String, String, TrainingParameters, byte[], Map, TokenNameFinderEvaluationMonitor...)"/>
              /// instead and pass in a TrainingParameters object. 
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated("use <seealso cref="#TokenNameFinderCrossValidator(String, String, opennlp.tools.util.TrainingParameters, byte[] , java.util.Map, TokenNameFinderEvaluationMonitor...)"/>") public TokenNameFinderCrossValidator(String languageCode, String type, byte[] featureGeneratorBytes, java.util.Map<String, Object> resources, int iterations, int cutoff)
              TokenNameFinderCrossValidator(const std::string &languageCode, const std::string &type, char featureGeneratorBytes[], Map<std::string, void*> *resources, int iterations, int cutoff);

              /// <summary>
              /// Name finder cross validator
              /// </summary>
              /// <param name="languageCode">
              ///          the language of the training data </param>
              /// <param name="type">
              ///          null or an override type for all types in the training data </param>
              /// <param name="trainParams">
              ///          machine learning train parameters </param>
              /// <param name="featureGeneratorBytes">
              ///          descriptor to configure the feature generation or null </param>
              /// <param name="listeners">
              ///          a list of listeners </param>
              /// <param name="resources">
              ///          the resources for the name finder or null if none </param>
//ORIGINAL LINE: public TokenNameFinderCrossValidator(String languageCode, String type, opennlp.tools.util.TrainingParameters trainParams, byte[] featureGeneratorBytes, java.util.Map<String, Object> resources, TokenNameFinderEvaluationMonitor... listeners)
//JAVA TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
              TokenNameFinderCrossValidator(const std::string &languageCode, const std::string &type, TrainingParameters *trainParams, char featureGeneratorBytes[], Map<std::string, void*> *resources, ...);

              /// <summary>
              /// Starts the evaluation.
              /// </summary>
              /// <param name="samples">
              ///          the data to train and test </param>
              /// <param name="nFolds">
              ///          number of folds </param>
              /// <exception cref="IOException"> </exception>
              virtual void evaluate(ObjectStream<NameSample*> *samples, int nFolds) throw(IOException);

              virtual FMeasure *getFMeasure();

            private:
                void InitializeInstanceFields();
            };

        }
    }
}


#endif	//#ifndef TOKENNAMEFINDERCROSSVALIDATOR
