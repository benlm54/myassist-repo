#include "ADChunkSampleStream.h"

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

                ADChunkSampleStream::ADChunkSampleStream(ObjectStream<std::string> *lineStream) : adSentenceStream(new ADSentenceStream(lineStream))
                {
                    InitializeInstanceFields();
                }

                ADChunkSampleStream::ADChunkSampleStream(InputStream *in_Renamed, const std::string &charsetName) : adSentenceStream(new ADSentenceStream(new PlainTextByLineStream(in_Renamed, charsetName)))
                {

                    InitializeInstanceFields();
                    try
                    {
                    }
                    catch (UnsupportedEncodingException e)
                    {
                        // UTF-8 is available on all JVMs, will never happen
                        throw IllegalStateException(e);
                    }
                }

                opennlp::tools::chunker::ChunkSample *ADChunkSampleStream::read() throw(IOException)
                {

                    Sentence *paragraph;
                    while ((paragraph = this->adSentenceStream->read()) != 0)
                    {

                        if (end > -1 && index >= end)
                        {
                            // leave
                            return 0;
                        }

                        if (start > -1 && index < start)
                        {
                            index++;
                            // skip this one
                        }
                        else
                        {
                            Node *root = paragraph->getRoot();
                            std::vector<std::string> sentence = std::vector<std::string>();
                            std::vector<std::string> tags = std::vector<std::string>();
                            std::vector<std::string> target = std::vector<std::string>();

                            processRoot(root, sentence, tags, target);

                            if (sentence.size() > 0)
                            {
                                index++;
                                return new ChunkSample(sentence, tags, target);
                            }

                        }

                    }
                    return 0;
                }

                void ADChunkSampleStream::processRoot(Node *root, std::vector<std::string> &sentence, std::vector<std::string> &tags, std::vector<std::string> &target)
                {
                    if (root != 0)
                    {
//ORIGINAL LINE: opennlp.tools.formats.ad.ADSentenceStream.SentenceParser.TreeElement[] elements = root.getElements();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                        TreeElement *elements = root->getElements();
                        for (int i = 0; i < elements->length; i++)
                        {
                            if (elements[i]->isLeaf())
                            {
                                processLeaf(static_cast<Leaf*>(elements[i]), false, "O", sentence, tags, target);
                            }
                            else
                            {
                                processNode(static_cast<Node*>(elements[i]), sentence, tags, target);
                            }
                        }
                    }
                }

                void ADChunkSampleStream::processNode(Node *node, std::vector<std::string> &sentence, std::vector<std::string> &tags, std::vector<std::string> &target)
                {
                    std::string phraseTag = getChunkTag(node->getSyntacticTag());

//ORIGINAL LINE: opennlp.tools.formats.ad.ADSentenceStream.SentenceParser.TreeElement[] elements = node.getElements();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                    TreeElement *elements = node->getElements();
                    for (int i = 0; i < elements->length; i++)
                    {
                        if (elements[i]->isLeaf())
                        {
                            bool isIntermediate = false;
                            if (i > 0 && elements[i - 1]->isLeaf() && phraseTag != "" && phraseTag != "O")
                            {
                                isIntermediate = true;
                            }
                            processLeaf(static_cast<Leaf*>(elements[i]), isIntermediate, phraseTag, sentence, tags, target);
                        }
                        else
                        {
                            processNode(static_cast<Node*>(elements[i]), sentence, tags, target);
                        }
                    }
                }

                void ADChunkSampleStream::processLeaf(Leaf *leaf, bool isIntermediate, const std::string &phraseTag, std::vector<std::string> &sentence, std::vector<std::string> &tags, std::vector<std::string> &target)
                {
                    std::string chunkTag;



                    if (leaf->getSyntacticTag() != "" && phraseTag == "O")
                    {
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'endsWith' method:
                        if (leaf->getSyntacticTag().endsWith("v-fin"))
                        {
                            phraseTag = "VP";
                        }
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'endsWith' method:
                        else if (leaf->getSyntacticTag().endsWith(":n"))
                        {
                            phraseTag = "NP";
                        }
                    }

                    if (phraseTag != "O")
                    {
                        if (isIntermediate)
                        {
                            chunkTag = "I-" + phraseTag;
                        }
                        else
                        {
                            chunkTag = "B-" + phraseTag;
                        }
                    }
                    else
                    {
                        chunkTag = phraseTag;
                    }

                    sentence.push_back(leaf->getLexeme());
                    if (leaf->getSyntacticTag() == "")
                    {
                        tags.push_back(leaf->getLexeme());
                    }
                    else
                    {
                        tags.push_back(getMorphologicalTag(leaf->getSyntacticTag()));
                    }
                    target.push_back(chunkTag);
                }

                std::string ADChunkSampleStream::getMorphologicalTag(const std::string &tag)
                {
                    return tag.substr(tag.rfind(":") + 1);
                }

                std::string ADChunkSampleStream::getChunkTag(const std::string &tag)
                {

                    std::string phraseTag = tag.substr(tag.rfind(":") + 1);

                    // maybe we should use only np, vp and pp, but will keep ap and advp.
                if (phraseTag == "np" || phraseTag == "vp" || phraseTag == "pp" || phraseTag == "ap" || phraseTag == "advp")
                {
                  std::transform(phraseTag.begin(), phraseTag.end(), phraseTag.begin(), toupper);
                }
                else
                {
                  phraseTag = "O";
                }
                    return phraseTag;
                }

                void ADChunkSampleStream::setStart(int aStart)
                {
                    this->start = aStart;
                }

                void ADChunkSampleStream::setEnd(int aEnd)
                {
                    this->end = aEnd;
                }

                void ADChunkSampleStream::reset() throw(IOException, UnsupportedOperationException)
                {
                    adSentenceStream->reset();
                }

                void ADChunkSampleStream::close() throw(IOException)
                {
                    adSentenceStream->close();
                }

                void ADChunkSampleStream::InitializeInstanceFields()
                {
                    start = -1;
                    end = -1;
                    index = 0;
                }
            }
        }
    }
}
