#ifndef CHARACTERNGRAMFEATUREGENERATOR
#define CHARACTERNGRAMFEATUREGENERATOR

#include "FeatureGeneratorAdapter.h"
#include "const_iterator.h"
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


                using opennlp::tools::ngram::NGramModel;
                using opennlp::tools::util::StringList;

                /// <summary>
                /// The <seealso cref="CharacterNgramFeatureGenerator"/> uses character ngrams to
                /// generate features about each token.
                /// The minimum and maximum length can be specified.
                /// </summary>
                class CharacterNgramFeatureGenerator : public FeatureGeneratorAdapter
                {

              private:
                  const int minLength;
                  const int maxLength;

              public:
                  CharacterNgramFeatureGenerator(int minLength, int maxLength);

                  /// <summary>
                  /// Initializes the current instance with min 2 length and max 5 length of ngrams.
                  /// </summary>
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
                  CharacterNgramFeatureGenerator(); //this(2, 5);

                  virtual void createFeatures(std::vector<std::string> &features, std::string tokens[], int index, std::string preds[]);
                };

            }
        }
    }
}


#endif	//#ifndef CHARACTERNGRAMFEATUREGENERATOR
