#ifndef CACHEDFEATUREGENERATOR
#define CACHEDFEATUREGENERATOR

#include "AdaptiveFeatureGenerator.h"
#include "../tools/util/Cache.h"
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


                using opennlp::tools::util::Cache;

                /// <summary>
                /// Caches features of the aggregated <seealso cref="AdaptiveFeatureGenerator"/>s.
                /// </summary>
                class CachedFeatureGenerator : public AdaptiveFeatureGenerator
                {

              private:
                  AdaptiveFeatureGenerator *const generator;

//ORIGINAL LINE: private String[] prevTokens;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                  std::string *prevTokens;

                  Cache *contextsCache;

                  long long numberOfCacheHits;
                  long long numberOfCacheMisses;

              public:
//ORIGINAL LINE: public CachedFeatureGenerator(AdaptiveFeatureGenerator... generators)
//JAVA TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
                  CachedFeatureGenerator(...);

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @SuppressWarnings("unchecked") public void createFeatures(java.util.List<String> features, String[] tokens, int index, String[] previousOutcomes)
                  virtual void createFeatures(std::vector<std::string> &features, std::string tokens[], int index, std::string previousOutcomes[]);

                  virtual void updateAdaptiveData(std::string tokens[], std::string outcomes[]);

                  virtual void clearAdaptiveData();

                  /// <summary>
                  /// Retrieves the number of times a cache hit occurred.
                  /// </summary>
                  /// <returns> number of cache hits </returns>
                  virtual long long getNumberOfCacheHits();

                  /// <summary>
                  /// Retrieves the number of times a cache miss occurred.
                  /// </summary>
                  /// <returns> number of cache misses </returns>
                  virtual long long getNumberOfCacheMisses();

                  virtual std::string ToString();
                };

            }
        }
    }
}


#endif	//#ifndef CACHEDFEATUREGENERATOR
