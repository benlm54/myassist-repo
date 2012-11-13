#ifndef PARSE
#define PARSE

#include "../tools/util/Span.h"
#include "HeadRules.h"
#include "GapLabeler.h"
#include "Cloneable.h"
#include "Comparable<Parse>.h"
#include "StringBuffer.h"
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <set>
#include <cmath>

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
        namespace parser
        {


            using opennlp::tools::util::Span;

            /// <summary>
            /// Data structure for holding parse constituents.
            /// </summary>
            class Parse : public Cloneable, public Comparable<Parse*>
            {

          public:
              static const std::string BRACKET_LRB;
              static const std::string BRACKET_RRB;
              static const std::string BRACKET_LCB;
              static const std::string BRACKET_RCB;

              /// <summary>
              /// The text string on which this parse is based.
              /// This object is shared among all parses for the same sentence.
              /// </summary>
          private:
              std::string text;

              /// <summary>
              /// The character offsets into the text for this constituent.
              /// </summary>
              Span *span;

              /// <summary>
              /// The syntactic type of this parse.
              /// </summary>
              std::string type;

              /// <summary>
              /// The sub-constituents of this parse.
              /// </summary>
              std::vector<Parse*> parts;

              /// <summary>
              /// The head parse of this parse. A parse can be its own head.
              /// </summary>
              Parse *head;

              /// <summary>
              /// A string used during parse construction to specify which
              /// stage of parsing has been performed on this node.
              /// </summary>
              std::string label;

              /// <summary>
              /// Index in the sentence of the head of this constituent.
              /// </summary>
              int headIndex;

              /// <summary>
              /// The parent parse of this parse.
              /// </summary>
              Parse *parent;

              /// <summary>
              /// The probability associated with the syntactic type
              /// assigned to this parse.
              /// </summary>
              double prob;

              /// <summary>
              /// The string buffer used to track the derivation of this parse.
              /// </summary>
              StringBuffer *derivation;

              /// <summary>
              /// Specifies whether this constituent was built during the chunking phase.
              /// </summary>
//JAVA TO C++ CONVERTER NOTE: The variable isChunk was renamed since C++ does not allow variables with the same name as methods:
              bool isChunk_Renamed;

              /// <summary>
              /// The pattern used to find the base constituent label of a
              /// Penn Treebank labeled constituent.
              /// </summary>
              static Pattern *typePattern;

              /// <summary>
              /// The pattern used to find the function tags.
              /// </summary>
              static Pattern *funTypePattern;

              /// <summary>
              /// The patter used to identify tokens in Penn Treebank labeled constituents.
              /// </summary>
              static Pattern *tokenPattern;

              /// <summary>
              /// The set of punctuation parses which are between this parse and the previous parse.
              /// </summary>
              Collection<Parse*> *prevPunctSet;

              /// <summary>
              /// The set of punctuation parses which are between this parse and
              /// the subsequent parse.
              /// </summary>
              Collection<Parse*> *nextPunctSet;

              /// <summary>
              /// Specifies whether constituent labels should include parts specified
              /// after minus character.
              /// </summary>
//JAVA TO C++ CONVERTER NOTE: The variable useFunctionTags was renamed since C++ does not allow variables with the same name as methods:
              static bool useFunctionTags_Renamed;

              /// <summary>
              /// Creates a new parse node for this specified text and span of the specified type with the specified probability
              /// and the specified head index.
              /// </summary>
              /// <param name="text"> The text of the sentence for which this node is a part of. </param>
              /// <param name="span"> The character offsets for this node within the specified text. </param>
              /// <param name="type"> The constituent label of this node. </param>
              /// <param name="p"> The probability of this parse. </param>
              /// <param name="index"> The token index of the head of this parse. </param>
          public:
              Parse(const std::string &text, Span *span, const std::string &type, double p, int index);

              /// <summary>
              /// Creates a new parse node for this specified text and span of the specified type with the specified probability
              /// and the specified head and head index.
              /// </summary>
              /// <param name="text"> The text of the sentence for which this node is a part of. </param>
              /// <param name="span"> The character offsets for this node within the specified text. </param>
              /// <param name="type"> The constituent label of this node. </param>
              /// <param name="p"> The probability of this parse. </param>
              /// <param name="h"> The head token of this parse. </param>
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              Parse(const std::string &text, Span *span, const std::string &type, double p, Parse *h); //this(text, span, type, p, 0);

              virtual void *clone();

              /// <summary>
              /// Clones the right frontier of parse up to the specified node.
              /// </summary>
              /// <param name="node"> The last node in the right frontier of the parse tree which should be cloned. </param>
              /// <returns> A clone of this parse and its right frontier up to and including the specified node. </returns>
              virtual Parse *clone(Parse *node);
              /// <summary>
              /// Clones the right frontier of this root parse up to and including the specified node.
              /// </summary>
              /// <param name="node"> The last node in the right frontier of the parse tree which should be cloned. </param>
              /// <param name="parseIndex"> The child index of the parse for this root node. </param>
              /// <returns> A clone of this root parse and its right frontier up to and including the specified node. </returns>
              virtual Parse *cloneRoot(Parse *node, int parseIndex);

              /// <summary>
              /// Specifies whether function tags should be included as part of the constituent type.
              /// </summary>
              /// <param name="uft"> true is they should be included; false otherwise. </param>
              static void useFunctionTags(bool uft);


              /// <summary>
              /// Set the type of this constituent to the specified type.
              /// </summary>
              /// <param name="type"> The type of this constituent. </param>
              virtual void setType(const std::string &type);

              /// <summary>
              /// Returns the constituent label for this node of the parse.
              /// </summary>
              /// <returns> The constituent label for this node of the parse. </returns>
              virtual std::string getType();

              /// <summary>
              /// Returns the set of punctuation parses that occur immediately before this parse.
              /// </summary>
              /// <returns> the set of punctuation parses that occur immediately before this parse. </returns>
              virtual Collection<Parse*> *getPreviousPunctuationSet();

              /// <summary>
              /// Designates that the specified punctuation should is prior to this parse.
              /// </summary>
              /// <param name="punct"> The punctuation. </param>
              virtual void addPreviousPunctuation(Parse *punct);

              /// <summary>
              /// Returns the set of punctuation parses that occur immediately after this parse.
              /// </summary>
              /// <returns> the set of punctuation parses that occur immediately after this parse. </returns>
              virtual Collection<Parse*> *getNextPunctuationSet();

              /// <summary>
              /// Designates that the specified punctuation follows this parse.
              /// </summary>
              /// <param name="punct"> The punctuation set. </param>
              virtual void addNextPunctuation(Parse *punct);

              /// <summary>
              /// Sets the set of punctuation tags which follow this parse.
              /// </summary>
              /// <param name="punctSet"> The set of punctuation tags which follow this parse. </param>
              virtual void setNextPunctuation(Collection<Parse*> *punctSet);

              /// <summary>
              /// Sets the set of punctuation tags which preceed this parse.
              /// </summary>
              /// <param name="punctSet"> The set of punctuation tags which preceed this parse. </param>
              virtual void setPrevPunctuation(Collection<Parse*> *punctSet);

              /// <summary>
              /// Inserts the specified constituent into this parse based on its text span.This
              /// method assumes that the specified constituent can be inserted into this parse.
              /// </summary>
              /// <param name="constituent"> The constituent to be inserted. </param>
              virtual void insert(Parse *const constituent);

              /// <summary>
              /// Appends the specified string buffer with a string representation of this parse.
              /// </summary>
              /// <param name="sb"> A string buffer into which the parse string can be appended. </param>
              virtual void show(StringBuffer *sb);

              /// <summary>
              /// Displays this parse using Penn Treebank-style formatting.
              /// </summary>
              virtual void show();


              /// <summary>
              /// Returns the probability associated with the pos-tag sequence assigned to this parse.
              /// </summary>
              /// <returns> The probability associated with the pos-tag sequence assigned to this parse. </returns>
              virtual double getTagSequenceProb();

              /// <summary>
              /// Returns whether this parse is complete.
              /// </summary>
              /// <returns> Returns true if the parse contains a single top-most node. </returns>
              virtual bool complete();

              virtual std::string ToString();

              /// <summary>
              /// Returns the text of the sentence over which this parse was formed.
              /// </summary>
              /// <returns> The text of the sentence over which this parse was formed. </returns>
              virtual std::string getText();

              /// <summary>
              /// Returns the character offsets for this constituent.
              /// </summary>
              /// <returns> The character offsets for this constituent. </returns>
              virtual Span *getSpan();

              /// <summary>
              /// Returns the log of the product of the probability associated with all the decisions which formed this constituent.
              /// </summary>
              /// <returns> The log of the product of the probability associated with all the decisions which formed this constituent. </returns>
              virtual double getProb();

              /// <summary>
              /// Adds the specified probability log to this current log for this parse.
              /// </summary>
              /// <param name="logProb"> The probability of an action performed on this parse. </param>
              virtual void addProb(double logProb);

              /// <summary>
              /// Returns the child constituents of this constituent
              /// . </summary>
              /// <returns> The child constituents of this constituent. </returns>
              virtual Parse *getChildren();

              /// <summary>
              /// Replaces the child at the specified index with a new child with the specified label.
              /// </summary>
              /// <param name="index"> The index of the child to be replaced. </param>
              /// <param name="label"> The label to be assigned to the new child. </param>
              virtual void setChild(int index, const std::string &label);

              virtual void add(Parse *daughter, HeadRules *rules);

              virtual void remove(int index);

              virtual Parse *adjoinRoot(Parse *node, HeadRules *rules, int parseIndex);

              /// <summary>
              /// Sister adjoins this node's last child and the specified sister node and returns their
              /// new parent node.  The new parent node replace this nodes last child.
              /// </summary>
              /// <param name="sister"> The node to be adjoined. </param>
              /// <param name="rules"> The head rules for the parser. </param>
              /// <returns> The new parent node of this node and the specified sister node. </returns>
              virtual Parse *adjoin(Parse *sister, HeadRules *rules);

              virtual void expandTopNode(Parse *root);

              /// <summary>
              /// Returns the number of children for this parse node.
              /// </summary>
              /// <returns> the number of children for this parse node. </returns>
              virtual int getChildCount();

              /// <summary>
              /// Returns the index of this specified child.
              /// </summary>
              /// <param name="child"> A child of this parse.
              /// </param>
              /// <returns> the index of this specified child or -1 if the specified child is not a child of this parse. </returns>
              virtual int indexOf(Parse *child);

              /// <summary>
              /// Returns the head constituent associated with this constituent.
              /// </summary>
              /// <returns> The head constituent associated with this constituent. </returns>
              virtual Parse *getHead();

              /// <summary>
              /// Returns the index within a sentence of the head token for this parse.
              /// </summary>
              /// <returns> The index within a sentence of the head token for this parse. </returns>
              virtual int getHeadIndex();

              /// <summary>
              /// Returns the label assigned to this parse node during parsing
              /// which specifies how this node will be formed into a constituent.
              /// </summary>
              /// <returns> The outcome label assigned to this node during parsing. </returns>
              virtual std::string getLabel();

              /// <summary>
              /// Assigns this parse the specified label.  This is used by parsing schemes to
              /// tag parsing nodes while building.
              /// </summary>
              /// <param name="label"> A label indicating something about the stage of building for this parse node. </param>
              virtual void setLabel(const std::string &label);

          private:
              static std::string getType(const std::string &rest);

              static std::string encodeToken(const std::string &token);

              static std::string decodeToken(const std::string &token);

              /// <summary>
              /// Returns the string containing the token for the specified portion of the parse string or
              /// null if the portion of the parse string does not represent a token.
              /// </summary>
              /// <param name="rest"> The portion of the parse string remaining to be processed.
              /// </param>
              /// <returns> The string containing the token for the specified portion of the parse string or
              /// null if the portion of the parse string does not represent a token. </returns>
              static std::string getToken(const std::string &rest);

              /// <summary>
              /// Computes the head parses for this parse and its sub-parses and stores this information
              /// in the parse data structure.
              /// </summary>
              /// <param name="rules"> The head rules which determine how the head of the parse is computed. </param>
          public:
              virtual void updateHeads(HeadRules *rules);

              virtual void updateSpan();

              /// <summary>
              /// Prune the specified sentence parse of vacuous productions.
              /// </summary>
              /// <param name="parse"> </param>
              static void pruneParse(Parse *parse);

              static void fixPossesives(Parse *parse);



              /// <summary>
              /// Parses the specified tree-bank style parse string and return a Parse structure for that string.
              /// </summary>
              /// <param name="parse"> A tree-bank style parse string.
              /// </param>
              /// <returns> a Parse structure for the specified tree-bank style parse string. </returns>
              static Parse *parseParse(const std::string &parse);

              /// <summary>
              /// Parses the specified tree-bank style parse string and return a Parse structure
              /// for that string.
              /// </summary>
              /// <param name="parse"> A tree-bank style parse string. </param>
              /// <param name="gl"> The gap labeler.
              /// </param>
              /// <returns> a Parse structure for the specified tree-bank style parse string. </returns>
              static Parse *parseParse(const std::string &parse, GapLabeler *gl);

              /// <summary>
              /// Returns the parent parse node of this constituent.
              /// </summary>
              /// <returns> The parent parse node of this constituent. </returns>
              virtual Parse *getParent();

              /// <summary>
              /// Specifies the parent parse node for this constituent.
              /// </summary>
              /// <param name="parent"> The parent parse node for this constituent. </param>
              virtual void setParent(Parse *parent);

              /// <summary>
              /// Indicates whether this parse node is a pos-tag.
              /// </summary>
              /// <returns> true if this node is a pos-tag, false otherwise. </returns>
              virtual bool isPosTag();

              /// <summary>
              /// Returns true if this constituent contains no sub-constituents.
              /// </summary>
              /// <returns> true if this constituent contains no sub-constituents; false otherwise. </returns>
              virtual bool isFlat();

              virtual void isChunk(bool ic);

              virtual bool isChunk();

              /// <summary>
              /// Returns the parse nodes which are children of this node and which are pos tags.
              /// </summary>
              /// <returns> the parse nodes which are children of this node and which are pos tags. </returns>
              virtual Parse *getTagNodes();

              /// <summary>
              /// Returns the deepest shared parent of this node and the specified node.
              /// If the nodes are identical then their parent is returned.
              /// If one node is the parent of the other then the parent node is returned.
              /// </summary>
              /// <param name="node"> The node from which parents are compared to this node's parents.
              /// </param>
              /// <returns> the deepest shared parent of this node and the specified node. </returns>
              virtual Parse *getCommonParent(Parse *node);

              virtual bool Equals(void *o);

              virtual int GetHashCode();

              virtual int compareTo(Parse *p);

              /// <summary>
              /// Returns the derivation string for this parse if one has been created.
              /// </summary>
              /// <returns> the derivation string for this parse or null if no derivation
              /// string has been created. </returns>
              virtual StringBuffer *getDerivation();

              /// <summary>
              /// Specifies the derivation string to be associated with this parse.
              /// </summary>
              /// <param name="derivation"> The derivation string to be associated with this parse. </param>
              virtual void setDerivation(StringBuffer *derivation);

          private:
              void codeTree(Parse *p, int levels[]);

              /// <summary>
              /// Prints to standard out a representation of the specified parse which
              /// contains hash codes so that parent/child relationships can be explicitly seen.
              /// </summary>
          public:
              virtual void showCodeTree();

              /// <summary>
              /// Utility method to inserts named entities.
              /// </summary>
              /// <param name="tag"> </param>
              /// <param name="names"> </param>
              /// <param name="tokens"> </param>
              static void addNames(const std::string &tag, Span names[], Parse tokens[]);

              /// <summary>
              /// Reads training parses (one-sentence-per-line) and displays parse structure.
              /// </summary>
              /// <param name="args"> The head rules files.
              /// </param>
              /// <exception cref="IOException"> If the head rules file can not be opened and read. </exception>
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated public static void main(String[] args) throws java.io.IOException
              static void main(std::string args[]) throw(IOException);
            };
        }
    }
}


#endif	//#ifndef PARSE
