#ifndef TOKENIZERME
#define TOKENIZERME

#include "AbstractTokenizer.h"
#include "../model/MaxentModel.h"
#include "TokenContextGenerator.h"
#include "../tools/util/Span.h"
#include "TokenizerModel.h"
#include "lang/Factory.h"
#include "../tools/dictionary/Dictionary.h"
#include "TokenSample.h"
#include "../tools/util/ObjectStream.h"
#include "../tools/util/TrainingParameters.h"
#include <string>
#include <map>
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
        namespace tokenize
        {


            using opennlp::model::AbstractModel;
            using opennlp::model::EventStream;
            using opennlp::model::MaxentModel;
            using opennlp::model::TrainUtil;
            using opennlp::tools::dictionary::Dictionary;
            using opennlp::tools::tokenize::lang::Factory;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::Span;
            using opennlp::tools::util::TrainingParameters;
            using opennlp::tools::util::model::ModelUtil;

            /// <summary>
            /// A Tokenizer for converting raw text into separated tokens.  It uses
            /// Maximum Entropy to make its decisions.  The features are loosely
            /// based off of Jeff Reynar's UPenn thesis "Topic Segmentation:
            /// Algorithms and Applications.", which is available from his
            /// homepage: <http://www.cis.upenn.edu/~jcreynar>.
            /// <p>
            /// This tokenizer needs a statistical model to tokenize a text which reproduces
            /// the tokenization observed in the training data used to create the model.
            /// The <seealso cref="TokenizerModel"/> class encapsulates the model and provides
            /// methods to create it from the binary representation. 
            /// <p>
            /// A tokenizer instance is not thread safe. For each thread one tokenizer
            /// must be instantiated which can share one <code>TokenizerModel</code> instance
            /// to safe memory.
            /// <p>
            /// To train a new model {<seealso cref="#train(String, ObjectStream, boolean, TrainingParameters)"/> method
            /// can be used.
            /// <p>
            /// Sample usage:
            /// <p>
            /// <code>
            /// InputStream modelIn;<br>
            /// <br>
            /// ...<br>
            /// <br>
            /// TokenizerModel model = TokenizerModel(modelIn);<br>
            /// <br>
            /// Tokenizer tokenizer = new TokenizerME(model);<br>
            /// <br>
            /// String tokens[] = tokenizer.tokenize("A sentence to be tokenized.");
            /// </code>
            /// </summary>
            /// <seealso cref= Tokenizer </seealso>
            /// <seealso cref= TokenizerModel </seealso>
            /// <seealso cref= TokenSample </seealso>
            class TokenizerME : public AbstractTokenizer
            {

              /// <summary>
              /// Constant indicates a token split.
              /// </summary>
          public:
              static const std::string SPLIT;

              /// <summary>
              /// Constant indicates no token split.
              /// </summary>
              static const std::string NO_SPLIT;

              /// <summary>
              /// Alpha-Numeric Pattern </summary>
              /// @deprecated As of release 1.5.2, replaced by <seealso cref="Factory#getAlphanumericPattern(String)"/>  
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated("As of release 1.5.2, replaced by <seealso cref="Factory#getAlphanumericPattern(String)"/>") public static final java.util.regex.Pattern alphaNumeric = java.util.regex.Pattern.compile(opennlp.tools.tokenize.lang.Factory.DEFAULT_ALPHANUMERIC);
              static Pattern *const alphaNumeric;

          private:
              Pattern *const alphanumeric;

              /// <summary>
              /// The maximum entropy model to use to evaluate contexts.
              /// </summary>
              MaxentModel *model;

              /// <summary>
              /// The context generator.
              /// </summary>
              TokenContextGenerator *const cg;

              /// <summary>
              /// Optimization flag to skip alpha numeric tokens for further
              /// tokenization
              /// </summary>
//JAVA TO C++ CONVERTER NOTE: The variable useAlphaNumericOptimization was renamed since C++ does not allow variables with the same name as methods:
              bool useAlphaNumericOptimization_Renamed;

              /// <summary>
              /// List of probabilities for each token returned from a call to
              /// <code>tokenize</code> or <code>tokenizePos</code>.
              /// </summary>
              std::vector<double> tokProbs;

              std::vector<Span*> newTokens;

          public:
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              TokenizerME(TokenizerModel *model); //this(model, new Factory());

              TokenizerME(TokenizerModel *model, Factory *factory);

          private:
              static Set<std::string> *getAbbreviations(Dictionary *abbreviations);

              /// <summary>
              /// Returns the probabilities associated with the most recent
              /// calls to <seealso cref="TokenizerME#tokenize(String)"/> or <seealso cref="TokenizerME#tokenizePos(String)"/>.
              /// </summary>
              /// <returns> probability for each token returned for the most recent
              /// call to tokenize.  If not applicable an empty array is
              /// returned. </returns>
          public:
              virtual double *getTokenProbabilities();

              /// <summary>
              /// Tokenizes the string.
              /// </summary>
              /// <param name="d">  The string to be tokenized.
              /// </param>
              /// <returns>   A span array containing individual tokens as elements. </returns>
              virtual Span *tokenizePos(const std::string &d);

              /// <summary>
              /// Trains a model for the <seealso cref="TokenizerME"/>.
              /// </summary>
              /// <param name="languageCode"> the language of the natural text </param>
              /// <param name="samples"> the samples used for the training. </param>
              /// <param name="useAlphaNumericOptimization"> - if true alpha numerics are skipped </param>
              /// <param name="mlParams"> the machine learning train parameters
              /// </param>
              /// <returns> the trained <seealso cref="TokenizerModel"/>
              /// </returns>
              /// <exception cref="IOException"> it throws an <seealso cref="IOException"/> if an <seealso cref="IOException"/>
              /// is thrown during IO operations on a temp file which is created during training.
              /// Or if reading from the <seealso cref="ObjectStream"/> fails.
              ///  </exception>
              static TokenizerModel *train(const std::string &languageCode, ObjectStream<TokenSample*> *samples, bool useAlphaNumericOptimization, TrainingParameters *mlParams) throw(IOException);

              /// <summary>
              /// Trains a model for the <seealso cref="TokenizerME"/>.
              /// </summary>
              /// <param name="languageCode"> the language of the natural text </param>
              /// <param name="samples"> the samples used for the training. </param>
              /// <param name="abbreviations"> an abbreviations dictionary </param>
              /// <param name="useAlphaNumericOptimization"> - if true alpha numerics are skipped </param>
              /// <param name="mlParams"> the machine learning train parameters
              /// </param>
              /// <returns> the trained <seealso cref="TokenizerModel"/>
              /// </returns>
              /// <exception cref="IOException"> it throws an <seealso cref="IOException"/> if an <seealso cref="IOException"/>
              /// is thrown during IO operations on a temp file which is created during training.
              /// Or if reading from the <seealso cref="ObjectStream"/> fails.
              ///  </exception>
              static TokenizerModel *train(const std::string &languageCode, ObjectStream<TokenSample*> *samples, Dictionary *abbreviations, bool useAlphaNumericOptimization, TrainingParameters *mlParams) throw(IOException);

              /// <summary>
              /// Trains a model for the <seealso cref="TokenizerME"/>.
              /// </summary>
              /// <param name="languageCode"> the language of the natural text </param>
              /// <param name="samples"> the samples used for the training. </param>
              /// <param name="useAlphaNumericOptimization"> - if true alpha numerics are skipped </param>
              /// <param name="cutoff"> number of times a feature must be seen to be considered </param>
              /// <param name="iterations"> number of iterations to train the maxent model
              /// </param>
              /// <returns> the trained <seealso cref="TokenizerModel"/>
              /// </returns>
              /// <exception cref="IOException"> it throws an <seealso cref="IOException"/> if an <seealso cref="IOException"/>
              /// is thrown during IO operations on a temp file which is created during training.
              /// Or if reading from the <seealso cref="ObjectStream"/> fails.
              /// </exception>
              /// @deprecated use <seealso cref="#train(String, ObjectStream, boolean, TrainingParameters)"/>
              /// instead and pass in a TrainingParameters object. 
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated("use <seealso cref="#train(String, opennlp.tools.util.ObjectStream, boolean, opennlp.tools.util.TrainingParameters)"/>") public static TokenizerModel train(String languageCode, opennlp.tools.util.ObjectStream<TokenSample> samples, boolean useAlphaNumericOptimization, int cutoff, int iterations) throws java.io.IOException
              static TokenizerModel *train(const std::string &languageCode, ObjectStream<TokenSample*> *samples, bool useAlphaNumericOptimization, int cutoff, int iterations) throw(IOException);


              /// <summary>
              /// Trains a model for the <seealso cref="TokenizerME"/> with a default cutoff of 5 and 100 iterations.
              /// </summary>
              /// <param name="languageCode"> the language of the natural text </param>
              /// <param name="samples"> the samples used for the training. </param>
              /// <param name="useAlphaNumericOptimization"> - if true alpha numerics are skipped
              /// </param>
              /// <returns> the trained <seealso cref="TokenizerModel"/>
              /// </returns>
              /// <exception cref="IOException"> it throws an <seealso cref="IOException"/> if an <seealso cref="IOException"/>
              /// is thrown during IO operations on a temp file which is
              /// </exception>
              /// <exception cref="ObjectStreamException"> if reading from the <seealso cref="ObjectStream"/> fails
              /// created during training. </exception>
              static TokenizerModel *train(const std::string &languageCode, ObjectStream<TokenSample*> *samples, bool useAlphaNumericOptimization) throw(IOException, ObjectStreamException);

              /// <summary>
              /// Returns the value of the alpha-numeric optimization flag.
              /// </summary>
              /// <returns> true if the tokenizer should use alpha-numeric optimization, false otherwise. </returns>
              virtual bool useAlphaNumericOptimization();
            };

        }
    }
}


#endif	//#ifndef TOKENIZERME
