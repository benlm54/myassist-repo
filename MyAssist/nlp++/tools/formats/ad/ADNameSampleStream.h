#ifndef ADNAMESAMPLESTREAM
#define ADNAMESAMPLESTREAM

#include "../tools/namefind/NameSample.h"
#include "../tools/util/ObjectStream.h"
#include "ADSentenceStream.h"
#include "../tools/util/Span.h"
#include "NameSample>.h"
#include "const_iterator.h"
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
        namespace formats
        {
            namespace ad
            {


                using opennlp::tools::formats::ad::ADSentenceStream::Sentence;
                using opennlp::tools::formats::ad::ADSentenceStream::SentenceParser::Leaf;
                using opennlp::tools::formats::ad::ADSentenceStream::SentenceParser::Node;
                using opennlp::tools::formats::ad::ADSentenceStream::SentenceParser::TreeElement;
                using opennlp::tools::namefind::NameSample;
                using opennlp::tools::util::ObjectStream;
                using opennlp::tools::util::PlainTextByLineStream;
                using opennlp::tools::util::Span;

                /// <summary>
                /// Parser for Floresta Sita(c)tica Arvores Deitadas corpus, output to for the
                /// Portuguese NER training.
                /// <p>
                /// The data contains four named entity types: Person, Organization, Group,
                /// Place, Event, ArtProd, Abstract, Thing, Time and Numeric.<br>
                /// <p>
                /// Data can be found on this web site:<br>
                /// http://www.linguateca.pt/floresta/corpus.html
                /// <p>
                /// Information about the format:<br>
                /// Susana Afonso.
                /// "�?rvores deitadas: Descrição do formato e das opções de análise na Floresta Sintáctica"
                /// .<br>
                /// 12 de Fevereiro de 2006.
                /// http://www.linguateca.pt/documentos/Afonso2006ArvoresDeitadas.pdf
                /// <p>
                /// Detailed info about the NER tagset:
                /// http://beta.visl.sdu.dk/visl/pt/info/portsymbol.html#semtags_names
                /// <p>
                /// <b>Note:</b> Do not use this class, internal use only!
                /// </summary>
                class ADNameSampleStream : public ObjectStream<NameSample*>
                {

                  /// <summary>
                  /// Pattern of a NER tag in Arvores Deitadas 
                  /// </summary>
              private:
                  static Pattern *const tagPattern;

                  /// <summary>
                  /// Map to the Arvores Deitadas types to our types. It is read-only.
                  /// </summary>
                  static Map<std::string, std::string> *const HAREM;

//JAVA TO C++ CONVERTER TODO TASK: Static constructors are not allowed in native C++:
                  static ADNameSampleStream();

                  ObjectStream<ADSentenceStream::Sentence*> *const adSentenceStream;

                  /// <summary>
                  /// To keep the last left contraction part
                  /// </summary>
                  std::string leftContractionPart;

                  /// <summary>
                  /// Creates a new <seealso cref="NameSample"/> stream from a line stream, i.e.
                  /// <seealso cref="ObjectStream"/>< <seealso cref="String"/>>, that could be a
                  /// <seealso cref="PlainTextByLineStream"/> object.
                  /// </summary>
                  /// <param name="lineStream">
                  ///          a stream of lines as <seealso cref="String"/> </param>
              public:
                  ADNameSampleStream(ObjectStream<std::string> *lineStream);

                  /// <summary>
                  /// Creates a new <seealso cref="NameSample"/> stream from a <seealso cref="InputStream"/>
                  /// </summary>
                  /// <param name="in">
                  ///          the Corpus <seealso cref="InputStream"/> </param>
                  /// <param name="charsetName">
                  ///          the charset of the Arvores Deitadas Corpus </param>
                  ADNameSampleStream(InputStream *in_Renamed, const std::string &charsetName);

                  virtual NameSample *read() throw(IOException);

                  /// <summary>
                  /// Recursive method to process a node in Arvores Deitadas format.
                  /// </summary>
                  /// <param name="node">
                  ///          the node to be processed </param>
                  /// <param name="sentence">
                  ///          the sentence tokens we got so far </param>
                  /// <param name="names">
                  ///          the names we got so far </param>
              private:
                  void process(Node *node, std::vector<std::string> &sentence, std::vector<Span*> &names);

                  /// <summary>
                  /// Process a Leaf of Arvores Detaitadas format
                  /// </summary>
                  /// <param name="leaf">
                  ///          the leaf to be processed </param>
                  /// <param name="sentence">
                  ///          the sentence tokens we got so far </param>
                  /// <param name="names">
                  ///          the names we got so far </param>
                  void processLeaf(Leaf *leaf, std::vector<std::string> &sentence, std::vector<Span*> &names);





                  /// <summary>
                  /// Parse a NER tag in Arvores Deitadas format.
                  /// </summary>
                  /// <param name="tags">
                  ///          the NER tag in Arvores Deitadas format </param>
                  /// <returns> the NER tag, or null if not a NER tag in Arvores Deitadas format </returns>
                  static std::string getNER(const std::string &tags);

              public:
                  virtual void reset() throw(IOException, UnsupportedOperationException);

                  virtual void close() throw(IOException);


                private:
                    void InitializeInstanceFields();
                };

            }
        }
    }
}


#endif	//#ifndef ADNAMESAMPLESTREAM
