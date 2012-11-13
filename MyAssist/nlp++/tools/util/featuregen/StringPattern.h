#ifndef STRINGPATTERN
#define STRINGPATTERN

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
            namespace featuregen
            {

                /// <summary>
                /// Recognizes predefined patterns in strings.
                /// </summary>
                class StringPattern
                {

              private:
                  static const int INITAL_CAPITAL_LETTER = 0x1;
                  static const int ALL_CAPITAL_LETTER = 0x1 << 1;
                  static const int ALL_LOWERCASE_LETTER = 0x1 << 2;
                  static const int ALL_LETTERS = 0x1 << 3;
                  static const int ALL_DIGIT = 0x1 << 4;
                  static const int CONTAINS_PERIOD = 0x1 << 5;
                  static const int CONTAINS_COMMA = 0x1 << 6;
                  static const int CONTAINS_SLASH = 0x1 << 7;
                  static const int CONTAINS_DIGIT = 0x1 << 8;
                  static const int CONTAINS_HYPHEN = 0x1 << 9;
                  static const int CONTAINS_LETTERS = 0x1 << 10;
                  static const int CONTAINS_UPPERCASE = 0x1 << 11;

                  const int pattern;

//JAVA TO C++ CONVERTER NOTE: The variable digits was renamed since C++ does not allow variables with the same name as methods:
                  const int digits_Renamed;

                  StringPattern(int pattern, int digits);

                  /// <returns> true if all characters are letters. </returns>
              public:
                  virtual bool isAllLetter();

                  /// <returns> true if first letter is capital. </returns>
                  virtual bool isInitialCapitalLetter();

                  /// <returns> true if all letters are capital. </returns>
                  virtual bool isAllCapitalLetter();

                  /// <returns> true if all letters are lower case. </returns>
                  virtual bool isAllLowerCaseLetter();

                  /// <returns> true if all chars are digits. </returns>
                  virtual bool isAllDigit();

                  /// <summary>
                  /// Retrieves the number of digits.
                  /// </summary>
                  virtual int digits();

                  virtual bool containsPeriod();

                  virtual bool containsComma();

                  virtual bool containsSlash();

                  virtual bool containsDigit();

                  virtual bool containsHyphen();

                  virtual bool containsLetters();

                  static StringPattern *recognize(const std::string &token);
                };

            }
        }
    }
}


#endif	//#ifndef STRINGPATTERN
