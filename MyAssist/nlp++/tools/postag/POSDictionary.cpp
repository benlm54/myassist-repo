#include "POSDictionary.h"
#include "tools/util/StringUtil.h"
#include "tools/dictionary/serializer/DictionarySerializer.h"
#include "tools/dictionary/serializer/Attributes.h"
#include "tools/util/StringList.h"
#include "StringBuilder.h"

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

            POSDictionary::POSDictionary()
            {
              InitializeInstanceFields();
              dictionary = std::map<std::string, std::string[]>();
            }

            POSDictionary::POSDictionary(const std::string &file) throw(IOException)
            {
              InitializeInstanceFields();
            }

            POSDictionary::POSDictionary(const std::string &file, bool caseSensitive) throw(IOException)
            {
              InitializeInstanceFields();
            }

            POSDictionary::POSDictionary(const std::string &file, const std::string &encoding, bool caseSensitive) throw(IOException)
            {
              InitializeInstanceFields();
            }

            POSDictionary::POSDictionary(BufferedReader *reader, bool caseSensitive) throw(IOException)
            {
              InitializeInstanceFields();
              dictionary = std::map<std::string, std::string[]>();
              this->caseSensitive = caseSensitive;
              for (std::string line = reader->readLine(); line != ""; line = reader->readLine())
              {
//ORIGINAL LINE: String[] parts = line.split(" ");
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'split' method:
                std::string *parts = line.split(" ");
                std::string tags[parts->length - 1];
                for (int ti = 0, tl = parts->length - 1; ti < tl; ti++)
                {
                  tags[ti] = parts[ti + 1];
                }
                if (caseSensitive)
                {
                  dictionary->put(parts[0], tags);
                }
                else
                {
                  dictionary->put(StringUtil::toLowerCase(parts[0]), tags);
                }
              }
            }

            std::string *POSDictionary::getTags(const std::string &word)
            {
              if (caseSensitive)
              {
                return dictionary->get(word);
              }
              else
              {
                return dictionary->get(word.toLowerCase());
              }
            }

            void POSDictionary::addTags(const std::string &word, ...)
            {
              dictionary->put(word, tags);
            }

            Iterator<std::string> *POSDictionary::iterator()
            {
              return dictionary->keySet()->begin();
            }

            std::string POSDictionary::tagsToString(std::string tags[])
            {

              StringBuilder *tagString = new StringBuilder();

              for (int i = 0; i < sizeof(tags) / sizeof(tags[0]); i++)
              {
                tagString->append(tags[i]);
                tagString->append(' ');
              }

              // remove last space
              if (tagString->length() > 0)
              {
                tagString->setLength(tagString->length() - 1);
              }

//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              return tagString->toString();
            }

            void POSDictionary::serialize(OutputStream *out) throw(IOException)
            {
              Iterator<Entry*> entries = new IteratorAnonymousInnerClassHelper();

              DictionarySerializer::serialize(out, entries, caseSensitive);
            }

            bool POSDictionary::IteratorAnonymousInnerClassHelper::hasNext()
            {
              return iterator->hasNext();
            }

            opennlp::tools::dictionary::serializer::Entry *POSDictionary::IteratorAnonymousInnerClassHelper::next()
            {

              std::string word = iterator->next();

              Attributes *tagAttribute = new Attributes();
              tagAttribute->setValue("tags", tagsToString(outerInstance->getTags(word)));

              return new Entry(new StringList(word), tagAttribute);
            }

            void POSDictionary::IteratorAnonymousInnerClassHelper::remove()
            {
              throw UnsupportedOperationException();
            }

            bool POSDictionary::Equals(void *o)
            {

              if (o == this)
              {
                return true;
              }
              else if (dynamic_cast<POSDictionary*>(o) != 0)
              {
                POSDictionary *dictionary = static_cast<POSDictionary*>(o);

                if (this->dictionary->size() == dictionary->dictionary->size())
                {

                  for (unknown::const_iterator word = this->begin(); word != this->end(); ++word)
                  {

//ORIGINAL LINE: String aTags[] = getTags(word);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                    std::string *aTags = getTags(word);
//ORIGINAL LINE: String bTags[] = dictionary.getTags(word);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                    std::string *bTags = dictionary->getTags(word);

                    if (!Arrays::equals(aTags, bTags))
                    {
                      return false;
                    }
                  }

                  return true;
                }
              }

              return false;
            }

            std::string POSDictionary::ToString()
            {
              StringBuilder *dictionaryString = new StringBuilder();

              for (Map<std::string, std::string[]>::const_iterator word = dictionary->begin(); word != dictionary->end(); ++word)
              {
                dictionaryString->append(word->first + " -> " + tagsToString(getTags(word->first)));
                dictionaryString->append("\n");
              }

              // remove last new line
              if (dictionaryString->length() > 0)
              {
                dictionaryString->setLength(dictionaryString->length() - 1);
              }

//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              return dictionaryString->toString();
            }

            opennlp::tools::postag::POSDictionary *POSDictionary::create(InputStream *in_Renamed) throw(IOException, InvalidFormatException)
            {

              POSDictionary * const newPosDict = new POSDictionary();

              bool isCaseSensitive = DictionarySerializer::create(in_Renamed, new EntryInserterAnonymousInnerClassHelper();

              newPosDict->caseSensitive = isCaseSensitive;

              // TODO: The dictionary API needs to be improved to do this better!
              if (!isCaseSensitive)
              {
                Map<std::string, std::string[]> *lowerCasedDictionary = std::map<std::string, std::string[]>();

                for (unknown::const_iterator entry = newPosDict->dictionary->entrySet().begin(); entry != newPosDict->dictionary->entrySet().end(); ++entry)
                {
                  lowerCasedDictionary->put(StringUtil::toLowerCase(entry.getKey()), entry.getValue());
                }

                newPosDict->dictionary = lowerCasedDictionary;
              }

              return newPosDict;
            }

            void POSDictionary::EntryInserterAnonymousInnerClassHelper::insert(Entry *entry) throw(InvalidFormatException)
            {

              std::string tagString = entry->getAttributes()->getValue("tags");

//ORIGINAL LINE: String[] tags = tagString.split(" ");
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'split' method:
              std::string *tags = tagString.split(" ");

              StringList *word = entry->getTokens();

              if (word->size() != 1)
                throw InvalidFormatException("Each entry must have exactly one token! " + word);

              newPosDict::dictionary::put(word->getToken(0), tags);
            }

            void POSDictionary::InitializeInstanceFields()
            {
                caseSensitive = true;
            }
        }
    }
}
