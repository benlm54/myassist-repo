#ifndef TOKENCLASSFEATUREGENERATOR
#define TOKENCLASSFEATUREGENERATOR

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
                /// Generates features for different for the class of the token.
                /// </summary>
                class TokenClassFeatureGenerator : public FeatureGeneratorAdapter
                {

              private:
                  static const std::string TOKEN_CLASS_PREFIX;
                  static const std::string TOKEN_AND_CLASS_PREFIX;

                  bool generateWordAndClassFeature;

              public:
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
                  TokenClassFeatureGenerator(); //this(false);

                  TokenClassFeatureGenerator(bool genearteWordAndClassFeature);

                  virtual void createFeatures(std::vector<std::string> &features, std::string tokens[], int index, std::string preds[]);
                };

            }
        }
    }
}


#endif	//#ifndef TOKENCLASSFEATUREGENERATOR
