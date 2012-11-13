#ifndef TRAININGPARAMS
#define TRAININGPARAMS

#include "../tools/cmdline/params/BasicTrainingParams.h"

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
        namespace cmdline
        {
            namespace postag
            {


                using opennlp::tools::cmdline::ArgumentParser::OptionalParameter;
                using opennlp::tools::cmdline::ArgumentParser::ParameterDescription;
                using opennlp::tools::cmdline::params::BasicTrainingParams;

                /// <summary>
                /// TrainingParameters for Name Finder.
                /// 
                /// Note: Do not use this class, internal use only!
                /// </summary>
                class TrainingParams : public BasicTrainingParams
                {

              public:
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @ParameterDescription(valueName = "maxent|perceptron|perceptron_sequence", description = "The type of the token name finder model. One of maxent|perceptron|perceptron_sequence.") @OptionalParameter(defaultValue = "maxent") String getType();
                  virtual std::string getType() = 0;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @ParameterDescription(valueName = "dictionaryPath", description = "The XML tag dictionary file") @OptionalParameter java.io.File getDict();
                  virtual java::io::File *getDict() = 0;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @ParameterDescription(valueName = "cutoff", description = "NGram cutoff. If not specified will not create ngram dictionary.") @OptionalParameter Integer getNgram();
                  virtual int getNgram() = 0;
                };

            }
        }
    }
}


#endif	//#ifndef TRAININGPARAMS
