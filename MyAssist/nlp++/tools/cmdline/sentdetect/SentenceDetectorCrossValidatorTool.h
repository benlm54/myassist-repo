#ifndef SENTENCEDETECTORCROSSVALIDATORTOOL
#define SENTENCEDETECTORCROSSVALIDATORTOOL

#include "../tools/cmdline/CmdLineTool.h"
#include "../tools/cmdline/chunker/ChunkerCrossValidatorTool.h"
#include "../tools/cmdline/chunker/TrainingParams.h"
#include "../tools/cmdline/doccat/TrainingParams.h"
#include "../tools/cmdline/namefind/TokenNameFinderCrossValidatorTool.h"
#include "../tools/cmdline/namefind/TrainingParams.h"
#include "../tools/cmdline/params/CVParams.h"
#include "../tools/cmdline/parser/TrainingParams.h"
#include "../tools/cmdline/postag/POSTaggerCrossValidatorTool.h"
#include "../tools/cmdline/postag/TrainingParams.h"
#include "TrainingParams.h"
#include "../tools/cmdline/tokenizer/TokenizerCrossValidatorTool.h"
#include "../tools/cmdline/tokenizer/TrainingParams.h"
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
        namespace cmdline
        {
            namespace sentdetect
            {


                using opennlp::tools::cmdline::ArgumentParser;
                using opennlp::tools::cmdline::CLI;
                using opennlp::tools::cmdline::CmdLineTool;
                using opennlp::tools::cmdline::CmdLineUtil;
                using opennlp::tools::cmdline::TerminateToolException;
                using opennlp::tools::cmdline::params::CVParams;
                using opennlp::tools::dictionary::Dictionary;
                using opennlp::tools::sentdetect::SDCrossValidator;
                using opennlp::tools::sentdetect::SentenceDetectorEvaluationMonitor;
                using opennlp::tools::sentdetect::SentenceSample;
                using opennlp::tools::util::ObjectStream;
                using opennlp::tools::util::TrainingParameters;
                using opennlp::tools::util::eval::FMeasure;

                class SentenceDetectorCrossValidatorTool : public CmdLineTool
                {

              public:
                  class CVToolParams : public TrainingParams, public CVParams
                  {

                  };

              public:
                  std::string getName();

                  std::string getShortDescription();

                  std::string getHelp();

                  void run(std::string args[]);
                };

            }
        }
    }
}


#endif	//#ifndef SENTENCEDETECTORCROSSVALIDATORTOOL
