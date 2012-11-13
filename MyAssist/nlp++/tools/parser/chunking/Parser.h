#ifndef PARSER
#define PARSER

#include "../tools/parser/AbstractBottomUpParser.h"
#include "../model/MaxentModel.h"
#include "BuildContextGenerator.h"
#include "../tools/parser/treeinsert/BuildContextGenerator.h"
#include "CheckContextGenerator.h"
#include "../tools/parser/treeinsert/CheckContextGenerator.h"
#include "../tools/parser/ParserModel.h"
#include "../tools/chunker/Chunker.h"
#include "../tools/parser/HeadRules.h"
#include "../tools/postag/POSTagger.h"
#include "../tools/parser/Parse.h"
#include "../model/AbstractModel.h"
#include "../model/EventStream.h"
#include "../tools/util/ObjectStream.h"
#include "../tools/util/TrainingParameters.h"
#include <string>
#include <map>
#include <vector>
#include <cmath>

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
        namespace parser
        {
            namespace chunking
            {


                using opennlp::model::AbstractModel;
                using opennlp::model::MaxentModel;
                using opennlp::model::TrainUtil;
                using opennlp::model::TwoPassDataIndexer;
                using opennlp::tools::chunker::Chunker;
                using opennlp::tools::chunker::ChunkerME;
                using opennlp::tools::chunker::ChunkerModel;
                using opennlp::tools::dictionary::Dictionary;
                using opennlp::tools::namefind::TokenNameFinderEvaluationMonitor;
                using opennlp::tools::parser::AbstractBottomUpParser;
                using opennlp::tools::parser::ChunkContextGenerator;
                using opennlp::tools::parser::ChunkSampleStream;
                using opennlp::tools::parser::HeadRules;
                using opennlp::tools::parser::Parse;
                using opennlp::tools::parser::ParserChunkerSequenceValidator;
                using opennlp::tools::parser::ParserEventTypeEnum;
                using opennlp::tools::parser::ParserModel;
                using opennlp::tools::parser::ParserType;
                using opennlp::tools::parser::PosSampleStream;
                using opennlp::tools::postag::POSModel;
                using opennlp::tools::postag::POSTagger;
                using opennlp::tools::postag::POSTaggerME;
                using opennlp::tools::util::ObjectStream;
                using opennlp::tools::util::Span;
                using opennlp::tools::util::TrainingParameters;

                /// <summary>
                /// Class for a shift reduce style parser based on Adwait Ratnaparkhi's 1998 thesis.
                /// </summary>
                class Parser : public AbstractBottomUpParser
                {

              private:
                  MaxentModel *buildModel;
                  MaxentModel *checkModel;

                  BuildContextGenerator *buildContextGenerator;
                  CheckContextGenerator *checkContextGenerator;

//ORIGINAL LINE: private double[] bprobs;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                  double *bprobs;
//ORIGINAL LINE: private double[] cprobs;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                  double *cprobs;

                  static const std::string TOP_START;
                  int topStartIndex;
                  Map<std::string, std::string> *startTypeMap;
                  Map<std::string, std::string> *contTypeMap;

                  int completeIndex;
                  int incompleteIndex;

              public:
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
                  Parser(ParserModel *model, int beamSize, double advancePercentage); //this(model.getBuildModel(), model.getCheckModel(), new POSTaggerME(model.getParserTaggerModel(), 10, 0), new ChunkerME(model.getParserChunkerModel(), ChunkerME.DEFAULT_BEAM_SIZE, new ParserChunkerSequenceValidator(model.getParserChunkerModel()), new ChunkContextGenerator(ChunkerME.DEFAULT_BEAM_SIZE)), model.getHeadRules(), beamSize, advancePercentage);

//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
                  Parser(ParserModel *model); //this(model, defaultBeamSize, defaultAdvancePercentage);

                  /// <summary>
                  /// Creates a new parser using the specified models and head rules. </summary>
                  /// <param name="buildModel"> The model to assign constituent labels. </param>
                  /// <param name="checkModel"> The model to determine a constituent is complete. </param>
                  /// <param name="tagger"> The model to assign pos-tags. </param>
                  /// <param name="chunker"> The model to assign flat constituent labels. </param>
                  /// <param name="headRules"> The head rules for head word perculation. </param>
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated public Parser(opennlp.model.MaxentModel buildModel, opennlp.model.MaxentModel checkModel, opennlp.tools.postag.POSTagger tagger, opennlp.tools.chunker.Chunker chunker, opennlp.tools.parser.HeadRules headRules)
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
                  Parser(MaxentModel *buildModel, MaxentModel *checkModel, POSTagger *tagger, Chunker *chunker, HeadRules *headRules); //this(buildModel,checkModel,tagger,chunker,headRules,defaultBeamSize,defaultAdvancePercentage);

                  /// <summary>
                  /// Creates a new parser using the specified models and head rules using the specified beam size and advance percentage. </summary>
                  /// <param name="buildModel"> The model to assign constituent labels. </param>
                  /// <param name="checkModel"> The model to determine a constituent is complete. </param>
                  /// <param name="tagger"> The model to assign pos-tags. </param>
                  /// <param name="chunker"> The model to assign flat constituent labels. </param>
                  /// <param name="headRules"> The head rules for head word perculation. </param>
                  /// <param name="beamSize"> The number of different parses kept during parsing. </param>
                  /// <param name="advancePercentage"> The minimal amount of probability mass which advanced outcomes must represent.
                  /// Only outcomes which contribute to the top "advancePercentage" will be explored. </param>
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated public Parser(opennlp.model.MaxentModel buildModel, opennlp.model.MaxentModel checkModel, opennlp.tools.postag.POSTagger tagger, opennlp.tools.chunker.Chunker chunker, opennlp.tools.parser.HeadRules headRules, int beamSize, double advancePercentage)
                  Parser(MaxentModel *buildModel, MaxentModel *checkModel, POSTagger *tagger, Chunker *chunker, HeadRules *headRules, int beamSize, double advancePercentage);

              protected:
                  virtual void advanceTop(Parse *p);

                  virtual Parse *advanceParses(Parse *const p, double probMass);

                  /// @deprecated Please do not use anymore, use the ObjectStream train methods instead! This method
                  /// will be removed soon. 
              public:
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated("Please do not use anymore, use the ObjectStream train methods instead! This method") public static opennlp.model.AbstractModel train(opennlp.model.EventStream es, int iterations, int cut) throws java.io.IOException
                  static AbstractModel *train(opennlp::model::EventStream *es, int iterations, int cut) throw(IOException);

                  static void mergeReportIntoManifest(Map<std::string, std::string> *manifest, Map<std::string, std::string> *report, const std::string &namespace_Renamed);

                  static ParserModel *train(const std::string &languageCode, ObjectStream<Parse*> *parseSamples, HeadRules *rules, TrainingParameters *mlParams) throw(IOException);

                  /// @deprecated use <seealso cref="#train(String, ObjectStream, HeadRules, TrainingParameters)"/>
                  /// instead and pass in a TrainingParameters object. 
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated("use <seealso cref="#train(String, opennlp.tools.util.ObjectStream, opennlp.tools.parser.HeadRules, opennlp.tools.util.TrainingParameters)"/>") public static opennlp.tools.parser.ParserModel train(String languageCode, opennlp.tools.util.ObjectStream<opennlp.tools.parser.Parse> parseSamples, opennlp.tools.parser.HeadRules rules, int iterations, int cut) throws java.io.IOException
                  static ParserModel *train(const std::string &languageCode, ObjectStream<Parse*> *parseSamples, HeadRules *rules, int iterations, int cut) throw(IOException);
                };

            }
        }
    }
}


#endif	//#ifndef PARSER
