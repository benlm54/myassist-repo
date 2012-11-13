#ifndef NAMEFINDERME
#define NAMEFINDERME

#include "TokenNameFinder.h"
#include "../model/MaxentModel.h"
#include "NameContextGenerator.h"
#include "../tools/util/Sequence.h"
#include "../tools/util/BeamSearch.h"
#include "../tools/util/featuregen/AdditionalContextFeatureGenerator.h"
#include "TokenNameFinderModel.h"
#include "../tools/util/SequenceValidator.h"
#include "../tools/util/featuregen/AdaptiveFeatureGenerator.h"
#include "../tools/util/featuregen/FeatureGeneratorResourceProvider.h"
#include "../tools/util/Span.h"
#include "NameSample.h"
#include "../tools/util/ObjectStream.h"
#include "../tools/util/TrainingParameters.h"
#include "../maxent/GISModel.h"
#include "../model/EventStream.h"
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
        namespace namefind
        {


            using opennlp::maxent::GIS;
            using opennlp::maxent::GISModel;
            using opennlp::model::AbstractModel;
            using opennlp::model::EventStream;
            using opennlp::model::MaxentModel;
            using opennlp::model::TrainUtil;
            using opennlp::model::TwoPassDataIndexer;
            using opennlp::tools::util::BeamSearch;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::Sequence;
            using opennlp::tools::util::SequenceValidator;
            using opennlp::tools::util::Span;
            using opennlp::tools::util::TrainingParameters;
            using opennlp::tools::util::featuregen::AdaptiveFeatureGenerator;
            using opennlp::tools::util::featuregen::AdditionalContextFeatureGenerator;
            using opennlp::tools::util::featuregen::BigramNameFeatureGenerator;
            using opennlp::tools::util::featuregen::CachedFeatureGenerator;
            using opennlp::tools::util::featuregen::FeatureGeneratorResourceProvider;
            using opennlp::tools::util::featuregen::GeneratorFactory;
            using opennlp::tools::util::featuregen::OutcomePriorFeatureGenerator;
            using opennlp::tools::util::featuregen::PreviousMapFeatureGenerator;
            using opennlp::tools::util::featuregen::SentenceFeatureGenerator;
            using opennlp::tools::util::featuregen::TokenClassFeatureGenerator;
            using opennlp::tools::util::featuregen::TokenFeatureGenerator;
            using opennlp::tools::util::featuregen::WindowFeatureGenerator;
            using opennlp::tools::util::model::ModelUtil;

            /// <summary>
            /// Class for creating a maximum-entropy-based name finder.
            /// </summary>
            class NameFinderME : public TokenNameFinder
            {

          private:
//ORIGINAL LINE: private static String[][] EMPTY = new String[0][0];
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              static std::string **EMPTY;
          public:
              static const int DEFAULT_BEAM_SIZE = 3;
          private:
              static Pattern *const typedOutcomePattern;



          public:
              static const std::string START;
              static const std::string CONTINUE;
              static const std::string OTHER;

          protected:
              MaxentModel *model;
              NameContextGenerator *contextGenerator;
          private:
              Sequence *bestSequence;
              BeamSearch<std::string> *beam;

              AdditionalContextFeatureGenerator *additionalContextFeatureGenerator;

          public:
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              NameFinderME(TokenNameFinderModel *model); //this(model, DEFAULT_BEAM_SIZE);

              /// <summary>
              /// Initializes the name finder with the specified model.
              /// </summary>
              /// <param name="model"> </param>
              /// <param name="beamSize"> </param>
              NameFinderME(TokenNameFinderModel *model, AdaptiveFeatureGenerator *generator, int beamSize, SequenceValidator<std::string> *sequenceValidator);

//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              NameFinderME(TokenNameFinderModel *model, AdaptiveFeatureGenerator *generator, int beamSize); //this(model, generator, beamSize, nullptr);

//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              NameFinderME(TokenNameFinderModel *model, int beamSize); //this(model, nullptr, beamSize);


              /// <summary>
              /// Creates a new name finder with the specified model.
              /// </summary>
              /// <param name="mod"> The model to be used to find names.
              /// </param>
              /// @deprecated Use the new model API!  
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated("Use the new model API!") public NameFinderME(opennlp.model.MaxentModel mod)
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              NameFinderME(MaxentModel *mod); //this(mod, new DefaultNameContextGenerator(), DEFAULT_BEAM_SIZE);

              /// <summary>
              /// Creates a new name finder with the specified model and context generator.
              /// </summary>
              /// <param name="mod"> The model to be used to find names. </param>
              /// <param name="cg"> The context generator to be used with this name finder. </param>
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated public NameFinderME(opennlp.model.MaxentModel mod, NameContextGenerator cg)
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              NameFinderME(MaxentModel *mod, NameContextGenerator *cg); //this(mod, cg, DEFAULT_BEAM_SIZE);

              /// <summary>
              /// Creates a new name finder with the specified model and context generator.
              /// </summary>
              /// <param name="mod"> The model to be used to find names. </param>
              /// <param name="cg"> The context generator to be used with this name finder. </param>
              /// <param name="beamSize"> The size of the beam to be used in decoding this model. </param>
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated public NameFinderME(opennlp.model.MaxentModel mod, NameContextGenerator cg, int beamSize)
              NameFinderME(MaxentModel *mod, NameContextGenerator *cg, int beamSize);

          private:
              static AdaptiveFeatureGenerator *createFeatureGenerator();

              static AdaptiveFeatureGenerator *createFeatureGenerator(char generatorDescriptor[], Map<std::string, void*> *const resources) throw(IOException);

                    private:
                        class FeatureGeneratorResourceProviderAnonymousInnerClassHelper : public FeatureGeneratorResourceProvider
                        {

                        public:
                            virtual void *getResource(const std::string &key);
                        };

          public:
              virtual Span *find(std::string tokens[]);

              /// <summary>
              /// Generates name tags for the given sequence, typically a sentence, 
              /// returning token spans for any identified names.
              /// </summary>
              /// <param name="tokens"> an array of the tokens or words of the sequence,
              ///     typically a sentence. </param>
              /// <param name="additionalContext"> features which are based on context outside
              ///     of the sentence but which should also be used.
              /// </param>
              /// <returns> an array of spans for each of the names identified. </returns>
              virtual Span *find(std::string tokens[], std::string additionalContext[][]);

              /// <summary>
              /// Forgets all adaptive data which was collected during previous
              /// calls to one of the find methods.
              /// 
              /// This method is typical called at the end of a document.
              /// </summary>
              virtual void clearAdaptiveData();

              /// <summary>
              /// Populates the specified array with the probabilities of the last decoded
              /// sequence. The sequence was determined based on the previous call to
              /// <code>chunk</code>. The specified array should be at least as large as
              /// the number of tokens in the previous call to <code>chunk</code>.
              /// </summary>
              /// <param name="probs">
              ///          An array used to hold the probabilities of the last decoded
              ///          sequence. </param>
               virtual void probs(double probs[]);

              /// <summary>
              /// Returns an array with the probabilities of the last decoded sequence.  The
              /// sequence was determined based on the previous call to <code>chunk</code>.
              /// </summary>
              /// <returns> An array with the same number of probabilities as tokens were sent to <code>chunk</code>
              /// when it was last called. </returns>
               virtual double *probs();

               /// <summary>
               /// Returns an array of probabilities for each of the specified spans which is the arithmetic mean 
               /// of the probabilities for each of the outcomes which make up the span.
               /// </summary>
               /// <param name="spans"> The spans of the names for which probabilities are desired.
               /// </param>
               /// <returns> an array of probabilities for each of the specified spans. </returns>
               virtual double *probs(Span spans[]);

               /// <summary>
               /// Trains a name finder model.
               /// </summary>
               /// <param name="languageCode">
               ///          the language of the training data </param>
               /// <param name="type">
               ///          null or an override type for all types in the training data </param>
               /// <param name="samples">
               ///          the training data </param>
               /// <param name="trainParams">
               ///          machine learning train parameters </param>
               /// <param name="generator">
               ///          null or the feature generator </param>
               /// <param name="resources">
               ///          the resources for the name finder or null if none
               /// </param>
               /// <returns> the newly trained model
               /// </returns>
               /// <exception cref="IOException"> </exception>
               static TokenNameFinderModel *train(const std::string &languageCode, const std::string &type, ObjectStream<NameSample*> *samples, TrainingParameters *trainParams, AdaptiveFeatureGenerator *generator, Map<std::string, void*> *const resources) throw(IOException);

              /// <summary>
              /// Trains a name finder model.
              /// </summary>
              /// <param name="languageCode">
              ///          the language of the training data </param>
              /// <param name="type">
              ///          null or an override type for all types in the training data </param>
              /// <param name="samples">
              ///          the training data </param>
              /// <param name="trainParams">
              ///          machine learning train parameters </param>
              /// <param name="featureGeneratorBytes">
              ///          descriptor to configure the feature generation or null </param>
              /// <param name="resources">
              ///          the resources for the name finder or null if none
              /// </param>
              /// <returns> the newly trained model
              /// </returns>
              /// <exception cref="IOException"> </exception>
              static TokenNameFinderModel *train(const std::string &languageCode, const std::string &type, ObjectStream<NameSample*> *samples, TrainingParameters *trainParams, char featureGeneratorBytes[], Map<std::string, void*> *const resources) throw(IOException);

               /// <summary>
               /// Trains a name finder model.
               /// </summary>
               /// <param name="languageCode"> the language of the training data </param>
               /// <param name="type"> null or an override type for all types in the training data </param>
               /// <param name="samples"> the training data </param>
               /// <param name="iterations"> the number of iterations </param>
               /// <param name="cutoff"> </param>
               /// <param name="resources"> the resources for the name finder or null if none
               /// </param>
               /// <returns> the newly trained model
               /// </returns>
               /// <exception cref="IOException"> </exception>
               /// <exception cref="ObjectStreamException"> </exception>
               static TokenNameFinderModel *train(const std::string &languageCode, const std::string &type, ObjectStream<NameSample*> *samples, AdaptiveFeatureGenerator *generator, Map<std::string, void*> *const resources, int iterations, int cutoff) throw(IOException);

               /// @deprecated use <seealso cref="#train(String, String, ObjectStream, TrainingParameters, AdaptiveFeatureGenerator, Map)"/>
               /// instead and pass in a TrainingParameters object. 
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated("use <seealso cref="#train(String, String, opennlp.tools.util.ObjectStream, opennlp.tools.util.TrainingParameters, opennlp.tools.util.featuregen.AdaptiveFeatureGenerator, java.util.Map)"/>") public static TokenNameFinderModel train(String languageCode, String type, opennlp.tools.util.ObjectStream<NameSample> samples, final java.util.Map<String, Object> resources, int iterations, int cutoff) throws java.io.IOException
              static TokenNameFinderModel *train(const std::string &languageCode, const std::string &type, ObjectStream<NameSample*> *samples, Map<std::string, void*> *const resources, int iterations, int cutoff) throw(IOException);

               static TokenNameFinderModel *train(const std::string &languageCode, const std::string &type, ObjectStream<NameSample*> *samples, Map<std::string, void*> *const resources) throw(IOException);

               /// @deprecated use <seealso cref="#train(String, String, ObjectStream, TrainingParameters, byte[], Map)"/>
               /// instead and pass in a TrainingParameters object. 
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated("use <seealso cref="#train(String, String, opennlp.tools.util.ObjectStream, opennlp.tools.util.TrainingParameters, byte[] , java.util.Map)"/>") public static TokenNameFinderModel train(String languageCode, String type, opennlp.tools.util.ObjectStream<NameSample> samples, byte[] generatorDescriptor, final java.util.Map<String, Object> resources, int iterations, int cutoff) throws java.io.IOException
              static TokenNameFinderModel *train(const std::string &languageCode, const std::string &type, ObjectStream<NameSample*> *samples, char generatorDescriptor[], Map<std::string, void*> *const resources, int iterations, int cutoff) throw(IOException);

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated public static opennlp.maxent.GISModel train(opennlp.model.EventStream es, int iterations, int cut) throws java.io.IOException
              static GISModel *train(EventStream *es, int iterations, int cut) throw(IOException);

              /// <summary>
              /// Gets the name type from the outcome </summary>
              /// <param name="outcome"> the outcome </param>
              /// <returns> the name type, or null if not set </returns>
              static std::string extractNameType(const std::string &outcome);

              /// <summary>
              /// Removes spans with are intersecting or crossing in anyway.
              /// 
              /// <p>
              /// The following rules are used to remove the spans:<br>
              /// Identical spans: The first span in the array after sorting it remains<br>
              /// Intersecting spans: The first span after sorting remains<br>
              /// Contained spans: All spans which are contained by another are removed<br>
              /// </summary>
              /// <param name="spans">
              /// </param>
              /// <returns> non-overlapping spans </returns>
              static Span *dropOverlappingSpans(Span spans[]);

            private:
                void InitializeInstanceFields();
            };

        }
    }
}


#endif	//#ifndef NAMEFINDERME
