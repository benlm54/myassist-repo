#ifndef ABSTRACTBOTTOMUPPARSER
#define ABSTRACTBOTTOMUPPARSER

#include "Parser.h"
#include "chunking/Parser.h"
#include "treeinsert/Parser.h"
#include "Parse.h"
#include "../tools/util/Heap.h"
#include "HeadRules.h"
#include "../tools/postag/POSTagger.h"
#include "../tools/chunker/Chunker.h"
#include "../tools/dictionary/Dictionary.h"
#include "../tools/util/ObjectStream.h"
#include "../tools/util/TrainingParameters.h"
#include "const_iterator.h"
#include <string>
#include <vector>
#include <cmath>
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
        namespace parser
        {


            using opennlp::tools::chunker::Chunker;
            using opennlp::tools::dictionary::Dictionary;
            using opennlp::tools::ngram::NGramModel;
            using opennlp::tools::parser::chunking::ParserEventStream;
            using opennlp::tools::postag::POSTagger;
            using opennlp::tools::util::Heap;
            using opennlp::tools::util::ListHeap;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::Sequence;
            using opennlp::tools::util::Span;
            using opennlp::tools::util::StringList;
            using opennlp::tools::util::TrainingParameters;

            /// <summary>
            /// Abstract class which contains code to tag and chunk parses for bottom up parsing and
            /// leaves implementation of advancing parses and completing parses to extend class.
            /// <p>
            /// <b>Note:</b> <br> The nodes within
            /// the returned parses are shared with other parses and therefore their parent node references will not be consistent
            /// with their child node reference.  <seealso cref="#setParents setParents"/> can be used to make the parents consistent
            /// with a particular parse, but subsequent calls to <code>setParents</code> can invalidate the results of earlier
            /// calls.<br>
            /// </summary>
            class AbstractBottomUpParser : public Parser
            {

              /// <summary>
              /// The maximum number of parses advanced from all preceding
              /// parses at each derivation step.
              /// </summary>
          protected:
              int M;

              /// <summary>
              /// The maximum number of parses to advance from a single preceding parse.
              /// </summary>
              int K;

              /// <summary>
              /// The minimum total probability mass of advanced outcomes.
              /// </summary>
              double Q;

              /// <summary>
              /// The default beam size used if no beam size is given.
              /// </summary>
          public:
              static const int defaultBeamSize = 20;

              /// <summary>
              /// The default amount of probability mass required of advanced outcomes.
              /// </summary>
              static const double defaultAdvancePercentage;

              /// <summary>
              /// Completed parses.
              /// </summary>
          protected:
              Heap<Parse*> *completeParses;

              /// <summary>
              /// Incomplete parses which will be advanced.
              /// </summary>
              Heap<Parse*> *odh;

              /// <summary>
              /// Incomplete parses which have been advanced. 
              /// </summary>
              Heap<Parse*> *ndh;

              /// <summary>
              /// The head rules for the parser.
              /// </summary>
              HeadRules *headRules;

              /// <summary>
              /// The set strings which are considered punctuation for the parser.
              /// Punctuation is not attached, but floats to the top of the parse as attachment
              /// decisions are made about its non-punctuation sister nodes.
              /// </summary>
              Set<std::string> *punctSet;

              /// <summary>
              /// The label for the top node. 
              /// </summary>
          public:
              static const std::string TOP_NODE;

              /// <summary>
              /// The label for the top if an incomplete node.
              /// </summary>
              static const std::string INC_NODE;

              /// <summary>
              /// The label for a token node. 
              /// </summary>
              static const std::string TOK_NODE;

              /// <summary>
              /// The integer 0.
              /// </summary>
              static const int ZERO = 0;

              /// <summary>
              /// Prefix for outcomes starting a constituent. 
              /// </summary>
              static const std::string START;

              /// <summary>
              /// Prefix for outcomes continuing a constituent. 
              /// </summary>
              static const std::string CONT;

              /// <summary>
              /// Outcome for token which is not contained in a basal constituent. 
              /// </summary>
              static const std::string OTHER;

              /// <summary>
              /// Outcome used when a constituent is complete. 
              /// </summary>
              static const std::string COMPLETE;

              /// <summary>
              /// Outcome used when a constituent is incomplete. 
              /// </summary>
              static const std::string INCOMPLETE;

              /// <summary>
              /// The pos-tagger that the parser uses. 
              /// </summary>
          protected:
              POSTagger *tagger;

              /// <summary>
              /// The chunker that the parser uses to chunk non-recursive structures. 
              /// </summary>
              Chunker *chunker;

              /// <summary>
              /// Specifies whether failed parses should be reported to standard error. 
              /// </summary>
              bool reportFailedParse;

              /// <summary>
              /// Specifies whether a derivation string should be created during parsing. 
              /// This is useful for debugging. 
              /// </summary>
              bool createDerivationString;

              /// <summary>
              /// Turns debug print on or off.
              /// </summary>
              bool debugOn;

          public:
              AbstractBottomUpParser(POSTagger *tagger, Chunker *chunker, HeadRules *headRules, int beamSize, double advancePercentage);

              /// <summary>
              /// Specifies whether the parser should report when it was unable to find a parse for
              /// a particular sentence. </summary>
              /// <param name="errorReporting"> If true then un-parsed sentences are reported, false otherwise. </param>
              virtual void setErrorReporting(bool errorReporting);

              /// <summary>
              /// Assigns parent references for the specified parse so that they
              /// are consistent with the children references. </summary>
              /// <param name="p"> The parse whose parent references need to be assigned. </param>
              static void setParents(Parse *p);

              /// <summary>
              /// Removes the punctuation from the specified set of chunks, adds it to the parses
              /// adjacent to the punctuation is specified, and returns a new array of parses with the punctuation
              /// removed. </summary>
              /// <param name="chunks"> A set of parses. </param>
              /// <param name="punctSet"> The set of punctuation which is to be removed. </param>
              /// <returns> An array of parses which is a subset of chunks with punctuation removed. </returns>
              static Parse *collapsePunctuation(Parse chunks[], Set<std::string> *punctSet);



              /// <summary>
              /// Advances the specified parse and returns the an array advanced parses whose probability accounts for
              /// more than the specified amount of probability mass. </summary>
              /// <param name="p"> The parse to advance. </param>
              /// <param name="probMass"> The amount of probability mass that should be accounted for by the advanced parses. </param>
          protected:
              virtual Parse *advanceParses(Parse *const p, double probMass) = 0;

              /// <summary>
              /// Adds the "TOP" node to the specified parse. </summary>
              /// <param name="p"> The complete parse. </param>
              virtual void advanceTop(Parse *p) = 0;

          public:
              virtual Parse *parse(Parse *tokens, int numParses);

              virtual Parse *parse(Parse *tokens);

              /// <summary>
              /// Returns the top chunk sequences for the specified parse. </summary>
              /// <param name="p"> A pos-tag assigned parse. </param>
              /// <param name="minChunkScore"> A minimum score below which chunks should not be advanced. </param>
              /// <returns> The top chunk assignments to the specified parse. </returns>
          protected:
              virtual Parse *advanceChunks(Parse *const p, double minChunkScore);

              /// <summary>
              /// Advances the parse by assigning it POS tags and returns multiple tag sequences. </summary>
              /// <param name="p"> The parse to be tagged. </param>
              /// <returns> Parses with different POS-tag sequence assignments. </returns>
              virtual Parse *advanceTags(Parse *const p);

              /// <summary>
              /// Determines the mapping between the specified index into the specified parses without punctuation to
              /// the corresponding index into the specified parses. </summary>
              /// <param name="index"> An index into the parses without punctuation. </param>
              /// <param name="nonPunctParses"> The parses without punctuation. </param>
              /// <param name="parses"> The parses wit punctuation. </param>
              /// <returns> An index into the specified parses which corresponds to the same node the specified index
              /// into the parses with punctuation. </returns>
              virtual int mapParseIndex(int index, Parse nonPunctParses[], Parse parses[]);

          private:
              static bool lastChild(Parse *child, Parse *parent, Set<std::string> *punctSet);

              /// <summary>
              /// Creates a n-gram dictionary from the specified data stream using the specified head rule and specified cut-off.
              /// </summary>
              /// <param name="data"> The data stream of parses. </param>
              /// <param name="rules"> The head rules for the parses. </param>
              /// <param name="params"> can contain a cutoff, the minimum number of entries required for the
              ///        n-gram to be saved as part of the dictionary. </param>
              /// <returns> A dictionary object. </returns>
          public:
              static Dictionary *buildDictionary(ObjectStream<Parse*> *data, HeadRules *rules, TrainingParameters *params) throw(IOException);

              /// <summary>
              /// Creates a n-gram dictionary from the specified data stream using the specified head rule and specified cut-off.
              /// </summary>
              /// <param name="data"> The data stream of parses. </param>
              /// <param name="rules"> The head rules for the parses. </param>
              /// <param name="cutoff"> The minimum number of entries required for the n-gram to be saved as part of the dictionary. </param>
              /// <returns> A dictionary object. </returns>
              static Dictionary *buildDictionary(ObjectStream<Parse*> *data, HeadRules *rules, int cutoff) throw(IOException);

            private:
                void InitializeInstanceFields();
            };

        }
    }
}


#endif	//#ifndef ABSTRACTBOTTOMUPPARSER
