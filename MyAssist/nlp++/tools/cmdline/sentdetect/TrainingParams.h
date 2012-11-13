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
            namespace sentdetect
            {


                using opennlp::tools::cmdline::ArgumentParser::OptionalParameter;
                using opennlp::tools::cmdline::ArgumentParser::ParameterDescription;
                using opennlp::tools::cmdline::params::BasicTrainingParams;

                /// <summary>
                /// TrainingParams for Sentence Detector.
                /// 
                /// Note: Do not use this class, internal use only!
                /// </summary>
                class TrainingParams : public BasicTrainingParams
                {

              public:
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @ParameterDescription(valueName = "path", description = "The abbreviation dictionary in XML format.") @OptionalParameter java.io.File getAbbDict();
                  virtual java::io::File *getAbbDict() = 0;

                };

            }
        }
    }
}


#endif	//#ifndef TRAININGPARAMS
