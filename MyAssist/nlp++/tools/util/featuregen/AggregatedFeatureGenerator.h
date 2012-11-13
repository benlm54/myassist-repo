#ifndef AGGREGATEDFEATUREGENERATOR
#define AGGREGATEDFEATUREGENERATOR

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
                /// The <seealso cref="AggregatedFeatureGenerator"/> aggregates a set of
                /// <seealso cref="AdaptiveFeatureGenerator"/>s and calls them to generate the features.
                /// </summary>
                class AggregatedFeatureGenerator : public AdaptiveFeatureGenerator
                {

                  /// <summary>
                  /// Contains all aggregated <seealso cref="AdaptiveFeatureGenerator"/>s.
                  /// </summary>
              private:
                  Collection<AdaptiveFeatureGenerator*> *generators;

                  /// <summary>
                  /// Initializes the current instance.
                  /// </summary>
                  /// <param name="generators"> array of generators, null values are not permitted </param>
              public:
//ORIGINAL LINE: public AggregatedFeatureGenerator(AdaptiveFeatureGenerator... generators)
//JAVA TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
                  AggregatedFeatureGenerator(...);

//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
                  AggregatedFeatureGenerator(Collection<AdaptiveFeatureGenerator*> *generators); //this(generators.toArray(new AdaptiveFeatureGenerator[generators.size()]));

                  /// <summary>
                  /// Calls the <seealso cref="AdaptiveFeatureGenerator#clearAdaptiveData()"/> method
                  /// on all aggregated <seealso cref="AdaptiveFeatureGenerator"/>s.
                  /// </summary>
                  virtual void clearAdaptiveData();

                  /// <summary>
                  /// Calls the <seealso cref="AdaptiveFeatureGenerator#createFeatures(List, String[], int, String[])"/>
                  /// method on all aggregated <seealso cref="AdaptiveFeatureGenerator"/>s.
                  /// </summary>
                  virtual void createFeatures(std::vector<std::string> &features, std::string tokens[], int index, std::string previousOutcomes[]);

                  /// <summary>
                  /// Calls the <seealso cref="AdaptiveFeatureGenerator#updateAdaptiveData(String[], String[])"/>
                  /// method on all aggregated <seealso cref="AdaptiveFeatureGenerator"/>s.
                  /// </summary>
                  virtual void updateAdaptiveData(std::string tokens[], std::string outcomes[]);

                  /// <summary>
                  /// Retrieves a <seealso cref="Collections"/> of all aggregated
                  /// <seealso cref="AdaptiveFeatureGenerator"/>s.
                  /// </summary>
                  /// <returns> all aggregated generators </returns>
                  virtual Collection<AdaptiveFeatureGenerator*> *getGenerators();
                };

            }
        }
    }
}


#endif	//#ifndef AGGREGATEDFEATUREGENERATOR
