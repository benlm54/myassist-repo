#ifndef TOKENPATTERNFEATUREGENERATOR
#define TOKENPATTERNFEATUREGENERATOR

#include "FeatureGeneratorAdapter.h"
#include "../tools/tokenize/Tokenizer.h"
#include "StringBuffer.h"
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


                using opennlp::tools::tokenize::SimpleTokenizer;
                using opennlp::tools::tokenize::Tokenizer;

                /// <summary>
                /// Partitions tokens into sub-tokens based on character classes and generates
                /// class features for each of the sub-tokens and combinations of those sub-tokens.
                /// </summary>
                class TokenPatternFeatureGenerator : public FeatureGeneratorAdapter
                {

                private:
                    Pattern *noLetters;
                    Tokenizer *tokenizer;

                    /// <summary>
                    /// Initializes a new instance.
                    /// For tokinization the <seealso cref="SimpleTokenizer"/> is used.
                    /// </summary>
                public:
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
                    TokenPatternFeatureGenerator(); //this(SimpleTokenizer.INSTANCE);

                    /// <summary>
                    /// Initializes a new instance.
                    /// </summary>
                    /// <param name="supportTokenizer"> </param>
                    TokenPatternFeatureGenerator(Tokenizer *supportTokenizer);

                    virtual void createFeatures(std::vector<std::string> &feats, std::string toks[], int index, std::string preds[]);

                private:
                    void InitializeInstanceFields();
                };

            }
        }
    }
}


#endif	//#ifndef TOKENPATTERNFEATUREGENERATOR
