#include "DictionarySerializer.h"
#include "tools/util/StringList.h"
#include "tools/util/model/UncloseableInputStream.h"
#include "StringBuilder.h"
#include "Attributes.h"
#include "Locator.h"
#include "XMLReader.h"
#include "SAXException.h"
#include "StreamResult.h"
#include "SAXTransformerFactory.h"
#include "TransformerHandler.h"
#include "TransformerConfigurationException.h"
#include "Transformer.h"
#include "AttributesImpl.h"
#include "const_iterator.h"

namespace opennlp
{
    namespace tools
    {
        namespace dictionary
        {
            namespace serializer
            {
                using javax::xml::transform::OutputKeys;
                using javax::xml::transform::Transformer;
                using javax::xml::transform::TransformerConfigurationException;
                using javax::xml::transform::sax::SAXTransformerFactory;
                using javax::xml::transform::sax::TransformerHandler;
                using javax::xml::transform::stream::StreamResult;
                using opennlp::tools::util::InvalidFormatException;
                using opennlp::tools::util::StringList;
                using opennlp::tools::util::model::UncloseableInputStream;
                using org::xml::sax::ContentHandler;
                using org::xml::sax::InputSource;
                using org::xml::sax::Locator;
                using org::xml::sax::SAXException;
                using org::xml::sax::XMLReader;
                using org::xml::sax::helpers::AttributesImpl;
                using org::xml::sax::helpers::XMLReaderFactory;

                DictionarySerializer::DictionaryContenthandler::DictionaryContenthandler(EntryInserter *inserter)
                {
                  InitializeInstanceFields();
                  mInserter = inserter;
                  mIsCaseSensitiveDictionary = true;
                }

                void DictionarySerializer::DictionaryContenthandler::processingInstruction(const std::string &target, const std::string &data) throw(SAXException)
                {
                }

                void DictionarySerializer::DictionaryContenthandler::startDocument() throw(SAXException)
                {
                }

                void DictionarySerializer::DictionaryContenthandler::startElement(const std::string &uri, const std::string &localName, const std::string &qName, org::xml::sax::Attributes *atts) throw(SAXException)
                {
                  if (DICTIONARY_ELEMENT == localName)
                  {

                    mAttributes = new Attributes();

                    for (int i = 0; i < atts->getLength(); i++)
                    {
                      mAttributes->setValue(atts->getLocalName(i), atts->getValue(i));
                    }
                    /* get the attribute here ... */
                    if (mAttributes->getValue(ATTRIBUTE_CASE_SENSITIVE) != "")
                    {
                      mIsCaseSensitiveDictionary = StringConverterHelper::fromString<bool>(mAttributes->getValue(ATTRIBUTE_CASE_SENSITIVE));
                    }
//JAVA TO C++ CONVERTER WARNING: Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
                    delete mAttributes;
                  }
                  else if (ENTRY_ELEMENT == localName)
                  {

                    mAttributes = new Attributes();

                    for (int i = 0; i < atts->getLength(); i++)
                    {
                      mAttributes->setValue(atts->getLocalName(i), atts->getValue(i));
                    }
                  }
                  else if (TOKEN_ELEMENT == localName)
                  {
                    mIsInsideTokenElement = true;
                  }
                }

                void DictionarySerializer::DictionaryContenthandler::characters(char ch[], int start, int length) throw(SAXException)
                {
                  if (mIsInsideTokenElement)
                  {
                    token->append(ch, start, length);
                  }
                }

                void DictionarySerializer::DictionaryContenthandler::endElement(const std::string &uri, const std::string &localName, const std::string &qName) throw(SAXException)
                {

                  if (TOKEN_ELEMENT == localName)
                  {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'trim' method:
                    mTokenList.push_back(token->toString()->trim());
                    token->setLength(0);
                    mIsInsideTokenElement = false;
                  }
                  else if (ENTRY_ELEMENT == localName)
                  {

//ORIGINAL LINE: String[] tokens = mTokenList.toArray(new String[mTokenList.size()]);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                    std::string *tokens = mTokenList.toArray(new std::string[mTokenList.size()]);

                    Entry *entry = new Entry(new StringList(tokens), mAttributes);

                    try
                    {
                      mInserter->insert(entry);
                    }
                    catch (InvalidFormatException e)
                    {
                      throw SAXException("Invalid dictionary format!", e);
                    }

                    mTokenList.clear();
//JAVA TO C++ CONVERTER WARNING: Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
                    delete mAttributes;
                  }
                }

                void DictionarySerializer::DictionaryContenthandler::endDocument() throw(SAXException)
                {
                }

                void DictionarySerializer::DictionaryContenthandler::endPrefixMapping(const std::string &prefix) throw(SAXException)
                {
                }

                void DictionarySerializer::DictionaryContenthandler::ignorableWhitespace(char ch[], int start, int length) throw(SAXException)
                {
                }

                void DictionarySerializer::DictionaryContenthandler::setDocumentLocator(Locator *locator)
                {
                }

                void DictionarySerializer::DictionaryContenthandler::skippedEntity(const std::string &name) throw(SAXException)
                {
                }

                void DictionarySerializer::DictionaryContenthandler::startPrefixMapping(const std::string &prefix, const std::string &uri) throw(SAXException)
                {
                }

                void DictionarySerializer::DictionaryContenthandler::InitializeInstanceFields()
                {
                    mTokenList = std::list<std::string>();
                    token = new StringBuilder();
                }

const std::string DictionarySerializer::CHARSET = "UTF-8";
const std::string DictionarySerializer::DICTIONARY_ELEMENT = "dictionary";
const std::string DictionarySerializer::ENTRY_ELEMENT = "entry";
const std::string DictionarySerializer::TOKEN_ELEMENT = "token";
const std::string DictionarySerializer::ATTRIBUTE_CASE_SENSITIVE = "case_sensitive";

                bool DictionarySerializer::create(InputStream *in_Renamed, EntryInserter *inserter) throw(IOException, InvalidFormatException)
                {

                  DictionaryContenthandler *profileContentHandler = new DictionaryContenthandler(inserter);

                  XMLReader *xmlReader;
                  try
                  {
                    xmlReader = XMLReaderFactory::createXMLReader();
                    xmlReader->setContentHandler(profileContentHandler);
                    xmlReader->parse(new InputSource(new UncloseableInputStream(in_Renamed)));
                  }
                  catch (SAXException e)
                  {
                    throw InvalidFormatException("The profile data stream has " + "an invalid format!", e);
                  }
                  return profileContentHandler->mIsCaseSensitiveDictionary;
                }

                void DictionarySerializer::serialize(OutputStream *out, Iterator<Entry*> *entries) throw(IOException)
                {
                    DictionarySerializer::serialize(out, entries, true);
                }

                void DictionarySerializer::serialize(OutputStream *out, Iterator<Entry*> *entries, bool casesensitive) throw(IOException)
                {
                  StreamResult *streamResult = new StreamResult(out);
                  SAXTransformerFactory *tf = static_cast<SAXTransformerFactory*>(SAXTransformerFactory::newInstance());

                  TransformerHandler *hd;
                  try
                  {
                    hd = tf->newTransformerHandler();
                  }
                  catch (TransformerConfigurationException e1)
                  {
                    throw AssertionError("The Tranformer configuration must be valid!");
                  }

                  Transformer *serializer = hd->getTransformer();
                  serializer->setOutputProperty(OutputKeys::ENCODING, CHARSET);
                  serializer->setOutputProperty(OutputKeys::INDENT, "yes");

                  hd->setResult(streamResult);


                  try
                  {
                    hd->startDocument();

                    AttributesImpl *dictionaryAttributes = new AttributesImpl();

                    dictionaryAttributes->addAttribute("", "", ATTRIBUTE_CASE_SENSITIVE, "", StringConverterHelper::toString(casesensitive));
                    hd->startElement("", "", DICTIONARY_ELEMENT, dictionaryAttributes);

                    while (entries->hasNext())
                    {
                      Entry *entry = entries->next();

                      serializeEntry(hd, entry);
                        entries++;
                    }

                    hd->endElement("", "", DICTIONARY_ELEMENT);

                    hd->endDocument();
                  }
                  catch (SAXException e)
                  {
                    throw IOException("There was an error during serialization!");
                  }
                }

                void DictionarySerializer::serializeEntry(TransformerHandler *hd, Entry *entry) throw(SAXException)
                {

                  AttributesImpl *entryAttributes = new AttributesImpl();

                  for (Iterator it = entry->getAttributes()->begin(); it->hasNext();)
                  {
                    std::string key = it->next();

                    entryAttributes->addAttribute("", "", key, "", entry->getAttributes()->getValue(key));
                  }

                  hd->startElement("", "", ENTRY_ELEMENT, entryAttributes);

                  StringList *tokens = entry->getTokens();

//JAVA TO C++ CONVERTER TODO TASK: Java iterators are only converted within the context of 'while' and 'for' loops:
                  for (StringList::const_iterator it = tokens->begin(); it->hasNext();)
                  {

                    hd->startElement("", "", TOKEN_ELEMENT, new AttributesImpl());

//JAVA TO C++ CONVERTER TODO TASK: Java iterators are only converted within the context of 'while' and 'for' loops:
                    std::string token = it->next();

                    hd->characters(token.toCharArray(), 0, token.length());

                    hd->endElement("", "", TOKEN_ELEMENT);
                  }

                  hd->endElement("", "", ENTRY_ELEMENT);
                }
            }
        }
    }
}
