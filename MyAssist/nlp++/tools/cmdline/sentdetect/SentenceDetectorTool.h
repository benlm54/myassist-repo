#ifndef SENTENCEDETECTORTOOL
#define SENTENCEDETECTORTOOL

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
            namespace sentdetect
            {


                using opennlp::tools::cmdline::CLI;
                using opennlp::tools::cmdline::CmdLineTool;
                using opennlp::tools::cmdline::CmdLineUtil;
                using opennlp::tools::cmdline::PerformanceMonitor;
                using opennlp::tools::cmdline::TerminateToolException;
                using opennlp::tools::sentdetect::SentenceDetectorME;
                using opennlp::tools::sentdetect::SentenceModel;
                using opennlp::tools::util::ObjectStream;
                using opennlp::tools::util::ParagraphStream;
                using opennlp::tools::util::PlainTextByLineStream;

                /// <summary>
                /// A sentence detector which uses a maxent model to predict the sentences.
                /// </summary>
                class SentenceDetectorTool : public CmdLineTool
                {

              public:
                  std::string getName();

                  std::string getShortDescription();

                  std::string getHelp();

                  /// <summary>
                  /// Perform sentence detection the input stream.
                  /// 
                  /// A newline will be treated as a paragraph boundary.
                  /// </summary>
                  void run(std::string args[]);
                };

            }
        }
    }
}


#endif	//#ifndef SENTENCEDETECTORTOOL
