#ifndef ADCHUNKSAMPLESTREAM
#define ADCHUNKSAMPLESTREAM

#include "../tools/chunker/ChunkSample.h"
#include "../tools/util/ObjectStream.h"
#include "ADSentenceStream.h"
#include "ChunkSample>.h"
#include <string>
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


                using opennlp::tools::chunker::ChunkSample;
                using opennlp::tools::formats::ad::ADSentenceStream::Sentence;
                using opennlp::tools::formats::ad::ADSentenceStream::SentenceParser::Leaf;
                using opennlp::tools::formats::ad::ADSentenceStream::SentenceParser::Node;
                using opennlp::tools::formats::ad::ADSentenceStream::SentenceParser::TreeElement;
                using opennlp::tools::namefind::NameSample;
                using opennlp::tools::util::ObjectStream;
                using opennlp::tools::util::PlainTextByLineStream;

                /// <summary>
                /// Parser for Floresta Sita(c)tica Arvores Deitadas corpus, output to for the
                /// Portuguese Chunker training.
                /// <p>
                /// The heuristic to extract chunks where based o paper 'A Machine Learning
                /// Approach to Portuguese Clause Identification', (Eraldo Fernandes, Cicero
                /// Santos and Ruy Milidiú).<br>
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
                class ADChunkSampleStream : public ObjectStream<ChunkSample*>
                {

                private:
                    ObjectStream<ADSentenceStream::Sentence*> *const adSentenceStream;

                    int start;
                    int end;

                    int index;

                    /// <summary>
                    /// Creates a new <seealso cref="NameSample"/> stream from a line stream, i.e.
                    /// <seealso cref="ObjectStream"/>< <seealso cref="String"/>>, that could be a
                    /// <seealso cref="PlainTextByLineStream"/> object.
                    /// </summary>
                    /// <param name="lineStream">
                    ///          a stream of lines as <seealso cref="String"/> </param>
                public:
                    ADChunkSampleStream(ObjectStream<std::string> *lineStream);

                    /// <summary>
                    /// Creates a new <seealso cref="NameSample"/> stream from a <seealso cref="InputStream"/>
                    /// </summary>
                    /// <param name="in">
                    ///          the Corpus <seealso cref="InputStream"/> </param>
                    /// <param name="charsetName">
                    ///          the charset of the Arvores Deitadas Corpus </param>
                    ADChunkSampleStream(InputStream *in_Renamed, const std::string &charsetName);

                    virtual ChunkSample *read() throw(IOException);

                private:
                    void processRoot(Node *root, std::vector<std::string> &sentence, std::vector<std::string> &tags, std::vector<std::string> &target);

                    void processNode(Node *node, std::vector<std::string> &sentence, std::vector<std::string> &tags, std::vector<std::string> &target);

                    void processLeaf(Leaf *leaf, bool isIntermediate, const std::string &phraseTag, std::vector<std::string> &sentence, std::vector<std::string> &tags, std::vector<std::string> &target);

                    std::string getMorphologicalTag(const std::string &tag);

                    std::string getChunkTag(const std::string &tag);

                public:
                    virtual void setStart(int aStart);

                    virtual void setEnd(int aEnd);

                    virtual void reset() throw(IOException, UnsupportedOperationException);

                    virtual void close() throw(IOException);


                private:
                    void InitializeInstanceFields();
                };

            }
        }
    }
}


#endif	//#ifndef ADCHUNKSAMPLESTREAM
