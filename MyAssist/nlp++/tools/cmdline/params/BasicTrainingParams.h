#ifndef BASICTRAININGPARAMS
#define BASICTRAININGPARAMS

#include "EncodingParameter.h"

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
            namespace params
            {

                using opennlp::tools::cmdline::ArgumentParser::OptionalParameter;
                using opennlp::tools::cmdline::ArgumentParser::ParameterDescription;

                // TODO: remove the old BasicTrainingParameters and rename this class to BasicTrainingParameters

                /// <summary>
                /// Common training parameters.
                /// 
                /// Note: Do not use this class, internal use only!
                /// </summary>
                class BasicTrainingParams : public EncodingParameter
                {

              public:
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @ParameterDescription(valueName = "language", description = "specifies the language which is being processed.") String getLang();
                  virtual std::string getLang() = 0;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @ParameterDescription(valueName = "num", description = "specifies the number of training iterations. It is ignored if a parameters file is passed.") @OptionalParameter(defaultValue="100") Integer getIterations();
                  virtual int getIterations() = 0;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @ParameterDescription(valueName = "num", description = "specifies the min number of times a feature must be seen. It is ignored if a parameters file is passed.") @OptionalParameter(defaultValue="5") Integer getCutoff();
                  virtual int getCutoff() = 0;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @ParameterDescription(valueName = "paramsFile", description = "Training parameters file.") @OptionalParameter() String getParams();
                  virtual std::string getParams() = 0;

                };

            }
        }
    }
}


#endif	//#ifndef BASICTRAININGPARAMS
