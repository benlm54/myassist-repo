#ifndef ADSENTENCESTREAM
#define ADSENTENCESTREAM

#include "../tools/util/FilterObjectStream.h"
#include "../tools/util/ObjectStream.h"
#include "Sentence>.h"
#include "StringBuffer.h"
#include "Exception.h"
#include "StringBuilder.h"
#include "S.h"
#include <string>
#include <vector>
#include <stack>

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
        namespace formats
        {
            namespace ad
            {


                using opennlp::tools::formats::ad::ADSentenceStream::SentenceParser::Node;
                using opennlp::tools::util::FilterObjectStream;
                using opennlp::tools::util::ObjectStream;

                /// <summary>
                /// Stream filter which merges text lines into sentences, following the Arvores
                /// Deitadas syntax.
                /// <p>
                /// Information about the format:<br>
                /// Susana Afonso.
                /// "�?rvores deitadas: Descrição do formato e das opções de análise na Floresta Sintáctica"
                /// .<br>
                /// 12 de Fevereiro de 2006. 
                /// http://www.linguateca.pt/documentos/Afonso2006ArvoresDeitadas.pdf 
                /// <p>
                /// <b>Note:</b> Do not use this class, internal use only!
                /// </summary>
                class ADSentenceStream : public FilterObjectStream<std::string, ADSentenceStream::Sentence*>
                {

              public:
                  class Sentence
                  {

                private:
                    std::string text;
                    Node *root;
                    std::string metadata;

                public:
                    virtual std::string getText();

                    virtual void setText(const std::string &text);

                    virtual Node *getRoot();

                    virtual void setRoot(Node *root);

                    virtual void setMetadata(const std::string &metadata);

                    virtual std::string getMetadata();

                  };

                  /// <summary>
                  /// Parses a sample of AD corpus. A sentence in AD corpus is represented by a
                  /// Tree. In this class we declare some types to represent that tree. Today we get only
                  /// the first alternative (A1).
                  /// </summary>
              public:
                  class SentenceParser
                  {
                public:
                    class TreeElement
                    {
                                private:
                                    ADSentenceStream::SentenceParser *const outerInstance;

                                public:
                                    TreeElement(ADSentenceStream::SentenceParser *outerInstance);


                  private:
                      std::string syntacticTag;
                      std::string morphologicalTag;
                      int level;

                  public:
                      virtual bool isLeaf();

                      virtual void setSyntacticTag(const std::string &syntacticTag);

                      virtual std::string getSyntacticTag();

                      virtual void setLevel(int level);

                      virtual int getLevel();

                      virtual void setMorphologicalTag(const std::string &morphologicalTag);

                      virtual std::string getMorphologicalTag();
                    };

                public:
                    class Node : public TreeElement
                    {
                                private:
                                    ADSentenceStream::SentenceParser *const outerInstance;

                                public:
                                    internal *Node(ADSentenceStream::SentenceParser *outerInstance);

                  private:
                      std::vector<TreeElement*> elems;

                  public:
                      virtual void addElement(TreeElement *element);

                      virtual TreeElement *getElements();

                      virtual std::string ToString();

                    private:
                        void InitializeInstanceFields();
                    };

                public:
                    class Leaf : public TreeElement
                    {
                                private:
                                    ADSentenceStream::SentenceParser *const outerInstance;

                                public:
                                    Leaf(ADSentenceStream::SentenceParser *outerInstance);


                  private:
                      std::string word;
                      std::string lemma;

                  public:
                      virtual bool isLeaf();

                      virtual void setLexeme(const std::string &lexeme);

                      virtual std::string getLexeme();

                      virtual std::string ToString();

                      virtual void setLemma(const std::string &lemma);

                      virtual std::string getLemma();
                    };


                    //private Pattern rootPattern = Pattern.compile("^[^:=]+:[^(\\s]+(\\(.*?\\))?$");
                private:
                    Pattern *rootPattern;
                    Pattern *nodePattern;
                    Pattern *leafPattern;
                    Pattern *bizarreLeafPattern;
                    Pattern *punctuationPattern;

                    std::string text, meta;

                    /// <summary>
                    /// Parse the sentence 
                    /// </summary>
                public:
                    virtual Sentence *parse(const std::string &sentenceString, int para, bool isTitle, bool isBox);

                    /// <summary>
                    /// Parse a tree element from a AD line
                    /// </summary>
                    /// <param name="line">
                    ///          the AD line </param>
                    /// <returns> the tree element </returns>
                    virtual TreeElement *getElement(const std::string &line);

                    /// <summary>
                    /// Represents a tree element, Node or Leaf </summary>
                    /// <summary>
                    /// Represents the AD node </summary>
                    /// <summary>
                    /// Represents the AD leaf </summary>

                  private:
                      void InitializeInstanceFields();

public:
                      SentenceParser()
                      {
                          InitializeInstanceFields();
                      }
                  };

                  /// <summary>
                  /// The start sentence pattern 
                  /// </summary>
              private:
                  static Pattern *const sentStart;

                  /// <summary>
                  /// The end sentence pattern 
                  /// </summary>
                  static Pattern *const sentEnd;

                  /// <summary>
                  /// The start sentence pattern 
                  /// </summary>
                  static Pattern *const titleStart;

                  /// <summary>
                  /// The end sentence pattern 
                  /// </summary>
                  static Pattern *const titleEnd;

                  /// <summary>
                  /// The start sentence pattern 
                  /// </summary>
                  static Pattern *const boxStart;

                  /// <summary>
                  /// The end sentence pattern 
                  /// </summary>
                  static Pattern *const boxEnd;


                  /// <summary>
                  /// The start sentence pattern 
                  /// </summary>
                  static Pattern *const paraStart;

                  /// <summary>
                  /// The start sentence pattern 
                  /// </summary>
                  static Pattern *const textStart;

                  SentenceParser *parser;

                  int paraID;
                  bool isTitle;
                  bool isBox;

              public:
                  ADSentenceStream(ObjectStream<std::string> *lineStream);


                  virtual Sentence *read() throw(IOException);

                private:
                    void InitializeInstanceFields();
                };

            }
        }
    }
}


#endif	//#ifndef ADSENTENCESTREAM
