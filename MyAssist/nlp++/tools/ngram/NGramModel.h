#ifndef NGRAMMODEL
#define NGRAMMODEL

#include "../tools/util/StringList.h"
#include "../tools/util/InvalidFormatException.h"
#include "../tools/dictionary/serializer/EntryInserter.h"
#include "../tools/dictionary/serializer/Entry.h"
#include "../tools/dictionary/Dictionary.h"
#include "StringList>.h"
#include "NumberFormatException.h"
#include <string>
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
        namespace ngram
        {


            using opennlp::tools::dictionary::Dictionary;
            using opennlp::tools::dictionary::serializer::Attributes;
            using opennlp::tools::dictionary::serializer::DictionarySerializer;
            using opennlp::tools::dictionary::serializer::Entry;
            using opennlp::tools::dictionary::serializer::EntryInserter;
            using opennlp::tools::util::InvalidFormatException;
            using opennlp::tools::util::StringList;

            /// <summary>
            /// The <seealso cref="NGramModel"/> can be used to crate ngrams and character ngrams.
            /// </summary>
            /// <seealso cref= StringList </seealso>
            class NGramModel : public Iterable<StringList*>
            {

          protected:
              static const std::string COUNT;

          private:
              Map<StringList*, int> *mNGrams;

              /// <summary>
              /// Initializes an empty instance.
              /// </summary>
          public:
              NGramModel();

              /// <summary>
              /// Initializes the current instance.
              /// </summary>
              /// <param name="in"> </param>
              /// <exception cref="IOException"> </exception>
              /// <exception cref="InvalidFormatException"> </exception>
              NGramModel(InputStream *in_Renamed) throw(IOException, InvalidFormatException);

                    private:
                        class EntryInserterAnonymousInnerClassHelper : public EntryInserter
                        {
                        public:
                            virtual void insert(Entry *entry) throw(InvalidFormatException);
                        };

              /// <summary>
              /// Retrieves the count of the given ngram.
              /// </summary>
              /// <param name="ngram">
              /// </param>
              /// <returns> count of the ngram or 0 if it is not contained
              ///  </returns>
          public:
              virtual int getCount(StringList *ngram);

              /// <summary>
              /// Sets the count of an existing ngram.
              /// </summary>
              /// <param name="ngram"> </param>
              /// <param name="count"> </param>
              virtual void setCount(StringList *ngram, int count);

              /// <summary>
              /// Adds one NGram, if it already exists the count increase by one.
              /// </summary>
              /// <param name="ngram"> </param>
              virtual void add(StringList *ngram);

              /// <summary>
              /// Adds NGrams up to the specified length to the current instance.
              /// </summary>
              /// <param name="ngram"> the tokens to build the uni-grams, bi-grams, tri-grams, ..
              ///     from. </param>
              /// <param name="minLength"> - minimal length </param>
              /// <param name="maxLength"> - maximal length </param>
              virtual void add(StringList *ngram, int minLength, int maxLength);

              /// <summary>
              /// Adds character NGrams to the current instance.
              /// </summary>
              /// <param name="chars"> </param>
              /// <param name="minLength"> </param>
              /// <param name="maxLength"> </param>
              virtual void add(const std::string &chars, int minLength, int maxLength);

              /// <summary>
              /// Removes the specified tokens form the NGram model, they are just dropped.
              /// </summary>
              /// <param name="tokens"> </param>
              virtual void remove(StringList *tokens);

              /// <summary>
              /// Checks fit he given tokens are contained by the current instance.
              /// </summary>
              /// <param name="tokens">
              /// </param>
              /// <returns> true if the ngram is contained </returns>
              virtual bool contains(StringList *tokens);

              /// <summary>
              /// Retrieves the number of <seealso cref="StringList"/> entries in the current instance.
              /// </summary>
              /// <returns> number of different grams </returns>
              virtual int size();

              /// <summary>
              /// Retrieves an <seealso cref="Iterator"/> over all <seealso cref="StringList"/> entries.
              /// </summary>
              /// <returns> iterator over all grams </returns>
              virtual Iterator<StringList*> *iterator();

              /// <summary>
              /// Retrieves the total count of all Ngrams.
              /// </summary>
              /// <returns> total count of all ngrams </returns>
              virtual int numberOfGrams();

              /// <summary>
              /// Deletes all ngram which do appear less than the cutoffUnder value
              /// and more often than the cutoffOver value.
              /// </summary>
              /// <param name="cutoffUnder"> </param>
              /// <param name="cutoffOver"> </param>
              virtual void cutoff(int cutoffUnder, int cutoffOver);

              /// <summary>
              /// Creates a dictionary which contain all <seealso cref="StringList"/> which
              /// are in the current <seealso cref="NGramModel"/>.
              /// 
              /// Entries which are only different in the case are merged into one.
              /// 
              /// Calling this method is the same as calling <seealso cref="#toDictionary(boolean)"/> with true.
              /// </summary>
              /// <returns> a dictionary of the ngrams </returns>
              virtual Dictionary *toDictionary();

              /// <summary>
              /// Creates a dictionary which contains all <seealso cref="StringList"/>s which
              /// are in the current <seealso cref="NGramModel"/>.
              /// </summary>
              /// <param name="caseSensitive"> Specifies whether case distinctions should be kept in the creation of the dictionary.
              /// </param>
              /// <returns> a dictionary of the ngrams </returns>
              virtual Dictionary *toDictionary(bool caseSensitive);

              /// <summary>
              /// Writes the ngram instance to the given <seealso cref="OutputStream"/>.
              /// </summary>
              /// <param name="out">
              /// </param>
              /// <exception cref="IOException"> if an I/O Error during writing occurs </exception>
              virtual void serialize(OutputStream *out) throw(IOException);

                    private:
                        class IteratorAnonymousInnerClassHelper : public Iterator<Entry*>
                        {
                        private:
                            Iterator<StringList*> *mDictionaryIterator;

                        public:
                            virtual bool hasNext();

                            virtual Entry *next();

                            virtual void remove();

                        };

          public:
              virtual bool Equals(void *obj);

              virtual std::string ToString();

              virtual int GetHashCode();

            private:
                void InitializeInstanceFields();
            };

        }
    }
}


#endif	//#ifndef NGRAMMODEL
