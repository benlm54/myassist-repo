#ifndef PARSER
#define PARSER

#include "../tools/parser/AbstractBottomUpParser.h"
#include "../model/MaxentModel.h"
#include "../tools/parser/chunking/BuildContextGenerator.h"
#include "BuildContextGenerator.h"
#include "AttachContextGenerator.h"
#include "../tools/parser/chunking/CheckContextGenerator.h"
#include "CheckContextGenerator.h"
#include "../tools/parser/ParserModel.h"
#include "../model/AbstractModel.h"
#include "../tools/chunker/Chunker.h"
#include "../tools/parser/HeadRules.h"
#include "../tools/postag/POSTagger.h"
#include "../tools/parser/Parse.h"
#include "../tools/util/ObjectStream.h"
#include "../tools/util/TrainingParameters.h"
#include "../model/EventStream.h"
#include <string>
#include <map>
#include <vector>
#include <list>
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
            namespace treeinsert
            {


                using opennlp::model::AbstractModel;
                using opennlp::model::MaxentModel;
                using opennlp::model::TrainUtil;
                using opennlp::model::TwoPassDataIndexer;
                using opennlp::tools::chunker::Chunker;
                using opennlp::tools::chunker::ChunkerME;
                using opennlp::tools::chunker::ChunkerModel;
                using opennlp::tools::dictionary::Dictionary;
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
                using opennlp::tools::util::TrainingParameters;

                /// <summary>
                /// Built/attach parser.  Nodes are built when their left-most
                /// child is encountered.  Subsequent children are attached as
                /// daughters.  Attachment is based on node in the right-frontier
                /// of the tree.  After each attachment or building, nodes are
                /// assesed as either complete or incomplete.  Complete nodes
                /// are no longer elligable for daughter attachment.
                /// Complex modifiers which produce additional node
                /// levels of the same type are attached with sister-adjunction.
                /// Attachment can not take place higher in the right-frontier
                /// than an incomplete node.
                /// </summary>
                class Parser : public AbstractBottomUpParser
                {

                  /// <summary>
                  /// Outcome used when a constituent needs an no additional parent node/building. </summary>
              public:
                  static const std::string DONE;

                  /// <summary>
                  /// Outcome used when a node should be attached as a sister to another node. </summary>
                  static const std::string ATTACH_SISTER;
                  /// <summary>
                  /// Outcome used when a node should be attached as a daughter to another node. </summary>
                  static const std::string ATTACH_DAUGHTER;
                  /// <summary>
                  /// Outcome used when a node should not be attached to another node. </summary>
                  static const std::string NON_ATTACH;

                  /// <summary>
                  /// Label used to distinguish build nodes from non-built nodes. </summary>
                  static const std::string BUILT;
              private:
                  MaxentModel *buildModel;
                  MaxentModel *attachModel;
                  MaxentModel *checkModel;

              public:
                  static bool checkComplete;

              private:
                  BuildContextGenerator *buildContextGenerator;
                  AttachContextGenerator *attachContextGenerator;
                  CheckContextGenerator *checkContextGenerator;

//ORIGINAL LINE: private double[] bprobs;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                  double *bprobs;
//ORIGINAL LINE: private double[] aprobs;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                  double *aprobs;
//ORIGINAL LINE: private double[] cprobs;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                  double *cprobs;

                  int doneIndex;
                  int sisterAttachIndex;
                  int daughterAttachIndex;
                  int nonAttachIndex;
                  int completeIndex;

//ORIGINAL LINE: private int[] attachments;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                  int *attachments;

              public:
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
                  Parser(ParserModel *model, int beamSize, double advancePercentage); //this(model.getBuildModel(), model.getAttachModel(), model.getCheckModel(), new POSTaggerME(model.getParserTaggerModel()), new ChunkerME(model.getParserChunkerModel(), ChunkerME.DEFAULT_BEAM_SIZE, new ParserChunkerSequenceValidator(model.getParserChunkerModel()), new ChunkContextGenerator(ChunkerME.DEFAULT_BEAM_SIZE)), model.getHeadRules(), beamSize, advancePercentage);

//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
                  Parser(ParserModel *model); //this(model, defaultBeamSize, defaultAdvancePercentage);

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated public Parser(opennlp.model.AbstractModel buildModel, opennlp.model.AbstractModel attachModel, opennlp.model.AbstractModel checkModel, opennlp.tools.postag.POSTagger tagger, opennlp.tools.chunker.Chunker chunker, opennlp.tools.parser.HeadRules headRules, int beamSize, double advancePercentage)
                  Parser(AbstractModel *buildModel, AbstractModel *attachModel, AbstractModel *checkModel, POSTagger *tagger, Chunker *chunker, HeadRules *headRules, int beamSize, double advancePercentage);

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated public Parser(opennlp.model.AbstractModel buildModel, opennlp.model.AbstractModel attachModel, opennlp.model.AbstractModel checkModel, opennlp.tools.postag.POSTagger tagger, opennlp.tools.chunker.Chunker chunker, opennlp.tools.parser.HeadRules headRules)
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
                  Parser(AbstractModel *buildModel, AbstractModel *attachModel, AbstractModel *checkModel, POSTagger *tagger, Chunker *chunker, HeadRules *headRules); //this(buildModel,attachModel,checkModel, tagger,chunker,headRules,defaultBeamSize,defaultAdvancePercentage);

                  /// <summary>
                  /// Returns the right frontier of the specified parse tree with nodes ordered from deepest
                  /// to shallowest. </summary>
                  /// <param name="root"> The root of the parse tree. </param>
                  /// <returns> The right frontier of the specified parse tree. </returns>
                  static std::vector<Parse*> getRightFrontier(Parse *root, Set<std::string> *punctSet);

              private:
                  void setBuilt(Parse *p);

                  void setComplete(Parse *p);

                  void setIncomplete(Parse *p);

                  bool isBuilt(Parse *p);

                  bool isComplete(Parse *p);

              protected:
                  virtual Parse *advanceChunks(Parse *p, double minChunkScore);

                  virtual Parse *advanceParses(Parse *p, double probMass);

                  virtual void advanceTop(Parse *p);

              public:
                  static ParserModel *train(const std::string &languageCode, ObjectStream<Parse*> *parseSamples, HeadRules *rules, TrainingParameters *mlParams) throw(IOException);

                  static ParserModel *train(const std::string &languageCode, ObjectStream<Parse*> *parseSamples, HeadRules *rules, int iterations, int cut) throw(IOException);

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated public static opennlp.model.AbstractModel train(opennlp.model.EventStream es, int iterations, int cut) throws java.io.IOException
                  static AbstractModel *train(opennlp::model::EventStream *es, int iterations, int cut) throw(IOException);
                };

            }
        }
    }
}


#endif	//#ifndef PARSER
