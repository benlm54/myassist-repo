#ifndef CLI
#define CLI

#include "CmdLineTool.h"
#include <string>
#include <vector>
#include <list>
#include <cmath>

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


            using opennlp::tools::cmdline::chunker::ChunkerConverterTool;
            using opennlp::tools::cmdline::chunker::ChunkerCrossValidatorTool;
            using opennlp::tools::cmdline::chunker::ChunkerEvaluatorTool;
            using opennlp::tools::cmdline::chunker::ChunkerMETool;
            using opennlp::tools::cmdline::chunker::ChunkerTrainerTool;
            using opennlp::tools::cmdline::dictionary::DictionaryBuilderTool;
            using opennlp::tools::cmdline::doccat::DoccatConverterTool;
            using opennlp::tools::cmdline::doccat::DoccatTool;
            using opennlp::tools::cmdline::doccat::DoccatTrainerTool;
            using opennlp::tools::cmdline::namefind::CensusDictionaryCreatorTool;
            using opennlp::tools::cmdline::namefind::TokenNameFinderConverterTool;
            using opennlp::tools::cmdline::namefind::TokenNameFinderCrossValidatorTool;
            using opennlp::tools::cmdline::namefind::TokenNameFinderEvaluatorTool;
            using opennlp::tools::cmdline::namefind::TokenNameFinderTool;
            using opennlp::tools::cmdline::namefind::TokenNameFinderTrainerTool;
            using opennlp::tools::cmdline::parser::BuildModelUpdaterTool;
            using opennlp::tools::cmdline::parser::CheckModelUpdaterTool;
            using opennlp::tools::cmdline::parser::ParserTool;
            using opennlp::tools::cmdline::parser::ParserTrainerTool;
            using opennlp::tools::cmdline::parser::TaggerModelReplacerTool;
            using opennlp::tools::cmdline::postag::POSTaggerConverter;
            using opennlp::tools::cmdline::postag::POSTaggerCrossValidatorTool;
            using opennlp::tools::cmdline::postag::POSTaggerEvaluatorTool;
            using opennlp::tools::cmdline::postag::POSTaggerTrainerTool;
            using opennlp::tools::cmdline::sentdetect::SentenceDetectorConverterTool;
            using opennlp::tools::cmdline::sentdetect::SentenceDetectorCrossValidatorTool;
            using opennlp::tools::cmdline::sentdetect::SentenceDetectorEvaluatorTool;
            using opennlp::tools::cmdline::sentdetect::SentenceDetectorTool;
            using opennlp::tools::cmdline::sentdetect::SentenceDetectorTrainerTool;
            using opennlp::tools::cmdline::tokenizer::DictionaryDetokenizerTool;
            using opennlp::tools::cmdline::tokenizer::SimpleTokenizerTool;
            using opennlp::tools::cmdline::tokenizer::TokenizerConverterTool;
            using opennlp::tools::cmdline::tokenizer::TokenizerCrossValidatorTool;
            using opennlp::tools::cmdline::tokenizer::TokenizerMEEvaluatorTool;
            using opennlp::tools::cmdline::tokenizer::TokenizerMETool;
            using opennlp::tools::cmdline::tokenizer::TokenizerTrainerTool;

            class CLI
            {

          public:
              static const std::string CMD;

          private:
              static Map<std::string, CmdLineTool*> *toolLookupMap;

//JAVA TO C++ CONVERTER TODO TASK: Static constructors are not allowed in native C++:
              static CLI();

              /// <returns> a set which contains all tool names </returns>
          public:
              static Set<std::string> *getToolNames();

          private:
              static void usage();

              static void main(std::string args[]);
            };

        }
    }
}


#endif	//#ifndef CLI
