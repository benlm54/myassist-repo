#ifndef NAMESAMPLEDATASTREAM
#define NAMESAMPLEDATASTREAM

#include "NameSample.h"
#include "../tools/util/FilterObjectStream.h"
#include "../tools/util/ObjectStream.h"
#include "FilterObjectStream<String, NameSample>.h"
#include "S.h"
#include <string>

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
        namespace namefind
        {


            using opennlp::maxent::DataStream;
            using opennlp::tools::util::FilterObjectStream;
            using opennlp::tools::util::ObjectStream;

            /// <summary>
            /// The <seealso cref="NameSampleDataStream"/> class converts tagged <seealso cref="String"/>s
            /// provided by a <seealso cref="DataStream"/> to <seealso cref="NameSample"/> objects.
            /// It uses text that is is one-sentence per line and tokenized
            /// with names identified by <code>&lt;START&gt;</code> and <code>&lt;END&gt;</code> tags.
            /// </summary>
            class NameSampleDataStream : public FilterObjectStream<std::string, NameSample*>
            {

          public:
              static const std::string START_TAG_PREFIX;
              static const std::string START_TAG;
              static const std::string END_TAG;

              NameSampleDataStream(ObjectStream<std::string> *in_Renamed);

              virtual NameSample *read() throw(IOException);
            };

        }
    }
}


#endif	//#ifndef NAMESAMPLEDATASTREAM
