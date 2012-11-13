#ifndef CONLLXSENTENCESAMPLESTREAMFACTORY
#define CONLLXSENTENCESAMPLESTREAMFACTORY

#include "../tools/cmdline/ObjectStreamFactory.h"
#include "../tools/sentdetect/SentenceSample.h"
#include "../tools/cmdline/namefind/CensusDictionaryCreatorTool.h"
#include "../tools/cmdline/params/DetokenizerParameter.h"
#include "BioNLP2004NameSampleStreamFactory.h"
#include "Conll02NameSampleStreamFactory.h"
#include "Conll03NameSampleStreamFactory.h"
#include "ConllXPOSSampleStreamFactory.h"
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
#include "SentenceSample>.h"
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
            using opennlp::tools::cmdline::ObjectStreamFactory;
            using opennlp::tools::cmdline::TerminateToolException;
            using opennlp::tools::cmdline::params::DetokenizerParameter;
            using opennlp::tools::postag::POSSample;
            using opennlp::tools::sentdetect::SentenceSample;
            using opennlp::tools::tokenize::DetokenizationDictionary;
            using opennlp::tools::tokenize::Detokenizer;
            using opennlp::tools::tokenize::DictionaryDetokenizer;
            using opennlp::tools::util::ObjectStream;

            /// <summary>
            /// <b>Note:</b> Do not use this class, internal use only!
            /// </summary>
            class ConllXSentenceSampleStreamFactory : public ObjectStreamFactory<SentenceSample*>
            {

          public:
              class Parameters : public ConllXPOSSampleStreamFactory::Parameters, public DetokenizerParameter
              {
                // TODO:
                // Make chunk size configurable
              };

          public:
              virtual std::string getUsage();

              virtual bool validateArguments(std::string args[]);

              virtual ObjectStream<SentenceSample*> *create(std::string args[]);
            };

        }
    }
}


#endif	//#ifndef CONLLXSENTENCESAMPLESTREAMFACTORY
