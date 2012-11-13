#include "Dictionary.h"
#include "tools/dictionary/serializer/DictionarySerializer.h"
#include "tools/dictionary/serializer/Attributes.h"

namespace opennlp
{
    namespace tools
    {
        namespace dictionary
        {
            using opennlp::tools::dictionary::serializer::Attributes;
            using opennlp::tools::dictionary::serializer::DictionarySerializer;
            using opennlp::tools::dictionary::serializer::Entry;
            using opennlp::tools::dictionary::serializer::EntryInserter;
            using opennlp::tools::util::InvalidFormatException;
            using opennlp::tools::util::StringList;

            Dictionary::StringListWrapper::StringListWrapper(Dictionary *outerInstance, StringList *stringList) : stringList(stringList), outerInstance(outerInstance)
            {
            }

            opennlp::tools::util::StringList *Dictionary::StringListWrapper::getStringList()
            {
              return stringList;
            }

            bool Dictionary::StringListWrapper::Equals(void *obj)
            {

              bool result;

              if (obj == this)
              {
                result = true;
              }
              else if (dynamic_cast<StringListWrapper*>(obj) != 0)
              {
                StringListWrapper *other = static_cast<StringListWrapper*>(obj);

                if (outerInstance->isCaseSensitive)
                {
                  result = this->stringList->equals(other->getStringList());
                }
                else
                {
                  result = this->stringList->compareToIgnoreCase(other->getStringList());
                }
              }
              else
              {
                result = false;
              }

              return result;
            }

            int Dictionary::StringListWrapper::GetHashCode()
            {
              // if lookup is too slow optimize this
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              return this->stringList->toString()->toLowerCase()->hashCode();
            }

            std::string Dictionary::StringListWrapper::ToString()
            {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              return this->stringList->toString();
            }

            Dictionary::Dictionary()
            {
              InitializeInstanceFields();
            }

            Dictionary::Dictionary(bool caseSensitive) : isCaseSensitive(caseSensitive)
            {
              InitializeInstanceFields();
            }

            Dictionary::Dictionary(InputStream *in_Renamed) throw(IOException, InvalidFormatException) : isCaseSensitive(DictionarySerializer::create(in_Renamed, new EntryInserter())
            {
              InitializeInstanceFields();
              {
                void insert(Entry entry)
                {
                  put(entry::getTokens());
                }
              });
            }

            /// <summary>
            /// Loads a Dictionary from a XML file.
            /// </summary>
            /// @deprecated This constructor is deprecated. Passing the case sensitivity
            ///             flag has no effect. Use
            ///             <seealso cref="Dictionary#Dictionary(InputStream)"/> instead and set the
            ///             case sensitivity during the dictionary creation.
            /// 
            /// <param name="in">
            ///          the dictionary in its XML format </param>
            /// <param name="caseSensitive">
            ///          has no effect </param>
            /// <exception cref="IOException"> </exception>
            /// <exception cref="InvalidFormatException"> </exception>
            Dictionary(InputStream in_Renamed, bool caseSensitive) throws IOException, InvalidFormatException
            {
              this(in_Renamed);
            }

            /// <summary>
            /// Adds the tokens to the dictionary as one new entry.
            /// </summary>
            /// <param name="tokens"> the new entry </param>
            void put(StringList tokens)
            {
                entrySet->add(new StringListWrapper(this, tokens));
            }

            /// <summary>
            /// Checks if this dictionary has the given entry.
            /// </summary>
            /// <param name="tokens">
            /// </param>
            /// <returns> true if it contains the entry otherwise false </returns>
            bool contains(StringList tokens)
            {
                return entrySet->contains(new StringListWrapper(this, tokens));
            }

            /// <summary>
            /// Removes the given tokens form the current instance.
            /// </summary>
            /// <param name="tokens"> </param>
            void remove(StringList tokens)
            {
                entrySet->remove(new StringListWrapper(this, tokens));
            }

            /// <summary>
            /// Retrieves an Iterator over all tokens.
            /// </summary>
            /// <returns> token-<seealso cref="Iterator"/> </returns>
            Iterator<StringList*> iterator()
            {
              const Set<StringListWrapper*>::const_iterator entries = entrySet->begin();

              return new IteratorAnonymousInnerClassHelper();
            }

            /// <summary>
            /// Retrieves the number of tokens in the current instance.
            /// </summary>
            /// <returns> number of tokens </returns>
            int size()
            {
              return entrySet->size();
            }

            /// <summary>
            /// Writes the current instance to the given <seealso cref="OutputStream"/>.
            /// </summary>
            /// <param name="out"> </param>
            /// <exception cref="IOException"> </exception>
            void serialize(OutputStream out) throws IOException
            {

              Iterator<Entry*> entryIterator = new IteratorAnonymousInnerClassHelper2();

              DictionarySerializer::serialize(out, entryIterator, isCaseSensitive);
            }

            bool equals(Object obj)
            {

              bool result;

              if (obj == this)
              {
                result = true;
              }
              else if (dynamic_cast<Dictionary*>(obj) != 0)
              {
                Dictionary *dictionary = static_cast<Dictionary*>(obj);

                result = entrySet->equals(dictionary->entrySet);
              }
              else
              {
                result = false;
              }

              return result;
            }

            int hashCode()
            {
              return entrySet->hashCode();
            }

            std::string toString()
            {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              return entrySet->toString();
            }

            /// <summary>
            /// Reads a dictionary which has one entry per line. The tokens inside an
            /// entry are whitespace delimited.
            /// </summary>
            /// <param name="in">
            /// </param>
            /// <returns> the parsed dictionary
            /// </returns>
            /// <exception cref="IOException"> </exception>
            static Dictionary parseOneEntryPerLine(Reader in_Renamed) throws IOException
            {
              BufferedReader *lineReader = new BufferedReader(in_Renamed);

              Dictionary *dictionary = new Dictionary();

              std::string line;

              while ((line = lineReader->readLine()) != "")
              {
                StringTokenizer *whiteSpaceTokenizer = new StringTokenizer(line, " ");

                std::string tokens[whiteSpaceTokenizer->countTokens()];

                if (sizeof(tokens) / sizeof(tokens[0]) > 0)
                {
                  int tokenIndex = 0;
                  while (whiteSpaceTokenizer->hasMoreTokens())
                  {
                    tokens[tokenIndex++] = whiteSpaceTokenizer->nextToken();
                  }

                  dictionary->put(new StringList(tokens));
                }
              }

              return dictionary;
            }

            /// <summary>
            /// Gets this dictionary as a {@code Set<String>}. Only {@code iterator()},
            /// {@code size()} and {@code contains(Object)} methods are implemented.
            /// 
            /// If this dictionary entries are multi tokens only the first token of the
            /// entry will be part of the Set.
            /// </summary>
            /// <returns> a Set containing the entries of this dictionary </returns>
            Set<std::string> asStringSet()
            {
              return new AbstractSetAnonymousInnerClassHelper();
            }
        }

            bool Dictionary::IteratorAnonymousInnerClassHelper::hasNext()
            {
              return entries->hasNext();
            }

            opennlp::tools::util::StringList *Dictionary::IteratorAnonymousInnerClassHelper::next()
            {
              return entries->next()->getStringList();
            }

            void Dictionary::IteratorAnonymousInnerClassHelper::remove()
            {
              entries->remove();
            }

            bool Dictionary::IteratorAnonymousInnerClassHelper2::hasNext()
            {
              return dictionaryIterator->hasNext();
            }

            opennlp::tools::dictionary::serializer::Entry *Dictionary::IteratorAnonymousInnerClassHelper2::next()
            {

              StringList *tokens = dictionaryIterator->next();

              return new Entry(tokens, new Attributes());
            }

            void Dictionary::IteratorAnonymousInnerClassHelper2::remove()
            {
              throw UnsupportedOperationException();
            }

            Iterator<std::string> *Dictionary::AbstractSetAnonymousInnerClassHelper::iterator()
            {
              const Iterator<StringListWrapper*> entries = outerInstance->entrySet->begin();

              return new IteratorAnonymousInnerClassHelper3();
            }

            bool Dictionary::AbstractSetAnonymousInnerClassHelper::IteratorAnonymousInnerClassHelper3::hasNext()
            {
              return entries->hasNext();
            }

            std::string Dictionary::AbstractSetAnonymousInnerClassHelper::IteratorAnonymousInnerClassHelper3::next()
            {
              return entries->next()->getStringList()->getToken(0);
            }

            void Dictionary::AbstractSetAnonymousInnerClassHelper::IteratorAnonymousInnerClassHelper3::remove()
            {
              throw UnsupportedOperationException();
            }

            int Dictionary::AbstractSetAnonymousInnerClassHelper::size()
            {
              return outerInstance->entrySet->size();
            }

            bool Dictionary::AbstractSetAnonymousInnerClassHelper::contains(void *obj)
            {
              bool result = false;

              if (dynamic_cast<std::string>(obj) != 0)
              {
                std::string str = static_cast<std::string>(obj);

                result = outerInstance->entrySet->contains(new StringListWrapper(new StringList(str)));

              }

              return result;
            }
    }
}
}
