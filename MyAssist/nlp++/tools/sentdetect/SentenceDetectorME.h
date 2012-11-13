#ifndef SENTENCEDETECTORME
#define SENTENCEDETECTORME

#include "SentenceDetector.h"
#include "../model/MaxentModel.h"
#include "SDContextGenerator.h"
#include "EndOfSentenceScanner.h"
#include "SentenceModel.h"
#include "lang/Factory.h"
#include "../tools/dictionary/Dictionary.h"
#include "../tools/util/Span.h"
#include "SentenceSample.h"
#include "../tools/util/ObjectStream.h"
#include "../tools/util/TrainingParameters.h"
#include "StringBuffer.h"
#include <string>
#include <map>
#include <vector>

/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
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
        namespace sentdetect
        {


            using opennlp::model::AbstractModel;
            using opennlp::model::EventStream;
            using opennlp::model::MaxentModel;
            using opennlp::model::TrainUtil;
            using opennlp::tools::dictionary::Dictionary;
            using opennlp::tools::sentdetect::lang::Factory;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::Span;
            using opennlp::tools::util::StringUtil;
            using opennlp::tools::util::TrainingParameters;
            using opennlp::tools::util::model::ModelUtil;

            /// <summary>
            /// A sentence detector for splitting up raw text into sentences.
            /// <p>
            /// A maximum entropy model is used to evaluate the characters ".", "!", and "?" in a
            /// string to determine if they signify the end of a sentence.
            /// </summary>
            class SentenceDetectorME : public SentenceDetector
            {

              /// <summary>
              /// Constant indicates a sentence split.
              /// </summary>
          public:
              static const std::string SPLIT;

              /// <summary>
              /// Constant indicates no sentence split.
              /// </summary>
              static const std::string NO_SPLIT;

          private:
              static const double ONE;

              /// <summary>
              /// The maximum entropy model to use to evaluate contexts.
              /// </summary>
              MaxentModel *model;

              /// <summary>
              /// The feature context generator.
              /// </summary>
              SDContextGenerator *const cgen;

              /// <summary>
              /// The <seealso cref="EndOfSentenceScanner"/> to use when scanning for end of sentence offsets.
              /// </summary>
              EndOfSentenceScanner *const scanner;

              /// <summary>
              /// The list of probabilities associated with each decision.
              /// </summary>
              std::vector<double> sentProbs;

          protected:
              bool useTokenEnd;

              /// <summary>
              /// Initializes the current instance.
              /// </summary>
              /// <param name="model"> the <seealso cref="SentenceModel"/> </param>
          public:
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              SentenceDetectorME(SentenceModel *model); //this(model, new Factory());

              SentenceDetectorME(SentenceModel *model, Factory *factory);

          private:
              static Set<std::string> *getAbbreviations(Dictionary *abbreviations);

              /// <summary>
              /// Detect sentences in a String.
              /// </summary>
              /// <param name="s">  The string to be processed.
              /// </param>
              /// <returns>   A string array containing individual sentences as elements. </returns>
          public:
              virtual std::string *sentDetect(const std::string &s);

          private:
              int getFirstWS(const std::string &s, int pos);

              int getFirstNonWS(const std::string &s, int pos);

              /// <summary>
              /// Detect the position of the first words of sentences in a String.
              /// </summary>
              /// <param name="s">  The string to be processed. </param>
              /// <returns>   A integer array containing the positions of the end index of
              ///          every sentence
              ///  </returns>
          public:
              virtual Span *sentPosDetect(const std::string &s);

              /// <summary>
              /// Returns the probabilities associated with the most recent
              /// calls to sentDetect().
              /// </summary>
              /// <returns> probability for each sentence returned for the most recent
              /// call to sentDetect.  If not applicable an empty array is
              /// returned. </returns>
              virtual double *getSentenceProbabilities();

              /// <summary>
              /// Allows subclasses to check an overzealous (read: poorly
              /// trained) model from flagging obvious non-breaks as breaks based
              /// on some boolean determination of a break's acceptability.
              /// 
              /// <p>The implementation here always returns true, which means
              /// that the MaxentModel's outcome is taken as is.</p>
              /// </summary>
              /// <param name="s"> the string in which the break occurred. </param>
              /// <param name="fromIndex"> the start of the segment currently being evaluated </param>
              /// <param name="candidateIndex"> the index of the candidate sentence ending </param>
              /// <returns> true if the break is acceptable </returns>
          protected:
              virtual bool isAcceptableBreak(const std::string &s, int fromIndex, int candidateIndex);


          public:
              static SentenceModel *train(const std::string &languageCode, ObjectStream<SentenceSample*> *samples, bool useTokenEnd, Dictionary *abbreviations, TrainingParameters *mlParams) throw(IOException);

              /// @deprecated use <seealso cref="#train(String, ObjectStream, boolean, Dictionary, TrainingParameters)"/>
              /// instead and pass in a TrainingParameters object. 
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated("use <seealso cref="#train(String, opennlp.tools.util.ObjectStream, boolean, opennlp.tools.dictionary.Dictionary, opennlp.tools.util.TrainingParameters)"/>") public static SentenceModel train(String languageCode, opennlp.tools.util.ObjectStream<SentenceSample> samples, boolean useTokenEnd, opennlp.tools.dictionary.Dictionary abbreviations, int cutoff, int iterations) throws java.io.IOException
              static SentenceModel *train(const std::string &languageCode, ObjectStream<SentenceSample*> *samples, bool useTokenEnd, Dictionary *abbreviations, int cutoff, int iterations) throw(IOException);

              static SentenceModel *train(const std::string &languageCode, ObjectStream<SentenceSample*> *samples, bool useTokenEnd, Dictionary *abbreviations) throw(IOException);

            private:
                void InitializeInstanceFields();
            };

        }
    }
}


#endif	//#ifndef SENTENCEDETECTORME
