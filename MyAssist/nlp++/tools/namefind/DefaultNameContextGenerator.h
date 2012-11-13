#ifndef DEFAULTNAMECONTEXTGENERATOR
#define DEFAULTNAMECONTEXTGENERATOR

#include "NameContextGenerator.h"
#include "../tools/util/featuregen/AdaptiveFeatureGenerator.h"
#include "../tools/util/featuregen/BigramNameFeatureGenerator.h"
#include "../tools/util/featuregen/CachedFeatureGenerator.h"
#include "../tools/util/featuregen/OutcomePriorFeatureGenerator.h"
#include "../tools/util/featuregen/PreviousMapFeatureGenerator.h"
#include "../tools/util/featuregen/TokenClassFeatureGenerator.h"
#include "../tools/util/featuregen/TokenFeatureGenerator.h"
#include "../tools/util/featuregen/WindowFeatureGenerator.h"
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
        namespace namefind
        {


            using opennlp::tools::util::featuregen::AdaptiveFeatureGenerator;
            using opennlp::tools::util::featuregen::BigramNameFeatureGenerator;
            using opennlp::tools::util::featuregen::CachedFeatureGenerator;
            using opennlp::tools::util::featuregen::FeatureGeneratorUtil;
            using opennlp::tools::util::featuregen::OutcomePriorFeatureGenerator;
            using opennlp::tools::util::featuregen::PreviousMapFeatureGenerator;
            using opennlp::tools::util::featuregen::TokenClassFeatureGenerator;
            using opennlp::tools::util::featuregen::TokenFeatureGenerator;
            using opennlp::tools::util::featuregen::WindowFeatureGenerator;

            /// <summary>
            /// Class for determining contextual features for a tag/chunk style
            /// named-entity recognizer.
            /// </summary>
            class DefaultNameContextGenerator : public NameContextGenerator
            {

          private:
//ORIGINAL LINE: private opennlp.tools.util.featuregen.AdaptiveFeatureGenerator featureGenerators[];
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              AdaptiveFeatureGenerator *featureGenerators;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated private static opennlp.tools.util.featuregen.AdaptiveFeatureGenerator windowFeatures = new opennlp.tools.util.featuregen.CachedFeatureGenerator(new opennlp.tools.util.featuregen.AdaptiveFeatureGenerator[]{ new opennlp.tools.util.featuregen.WindowFeatureGenerator(new opennlp.tools.util.featuregen.TokenFeatureGenerator(), 2, 2), new opennlp.tools.util.featuregen.WindowFeatureGenerator(new opennlp.tools.util.featuregen.TokenClassFeatureGenerator(true), 2, 2), new opennlp.tools.util.featuregen.OutcomePriorFeatureGenerator(), new opennlp.tools.util.featuregen.PreviousMapFeatureGenerator(), new opennlp.tools.util.featuregen.BigramNameFeatureGenerator()
              static AdaptiveFeatureGenerator windowFeatures = new CachedFeatureGenerator(new AdaptiveFeatureGenerator[]{ new WindowFeatureGenerator(new TokenFeatureGenerator(), 2, 2), new WindowFeatureGenerator(new TokenClassFeatureGenerator(true), 2, 2), new OutcomePriorFeatureGenerator(), new PreviousMapFeatureGenerator(), new BigramNameFeatureGenerator()
              public:
            });

              /// <summary>
              /// Creates a name context generator. </summary>
              /// @deprecated use the other constructor and always provide the feature generators 
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated("use the other constructor and always provide the feature generators") public DefaultNameContextGenerator()
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              DefaultNameContextGenerator(); //this((AdaptiveFeatureGenerator[]) nullptr);

              /// <summary>
              /// Creates a name context generator with the specified cache size.
              /// </summary>
//ORIGINAL LINE: public DefaultNameContextGenerator(opennlp.tools.util.featuregen.AdaptiveFeatureGenerator... featureGenerators)
//JAVA TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
              DefaultNameContextGenerator(...);

              virtual void addFeatureGenerator(AdaptiveFeatureGenerator *generator);

              virtual void updateAdaptiveData(std::string tokens[], std::string outcomes[]);

              virtual void clearAdaptiveData();

              /// <summary>
              /// Return the context for finding names at the specified index. </summary>
              /// <param name="index"> The index of the token in the specified toks array for which the context should be constructed. </param>
              /// <param name="tokens"> The tokens of the sentence.  The <code>toString</code> methods of these objects should return the token text. </param>
              /// <param name="preds"> The previous decisions made in the tagging of this sequence.  Only indices less than i will be examined. </param>
              /// <param name="additionalContext"> Addition features which may be based on a context outside of the sentence.
              /// </param>
              /// <returns> the context for finding names at the specified index. </returns>
              virtual std::string *getContext(int index, std::string tokens[], std::string preds[], Object additionalContext[]);
        };
    }
}
}


#endif	//#ifndef DEFAULTNAMECONTEXTGENERATOR
