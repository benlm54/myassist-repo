#include "NGramModel.h"
#include "tools/dictionary/serializer/DictionarySerializer.h"
#include "tools/dictionary/serializer/Attributes.h"
#include "NumberFormatException.h"

namespace opennlp
{
    namespace tools
    {
        namespace ngram
        {
            using opennlp::tools::dictionary::Dictionary;
            using opennlp::tools::dictionary::serializer::Attributes;
            using opennlp::tools::dictionary::serializer::DictionarySerializer;
            using opennlp::tools::dictionary::serializer::Entry;
            using opennlp::tools::dictionary::serializer::EntryInserter;
            using opennlp::tools::util::InvalidFormatException;
            using opennlp::tools::util::StringList;
const std::string NGramModel::COUNT = "count";

            NGramModel::NGramModel()
            {
                InitializeInstanceFields();
            }

            NGramModel::NGramModel(InputStream *in_Renamed) throw(IOException, InvalidFormatException)
            {
              InitializeInstanceFields();
              DictionarySerializer::create(in_Renamed, new EntryInserterAnonymousInnerClassHelper();
            }

            void NGramModel::EntryInserterAnonymousInnerClassHelper::insert(Entry *entry) throw(InvalidFormatException)
            {

              int count;

              try
              {
                std::string countValueString = entry->getAttributes()->getValue(COUNT);

                if (countValueString == "")
                {
                    throw InvalidFormatException("The count attribute must be set!");
                }

                count = StringConverterHelper::fromString<int>(countValueString);
              }
              catch (NumberFormatException e)
              {
                throw InvalidFormatException("The count attribute must be a nubmer!");
              }

              outerInstance->add(entry->getTokens());
              outerInstance->setCount(entry->getTokens(), count);
            }

            int NGramModel::getCount(StringList *ngram)
            {

              int count = mNGrams->get(ngram);

              if (count == 0)
              {
                return 0;
              }

              return count;
            }

            void NGramModel::setCount(StringList *ngram, int count)
            {

              int oldCount = mNGrams->put(ngram, count);

              if (oldCount == 0)
              {
                mNGrams->remove(ngram);
                throw NoSuchElementException();
              }
            }

            void NGramModel::add(StringList *ngram)
            {
              if (contains(ngram))
              {
                setCount(ngram, getCount(ngram) + 1);
              }
              else
              {
                mNGrams->put(ngram, 1);
              }
            }

            void NGramModel::add(StringList *ngram, int minLength, int maxLength)
            {

              if (minLength < 1 || maxLength < 1)
                  throw IllegalArgumentException("minLength and maxLength param must be at least 1!");

              if (minLength > maxLength)
                  throw IllegalArgumentException("minLength param must not be larger than maxLength param!");

              for (int lengthIndex = minLength; lengthIndex < maxLength + 1; lengthIndex++)
              {
                for (int textIndex = 0; textIndex + lengthIndex - 1 < ngram->size(); textIndex++)
                {

                  std::string grams[lengthIndex];

                  for (int i = textIndex; i < textIndex + lengthIndex; i++)
                  {
                    grams[i - textIndex] = ngram->getToken(i);
                  }

                  add(new StringList(grams));
                }
              }
            }

            void NGramModel::add(const std::string &chars, int minLength, int maxLength)
            {

              for (int lengthIndex = minLength; lengthIndex < maxLength + 1; lengthIndex++)
              {
                for (int textIndex = 0; textIndex + lengthIndex - 1 < chars.length(); textIndex++)
                {

                  std::string gram = chars.substr(textIndex, lengthIndex)->toLowerCase();

                  add(new StringList(new std::string[]{gram}));
                }
              }
            }

            void NGramModel::remove(StringList *tokens)
            {
              mNGrams->remove(tokens);
            }

            bool NGramModel::contains(StringList *tokens)
            {
              return mNGrams->containsKey(tokens);
            }

            int NGramModel::size()
            {
              return mNGrams->size();
            }

            Iterator<StringList*> *NGramModel::iterator()
            {
              return mNGrams->keySet()->begin();
            }

            int NGramModel::numberOfGrams()
            {
              int counter = 0;

              for (Iterator it = iterator(); it->hasNext();)
              {

                StringList *ngram = it->next();

                counter += getCount(ngram);
              }

              return counter;
            }

            void NGramModel::cutoff(int cutoffUnder, int cutoffOver)
            {

              if (cutoffUnder > 0 || cutoffOver < int::MAX_VALUE)
              {

                for (Iterator it = iterator(); it->hasNext();)
                {

                  StringList *ngram = it->next();

                  int count = getCount(ngram);

                  if (count < cutoffUnder || count > cutoffOver)
                  {
                    it->remove();
                  }
                }
              }
            }

            opennlp::tools::dictionary::Dictionary *NGramModel::toDictionary()
            {
              return toDictionary(false);
            }

            opennlp::tools::dictionary::Dictionary *NGramModel::toDictionary(bool caseSensitive)
            {

              Dictionary *dict = new Dictionary(caseSensitive);

              for (Iterator it = iterator(); it->hasNext();)
              {
                dict->put(it->next());
              }

              return dict;
            }

            void NGramModel::serialize(OutputStream *out) throw(IOException)
            {
                  Iterator<Entry*> entryIterator = new IteratorAnonymousInnerClassHelper();

                  DictionarySerializer::serialize(out, entryIterator, false);
            }

            bool NGramModel::IteratorAnonymousInnerClassHelper::hasNext()
            {
              return mDictionaryIterator->hasNext();
            }

            opennlp::tools::dictionary::serializer::Entry *NGramModel::IteratorAnonymousInnerClassHelper::next()
            {

              StringList *tokens = mDictionaryIterator->next();

              Attributes *attributes = new Attributes();

//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              attributes->setValue(COUNT, int::toString(outerInstance->getCount(tokens)));

              return new Entry(tokens, attributes);
            }

            void NGramModel::IteratorAnonymousInnerClassHelper::remove()
            {
              throw UnsupportedOperationException();
            }

            bool NGramModel::Equals(void *obj)
            {
              bool result;

              if (obj == this)
              {
                result = true;
              }
              else if (dynamic_cast<NGramModel*>(obj) != 0)
              {
                NGramModel *model = static_cast<NGramModel*>(obj);

                result = mNGrams->equals(model->mNGrams);
              }
              else
              {
                result = false;
              }

              return result;
            }

            std::string NGramModel::ToString()
            {
              return "Size: " + size();
            }

            int NGramModel::GetHashCode()
            {
              return mNGrams->hashCode();
            }

            void NGramModel::InitializeInstanceFields()
            {
                mNGrams = std::map<opennlp::tools::util::StringList*, int>();
            }
        }
    }
}
