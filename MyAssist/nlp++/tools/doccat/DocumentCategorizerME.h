#ifndef DOCUMENTCATEGORIZERME
#define DOCUMENTCATEGORIZERME

#include "DocumentCategorizer.h"
#include "FeatureGenerator.h"
#include "../model/MaxentModel.h"
#include "DocumentCategorizerContextGenerator.h"
#include "DoccatModel.h"
#include "../model/AbstractModel.h"
#include "DocumentCategorizerEventStream.h"
#include "DocumentSample.h"
#include "../tools/util/ObjectStream.h"
#include "../tools/util/TrainingParameters.h"
#include <string>
#include <map>

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
        namespace doccat
        {


            using opennlp::maxent::GIS;
            using opennlp::model::AbstractModel;
            using opennlp::model::MaxentModel;
            using opennlp::model::TrainUtil;
            using opennlp::model::TwoPassDataIndexer;
            using opennlp::tools::tokenize::SimpleTokenizer;
            using opennlp::tools::tokenize::Tokenizer;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::TrainingParameters;
            using opennlp::tools::util::model::ModelUtil;

            /// <summary>
            /// Maxent implementation of <seealso cref="DocumentCategorizer"/>.
            /// </summary>
            class DocumentCategorizerME : public DocumentCategorizer
            {

              /// <summary>
              /// Shared default thread safe feature generator.
              /// </summary>
          private:
              static FeatureGenerator *defaultFeatureGenerator;

              MaxentModel *model;
              DocumentCategorizerContextGenerator *mContextGenerator;

              /// <summary>
              /// Initializes a the current instance with a doccat model and custom feature generation.
              /// The feature generation must be identical to the configuration at training time.
              /// </summary>
              /// <param name="model"> </param>
              /// <param name="featureGenerators"> </param>
          public:
//ORIGINAL LINE: public DocumentCategorizerME(DoccatModel model, FeatureGenerator... featureGenerators)
//JAVA TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
              DocumentCategorizerME(DoccatModel *model, ...);

              /// <summary>
              /// Initializes the current instance with a doccat model. Default feature generation is used.
              /// </summary>
              /// <param name="model"> </param>
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              DocumentCategorizerME(DoccatModel *model); //this(model, defaultFeatureGenerator);

              /// <summary>
              /// Initializes the current instance with the given <seealso cref="MaxentModel"/>.
              /// </summary>
              /// <param name="model">
              /// </param>
              /// @deprecated Use <seealso cref="DocumentCategorizerME#DocumentCategorizerME(DoccatModel)"/> instead. 
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated("Use <seealso cref="DocumentCategorizerME#DocumentCategorizerME(DoccatModel)"/> instead.") public DocumentCategorizerME(opennlp.model.MaxentModel model)
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              DocumentCategorizerME(MaxentModel *model); //this(model, new FeatureGenerator[]{new BagOfWordsFeatureGenerator()});

              /// <summary>
              /// Initializes the current instance with a the given <seealso cref="MaxentModel"/>
              /// and <seealso cref="FeatureGenerator"/>s.
              /// </summary>
              /// <param name="model"> </param>
              /// <param name="featureGenerators">
              /// </param>
              /// @deprecated Use <seealso cref="DocumentCategorizerME#DocumentCategorizerME(DoccatModel, FeatureGenerator...)"/> instead. 
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated("Use <seealso cref="DocumentCategorizerME#DocumentCategorizerME(DoccatModel, FeatureGenerator...)"/> instead.") public DocumentCategorizerME(opennlp.model.MaxentModel model, FeatureGenerator... featureGenerators)
//JAVA TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
              DocumentCategorizerME(MaxentModel *model, ...);

              /// <summary>
              /// Categorizes the given text.
              /// </summary>
              /// <param name="text"> </param>
              virtual double *categorize(std::string text[]);

              virtual double *categorize(const std::string &documentText);

              virtual std::string getBestCategory(double outcome[]);

              virtual int getIndex(const std::string &category);

              virtual std::string getCategory(int index);

              virtual int getNumberOfCategories();

              virtual std::string getAllResults(double results[]);

              /// <summary>
              /// Trains a new model for the <seealso cref="DocumentCategorizerME"/>.
              /// </summary>
              /// <param name="eventStream">
              /// </param>
              /// <returns> the new model </returns>
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated public static opennlp.model.AbstractModel train(DocumentCategorizerEventStream eventStream) throws java.io.IOException
               static AbstractModel *train(DocumentCategorizerEventStream *eventStream) throw(IOException);


//ORIGINAL LINE: public static DoccatModel train(String languageCode, opennlp.tools.util.ObjectStream<DocumentSample> samples, opennlp.tools.util.TrainingParameters mlParams, FeatureGenerator... featureGenerators) throws java.io.IOException
//JAVA TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
               static DoccatModel *train(const std::string &languageCode, ObjectStream<DocumentSample*> *samples, TrainingParameters *mlParams, ...) throw(IOException);

              /// <summary>
              /// Trains a document categorizer model with custom feature generation.
              /// </summary>
              /// <param name="languageCode"> </param>
              /// <param name="samples"> </param>
              /// <param name="cutoff"> </param>
              /// <param name="iterations"> </param>
              /// <param name="featureGenerators">
              /// </param>
              /// <returns> the trained doccat model
              /// </returns>
              /// <exception cref="IOException"> </exception>
//ORIGINAL LINE: public static DoccatModel train(String languageCode, opennlp.tools.util.ObjectStream<DocumentSample> samples, int cutoff, int iterations, FeatureGenerator... featureGenerators) throws java.io.IOException
//JAVA TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
              static DoccatModel *train(const std::string &languageCode, ObjectStream<DocumentSample*> *samples, int cutoff, int iterations, ...) throw(IOException);

              /// <summary>
              /// Trains a doccat model with default feature generation.
              /// </summary>
              /// <param name="languageCode"> </param>
              /// <param name="samples">
              /// </param>
              /// <returns> the trained doccat model
              /// </returns>
              /// <exception cref="IOException"> </exception>
              /// <exception cref="ObjectStreamException">  </exception>
              static DoccatModel *train(const std::string &languageCode, ObjectStream<DocumentSample*> *samples, int cutoff, int iterations) throw(IOException);

              /// <summary>
              /// Trains a doccat model with default feature generation.
              /// </summary>
              /// <param name="languageCode"> </param>
              /// <param name="samples">
              /// </param>
              /// <returns> the trained doccat model
              /// </returns>
              /// <exception cref="IOException"> </exception>
              /// <exception cref="ObjectStreamException">  </exception>
              static DoccatModel *train(const std::string &languageCode, ObjectStream<DocumentSample*> *samples) throw(IOException);
            };

        }
    }
}


#endif	//#ifndef DOCUMENTCATEGORIZERME
