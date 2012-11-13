#ifndef OBJECTSTREAMFACTORY
#define OBJECTSTREAMFACTORY

#include "../tools/util/ObjectStream.h"

/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
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
        namespace cmdline
        {

            using opennlp::tools::util::ObjectStream;

            template<typename T>
            class ObjectStreamFactory
            {

          public:
              virtual std::string getUsage() = 0;

              virtual bool validateArguments(std::string args[]) = 0;

              /// <summary>
              /// Creates the <code>ObjectStream</code>
              /// </summary>
              /// <param name="args">
              /// @return </param>
              virtual opennlp::tools::util::ObjectStream<T*> *create(std::string args[]) = 0;
            };

        }
    }
}


#endif	//#ifndef OBJECTSTREAMFACTORY
