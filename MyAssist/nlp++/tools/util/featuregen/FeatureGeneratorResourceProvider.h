#ifndef FEATUREGENERATORRESOURCEPROVIDER
#define FEATUREGENERATORRESOURCEPROVIDER

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
                /// The <seealso cref="FeatureGeneratorResourceProvider"/> provides access to the resources
                /// provided in the model. Inside the model resources are identified by a
                /// name.
                /// <p>
                /// <b>Note:</b><br>
                /// This class is not be intended to be implemented by users.<br>
                /// All implementing classes must be thread safe.
                /// </summary>
                class FeatureGeneratorResourceProvider
                {

                  /// <summary>
                  /// Retrieves the resource object for the given name/identifier.
                  /// </summary>
                  /// <param name="resourceIdentifier"> the identifier which names the resource.
                  /// </param>
                  /// <returns> the resource object </returns>
              public:
                  virtual void *getResource(const std::string &resourceIdentifier) = 0;
                };

            }
        }
    }
}


#endif	//#ifndef FEATUREGENERATORRESOURCEPROVIDER
