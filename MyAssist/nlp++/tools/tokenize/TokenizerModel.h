#ifndef TOKENIZERMODEL
#define TOKENIZERMODEL

#include "../tools/util/model/BaseModel.h"
#include "../model/AbstractModel.h"
#include "../tools/dictionary/Dictionary.h"
#include "../tools/util/InvalidFormatException.h"
#include "../model/MaxentModel.h"
#include <string>
#include "stringconverter.h"

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
        namespace tokenize
        {


            using opennlp::maxent::io::BinaryGISModelReader;
            using opennlp::model::AbstractModel;
            using opennlp::model::MaxentModel;
            using opennlp::tools::dictionary::Dictionary;
            using opennlp::tools::util::InvalidFormatException;
            using opennlp::tools::util::model::BaseModel;
            using opennlp::tools::util::model::ModelUtil;

            /// <summary>
            /// The <seealso cref="TokenizerModel"/> is the model used
            /// by a learnable <seealso cref="Tokenizer"/>.
            /// </summary>
            /// <seealso cref= TokenizerME </seealso>
            class TokenizerModel : public BaseModel
            {

          private:
              static const std::string COMPONENT_NAME;

              static const std::string TOKENIZER_MODEL_ENTRY;
              static const std::string ABBREVIATIONS_ENTRY_NAME;

              static const std::string USE_ALPHA_NUMERIC_OPTIMIZATION;

              /// <summary>
              /// Initializes the current instance.
              /// </summary>
              /// <param name="tokenizerMaxentModel"> </param>
              /// <param name="useAlphaNumericOptimization"> </param>
          public:
              TokenizerModel(const std::string &language, AbstractModel *tokenizerMaxentModel, Dictionary *abbreviations, bool useAlphaNumericOptimization, Map<std::string, std::string> *manifestInfoEntries);

              /// <summary>
              /// Initializes the current instance.
              /// </summary>
              /// <param name="language"> </param>
              /// <param name="tokenizerMaxentModel"> </param>
              /// <param name="useAlphaNumericOptimization"> </param>
              /// <param name="manifestInfoEntries"> </param>
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              TokenizerModel(const std::string &language, AbstractModel *tokenizerMaxentModel, bool useAlphaNumericOptimization, Map<std::string, std::string> *manifestInfoEntries); //this(language, tokenizerMaxentModel, nullptr, useAlphaNumericOptimization, manifestInfoEntries);

              /// <summary>
              /// Initializes the current instance.
              /// </summary>
              /// <param name="language"> </param>
              /// <param name="tokenizerMaxentModel"> </param>
              /// <param name="useAlphaNumericOptimization"> </param>
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              TokenizerModel(const std::string &language, AbstractModel *tokenizerMaxentModel, bool useAlphaNumericOptimization); //this(language, tokenizerMaxentModel, useAlphaNumericOptimization, nullptr);

              /// <summary>
              /// Initializes the current instance.
              /// </summary>
              /// <param name="in">
              /// </param>
              /// <exception cref="IOException"> </exception>
              /// <exception cref="InvalidFormatException"> </exception>
              TokenizerModel(InputStream *in_Renamed) throw(IOException, InvalidFormatException);

              /// <summary>
              /// Checks if the tokenizer model has the right outcomes.
              /// </summary>
              /// <param name="model">
              /// @return </param>
          private:
              static bool isModelCompatible(MaxentModel *model);

          protected:
              virtual void validateArtifactMap() throw(InvalidFormatException);

          public:
              AbstractModel *getMaxentModel();

              Dictionary *getAbbreviations();

              bool useAlphaNumericOptimization();

              static void main(std::string args[]) throw(IOException);
            };

        }
    }
}


#endif	//#ifndef TOKENIZERMODEL
