#ifndef LEIPZIGDOCUMENTSAMPLESTREAMFACTORY
#define LEIPZIGDOCUMENTSAMPLESTREAMFACTORY

#include "../tools/cmdline/ObjectStreamFactory.h"
#include "../tools/doccat/DocumentSample.h"
#include "../tools/cmdline/namefind/CensusDictionaryCreatorTool.h"
#include "BioNLP2004NameSampleStreamFactory.h"
#include "Conll02NameSampleStreamFactory.h"
#include "Conll03NameSampleStreamFactory.h"
#include "ConllXPOSSampleStreamFactory.h"
#include "ConllXSentenceSampleStreamFactory.h"
#include "ConllXTokenSampleStreamFactory.h"
#include "NameSampleStreamFactory.h"
#include "NameToSentenceSampleStreamFactory.h"
#include "NameToTokenSampleStreamFactory.h"
#include "POSToSentenceSampleStreamFactory.h"
#include "POSToTokenSampleStreamFactory.h"
#include "WordTagSampleStreamFactory.h"
#include "ad/ADChunkSampleStreamFactory.h"
#include "ad/ADNameSampleStreamFactory.h"
#include "../tools/util/ObjectStream.h"
#include "DocumentSample>.h"
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
        namespace formats
        {


            using opennlp::tools::cmdline::ArgumentParser;
            using opennlp::tools::cmdline::ArgumentParser::ParameterDescription;
            using opennlp::tools::cmdline::CmdLineUtil;
            using opennlp::tools::cmdline::ObjectStreamFactory;
            using opennlp::tools::cmdline::TerminateToolException;
            using opennlp::tools::doccat::DocumentSample;
            using opennlp::tools::util::ObjectStream;

            /// <summary>
            /// <b>Note:</b> Do not use this class, internal use only!
            /// </summary>
            class LeipzigDocumentSampleStreamFactory : public ObjectStreamFactory<DocumentSample*>
            {

          public:
              class Parameters
              {
            public:
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @ParameterDescription(valueName = "languageCode") String getLang();
                virtual std::string getLang() = 0;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @ParameterDescription(valueName = "sampleData") String getData();
                virtual std::string getData() = 0;
              };

          public:
              virtual std::string getUsage();

              virtual bool validateArguments(std::string args[]);

              virtual ObjectStream<DocumentSample*> *create(std::string args[]);
            };

        }
    }
}


#endif	//#ifndef LEIPZIGDOCUMENTSAMPLESTREAMFACTORY
