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
            namespace namefind
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
//ORIGINAL LINE: @ParameterDescription(valueName = "modelType", description = "The type of the token name finder model") @OptionalParameter(defaultValue = "default") String getType();
                  virtual std::string getType() = 0;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @ParameterDescription(valueName = "resourcesDir", description = "The resources directory") @OptionalParameter java.io.File getResources();
                  virtual java::io::File *getResources() = 0;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @ParameterDescription(valueName = "featuregenFile", description = "The feature generator descriptor file") @OptionalParameter java.io.File getFeaturegen();
                  virtual java::io::File *getFeaturegen() = 0;
                };

            }
        }
    }
}


#endif	//#ifndef TRAININGPARAMS
