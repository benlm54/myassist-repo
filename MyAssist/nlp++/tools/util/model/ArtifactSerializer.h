#ifndef ARTIFACTSERIALIZER
#define ARTIFACTSERIALIZER

#include "T.h"

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
            namespace model
            {


                using opennlp::tools::util::InvalidFormatException;

                /// <summary>
                /// Responsible to create an artifact from an <seealso cref="InputStream"/>.
                /// </summary>
                template<typename T>
                class ArtifactSerializer
                {

                  /// <summary>
                  /// Creates the artifact from the provided <seealso cref="InputStream"/>.
                  /// 
                  /// The <seealso cref="InputStream"/> remains open.
                  /// </summary>
                  /// <returns> the artifact
                  /// </returns>
                  /// <exception cref="IOException"> </exception>
                  /// <exception cref="InvalidFormatException"> </exception>
              public:
                  virtual T *create(java::io::InputStream *in) = 0;

                  /// <summary>
                  /// Serializes the artifact to the provided <seealso cref="OutputStream"/>.
                  /// 
                  /// The <seealso cref="OutputStream"/> remains open.
                  /// </summary>
                  /// <param name="artifact"> </param>
                  /// <param name="out"> </param>
                  /// <exception cref="IOException"> </exception>
                  virtual void serialize(T *artifact, java::io::OutputStream *out) = 0;
                };

            }
        }
    }
}


#endif	//#ifndef ARTIFACTSERIALIZER
