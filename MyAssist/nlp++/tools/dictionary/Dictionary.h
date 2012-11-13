#ifndef DICTIONARY
#define DICTIONARY

#include "../tools/util/StringList.h"
#include "../tools/util/InvalidFormatException.h"
#include "serializer/Entry.h"
#include "StringList>.h"
#include <string>

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


            using opennlp::tools::dictionary::serializer::Attributes;
            using opennlp::tools::dictionary::serializer::DictionarySerializer;
            using opennlp::tools::dictionary::serializer::Entry;
            using opennlp::tools::dictionary::serializer::EntryInserter;
            using opennlp::tools::util::InvalidFormatException;
            using opennlp::tools::util::StringList;

            /// <summary>
            /// This class is a dictionary.
            /// </summary>
            class Dictionary : public Iterable<StringList*>
            {

          private:
              class StringListWrapper
              {
                      private:
                          Dictionary *const outerInstance;


                StringList *const stringList;

                StringListWrapper(Dictionary *outerInstance, StringList *stringList);

                StringList *getStringList();

            public:
                virtual bool Equals(void *obj);

                virtual int GetHashCode();

                virtual std::string ToString();
              };

          private:
              Set<StringListWrapper*> *entrySet;
              const bool isCaseSensitive;


              /// <summary>
              /// Initializes an empty <seealso cref="Dictionary"/>.
              /// </summary>
          public:
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              Dictionary(); //this(false);

              Dictionary(bool caseSensitive);

              /// <summary>
              /// Initializes the <seealso cref="Dictionary"/> from an existing dictionary resource.
              /// </summary>
              /// <param name="in"> </param>
              /// <exception cref="IOException"> </exception>
              /// <exception cref="InvalidFormatException"> </exception>
              Dictionary(InputStream *in_Renamed) throw(IOException, InvalidFormatException);

                                private:
                                    class IteratorAnonymousInnerClassHelper : public Iterator<StringList*>
                                    {

                                    public:
                                        virtual bool hasNext();

                                        virtual StringList *next();

                                        virtual void remove();
                                    };

                                private:
                                    class IteratorAnonymousInnerClassHelper2 : public Iterator<Entry*>
                                    {
                                    private:
                                        Iterator<StringList*> *dictionaryIterator;

                                    public:
                                        virtual bool hasNext();

                                        virtual Entry *next();

                                        virtual void remove();

                                    };

                                private:
                                    class AbstractSetAnonymousInnerClassHelper : public AbstractSet<std::string>
                                    {

                                    public:
                                        virtual Iterator<std::string> *iterator();

                    private:
                        class IteratorAnonymousInnerClassHelper3 : public Iterator<std::string>
                        {

                        public:
                            virtual bool hasNext();

                            virtual std::string next();

                            virtual void remove();
                        };

                                    public:
                                        virtual int size();

                                        virtual bool contains(void *obj);
                                    };

            }
        }
    }


#endif	//#ifndef DICTIONARY
