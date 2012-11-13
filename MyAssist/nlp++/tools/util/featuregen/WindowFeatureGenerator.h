#ifndef WINDOWFEATUREGENERATOR
#define WINDOWFEATUREGENERATOR

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
                /// Generates previous and next features for a given <seealso cref="AdaptiveFeatureGenerator"/>.
                /// The window size can be specified.
                /// 
                /// Features:
                /// Current token is always included unchanged
                /// Previous tokens are prefixed with p distance
                /// Next tokens are prefix with n distance
                /// </summary>
                class WindowFeatureGenerator : public AdaptiveFeatureGenerator
                {

              public:
                  static const std::string PREV_PREFIX;
                  static const std::string NEXT_PREFIX;

              private:
                  AdaptiveFeatureGenerator *const generator;

                  const int prevWindowSize;
                  const int nextWindowSize;

                  /// <summary>
                  /// Initializes the current instance with the given parameters.
                  /// </summary>
                  /// <param name="generator"> Feature generator to apply to the window. </param>
                  /// <param name="prevWindowSize"> Size of the window to the left of the current token. </param>
                  /// <param name="nextWindowSize"> Size of the window to the right of the current token. </param>
              public:
                  WindowFeatureGenerator(AdaptiveFeatureGenerator *generator, int prevWindowSize, int nextWindowSize);

                  /// <summary>
                  /// Initializes the current instance with the given parameters.
                  /// </summary>
                  /// <param name="prevWindowSize"> </param>
                  /// <param name="nextWindowSize"> </param>
                  /// <param name="generators"> </param>
//ORIGINAL LINE: public WindowFeatureGenerator(int prevWindowSize, int nextWindowSize, AdaptiveFeatureGenerator... generators)
//JAVA TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
                  WindowFeatureGenerator(int prevWindowSize, int nextWindowSize, ...); //this(new AggregatedFeatureGenerator(generators), prevWindowSize, nextWindowSize);

                  /// <summary>
                  /// Initializes the current instance. The previous and next window size is 5.
                  /// </summary>
                  /// <param name="generator"> </param>
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
                  WindowFeatureGenerator(AdaptiveFeatureGenerator *generator); //this(generator, 5, 5);

                  /// <summary>
                  /// Initializes the current isntance with the given parameters.
                  /// </summary>
                  /// <param name="generators"> </param>
//ORIGINAL LINE: public WindowFeatureGenerator(AdaptiveFeatureGenerator... generators)
//JAVA TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
                  WindowFeatureGenerator(...); //this(new AggregatedFeatureGenerator(generators), 5, 5);

                  virtual void createFeatures(std::vector<std::string> &features, std::string tokens[], int index, std::string preds[]);

                  virtual void updateAdaptiveData(std::string tokens[], std::string outcomes[]);

                  virtual void clearAdaptiveData();

                  virtual std::string ToString();
                };

            }
        }
    }
}


#endif	//#ifndef WINDOWFEATUREGENERATOR
