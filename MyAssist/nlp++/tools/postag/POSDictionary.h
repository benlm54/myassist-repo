#ifndef POSDICTIONARY
#define POSDICTIONARY

#include "TagDictionary.h"
#include "../tools/dictionary/serializer/Entry.h"
#include "../tools/util/InvalidFormatException.h"
#include "../tools/dictionary/serializer/EntryInserter.h"
#include "Iterable<String>.h"
#include "StringBuilder.h"
#include <string>
#include <map>

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
        namespace postag
        {


            using opennlp::tools::dictionary::serializer::Attributes;
            using opennlp::tools::dictionary::serializer::DictionarySerializer;
            using opennlp::tools::dictionary::serializer::Entry;
            using opennlp::tools::dictionary::serializer::EntryInserter;
            using opennlp::tools::util::InvalidFormatException;
            using opennlp::tools::util::StringList;
            using opennlp::tools::util::StringUtil;

            /// <summary>
            /// Provides a means of determining which tags are valid for a particular word
            /// based on a tag dictionary read from a file.
            /// </summary>
            class POSDictionary : public Iterable<std::string>, public TagDictionary
            {

          private:
              Map<std::string, std::string[]> *dictionary;

              bool caseSensitive;

          public:
              POSDictionary();

              /// <summary>
              /// Creates a tag dictionary with contents of specified file.
              /// </summary>
              /// <param name="file"> The file name for the tag dictionary.
              /// </param>
              /// <exception cref="IOException"> when the specified file can not be read.
              /// </exception>
              /// @deprecated Use <seealso cref="POSDictionary#create(InputStream)"/> instead, old format might removed. 
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated("Use <seealso cref="POSDictionary#create(java.io.InputStream)"/> instead, old format might removed.") public POSDictionary(String file) throws java.io.IOException
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              POSDictionary(const std::string &file) throw(IOException); //this(file, nullptr, true);

              /// <summary>
              /// Creates a tag dictionary with contents of specified file and using specified
              /// case to determine how to access entries in the tag dictionary.
              /// </summary>
              /// <param name="file"> The file name for the tag dictionary. </param>
              /// <param name="caseSensitive"> Specifies whether the tag dictionary is case sensitive or not.
              /// </param>
              /// <exception cref="IOException"> when the specified file can not be read.
              /// </exception>
              /// @deprecated Use <seealso cref="POSDictionary#create(InputStream)"/> instead, old format might removed. 
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated("Use <seealso cref="POSDictionary#create(java.io.InputStream)"/> instead, old format might removed.") public POSDictionary(String file, boolean caseSensitive) throws java.io.IOException
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              POSDictionary(const std::string &file, bool caseSensitive) throw(IOException); //this(file, nullptr, caseSensitive);


              /// <summary>
              /// Creates a tag dictionary with contents of specified file and using specified case to determine how to access entries in the tag dictionary.
              /// </summary>
              /// <param name="file"> The file name for the tag dictionary. </param>
              /// <param name="encoding"> The encoding of the tag dictionary file. </param>
              /// <param name="caseSensitive"> Specifies whether the tag dictionary is case sensitive or not.
              /// </param>
              /// <exception cref="IOException"> when the specified file can not be read.
              /// </exception>
              /// @deprecated Use <seealso cref="POSDictionary#create(InputStream)"/> instead, old format might removed. 
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated("Use <seealso cref="POSDictionary#create(java.io.InputStream)"/> instead, old format might removed.") public POSDictionary(String file, String encoding, boolean caseSensitive) throws java.io.IOException
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              POSDictionary(const std::string &file, const std::string &encoding, bool caseSensitive) throw(IOException); //this(new BufferedReader(encoding == nullptr ? new FileReader(file) : new InputStreamReader(new FileInputStream(file),encoding)), caseSensitive);

              /// <summary>
              /// Create tag dictionary object with contents of specified file and using specified case to determine how to access entries in the tag dictionary.
              /// </summary>
              /// <param name="reader"> A reader for the tag dictionary. </param>
              /// <param name="caseSensitive"> Specifies whether the tag dictionary is case sensitive or not.
              /// </param>
              /// <exception cref="IOException"> when the specified file can not be read.
              /// </exception>
              /// @deprecated Use <seealso cref="POSDictionary#create(InputStream)"/> instead, old format might removed. 
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated("Use <seealso cref="POSDictionary#create(java.io.InputStream)"/> instead, old format might removed.") public POSDictionary(java.io.BufferedReader reader, boolean caseSensitive) throws java.io.IOException
              POSDictionary(BufferedReader *reader, bool caseSensitive) throw(IOException);

              /// <summary>
              /// Returns a list of valid tags for the specified word.
              /// </summary>
              /// <param name="word"> The word.
              /// </param>
              /// <returns> A list of valid tags for the specified word or
              /// null if no information is available for that word. </returns>
              virtual std::string *getTags(const std::string &word);

              /// <summary>
              /// Adds the tags for the word.
              /// </summary>
              /// <param name="word"> The word to be added to the dictionary. </param>
              /// <param name="tags"> The set of tags associated with the specified word. </param>
//ORIGINAL LINE: void addTags(String word, String... tags)
//JAVA TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
              virtual void addTags(const std::string &word, ...);

              /// <summary>
              /// Retrieves an iterator over all words in the dictionary.
              /// </summary>
              virtual Iterator<std::string> *iterator();

          private:
              static std::string tagsToString(std::string tags[]);

              /// <summary>
              /// Writes the <seealso cref="POSDictionary"/> to the given <seealso cref="OutputStream"/>;
              /// 
              /// After the serialization is finished the provided
              /// <seealso cref="OutputStream"/> remains open.
              /// </summary>
              /// <param name="out">
              ///            the <seealso cref="OutputStream"/> to write the dictionary into.
              /// </param>
              /// <exception cref="IOException">
              ///             if writing to the <seealso cref="OutputStream"/> fails </exception>
          public:
              virtual void serialize(OutputStream *out) throw(IOException);

                    private:
                        class IteratorAnonymousInnerClassHelper : public Iterator<Entry*>
                        {

                        public:
                            Iterator<std::string> *iterator;

                            virtual bool hasNext();

                            virtual Entry *next();

                            virtual void remove();
                        };

          public:
              virtual bool Equals(void *o);

              virtual std::string ToString();

              /// <summary>
              /// Creates a new <seealso cref="POSDictionary"/> from a provided <seealso cref="InputStream"/>.
              /// 
              /// After creation is finished the provided <seealso cref="InputStream"/> is closed.
              /// </summary>
              /// <param name="in">
              /// </param>
              /// <returns> the pos dictionary
              /// </returns>
              /// <exception cref="IOException"> </exception>
              /// <exception cref="InvalidFormatException"> </exception>
              static POSDictionary *create(InputStream *in_Renamed) throw(IOException, InvalidFormatException);

                    private:
                        class EntryInserterAnonymousInnerClassHelper : public EntryInserter
                        {
                        public:
                            virtual void insert(Entry *entry) throw(InvalidFormatException);
                        };

            private:
                void InitializeInstanceFields();
            };

        }
    }
}


#endif	//#ifndef POSDICTIONARY
