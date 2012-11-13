#ifndef SIMPLETOKENIZER
#define SIMPLETOKENIZER

#include "AbstractTokenizer.h"
#include "../tools/util/Span.h"
#include <string>
#include <vector>
#include <cctype>

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
        namespace tokenize
        {


            using opennlp::tools::util::Span;
            using opennlp::tools::util::StringUtil;

            /// <summary>
            /// Performs tokenization using character classes.
            /// </summary>
            class SimpleTokenizer : public AbstractTokenizer
            {

          public:
              static SimpleTokenizer *const INSTANCE;

//JAVA TO C++ CONVERTER TODO TASK: Static constructors are not allowed in native C++:
              static SimpleTokenizer();

              /// @deprecated Use INSTANCE field instead to obtain an instance, constructor
              /// will be made private in the future. 
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated("Use INSTANCE field instead to obtain an instance, constructor") public SimpleTokenizer()
              SimpleTokenizer();

              virtual Span *tokenizePos(const std::string &s);


              /// 
              /// <param name="args">
              /// </param>
              /// <exception cref="IOException"> </exception>
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated public static void main(String[] args) throws java.io.IOException
              static void main(std::string args[]) throw(IOException);

            };

            class CharacterEnum
            {
          public:
              static CharacterEnum *const WHITESPACE;
              static CharacterEnum *const ALPHABETIC;
              static CharacterEnum *const NUMERIC;
              static CharacterEnum *const OTHER;

          private:
              std::string name;

              CharacterEnum(const std::string &name);

          public:
              virtual std::string ToString();
            };

        }
    }
}


#endif	//#ifndef SIMPLETOKENIZER
