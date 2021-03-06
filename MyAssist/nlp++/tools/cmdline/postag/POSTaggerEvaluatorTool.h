#ifndef POSTAGGEREVALUATORTOOL
#define POSTAGGEREVALUATORTOOL

#include "../tools/cmdline/CmdLineTool.h"
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
            namespace postag
            {


                using opennlp::tools::cmdline::ArgumentParser;
                using opennlp::tools::cmdline::CLI;
                using opennlp::tools::cmdline::CmdLineTool;
                using opennlp::tools::cmdline::CmdLineUtil;
                using opennlp::tools::cmdline::TerminateToolException;
                using opennlp::tools::cmdline::params::EvaluatorParams;
                using opennlp::tools::postag::POSEvaluator;
                using opennlp::tools::postag::POSModel;
                using opennlp::tools::postag::POSSample;
                using opennlp::tools::postag::POSTaggerEvaluationMonitor;
                using opennlp::tools::util::ObjectStream;

                class POSTaggerEvaluatorTool : public CmdLineTool
                {

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


#endif	//#ifndef POSTAGGEREVALUATORTOOL
