#ifndef ADNAMESAMPLESTREAMFACTORY
#define ADNAMESAMPLESTREAMFACTORY

#include "../tools/cmdline/ObjectStreamFactory.h"
#include "../tools/namefind/NameSample.h"
#include "../tools/cmdline/namefind/CensusDictionaryCreatorTool.h"
#include "../tools/formats/BioNLP2004NameSampleStreamFactory.h"
#include "../tools/formats/Conll02NameSampleStreamFactory.h"
#include "../tools/formats/Conll03NameSampleStreamFactory.h"
#include "../tools/formats/ConllXPOSSampleStreamFactory.h"
#include "../tools/formats/ConllXSentenceSampleStreamFactory.h"
#include "../tools/formats/ConllXTokenSampleStreamFactory.h"
#include "../tools/formats/LeipzigDocumentSampleStreamFactory.h"
#include "../tools/formats/NameSampleStreamFactory.h"
#include "../tools/formats/NameToSentenceSampleStreamFactory.h"
#include "../tools/formats/NameToTokenSampleStreamFactory.h"
#include "../tools/formats/POSToSentenceSampleStreamFactory.h"
#include "../tools/formats/POSToTokenSampleStreamFactory.h"
#include "../tools/formats/WordTagSampleStreamFactory.h"
#include "ADChunkSampleStreamFactory.h"
#include "../tools/util/ObjectStream.h"
#include "NameSample>.h"
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
            namespace ad
            {


                using opennlp::tools::cmdline::ArgumentParser;
                using opennlp::tools::cmdline::ArgumentParser::ParameterDescription;
                using opennlp::tools::cmdline::CmdLineUtil;
                using opennlp::tools::cmdline::ObjectStreamFactory;
                using opennlp::tools::cmdline::TerminateToolException;
                using opennlp::tools::namefind::NameSample;
                using opennlp::tools::util::ObjectStream;

                /// <summary>
                /// A Factory to create a Arvores Deitadas NameSampleStream from the command line
                /// utility.
                /// <p>
                /// <b>Note:</b> Do not use this class, internal use only!
                /// </summary>
                class ADNameSampleStreamFactory : public ObjectStreamFactory<NameSample*>
                {

              public:
                  class Parameters
                  {
                public:
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @ParameterDescription(valueName = "encoding") String getEncoding();
                    virtual std::string getEncoding() = 0;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @ParameterDescription(valueName = "sampleData") String getData();
                    virtual std::string getData() = 0;
                  };

              public:
                  virtual std::string getUsage();

                  virtual bool validateArguments(std::string args[]);

                  virtual ObjectStream<NameSample*> *create(std::string args[]);
                };

            }
        }
    }
}


#endif	//#ifndef ADNAMESAMPLESTREAMFACTORY
