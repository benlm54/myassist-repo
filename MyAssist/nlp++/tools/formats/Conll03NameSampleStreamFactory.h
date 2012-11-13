#ifndef CONLL03NAMESAMPLESTREAMFACTORY
#define CONLL03NAMESAMPLESTREAMFACTORY

#include "../tools/cmdline/ObjectStreamFactory.h"
#include "../tools/namefind/NameSample.h"
#include "../tools/cmdline/namefind/CensusDictionaryCreatorTool.h"
#include "BioNLP2004NameSampleStreamFactory.h"
#include "Conll02NameSampleStreamFactory.h"
#include "ConllXPOSSampleStreamFactory.h"
#include "ConllXSentenceSampleStreamFactory.h"
#include "ConllXTokenSampleStreamFactory.h"
#include "LeipzigDocumentSampleStreamFactory.h"
#include "NameSampleStreamFactory.h"
#include "NameToSentenceSampleStreamFactory.h"
#include "NameToTokenSampleStreamFactory.h"
#include "POSToSentenceSampleStreamFactory.h"
#include "POSToTokenSampleStreamFactory.h"
#include "WordTagSampleStreamFactory.h"
#include "ad/ADChunkSampleStreamFactory.h"
#include "ad/ADNameSampleStreamFactory.h"
#include "../tools/util/ObjectStream.h"
#include "NameSample>.h"
#include <string>

/*
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 * 
 *       http://www.apache.org/licenses/LICENSE-2.0
 * 
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *  under the License.
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
            using opennlp::tools::formats::Conll03NameSampleStream::LANGUAGE;
            using opennlp::tools::namefind::NameSample;
            using opennlp::tools::util::ObjectStream;

            class Conll03NameSampleStreamFactory : public ObjectStreamFactory<NameSample*>
            {

          public:
              class Parameters
              {
            public:
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @ParameterDescription(valueName = "en|de") String getLang();
                virtual std::string getLang() = 0;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @ParameterDescription(valueName = "sampleData") String getData();
                virtual std::string getData() = 0;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @ParameterDescription(valueName = "per,loc,org,misc") String getTypes();
                virtual std::string getTypes() = 0;
              };

          public:
              virtual std::string getUsage();

              virtual bool validateArguments(std::string args[]);

              virtual ObjectStream<NameSample*> *create(std::string args[]);

            };

        }
    }
}


#endif	//#ifndef CONLL03NAMESAMPLESTREAMFACTORY
