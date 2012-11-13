#ifndef CHUNKEREVALUATORTOOL
#define CHUNKEREVALUATORTOOL

#include "../tools/cmdline/CmdLineTool.h"
#include "../tools/cmdline/namefind/TokenNameFinderEvaluatorTool.h"
#include "../tools/cmdline/params/DetailedFMeasureEvaluatorParams.h"
#include "../tools/cmdline/params/EvaluatorParams.h"
#include "../tools/chunker/ChunkSample.h"
#include "../tools/util/ObjectStream.h"
#include "ChunkSample>.h"
#include <string>
#include <vector>
#include <list>

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
            namespace chunker
            {


                using opennlp::tools::chunker::ChunkSample;
                using opennlp::tools::chunker::ChunkerEvaluationMonitor;
                using opennlp::tools::chunker::ChunkerEvaluator;
                using opennlp::tools::chunker::ChunkerME;
                using opennlp::tools::chunker::ChunkerModel;
                using opennlp::tools::chunker::DefaultChunkerSequenceValidator;
                using opennlp::tools::cmdline::ArgumentParser;
                using opennlp::tools::cmdline::CLI;
                using opennlp::tools::cmdline::CmdLineTool;
                using opennlp::tools::cmdline::CmdLineUtil;
                using opennlp::tools::cmdline::PerformanceMonitor;
                using opennlp::tools::cmdline::TerminateToolException;
                using opennlp::tools::cmdline::params::DetailedFMeasureEvaluatorParams;
                using opennlp::tools::cmdline::params::EvaluatorParams;
                using opennlp::tools::util::ObjectStream;
                using opennlp::tools::util::eval::EvaluationMonitor;

                class ChunkerEvaluatorTool : public CmdLineTool
                {

              public:
                  class EvalToolParams : public EvaluatorParams, public DetailedFMeasureEvaluatorParams
                  {

                  };

              public:
                  std::string getName();

                  std::string getShortDescription();

                  std::string getHelp();

                  void run(std::string args[]);

                            private:
                                class ObjectStreamAnonymousInnerClassHelper : public ObjectStream<ChunkSample*>
                                {

                                public:
                                    virtual ChunkSample *read() throw(IOException);

                                    virtual void reset() throw(IOException);

                                    virtual void close() throw(IOException);
                                };
                };

            }
        }
    }
}


#endif	//#ifndef CHUNKEREVALUATORTOOL
