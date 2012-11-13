#ifndef STRINGLIST
#define STRINGLIST

#include "Iterable<String>.h"
#include "StringBuffer.h"
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
        namespace util
        {


            /// <summary>
            /// The <seealso cref="StringList"/> is an immutable list of <seealso cref="String"/>s.
            /// </summary>
            class StringList : public Iterable<std::string>
            {

          private:
//ORIGINAL LINE: private String tokens[];
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              std::string *tokens;

              /// <summary>
              /// Initializes the current instance.
              /// 
              /// Note: <br>
              /// Token String will be replaced by identical internal String object.
              /// </summary>
              /// <param name="singleToken"> one single token </param>
          public:
              StringList(const std::string &singleToken);

              /// <summary>
              /// Initializes the current instance.
              /// 
              /// Note: <br>
              /// Token Strings will be replaced by identical internal String object.
              /// </summary>
              /// <param name="tokens"> the string parts of the new <seealso cref="StringList"/>, an empty
              /// tokens array or null is not permitted. </param>
//ORIGINAL LINE: public StringList(String... tokens)
//JAVA TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
              StringList(...);

              /// <summary>
              /// Retrieves a token from the given index.
              /// </summary>
              /// <param name="index">
              /// </param>
              /// <returns> token at the given index </returns>
              virtual std::string getToken(int index);

              /// <summary>
              /// Retrieves the number of tokens inside this list.
              /// </summary>
              /// <returns> number of tokens </returns>
              virtual int size();

              /// <summary>
              /// Retrieves an <seealso cref="Iterator"/> over all tokens.
              /// </summary>
              /// <returns> iterator over tokens </returns>
              virtual Iterator<std::string> *iterator();

                    private:
                        class IteratorAnonymousInnerClassHelper : public Iterator<std::string>
                        {

                        private:
                            int index;

                        public:
                            virtual bool hasNext();

                            virtual std::string next();

                            virtual void remove();

                        };

              /// <summary>
              /// Compares to tokens list and ignores the case of the tokens.
              /// 
              /// Note: This can cause problems with some locals.
              /// </summary>
              /// <param name="tokens">
              /// </param>
              /// <returns> true if identically with ignore the case otherwise false </returns>
          public:
              virtual bool compareToIgnoreCase(StringList *tokens);


              virtual bool Equals(void *obj);

              virtual int GetHashCode();

              virtual std::string ToString();
            };

        }
    }
}


#endif	//#ifndef STRINGLIST
