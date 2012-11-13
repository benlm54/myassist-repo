#ifndef STRINGUTIL
#define STRINGUTIL

#include "CharSequence.h"
#include <string>
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
        namespace util
        {

            class StringUtil
            {

              /// <summary>
              /// Determines if the specified character is a whitespace.
              /// 
              /// A character is considered a whitespace when one
              /// of the following conditions is meet:
              /// 
              /// <ul>
              /// <li>Its a <seealso cref="Character#isWhitespace(int)"/> whitespace.</li>
              /// <li>Its a part of the Unicode Zs category (<seealso cref="Character#SPACE_SEPARATOR"/>).</li>
              /// </ul>
              /// 
              /// <code>Character.isWhitespace(int)</code> does not include no-break spaces.
              /// In OpenNLP no-break spaces are also considered as white spaces.
              /// </summary>
              /// <param name="charCode"> </param>
              /// <returns> true if white space otherwise false </returns>
          public:
              static bool isWhitespace(char charCode);

              /// <summary>
              /// Determines if the specified character is a whitespace.
              /// 
              /// A character is considered a whitespace when one
              /// of the following conditions is meet:
              /// 
              /// <ul>
              /// <li>Its a <seealso cref="Character#isWhitespace(int)"/> whitespace.</li>
              /// <li>Its a part of the Unicode Zs category (<seealso cref="Character#SPACE_SEPARATOR"/>).</li>
              /// </ul>
              /// 
              /// <code>Character.isWhitespace(int)</code> does not include no-break spaces.
              /// In OpenNLP no-break spaces are also considered as white spaces.
              /// </summary>
              /// <param name="charCode"> </param>
              /// <returns> true if white space otherwise false </returns>
              static bool isWhitespace(int charCode);


              /// <summary>
              /// Converts to lower case independent of the current locale via 
              /// <seealso cref="Character#toLowerCase(char)"/> which uses mapping information
              /// from the UnicodeData file.
              /// </summary>
              /// <param name="string"> </param>
              /// <returns> lower cased String </returns>
              static std::string toLowerCase(CharSequence *string);

              /// <summary>
              /// Converts to upper case independent of the current locale via 
              /// <seealso cref="Character#toUpperCase(char)"/> which uses mapping information
              /// from the UnicodeData file.
              /// </summary>
              /// <param name="string"> </param>
              /// <returns> upper cased String </returns>
              static std::string toUpperCase(CharSequence *string);

              /// <summary>
              /// Returns <tt>true</tt> if <seealso cref="CharSequence#length()"/> is
              /// <tt>0</tt> or <tt>null</tt>.
              /// </summary>
              /// <returns> <tt>true</tt> if <seealso cref="CharSequence#length()"/> is <tt>0</tt>, otherwise
              ///         <tt>false</tt>
              /// 
              /// @since 1.5.1 </returns>
              static bool isEmpty(CharSequence *theString);
            };

        }
    }
}


#endif	//#ifndef STRINGUTIL
