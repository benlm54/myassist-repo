#ifndef CHUNKERME
#define CHUNKERME

#include "Chunker.h"
#include "../tools/util/BeamSearch.h"
#include "../tools/util/Sequence.h"
#include "../model/MaxentModel.h"
#include "ChunkerContextGenerator.h"
#include "ChunkerModel.h"
#include "../tools/util/SequenceValidator.h"
#include "../tools/util/Span.h"
#include "ChunkSample.h"
#include "../tools/util/ObjectStream.h"
#include "../tools/util/TrainingParameters.h"
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
        namespace chunker
        {


            using opennlp::model::AbstractModel;
            using opennlp::model::EventStream;
            using opennlp::model::MaxentModel;
            using opennlp::model::TrainUtil;
            using opennlp::tools::util::BeamSearch;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::Sequence;
            using opennlp::tools::util::SequenceValidator;
            using opennlp::tools::util::Span;
            using opennlp::tools::util::TrainingParameters;
            using opennlp::tools::util::model::ModelUtil;

            /// <summary>
            /// The class represents a maximum-entropy-based chunker.  Such a chunker can be used to
            /// find flat structures based on sequence inputs such as noun phrases or named entities.
            /// </summary>
            class ChunkerME : public Chunker
            {

          public:
              static const int DEFAULT_BEAM_SIZE = 10;

              /// <summary>
              /// The beam used to search for sequences of chunk tag assignments.
              /// </summary>
          protected:
              BeamSearch<std::string> *beam;

          private:
              Sequence *bestSequence;

              /// <summary>
              /// The model used to assign chunk tags to a sequence of tokens.
              /// </summary>
          protected:
              MaxentModel *model;

              /// <summary>
              /// Initializes the current instance with the specified model and
              /// the specified beam size.
              /// </summary>
              /// <param name="model"> The model for this chunker. </param>
              /// <param name="beamSize"> The size of the beam that should be used when decoding sequences. </param>
              /// <param name="sequenceValidator">  The <seealso cref="SequenceValidator"/> to determines whether the outcome 
              ///        is valid for the preceding sequence. This can be used to implement constraints 
              ///        on what sequences are valid. </param>
          public:
              ChunkerME(ChunkerModel *model, int beamSize, SequenceValidator<std::string> *sequenceValidator, ChunkerContextGenerator *contextGenerator);

              /// <summary>
              /// Initializes the current instance with the specified model and
              /// the specified beam size.
              /// </summary>
              /// <param name="model"> The model for this chunker. </param>
              /// <param name="beamSize"> The size of the beam that should be used when decoding sequences. </param>
              /// <param name="sequenceValidator">  The <seealso cref="SequenceValidator"/> to determines whether the outcome 
              ///        is valid for the preceding sequence. This can be used to implement constraints 
              ///        on what sequences are valid. </param>
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              ChunkerME(ChunkerModel *model, int beamSize, SequenceValidator<std::string> *sequenceValidator); //this(model, beamSize, sequenceValidator, new DefaultChunkerContextGenerator());

              /// <summary>
              /// Initializes the current instance with the specified model and
              /// the specified beam size.
              /// </summary>
              /// <param name="model"> The model for this chunker. </param>
              /// <param name="beamSize"> The size of the beam that should be used when decoding sequences. </param>
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              ChunkerME(ChunkerModel *model, int beamSize); //this(model, beamSize, nullptr);

              /// <summary>
              /// Initializes the current instance with the specified model.
              /// The default beam size is used.
              /// </summary>
              /// <param name="model"> </param>
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              ChunkerME(ChunkerModel *model); //this(model, DEFAULT_BEAM_SIZE);

              /// <summary>
              /// Creates a chunker using the specified model.
              /// </summary>
              /// <param name="mod"> The maximum entropy model for this chunker. </param>
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated public ChunkerME(opennlp.model.MaxentModel mod)
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              ChunkerME(MaxentModel *mod); //this(mod, new DefaultChunkerContextGenerator(), DEFAULT_BEAM_SIZE);

              /// <summary>
              /// Creates a chunker using the specified model and context generator.
              /// </summary>
              /// <param name="mod"> The maximum entropy model for this chunker. </param>
              /// <param name="cg"> The context generator to be used by the specified model. </param>
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated public ChunkerME(opennlp.model.MaxentModel mod, ChunkerContextGenerator cg)
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              ChunkerME(MaxentModel *mod, ChunkerContextGenerator *cg); //this(mod, cg, DEFAULT_BEAM_SIZE);

              /// <summary>
              /// Creates a chunker using the specified model and context generator and decodes the
              /// model using a beam search of the specified size.
              /// </summary>
              /// <param name="mod"> The maximum entropy model for this chunker. </param>
              /// <param name="cg"> The context generator to be used by the specified model. </param>
              /// <param name="beamSize"> The size of the beam that should be used when decoding sequences. </param>
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated public ChunkerME(opennlp.model.MaxentModel mod, ChunkerContextGenerator cg, int beamSize)
              ChunkerME(MaxentModel *mod, ChunkerContextGenerator *cg, int beamSize);

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated public java.util.List<String> chunk(java.util.List<String> toks, java.util.List<String> tags)
              virtual std::vector<std::string> chunk(std::vector<std::string> &toks, std::vector<std::string> &tags);

              virtual std::string *chunk(std::string toks[], std::string tags[]);

              virtual Span *chunkAsSpans(std::string toks[], std::string tags[]);

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated public opennlp.tools.util.Sequence[] topKSequences(java.util.List<String> sentence, java.util.List<String> tags)
              virtual Sequence *topKSequences(std::vector<std::string> &sentence, std::vector<std::string> &tags);

              virtual Sequence *topKSequences(std::string sentence[], std::string tags[]);

              virtual Sequence *topKSequences(std::string sentence[], std::string tags[], double minSequenceScore);

              /// <summary>
              /// Populates the specified array with the probabilities of the last decoded sequence.  The
              /// sequence was determined based on the previous call to <code>chunk</code>.  The
              /// specified array should be at least as large as the numbe of tokens in the previous call to <code>chunk</code>.
              /// </summary>
              /// <param name="probs"> An array used to hold the probabilities of the last decoded sequence. </param>
              virtual void probs(double probs[]);

                /// <summary>
                /// Returns an array with the probabilities of the last decoded sequence.  The
                /// sequence was determined based on the previous call to <code>chunk</code>. </summary>
                /// <returns> An array with the same number of probabilities as tokens were sent to <code>chunk</code>
                /// when it was last called. </returns>
              virtual double *probs();

              static ChunkerModel *train(const std::string &lang, ObjectStream<ChunkSample*> *in_Renamed, ChunkerContextGenerator *contextGenerator, TrainingParameters *mlParams) throw(IOException);

              /// @deprecated use <seealso cref="#train(String, ObjectStream, ChunkerContextGenerator, TrainingParameters)"/>
              /// instead and pass in a TrainingParameters object. 
              static ChunkerModel *train(const std::string &lang, ObjectStream<ChunkSample*> *in_Renamed, int cutoff, int iterations, ChunkerContextGenerator *contextGenerator) throw(IOException);

              /// <summary>
              /// Trains a new model for the <seealso cref="ChunkerME"/>.
              /// </summary>
              /// <param name="in"> </param>
              /// <param name="cutoff"> </param>
              /// <param name="iterations">
              /// </param>
              /// <returns> the new model
              /// </returns>
              /// <exception cref="IOException">
              /// </exception>
              /// @deprecated use <seealso cref="#train(String, ObjectStream, ChunkerContextGenerator, TrainingParameters)"/>
              /// instead and pass in a TrainingParameters object. 
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated("use <seealso cref="#train(String, opennlp.tools.util.ObjectStream, ChunkerContextGenerator, opennlp.tools.util.TrainingParameters)"/>") public static ChunkerModel train(String lang, opennlp.tools.util.ObjectStream<ChunkSample> in, int cutoff, int iterations) throws java.io.IOException, java.io.ObjectStreamException
              static ChunkerModel *train(const std::string &lang, ObjectStream<ChunkSample*> *in_Renamed, int cutoff, int iterations) throw(IOException, ObjectStreamException);
            };

        }
    }
}


#endif	//#ifndef CHUNKERME
