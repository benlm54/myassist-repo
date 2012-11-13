#include "ADNameSampleStream.h"
#include "tools/formats/ad/PortugueseContractionUtility.h"
#include "const_iterator.h"

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
java::util::regex::Pattern *const ADNameSampleStream::tagPattern = java::util::regex::Pattern::compile("<(NER:)?(.*?)>");
java::util::Map<std::string, std::string> *const ADNameSampleStream::HAREM = 0;

                ADNameSampleStream::ADNameSampleStream()
                {
                  Map<std::string, std::string> *harem = std::map<std::string, std::string>();

                  const std::string person = "person";
                  harem->put("hum", person);
                  harem->put("official", person);
                  harem->put("member", person);

                  const std::string organization = "organization";
                  harem->put("admin", organization);
                  harem->put("org", organization);
                  harem->put("inst", organization);
                  harem->put("media", organization);
                  harem->put("party", organization);
                  harem->put("suborg", organization);

                  const std::string group = "group";
                  harem->put("groupind", group);
                  harem->put("groupofficial", group);

                  const std::string place = "place";
                  harem->put("top", place);
                  harem->put("civ", place);
                  harem->put("address", place);
                  harem->put("site", place);
                  harem->put("virtual", place);
                  harem->put("astro", place);

                  const std::string event_Renamed = "event";
                  harem->put("occ", event_Renamed);
                  harem->put("event", event_Renamed);
                  harem->put("history", event_Renamed);

                  const std::string artprod = "artprod";
                  harem->put("tit", artprod);
                  harem->put("pub", artprod);
                  harem->put("product", artprod);
                  harem->put("V", artprod);
                  harem->put("artwork", artprod);

                  const std::string _abstract = "abstract";
                  harem->put("brand", _abstract);
                  harem->put("genre", _abstract);
                  harem->put("school", _abstract);
                  harem->put("idea", _abstract);
                  harem->put("plan", _abstract);
                  harem->put("author", _abstract);
                  harem->put("absname", _abstract);
                  harem->put("disease", _abstract);

                  const std::string thing = "thing";
                  harem->put("object", thing);
                  harem->put("common", thing);
                  harem->put("mat", thing);
                  harem->put("class", thing);
                  harem->put("plant", thing);
                  harem->put("currency", thing);

                  const std::string time = "time";
                  harem->put("date", time);
                  harem->put("hour", time);
                  harem->put("period", time);
                  harem->put("cyclic", time);

                  const std::string numeric = "numeric";
                  harem->put("quantity", numeric);
                  harem->put("prednum", numeric);
                  harem->put("currency", numeric);

                  HAREM = Collections::unmodifiableMap(harem);
                }

                ADNameSampleStream::ADNameSampleStream(ObjectStream<std::string> *lineStream) : adSentenceStream(new ADSentenceStream(lineStream))
                {
                  InitializeInstanceFields();
                }

                ADNameSampleStream::ADNameSampleStream(InputStream *in_Renamed, const std::string &charsetName) : adSentenceStream(new ADSentenceStream(new PlainTextByLineStream(in_Renamed, charsetName)))
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

                opennlp::tools::namefind::NameSample *ADNameSampleStream::read() throw(IOException)
                {

                  Sentence *paragraph;
                  while ((paragraph = this->adSentenceStream->read()) != 0)
                  {
                    Node *root = paragraph->getRoot();
                    std::vector<std::string> sentence = std::vector<std::string>();
                    std::vector<Span*> names = std::vector<Span*>();
                    process(root, sentence, names);

                    return new NameSample(sentence.toArray(new std::string[sentence.size()]), names.toArray(new Span[names.size()]), true);
                  }
                  return 0;
                }

                void ADNameSampleStream::process(Node *node, std::vector<std::string> &sentence, std::vector<Span*> &names)
                {
                  if (node != 0)
                  {
                    for (TreeElement::const_iterator element = node->getElements()->begin(); element != node->getElements()->end(); ++element)
                    {
                      if (element->isLeaf())
                      {
                        processLeaf(static_cast<Leaf*>(element), sentence, names);
                      }
                      else
                      {
                        process(static_cast<Node*>(element), sentence, names);
                      }
                    }
                  }
                }

                void ADNameSampleStream::processLeaf(Leaf *leaf, std::vector<std::string> &sentence, std::vector<Span*> &names)
                {

                  if (leaf != 0 && leftContractionPart == "")
                  {

                    std::string namedEntityTag = "";
                    int startOfNamedEntity = -1;

                    std::string leafTag = leaf->getMorphologicalTag();
                    bool expandLastNER = false; // used when we find a <NER2> tag

                    if (leafTag != "")
                    {
                      if (leafTag.find("<sam->") != string::npos)
                      {
//ORIGINAL LINE: String[] lexemes = leaf.getLexeme().split("_");
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'split' method:
                        std::string *lexemes = leaf->getLexeme().split("_");
                        if (lexemes->length > 1)
                        {
                          for (int i = 0; i < lexemes->length - 1; i++)
                          {
                            sentence.push_back(lexemes[i]);
                          }
                        }
                        leftContractionPart = lexemes[lexemes->length - 1];
                        return;
                      }
                      if (leafTag.find("<NER2>") != string::npos)
                      {
                        // this one an be part of the last name
                        expandLastNER = true;
                      }
                      namedEntityTag = getNER(leafTag);
                    }

                    if (namedEntityTag != "")
                    {
                      startOfNamedEntity = sentence.size();
                    }

//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'split' method:
                    sentence.addAll(Arrays::asList(leaf->getLexeme().split("_")));

                    if (namedEntityTag != "")
                    {
                      names.push_back(new Span(startOfNamedEntity, sentence.size(), namedEntityTag));
                    }

                    if (expandLastNER)
                    {
                      // if the current leaf has the tag <NER2>, it can be the continuation of
                      // a NER.
                      // we check if it is true, and expand the lest NER
                      int lastIndex = names.size() - 1;
                      Span *last = 0;
                      bool error = false;
                      if (names.size() > 0)
                      {
                        last = names[lastIndex];
                        if (last->getEnd() == sentence.size() - 1)
                        {
                          names[lastIndex] = new Span(last->getStart(), sentence.size(), last->getType());
                        }
                        else
                        {
                          error = true;
                        }
                      }
                      else
                      {
                        error = true;
                      }
                      if (error)
                      {
                        // Maybe it is not the same NER, skip it.
                        // System.err.println("Missing NER start for sentence [" + sentence
                        // + "] node [" + leaf + "]");
                      }
                    }

                  }
                  else
                  {
                    // will handle the contraction
                    std::string tag = leaf->getMorphologicalTag();
                    std::string right = leaf->getLexeme();
                    if (tag != "" && tag.find("<-sam>") != string::npos)
                    {
                      right = leaf->getLexeme();
                      std::string c = PortugueseContractionUtility::toContraction(leftContractionPart, right);

                      if (c != "")
                      {
                        sentence.push_back(c);
                      }
                      else
                      {
                        System::err::println("missing " + leftContractionPart + " + " + right);
                        sentence.push_back(leftContractionPart);
                        sentence.push_back(right);
                      }

                    }
                    else
                    {
                      System::err::println("unmatch" + leftContractionPart + " + " + right);
                    }
                    leftContractionPart = "";
                  }

                }

                std::string ADNameSampleStream::getNER(const std::string &tags)
                {
//ORIGINAL LINE: String[] tag = tags.split("\\s+");
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'split' method:
                  std::string *tag = tags.split("\\s+");
                  for (std::string::const_iterator t = tag->begin(); t != tag->end(); ++t)
                  {
                    Matcher *matcher = tagPattern->matcher(*t);
                    if (matcher->matches())
                    {
                      std::string ner = matcher->group(2);
                      if (HAREM->containsKey(ner))
                      {
                        return HAREM->get(ner);
                      }
                    }
                  }
                  return 0;
                }

                void ADNameSampleStream::reset() throw(IOException, UnsupportedOperationException)
                {
                  adSentenceStream->reset();
                }

                void ADNameSampleStream::close() throw(IOException)
                {
                  adSentenceStream->close();
                }

                void ADNameSampleStream::InitializeInstanceFields()
                {
                    leftContractionPart = "";
                }
            }
        }
    }
}
