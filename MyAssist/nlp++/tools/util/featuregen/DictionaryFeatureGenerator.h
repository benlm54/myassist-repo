#ifndef DICTIONARYFEATUREGENERATOR
#define DICTIONARYFEATUREGENERATOR

#include "FeatureGeneratorAdapter.h"
#include "InSpanGenerator.h"
#include "../tools/dictionary/Dictionary.h"
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


                using opennlp::tools::dictionary::Dictionary;
                using opennlp::tools::namefind::DictionaryNameFinder;

                /// <summary>
                /// The <seealso cref="DictionaryFeatureGenerator"/> uses the <seealso cref="DictionaryNameFinder"/>
                /// to generated features for detected names based on the <seealso cref="InSpanGenerator"/>.
                /// </summary>
                /// <seealso cref= Dictionary </seealso>
                /// <seealso cref= DictionaryNameFinder </seealso>
                /// <seealso cref= InSpanGenerator </seealso>
                class DictionaryFeatureGenerator : public FeatureGeneratorAdapter
                {

              private:
                  InSpanGenerator *isg;

              public:
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
                  DictionaryFeatureGenerator(Dictionary *dict); //this("",dict);
                  DictionaryFeatureGenerator(const std::string &prefix, Dictionary *dict);

                  virtual void setDictionary(Dictionary *dict);

                  virtual void setDictionary(const std::string &name, Dictionary *dict);

                  virtual void createFeatures(std::vector<std::string> &features, std::string tokens[], int index, std::string previousOutcomes[]);

                };

            }
        }
    }
}


#endif	//#ifndef DICTIONARYFEATUREGENERATOR
