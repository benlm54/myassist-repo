#ifndef OUTCOMEPRIORFEATUREGENERATOR
#define OUTCOMEPRIORFEATUREGENERATOR

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
                /// The definition feature maps the underlying distribution of outcomes.
                /// </summary>
                class OutcomePriorFeatureGenerator : public FeatureGeneratorAdapter
                {

              public:
                  static const std::string OUTCOME_PRIOR_FEATURE;

                  virtual void createFeatures(std::vector<std::string> &features, std::string tokens[], int index, std::string previousOutcomes[]);
                };

            }
        }
    }
}


#endif	//#ifndef OUTCOMEPRIORFEATUREGENERATOR
