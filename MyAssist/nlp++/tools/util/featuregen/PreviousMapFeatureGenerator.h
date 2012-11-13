#ifndef PREVIOUSMAPFEATUREGENERATOR
#define PREVIOUSMAPFEATUREGENERATOR

#include "AdaptiveFeatureGenerator.h"
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
                /// This <seealso cref="FeatureGeneratorAdapter"/> generates features indicating the outcome associated with a previously occuring word.
                /// </summary>
                class PreviousMapFeatureGenerator : public AdaptiveFeatureGenerator
                {

              private:
                  Map<std::string, std::string> *previousMap;

              public:
                  virtual void createFeatures(std::vector<std::string> &features, std::string tokens[], int index, std::string preds[]);

                  /// <summary>
                  /// Generates previous decision features for the token based on contents of the previous map.
                  /// </summary>
                  virtual void updateAdaptiveData(std::string tokens[], std::string outcomes[]);

                  /// <summary>
                  /// Clears the previous map.
                  /// </summary>
                  virtual void clearAdaptiveData();

                private:
                    void InitializeInstanceFields();

public:
                    PreviousMapFeatureGenerator()
                    {
                        InitializeInstanceFields();
                    }
                };

            }
        }
    }
}


#endif	//#ifndef PREVIOUSMAPFEATUREGENERATOR
