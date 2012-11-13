#ifndef PARSEREVENTSTREAM
#define PARSEREVENTSTREAM

#include "../tools/parser/AbstractParserEventStream.h"
#include "BuildContextGenerator.h"
#include "../tools/parser/treeinsert/BuildContextGenerator.h"
#include "CheckContextGenerator.h"
#include "../tools/parser/treeinsert/CheckContextGenerator.h"
#include "../tools/dictionary/Dictionary.h"
#include "../tools/parser/HeadRules.h"
#include "../tools/parser/Parse.h"
#include "../tools/parser/ParserEventTypeEnum.h"
#include "../tools/util/ObjectStream.h"
#include "../model/Event.h"
#include "../tools/util/InvalidFormatException.h"
#include <string>
#include <vector>

/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreemnets.  See the NOTICE file distributed with
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
        namespace parser
        {
            namespace chunking
            {


                using opennlp::model::Event;
                using opennlp::tools::dictionary::Dictionary;
                using opennlp::tools::parser::AbstractBottomUpParser;
                using opennlp::tools::parser::AbstractParserEventStream;
                using opennlp::tools::parser::HeadRules;
                using opennlp::tools::parser::Parse;
                using opennlp::tools::parser::ParseSampleStream;
                using opennlp::tools::parser::ParserEventTypeEnum;
                using opennlp::tools::util::InvalidFormatException;
                using opennlp::tools::util::ObjectStream;
                using opennlp::tools::util::PlainTextByLineStream;

                /// <summary>
                /// Wrapper class for one of four parser event streams.  The particular event stream is specified
                /// at construction.
                /// </summary>
                class ParserEventStream : public AbstractParserEventStream
                {

              protected:
                  BuildContextGenerator *bcg;
                  CheckContextGenerator *kcg;

                  /// <summary>
                  /// Create an event stream based on the specified data stream of the specified type using the specified head rules. </summary>
                  /// <param name="d"> A 1-parse-per-line Penn Treebank Style parse. </param>
                  /// <param name="rules"> The head rules. </param>
                  /// <param name="etype"> The type of events desired (tag, chunk, build, or check). </param>
                  /// <param name="dict"> A tri-gram dictionary to reduce feature generation. </param>
              public:
                  ParserEventStream(ObjectStream<Parse*> *d, HeadRules *rules, ParserEventTypeEnum etype, Dictionary *dict);

              protected:
                  virtual void init();



              public:
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
                  ParserEventStream(ObjectStream<Parse*> *d, HeadRules *rules, ParserEventTypeEnum etype); //this(d,rules,etype,nullptr);

                  /// <summary>
                  /// Returns true if the specified child is the first child of the specified parent. </summary>
                  /// <param name="child"> The child parse. </param>
                  /// <param name="parent"> The parent parse. </param>
                  /// <returns> true if the specified child is the first child of the specified parent; false otherwise. </returns>
              protected:
                  virtual bool firstChild(Parse *child, Parse *parent);

              public:
                  static Parse *reduceChunks(Parse chunks[], int ci, Parse *parent);

                  /// <summary>
                  /// Adds events for parsing (post tagging and chunking to the specified list of events for the specified parse chunks. </summary>
                  /// <param name="parseEvents"> The events for the specified chunks. </param>
                  /// <param name="chunks"> The incomplete parses to be parsed. </param>
              protected:
                  virtual void addParseEvents(std::vector<Event*> &parseEvents, Parse chunks[]);

                  static void main(std::string args[]) throw(java::io::IOException, InvalidFormatException);
                };


            }
        }
    }
}


#endif	//#ifndef PARSEREVENTSTREAM
