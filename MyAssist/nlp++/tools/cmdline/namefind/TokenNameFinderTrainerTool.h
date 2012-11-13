#ifndef TOKENNAMEFINDERTRAINERTOOL
#define TOKENNAMEFINDERTRAINERTOOL

#include "../tools/cmdline/CmdLineTool.h"
#include "../tools/cmdline/chunker/ChunkerTrainerTool.h"
#include "../tools/cmdline/chunker/TrainingParams.h"
#include "../tools/cmdline/doccat/DoccatTrainerTool.h"
#include "../tools/cmdline/doccat/TrainingParams.h"
#include "TrainingParams.h"
#include "../tools/cmdline/params/TrainingToolParams.h"
#include "../tools/cmdline/parser/ParserTrainerTool.h"
#include "../tools/cmdline/parser/TrainingParams.h"
#include "../tools/cmdline/postag/POSTaggerTrainerTool.h"
#include "../tools/cmdline/postag/TrainingParams.h"
#include "../tools/cmdline/sentdetect/SentenceDetectorTrainerTool.h"
#include "../tools/cmdline/sentdetect/TrainingParams.h"
#include "../tools/cmdline/tokenizer/TokenizerTrainerTool.h"
#include "../tools/cmdline/tokenizer/TrainingParams.h"
#include "../tools/namefind/NameSample.h"
#include "../tools/util/ObjectStream.h"
#include <string>
#include <map>

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
            namespace namefind
            {


                using opennlp::tools::cmdline::ArgumentParser;
                using opennlp::tools::cmdline::CLI;
                using opennlp::tools::cmdline::CmdLineTool;
                using opennlp::tools::cmdline::CmdLineUtil;
                using opennlp::tools::cmdline::TerminateToolException;
                using opennlp::tools::cmdline::params::TrainingToolParams;
                using opennlp::tools::namefind::NameSample;
                using opennlp::tools::namefind::NameSampleDataStream;
                using opennlp::tools::namefind::TokenNameFinderModel;
                using opennlp::tools::util::InvalidFormatException;
                using opennlp::tools::util::ObjectStream;
                using opennlp::tools::util::PlainTextByLineStream;
                using opennlp::tools::util::model::ArtifactSerializer;
                using opennlp::tools::util::model::ModelUtil;

                class TokenNameFinderTrainerTool : public CmdLineTool
                {

              public:
                  class TrainerToolParams : public TrainingParams, public TrainingToolParams
                  {

                  };

              public:
                  std::string getName();

                  std::string getShortDescription();

                  std::string getHelp();

                  static ObjectStream<NameSample*> *openSampleData(const std::string &sampleDataName, File *sampleDataFile, Charset *encoding);

                  static char *openFeatureGeneratorBytes(const std::string &featureGenDescriptorFile);

                  static char *openFeatureGeneratorBytes(File *featureGenDescriptorFile);

                  static Map<std::string, void*> *loadResources(File *resourcePath);

                  static Map<std::string, void*> *loadResources(const std::string &resourceDirectory);

                  void run(std::string args[]);
                };

            }
        }
    }
}


#endif	//#ifndef TOKENNAMEFINDERTRAINERTOOL
