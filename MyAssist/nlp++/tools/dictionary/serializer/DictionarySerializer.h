#ifndef DICTIONARYSERIALIZER
#define DICTIONARYSERIALIZER

#include "EntryInserter.h"
#include "Attributes.h"
#include "../tools/util/InvalidFormatException.h"
#include "Entry.h"
#include "ContentHandler.h"
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
#include <string>
#include <vector>
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

                /// <summary>
                /// This class is used by for reading and writing dictionaries of all kinds.
                /// </summary>
                class DictionarySerializer
                {

                  // TODO: should check for invalid format, make it save
              private:
                  class DictionaryContenthandler : public ContentHandler
                  {

                private:
                    EntryInserter *mInserter;

                //    private boolean mIsInsideDictionaryElement;
                //    private boolean mIsInsideEntryElement;
                    bool mIsInsideTokenElement;
                    bool mIsCaseSensitiveDictionary;

                    std::vector<std::string> mTokenList;

                    StringBuilder *token;

                    Attributes *mAttributes;

                    DictionaryContenthandler(EntryInserter *inserter);
                    /// <summary>
                    /// Not implemented.
                    /// </summary>
                 public:
                     virtual void processingInstruction(const std::string &target, const std::string &data) throw(SAXException);

                     /// <summary>
                     /// Not implemented.
                     /// </summary>
                     virtual void startDocument() throw(SAXException);

                     virtual void startElement(const std::string &uri, const std::string &localName, const std::string &qName, org::xml::sax::Attributes *atts) throw(SAXException);

                     virtual void characters(char ch[], int start, int length) throw(SAXException);

                     /// <summary>
                     /// Creates the Profile object after processing is complete
                     /// and switches mIsInsideNgramElement flag.
                     /// </summary>
                     virtual void endElement(const std::string &uri, const std::string &localName, const std::string &qName) throw(SAXException);

                     /// <summary>
                     /// Not implemented.
                     /// </summary>
                     virtual void endDocument() throw(SAXException);

                     /// <summary>
                     /// Not implemented.
                     /// </summary>
                     virtual void endPrefixMapping(const std::string &prefix) throw(SAXException);

                     /// <summary>
                     /// Not implemented.
                     /// </summary>
                     virtual void ignorableWhitespace(char ch[], int start, int length) throw(SAXException);

                     /// <summary>
                     /// Not implemented.
                     /// </summary>
                     virtual void setDocumentLocator(Locator *locator);

                     /// <summary>
                     /// Not implemented.
                     /// </summary>
                     virtual void skippedEntity(const std::string &name) throw(SAXException);

                     /// <summary>
                     /// Not implemented.
                     /// </summary>
                     virtual void startPrefixMapping(const std::string &prefix, const std::string &uri) throw(SAXException);

                  private:
                      void InitializeInstanceFields();
                  };

              private:
                  static const std::string CHARSET;

                  static const std::string DICTIONARY_ELEMENT;
                  static const std::string ENTRY_ELEMENT;
                  static const std::string TOKEN_ELEMENT;
                  static const std::string ATTRIBUTE_CASE_SENSITIVE;


                  /// <summary>
                  /// Creates <seealso cref="Entry"/>s form the given <seealso cref="InputStream"/> and
                  /// forwards these <seealso cref="Entry"/>s to the <seealso cref="EntryInserter"/>.
                  /// 
                  /// After creation is finished the provided <seealso cref="InputStream"/> is closed.
                  /// </summary>
                  /// <param name="in"> </param>
                  /// <param name="inserter">
                  /// </param>
                  /// <returns> isCaseSensitive attribute for Dictionary
                  /// </returns>
                  /// <exception cref="IOException"> </exception>
                  /// <exception cref="InvalidFormatException"> </exception>
              public:
                  static bool create(InputStream *in_Renamed, EntryInserter *inserter) throw(IOException, InvalidFormatException);

                  /// <summary>
                  /// Serializes the given entries to the given <seealso cref="OutputStream"/>.
                  /// 
                  /// After the serialization is finished the provided
                  /// <seealso cref="OutputStream"/> remains open.
                  /// </summary>
                  /// <param name="out"> </param>
                  /// <param name="entries">
                  /// </param>
                  /// <exception cref="IOException"> If an I/O error occurs </exception>
                  /// @deprecated Use {@link DictionarySerializer#serialize(java.io.OutputStream, java.util.Iterator, boolean) instead 
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated("Use {@link DictionarySerializer#serialize(java.io.OutputStream, java.util.Iterator, boolean) instead") public static void serialize(java.io.OutputStream out, java.util.Iterator<Entry> entries) throws java.io.IOException
                  static void serialize(OutputStream *out, Iterator<Entry*> *entries) throw(IOException);

                  /// <summary>
                  /// Serializes the given entries to the given <seealso cref="OutputStream"/>.
                  /// 
                  /// After the serialization is finished the provided
                  /// <seealso cref="OutputStream"/> remains open.
                  /// </summary>
                  /// <param name="out"> </param>
                  /// <param name="entries"> </param>
                  /// <param name="casesensitive"> indicates if the written dictionary 
                  ///        should be case sensitive or case insensitive.
                  /// </param>
                  /// <exception cref="IOException"> If an I/O error occurs </exception>
                  static void serialize(OutputStream *out, Iterator<Entry*> *entries, bool casesensitive) throw(IOException);

              private:
                  static void serializeEntry(TransformerHandler *hd, Entry *entry) throw(SAXException);
                };

            }
        }
    }
}


#endif	//#ifndef DICTIONARYSERIALIZER
