#ifndef FEATUREGENERATORADAPTER
#define FEATUREGENERATORADAPTER

#include "AdaptiveFeatureGenerator.h"
#include <string>

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
                /// This class provides empty implementations of some of the optional methods in
                /// <seealso cref="AdditionalContextFeatureGenerator"/> to make implementing feature generators
                /// easier.
                /// </summary>
                class FeatureGeneratorAdapter : public AdaptiveFeatureGenerator
                {

              public:
                  virtual void updateAdaptiveData(std::string tokens[], std::string outcomes[]);

                  virtual void clearAdaptiveData();

                };

            }
        }
    }
}


#endif	//#ifndef FEATUREGENERATORADAPTER