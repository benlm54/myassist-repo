#ifndef CHUNKERCROSSVALIDATOR
#define CHUNKERCROSSVALIDATOR

#include "../tools/util/TrainingParameters.h"
#include "../tools/util/eval/FMeasure.h"
#include "ChunkerEvaluationMonitor.h"
#include "ChunkSample.h"
#include "../tools/util/InvalidFormatException.h"
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
        namespace chunker
        {


            using opennlp::tools::util::InvalidFormatException;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::TrainingParameters;
            using opennlp::tools::util::eval::CrossValidationPartitioner;
            using opennlp::tools::util::eval::FMeasure;
            using opennlp::tools::util::model::ModelUtil;

            class ChunkerCrossValidator
            {

          private:
              const std::string languageCode;
              TrainingParameters *const params;

              FMeasure *fmeasure;
//ORIGINAL LINE: private ChunkerEvaluationMonitor[] listeners;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              ChunkerEvaluationMonitor *listeners;

              /// @deprecated use <seealso cref="ChunkerCrossValidator#ChunkerCrossValidator(String, TrainingParameters, ChunkerEvaluationMonitor...)"/>
              /// instead and pass in a TrainingParameters object. 
          public:
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated("use <seealso cref="ChunkerCrossValidator#ChunkerCrossValidator(String, opennlp.tools.util.TrainingParameters, ChunkerEvaluationMonitor...)"/>") public ChunkerCrossValidator(String languageCode, int cutoff, int iterations)
              ChunkerCrossValidator(const std::string &languageCode, int cutoff, int iterations);

//ORIGINAL LINE: public ChunkerCrossValidator(String languageCode, opennlp.tools.util.TrainingParameters params, ChunkerEvaluationMonitor... listeners)
//JAVA TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
              ChunkerCrossValidator(const std::string &languageCode, TrainingParameters *params, ...);

              /// <summary>
              /// Starts the evaluation.
              /// </summary>
              /// <param name="samples">
              ///          the data to train and test </param>
              /// <param name="nFolds">
              ///          number of folds
              /// </param>
              /// <exception cref="IOException"> </exception>
              virtual void evaluate(ObjectStream<ChunkSample*> *samples, int nFolds) throw(IOException, InvalidFormatException, IOException);

              virtual FMeasure *getFMeasure();

            private:
                void InitializeInstanceFields();
            };

        }
    }
}


#endif	//#ifndef CHUNKERCROSSVALIDATOR
