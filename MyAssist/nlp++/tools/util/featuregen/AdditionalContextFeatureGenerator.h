#ifndef ADDITIONALCONTEXTFEATUREGENERATOR
#define ADDITIONALCONTEXTFEATUREGENERATOR

#include "FeatureGeneratorAdapter.h"
#include <string>
#include <vector>

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
        namespace util
        {
            namespace featuregen
            {



                /// <summary>
                /// The <seealso cref="AdditionalContextFeatureGenerator"/> generates the context from the passed
                /// in additional context.
                /// </summary>
                class AdditionalContextFeatureGenerator : public FeatureGeneratorAdapter
                {

              private:
//ORIGINAL LINE: private String[][] additionalContext;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                  std::string **additionalContext;

                //  public AdditionalContextFeatureGenerator() {
                //  }

              public:
                  virtual void createFeatures(std::vector<std::string> &features, std::string tokens[], int index, std::string preds[]);

                  virtual void setCurrentContext(std::string context[][]);
                };

            }
        }
    }
}


#endif	//#ifndef ADDITIONALCONTEXTFEATUREGENERATOR
