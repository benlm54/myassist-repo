#ifndef ATTRIBUTES
#define ATTRIBUTES

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
            namespace serializer
            {


                /// <summary>
                /// The <seealso cref="Attributes"/> class stores name value pairs.
                /// 
                /// Problem: The HashMap for storing the name value pairs has a very high
                /// memory footprint, replace it.
                /// </summary>
                class Attributes
                {

              private:
                  Map<std::string, std::string> *mNameValueMap;

                  /// <summary>
                  /// Retrieves the value for the given key or null if attribute it not set.
                  /// </summary>
                  /// <param name="key">
                  /// </param>
                  /// <returns> the value </returns>
              public:
                  virtual std::string getValue(const std::string &key);

                  /// <summary>
                  /// Sets a key/value pair.
                  /// </summary>
                  /// <param name="key"> </param>
                  /// <param name="value"> </param>
                  virtual void setValue(const std::string &key, const std::string &value);

                  /// <summary>
                  /// Iterates over the keys.
                  /// </summary>
                  /// <returns> key-<seealso cref="Iterator"/> </returns>
                  virtual Iterator<std::string> *iterator();

                private:
                    void InitializeInstanceFields();

public:
                    Attributes()
                    {
                        InitializeInstanceFields();
                    }
                };

            }
        }
    }
}


#endif	//#ifndef ATTRIBUTES
