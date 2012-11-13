#ifndef ENTRY
#define ENTRY

#include "../tools/util/StringList.h"
#include "Attributes.h"

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
            namespace serializer
            {

                using opennlp::tools::util::StringList;

                /// <summary>
                /// An <seealso cref="Entry"/> is a <seealso cref="StringList"/> which can
                /// optionally be mapped to attributes.
                /// 
                /// <seealso cref="Entry"/>s is a read and written by the <seealso cref="DictionarySerializer"/>.
                /// </summary>
                /// <seealso cref= DictionarySerializer </seealso>
                /// <seealso cref= Attributes </seealso>
                class Entry
                {

              private:
                  StringList *tokens;
                  Attributes *attributes;

                  /// <summary>
                  /// Initializes the current instance.
                  /// </summary>
                  /// <param name="tokens"> </param>
                  /// <param name="attributes"> </param>
              public:
                  Entry(StringList *tokens, Attributes *attributes);

                  /// <summary>
                  /// Retrieves the tokens.
                  /// </summary>
                  /// <returns> the tokens </returns>
                  virtual StringList *getTokens();

                  /// <summary>
                  /// Retrieves the <seealso cref="Attributes"/>.
                  /// </summary>
                  /// <returns> the <seealso cref="Attributes"/> </returns>
                  virtual Attributes *getAttributes();
                };

            }
        }
    }
}


#endif	//#ifndef ENTRY
