#ifndef BUILDMODELUPDATERTOOL
#define BUILDMODELUPDATERTOOL

#include "ModelUpdaterTool.h"
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


                using opennlp::model::AbstractModel;
                using opennlp::tools::dictionary::Dictionary;
                using opennlp::tools::parser::Parse;
                using opennlp::tools::parser::ParserEventTypeEnum;
                using opennlp::tools::parser::ParserModel;
                using opennlp::tools::parser::chunking::Parser;
                using opennlp::tools::parser::chunking::ParserEventStream;
                using opennlp::tools::util::ObjectStream;

                class BuildModelUpdaterTool : public ModelUpdaterTool
                {

              public:
                  std::string getName();

                  std::string getShortDescription();

              protected:
                  virtual ParserModel *trainAndUpdate(ParserModel *originalModel, ObjectStream<Parse*> *parseSamples, ModelUpdaterParams *parameters) throw(IOException);
                };

            }
        }
    }
}


#endif	//#ifndef BUILDMODELUPDATERTOOL
