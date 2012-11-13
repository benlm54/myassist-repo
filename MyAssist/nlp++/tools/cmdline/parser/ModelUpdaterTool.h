#ifndef MODELUPDATERTOOL
#define MODELUPDATERTOOL

#include "../tools/cmdline/CmdLineTool.h"
#include "../tools/cmdline/params/TrainingToolParams.h"
#include "../tools/parser/Parse.h"
#include "../tools/parser/ParserModel.h"
#include "../tools/util/ObjectStream.h"
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
            namespace parser
            {


                using opennlp::tools::cmdline::ArgumentParser;
                using opennlp::tools::cmdline::CLI;
                using opennlp::tools::cmdline::CmdLineTool;
                using opennlp::tools::cmdline::CmdLineUtil;
                using opennlp::tools::cmdline::TerminateToolException;
                using opennlp::tools::cmdline::params::TrainingToolParams;
                using opennlp::tools::parser::Parse;
                using opennlp::tools::parser::ParserModel;
                using opennlp::tools::util::ObjectStream;

                /// <summary>
                /// Abstract base class for tools which update the parser model.
                /// </summary>
                class ModelUpdaterTool : public CmdLineTool
                {

              public:
                  class ModelUpdaterParams : public TrainingToolParams
                  {

                  };

              protected:
                  virtual ParserModel *trainAndUpdate(ParserModel *originalModel, ObjectStream<Parse*> *parseSamples, ModelUpdaterParams *parameters) = 0;

              public:
                  virtual std::string getHelp();

                  void run(std::string args[]);
                };

            }
        }
    }
}


#endif	//#ifndef MODELUPDATERTOOL
