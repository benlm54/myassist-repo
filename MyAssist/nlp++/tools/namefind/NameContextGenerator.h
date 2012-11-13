#ifndef NAMECONTEXTGENERATOR
#define NAMECONTEXTGENERATOR

#include "../tools/util/BeamSearchContextGenerator.h"
#include "../tools/util/featuregen/AdaptiveFeatureGenerator.h"
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
        namespace namefind
        {

            using opennlp::tools::util::BeamSearchContextGenerator;
            using opennlp::tools::util::featuregen::AdaptiveFeatureGenerator;

            /// <summary>
            /// Interface for generating the context for an name finder by specifying a set of geature generators.
            /// 
            /// </summary>
            class NameContextGenerator : public BeamSearchContextGenerator<std::string>
            {

              /// <summary>
              /// Adds a feature generator to this set of feature generators. </summary>
              /// <param name="generator"> The feature generator to add. </param>
          public:
              virtual void addFeatureGenerator(opennlp::tools::util::featuregen::AdaptiveFeatureGenerator *generator) = 0;

              /// <summary>
              /// Informs all the feature generators for a name finder that the specified tokens have been classified with the coorisponds set of specified outcomes. </summary>
              /// <param name="tokens"> The tokens of the sentence or other text unit which has been processed. </param>
              /// <param name="outcomes"> The outcomes associated with the specified tokens. </param>
              virtual void updateAdaptiveData(std::string tokens[], std::string outcomes[]) = 0;

              /// <summary>
              /// Informs all the feature generators for a name finder that the context of the adaptive data (typically a document) is no longer valid.
              /// </summary>
              virtual void clearAdaptiveData() = 0;

            };

        }
    }
}


#endif	//#ifndef NAMECONTEXTGENERATOR
