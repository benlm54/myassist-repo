#ifndef POSTAGGERME
#define POSTAGGERME

#include "POSTagger.h"
#include "../tools/util/SequenceValidator.h"
#include "POSDictionary.h"
#include "../model/AbstractModel.h"
#include "POSContextGenerator.h"
#include "TagDictionary.h"
#include "../tools/dictionary/Dictionary.h"
#include "../tools/util/Sequence.h"
#include "../tools/util/BeamSearch.h"
#include "POSModel.h"
#include "POSSample.h"
#include "../tools/util/ObjectStream.h"
#include "../tools/util/TrainingParameters.h"
#include "../tools/util/model/ModelType.h"
#include "SequenceValidator<String>.h"
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
        namespace postag
        {


            using opennlp::model::AbstractModel;
            using opennlp::model::EventStream;
            using opennlp::model::TrainUtil;
            using opennlp::tools::chunker::ChunkerContextGenerator;
            using opennlp::tools::dictionary::Dictionary;
            using opennlp::tools::ngram::NGramModel;
            using opennlp::tools::util::BeamSearch;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::Sequence;
            using opennlp::tools::util::SequenceValidator;
            using opennlp::tools::util::StringList;
            using opennlp::tools::util::TrainingParameters;
            using opennlp::tools::util::model::ModelType;

            /// <summary>
            /// A part-of-speech tagger that uses maximum entropy.  Tries to predict whether
            /// words are nouns, verbs, or any of 70 other POS tags depending on their
            /// surrounding context.
            /// 
            /// </summary>
            class POSTaggerME : public POSTagger
            {

          private:
              class PosSequenceValidator : public SequenceValidator<std::string>
              {

            private:
                POSDictionary *tagDictionary;

            public:
                PosSequenceValidator(POSDictionary *tagDictionary);

                virtual bool validSequence(int i, std::string inputSequence[], std::string outcomesSequence[], const std::string &outcome);
              };

              /// <summary>
              /// The maximum entropy model to use to evaluate contexts.
              /// </summary>
          protected:
              AbstractModel *posModel;

              /// <summary>
              /// The feature context generator.
              /// </summary>
              POSContextGenerator *contextGen;

              /// <summary>
              /// Tag dictionary used for restricting words to a fixed set of tags.
              /// </summary>
              TagDictionary *tagDictionary;

              Dictionary *ngramDictionary;

              /// <summary>
              /// Says whether a filter should be used to check whether a tag assignment
              /// is to a word outside of a closed class.
              /// </summary>
              bool useClosedClassTagsFilter;

          public:
              static const int DEFAULT_BEAM_SIZE = 3;

              /// <summary>
              /// The size of the beam to be used in determining the best sequence of pos tags.
              /// </summary>
          protected:
              int size;

          private:
              Sequence *bestSequence;

              /// <summary>
              /// The search object used for search multiple sequences of tags.
              /// </summary>
          protected:
              BeamSearch<std::string> *beam;

          public:
              POSTaggerME(POSModel *model, int beamSize, int cacheSize, SequenceValidator<std::string> *sequenceValidator);

              /// <summary>
              /// Initializes the current instance with the provided
              /// model and provided beam size.
              /// </summary>
              /// <param name="model"> </param>
              /// <param name="beamSize"> </param>
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              POSTaggerME(POSModel *model, int beamSize, int cacheSize); //this(model, beamSize, cacheSize, new PosSequenceValidator(model.getTagDictionary()));

              /// <summary>
              /// Initializes the current instance with the provided model
              /// and the default beam size of 3.
              /// </summary>
              /// <param name="model"> </param>
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              POSTaggerME(POSModel *model); //this(model, DEFAULT_BEAM_SIZE, 0);

              /// <summary>
              /// Creates a new tagger with the specified model and tag dictionary.
              /// </summary>
              /// <param name="model"> The model used for tagging. </param>
              /// <param name="tagdict"> The tag dictionary used for specifying a set of valid tags. </param>
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated public POSTaggerME(opennlp.model.AbstractModel model, TagDictionary tagdict)
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              POSTaggerME(AbstractModel *model, TagDictionary *tagdict); //this(model, new DefaultPOSContextGenerator(nullptr),tagdict);

              /// <summary>
              /// Creates a new tagger with the specified model and n-gram dictionary.
              /// </summary>
              /// <param name="model"> The model used for tagging. </param>
              /// <param name="dict"> The n-gram dictionary used for feature generation. </param>
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated public POSTaggerME(opennlp.model.AbstractModel model, opennlp.tools.dictionary.Dictionary dict)
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              POSTaggerME(AbstractModel *model, Dictionary *dict); //this(model, new DefaultPOSContextGenerator(dict));

              /// <summary>
              /// Creates a new tagger with the specified model, n-gram dictionary, and tag dictionary.
              /// </summary>
              /// <param name="model"> The model used for tagging. </param>
              /// <param name="dict"> The n-gram dictionary used for feature generation. </param>
              /// <param name="tagdict"> The dictionary which specifies the valid set of tags for some words. </param>
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated public POSTaggerME(opennlp.model.AbstractModel model, opennlp.tools.dictionary.Dictionary dict, TagDictionary tagdict)
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              POSTaggerME(AbstractModel *model, Dictionary *dict, TagDictionary *tagdict); //this(DEFAULT_BEAM_SIZE,model, new DefaultPOSContextGenerator(dict),tagdict);

              /// <summary>
              /// Creates a new tagger with the specified model and context generator.
              /// </summary>
              /// <param name="model"> The model used for tagging. </param>
              /// <param name="cg"> The context generator used for feature creation. </param>
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated public POSTaggerME(opennlp.model.AbstractModel model, POSContextGenerator cg)
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              POSTaggerME(AbstractModel *model, POSContextGenerator *cg); //this(DEFAULT_BEAM_SIZE, model, cg, nullptr);

              /// <summary>
              /// Creates a new tagger with the specified model, context generator, and tag dictionary.
              /// </summary>
              /// <param name="model"> The model used for tagging. </param>
              /// <param name="cg"> The context generator used for feature creation. </param>
              /// <param name="tagdict"> The dictionary which specifies the valid set of tags for some words. </param>
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated public POSTaggerME(opennlp.model.AbstractModel model, POSContextGenerator cg, TagDictionary tagdict)
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              POSTaggerME(AbstractModel *model, POSContextGenerator *cg, TagDictionary *tagdict); //this(DEFAULT_BEAM_SIZE, model, cg, tagdict);

              /// <summary>
              /// Creates a new tagger with the specified beam size, model, context generator, and tag dictionary.
              /// </summary>
              /// <param name="beamSize"> The number of alternate tagging considered when tagging. </param>
              /// <param name="model"> The model used for tagging. </param>
              /// <param name="cg"> The context generator used for feature creation. </param>
              /// <param name="tagdict"> The dictionary which specifies the valid set of tags for some words. </param>
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated public POSTaggerME(int beamSize, opennlp.model.AbstractModel model, POSContextGenerator cg, TagDictionary tagdict)
              POSTaggerME(int beamSize, AbstractModel *model, POSContextGenerator *cg, TagDictionary *tagdict);

              /// <summary>
              /// Returns the number of different tags predicted by this model.
              /// </summary>
              /// <returns> the number of different tags predicted by this model. </returns>
              virtual int getNumTags();

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated public java.util.List<String> tag(java.util.List<String> sentence)
              virtual std::vector<std::string> tag(std::vector<std::string> &sentence);

              virtual std::string *tag(std::string sentence[]);

              /// <summary>
              /// Returns at most the specified number of taggings for the specified sentence.
              /// </summary>
              /// <param name="numTaggings"> The number of tagging to be returned. </param>
              /// <param name="sentence"> An array of tokens which make up a sentence.
              /// </param>
              /// <returns> At most the specified number of taggings for the specified sentence. </returns>
              virtual std::string **tag(int numTaggings, std::string sentence[]);

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated public opennlp.tools.util.Sequence[] topKSequences(java.util.List<String> sentence)
              virtual Sequence *topKSequences(std::vector<std::string> &sentence);

              virtual Sequence *topKSequences(std::string sentence[]);

              /// <summary>
              /// Populates the specified array with the probabilities for each tag of the last tagged sentence.
              /// </summary>
              /// <param name="probs"> An array to put the probabilities into. </param>
              virtual void probs(double probs[]);

              /// <summary>
              /// Returns an array with the probabilities for each tag of the last tagged sentence.
              /// </summary>
              /// <returns> an array with the probabilities for each tag of the last tagged sentence. </returns>
              virtual double *probs();

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated public String tag(String sentence)
              virtual std::string tag(const std::string &sentence);

              virtual std::string *getOrderedTags(std::vector<std::string> &words, std::vector<std::string> &tags, int index);

              virtual std::string *getOrderedTags(std::vector<std::string> &words, std::vector<std::string> &tags, int index, double tprobs[]);

              static POSModel *train(const std::string &languageCode, ObjectStream<POSSample*> *samples, TrainingParameters *trainParams, POSDictionary *tagDictionary, Dictionary *ngramDictionary) throw(IOException);

              /// @deprecated use <seealso cref="#train(String, ObjectStream, TrainingParameters, POSDictionary, Dictionary)"/>
              /// instead and pass in a TrainingParameters object. 
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated("use <seealso cref="#train(String, opennlp.tools.util.ObjectStream, opennlp.tools.util.TrainingParameters, POSDictionary, opennlp.tools.dictionary.Dictionary)"/>") public static POSModel train(String languageCode, opennlp.tools.util.ObjectStream<POSSample> samples, opennlp.tools.util.model.ModelType modelType, POSDictionary tagDictionary, opennlp.tools.dictionary.Dictionary ngramDictionary, int cutoff, int iterations) throws java.io.IOException
              static POSModel *train(const std::string &languageCode, ObjectStream<POSSample*> *samples, ModelType modelType, POSDictionary *tagDictionary, Dictionary *ngramDictionary, int cutoff, int iterations) throw(IOException);

              static Dictionary *buildNGramDictionary(ObjectStream<POSSample*> *samples, int cutoff) throw(IOException);

            private:
                void InitializeInstanceFields();
            };

        }
    }
}


#endif	//#ifndef POSTAGGERME
