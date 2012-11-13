#include "ADSentenceStream.h"
#include "StringBuffer.h"
#include "Exception.h"
#include "StringBuilder.h"
#include "S.h"

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

                std::string ADSentenceStream::Sentence::getText()
                {
                  return text;
                }

                void ADSentenceStream::Sentence::setText(const std::string &text)
                {
                  this->text = text;
                }

                opennlp::tools::formats::ad::ADSentenceStream::SentenceParser::Node *ADSentenceStream::Sentence::getRoot()
                {
                  return root;
                }

                void ADSentenceStream::Sentence::setRoot(Node *root)
                {
                  this->root = root;
                }

                void ADSentenceStream::Sentence::setMetadata(const std::string &metadata)
                {
                    this->metadata = metadata;
                }

                std::string ADSentenceStream::Sentence::getMetadata()
                {
                    return metadata;
                }

                ADSentenceStream::SentenceParser::TreeElement::TreeElement(ADSentenceStream::SentenceParser *outerInstance) : outerInstance(outerInstance)
                {
                }

                bool ADSentenceStream::SentenceParser::TreeElement::isLeaf()
                {
                    return false;
                }

                void ADSentenceStream::SentenceParser::TreeElement::setSyntacticTag(const std::string &syntacticTag)
                {
                  this->syntacticTag = syntacticTag;
                }

                std::string ADSentenceStream::SentenceParser::TreeElement::getSyntacticTag()
                {
                  return syntacticTag;
                }

                void ADSentenceStream::SentenceParser::TreeElement::setLevel(int level)
                {
                  this->level = level;
                }

                int ADSentenceStream::SentenceParser::TreeElement::getLevel()
                {
                  return level;
                }

                void ADSentenceStream::SentenceParser::TreeElement::setMorphologicalTag(const std::string &morphologicalTag)
                {
                  this->morphologicalTag = morphologicalTag;
                }

                std::string ADSentenceStream::SentenceParser::TreeElement::getMorphologicalTag()
                {
                  return morphologicalTag;
                }

                internal *ADSentenceStream::SentenceParser::Node::Node(ADSentenceStream::SentenceParser *outerInstance) : outerInstance(outerInstance)
                {
                    InitializeInstanceFields();
                }

                void ADSentenceStream::SentenceParser::Node::addElement(TreeElement *element)
                {
                  elems.push_back(element);
                }

                TreeElement *ADSentenceStream::SentenceParser::Node::getElements()
                {
                  return elems.toArray(new TreeElement[elems.size()]);
                }

                std::string ADSentenceStream::SentenceParser::Node::ToString()
                {
                  StringBuffer *sb = new StringBuffer();
                  // print itself and its children
                  for (int i = 0; i < this->getLevel(); i++)
                  {
                    sb->append("=");
                  }
                  sb->append(this->getSyntacticTag());
                  if (this->getMorphologicalTag() != "")
                  {
                    sb->append(this->getMorphologicalTag());
                  }
                  sb->append("\n");
                  for (std::vector<TreeElement*>::const_iterator element = elems.begin(); element != elems.end(); ++element)
                  {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                    sb->append((*element)->toString());
                  }
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                  return sb->toString();
                }

                void ADSentenceStream::SentenceParser::Node::InitializeInstanceFields()
                {
                    elems = std::vector<TreeElement*>();
                }

                ADSentenceStream::SentenceParser::Leaf::Leaf(ADSentenceStream::SentenceParser *outerInstance) : outerInstance(outerInstance)
                {
                }

                bool ADSentenceStream::SentenceParser::Leaf::isLeaf()
                {
                    return true;
                }

                void ADSentenceStream::SentenceParser::Leaf::setLexeme(const std::string &lexeme)
                {
                  this->word = lexeme;
                }

                std::string ADSentenceStream::SentenceParser::Leaf::getLexeme()
                {
                  return word;
                }

                std::string ADSentenceStream::SentenceParser::Leaf::ToString()
                {
                  StringBuffer *sb = new StringBuffer();
                  // print itself and its children
                  for (int i = 0; i < this->getLevel(); i++)
                  {
                    sb->append("=");
                  }
                  if (this->getSyntacticTag() != "")
                  {
                    sb->append(this->getSyntacticTag() + "(" + this->getMorphologicalTag() + ") ");
                  }
                  sb->append(this->word + "\n");
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                  return sb->toString();
                }

                void ADSentenceStream::SentenceParser::Leaf::setLemma(const std::string &lemma)
                {
                  this->lemma = lemma;
                }

                std::string ADSentenceStream::SentenceParser::Leaf::getLemma()
                {
                  return lemma;
                }

                opennlp::tools::formats::ad::ADSentenceStream::Sentence *ADSentenceStream::SentenceParser::parse(const std::string &sentenceString, int para, bool isTitle, bool isBox)
                {
                  BufferedReader *reader = new BufferedReader(new StringReader(sentenceString));
                  Sentence *sentence = new Sentence();
                  Node *root = new Node();
                  try
                  {
                    // first line is <s ...>
                    std::string line = reader->readLine();

                    bool useSameTextAndMeta = false; // to handle cases where there are diff sug of parse (&&)

                      // should find the source source
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'startsWith' method:
                      while (!line.startsWith("SOURCE"))
                      {
                          if (line == "&&")
                          {
                              // same sentence again!
                              useSameTextAndMeta = true;
                              break;
                          }
                        line = reader->readLine();
                        if (line == "")
                        {
                          return 0;
                        }
                      }
                    if (!useSameTextAndMeta)
                    {
                        // got source, get the metadata
                        std::string metaFromSource = line.substr(7);
                        line = reader->readLine();
                        // we should have the plain sentence
                        // we remove the first token
                        int start = line.find(" ");
                        text = line.substr(start + 1);
                        std::string titleTag = "";
                        if (isTitle)
                            titleTag = " title";
                        std::string boxTag = "";
                        if (isBox)
                            boxTag = " box";
                        meta = line.substr(0, start) + " p=" + para + titleTag + boxTag + metaFromSource;
                    }
                    sentence->setText(text);
                    sentence->setMetadata(meta);
                    // now we look for the root node
                    line = reader->readLine();

                    while (!rootPattern->matcher(line)->matches())
                    {
                      line = reader->readLine();
                      if (line == "")
                      {
                        return 0;
                      }
                    }
                    // got the root. Add it to the stack
                    std::stack<Node*> nodeStack = std::stack<Node*>();
                    // we get the complete line

                    root->setSyntacticTag(line);
                    root->setLevel(0);
                    nodeStack.add(root);
                    // now we have to take care of the lastLevel. Every time it raises, we
                    // will add the
                    // leaf to the node at the top. If it decreases, we remove the top.
                    line = reader->readLine();
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'startsWith' method:
                    while (line != "" && line.length() != 0 && line.startsWith("</s>") == false && line != "&&")
                    {
                      TreeElement *element = this->getElement(line);

                      if (element != 0)
                      {
                        // remove elements at same level or higher
                        while (!nodeStack.empty() && element->getLevel() > 0 && element->getLevel() <= nodeStack.top()->getLevel())
                        {
                          nodeStack.pop();
                        }
                        if (element->isLeaf())
                        {
                          if (nodeStack.empty())
                          {
                            root->addElement(element);
                          }
                                      else
                                      {
                                          // look for the node with the correct level
                                          Node *peek = nodeStack.top();
                                          if (element->level == 0) // add to the root
                                          {
                                              nodeStack.firstElement()->addElement(element);
                                          }
                                          else
                                          {
                                              Node *parent = 0;
                                              int index = nodeStack.size() - 1;
                                              while (parent == 0)
                                              {
                                                  if (peek->getLevel() < element->getLevel())
                                                  {
                                                      parent = peek;
                                                  }
                                                  else
                                                  {
                                                      index--;
                                                      if (index > -1)
                                                      {
                                                          peek = nodeStack.get(index);
                                                      }
                                                      else
                                                      {
                                                          parent = nodeStack.firstElement();
                                                      }
                                                  }
                                              }
                                              parent->addElement(element);
                                          }
                                      }
                        }
                        else
                        {
                          if (!nodeStack.empty())
                          {
                            nodeStack.top()->addElement(element);
                          }
                          nodeStack.push(static_cast<Node*>(element));
                        }
                      }
                      line = reader->readLine();
                    }

                  }
                  catch (Exception e)
                  {
                    System::err::println(sentenceString);
                    e->printStackTrace();
                    return sentence;
                  }
                  // second line should be SOURCE
                  sentence->setRoot(root);
                  return sentence;
                }

                opennlp::tools::formats::ad::ADSentenceStream::SentenceParser::TreeElement *ADSentenceStream::SentenceParser::getElement(const std::string &line)
                {
                  // try node
                  Matcher *nodeMatcher = nodePattern->matcher(line);
                  if (nodeMatcher->matches())
                  {
                    int level = nodeMatcher->group(1)->length();
                    std::string syntacticTag = nodeMatcher->group(2);
                    std::string morphologicalTag = nodeMatcher->group(3);
                    Node *node = new Node();
                    node->setLevel(level);
                    node->setSyntacticTag(syntacticTag);
                    node->setMorphologicalTag(morphologicalTag);
                    return node;
                  }

                  Matcher *leafMatcher = leafPattern->matcher(line);
                  if (leafMatcher->matches())
                  {
                    int level = leafMatcher->group(1)->length();
                    std::string syntacticTag = leafMatcher->group(2);
                    std::string lemma = leafMatcher->group(3);
                    std::string morphologicalTag = leafMatcher->group(4);
                    std::string lexeme = leafMatcher->group(5);
                    Leaf *leaf = new Leaf(this);
                    leaf->setLevel(level);
                    leaf->setSyntacticTag(syntacticTag);
                    leaf->setMorphologicalTag(morphologicalTag);
                    leaf->setLexeme(lexeme);
                    if (lemma != "")
                    {
                      if (lemma.length() > 2)
                      {
                        lemma = lemma.substr(1, lemma.length() - 1 - 1);
                      }
                      leaf->setLemma(lemma);
                    }

                    return leaf;
                  }

                  Matcher *punctuationMatcher = punctuationPattern->matcher(line);
                  if (punctuationMatcher->matches())
                  {
                    int level = punctuationMatcher->group(1)->length();
                    std::string lexeme = punctuationMatcher->group(2);
                    Leaf *leaf = new Leaf(this);
                    leaf->setLevel(level);
                    leaf->setLexeme(lexeme);
                    return leaf;
                  }

                  // process the bizarre cases
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'startsWith' method:
                  if (line == "_" || line.startsWith("<lixo") || line.startsWith("pause"))
                  {
                      return 0;
                  }

//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'startsWith' method:
                  if (line.startsWith("="))
                  {
                      Matcher *bizarreLeafMatcher = bizarreLeafPattern->matcher(line);
                    if (bizarreLeafMatcher->matches())
                    {
                      int level = bizarreLeafMatcher->group(1)->length();
                      std::string syntacticTag = bizarreLeafMatcher->group(2);
                      std::string lemma = bizarreLeafMatcher->group(3);
                      std::string morphologicalTag = bizarreLeafMatcher->group(4);
                      std::string lexeme = bizarreLeafMatcher->group(5);
                      Leaf *leaf = new Leaf(this);
                      leaf->setLevel(level);
                      leaf->setSyntacticTag(syntacticTag);
                      leaf->setMorphologicalTag(morphologicalTag);
                      leaf->setLexeme(lexeme);
                      if (lemma != "")
                      {
                        if (lemma.length() > 2)
                        {
                          lemma = lemma.substr(1, lemma.length() - 1 - 1);
                        }
                        leaf->setLemma(lemma);
                      }

                      return leaf;
                    }
                    else
                    {
                        int level = line.rfind("=");
                        std::string lexeme = line.substr(level + 1);

                         Leaf *leaf = new Leaf(this);
                       leaf->setLevel(level + 1);
                       leaf->setSyntacticTag("");
                       leaf->setMorphologicalTag("");
                       leaf->setLexeme(lexeme);

                       return leaf;
                    }
                  }

                  System::err::println("Couldn't parse leaf: " + line);
                  Leaf *leaf = new Leaf(this);
                  leaf->setLevel(0);
                  leaf->setSyntacticTag("");
                  leaf->setMorphologicalTag("");
                  leaf->setLexeme(line);

                  return leaf;
                }

                void ADSentenceStream::SentenceParser::InitializeInstanceFields()
                {
                    rootPattern = java::util::regex::Pattern::compile("^A\\d+$");
                    nodePattern = java::util::regex::Pattern::compile("^([=-]*)([^:=]+:[^\\(\\s]+)(\\(([^\\)]+)\\))?\\s*$");
                    leafPattern = java::util::regex::Pattern::compile("^([=-]*)([^:=]+:[^\\(\\s]+)\\(([\"'].+[\"'])?\\s*([^\\)]+)?\\)\\s+(.+)");
                    bizarreLeafPattern = java::util::regex::Pattern::compile("^([=-]*)([^:=]+=[^\\(\\s]+)\\(([\"'].+[\"'])?\\s*([^\\)]+)?\\)\\s+(.+)");
                    punctuationPattern = java::util::regex::Pattern::compile("^(=*)(\\W+)$");
                }

java::util::regex::Pattern *const ADSentenceStream::sentStart = java::util::regex::Pattern::compile("<s[^>]*>");
java::util::regex::Pattern *const ADSentenceStream::sentEnd = java::util::regex::Pattern::compile("</s>");
java::util::regex::Pattern *const ADSentenceStream::titleStart = java::util::regex::Pattern::compile("<t[^>]*>");
java::util::regex::Pattern *const ADSentenceStream::titleEnd = java::util::regex::Pattern::compile("</t>");
java::util::regex::Pattern *const ADSentenceStream::boxStart = java::util::regex::Pattern::compile("<caixa[^>]*>");
java::util::regex::Pattern *const ADSentenceStream::boxEnd = java::util::regex::Pattern::compile("</caixa>");
java::util::regex::Pattern *const ADSentenceStream::paraStart = java::util::regex::Pattern::compile("<p[^>]*>");
java::util::regex::Pattern *const ADSentenceStream::textStart = java::util::regex::Pattern::compile("<ext[^>]*>");

                ADSentenceStream::ADSentenceStream(ObjectStream<std::string> *lineStream) : opennlp.tools.util.FilterObjectStream<String, ADSentenceStream.Sentence>(lineStream)
                {
                  InitializeInstanceFields();
                  parser = new SentenceParser();
                }

                opennlp::tools::formats::ad::ADSentenceStream::Sentence *ADSentenceStream::read() throw(IOException)
                {

                  StringBuilder *sentence = new StringBuilder();
                  bool sentenceStarted = false;

                  while (true)
                  {
                    std::string line = samples->read();

                    if (line != "")
                    {

                        if (sentenceStarted)
                        {
                            if (sentEnd->matcher(line)->matches())
                            {
                                sentenceStarted = false;
                            }
                            else
                            {
                                sentence->append(line)->append('\n');
                            }
                        }
                        else
                        {
                            if (sentStart->matcher(line)->matches())
                            {
                                sentenceStarted = true;
                            }
                              else if (paraStart->matcher(line)->matches())
                              {
                                  paraID++;
                              }
                              else if (titleStart->matcher(line)->matches())
                              {
                                  isTitle = true;
                              }
                              else if (titleEnd->matcher(line)->matches())
                              {
                                  isTitle = false;
                              }
                              else if (textStart->matcher(line)->matches())
                              {
                                  paraID = 0;
                              }
                              else if (boxStart->matcher(line)->matches())
                              {
                                  isBox = true;
                              }
                              else if (boxEnd->matcher(line)->matches())
                              {
                                  isBox = false;
                              }
                        }


                      if (!sentenceStarted && sentence->length() > 0)
                      {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                        return parser->parse(sentence->toString(), paraID, isTitle, isBox);
                      }

                    }
                    else
                    {
                      // handle end of file
                      if (sentenceStarted)
                      {
                        if (sentence->length() > 0)
                        {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                          return parser->parse(sentence->toString(), paraID, isTitle, isBox);
                        }
                      }
                      else
                      {
                        return 0;
                      }
                    }
                  }
                }

                void ADSentenceStream::InitializeInstanceFields()
                {
                    paraID = 0;
                    isTitle = false;
                    isBox = false;
                }
            }
        }
    }
}
