#ifndef PARSEREVENTSTREAM
#define PARSEREVENTSTREAM

#include "../tools/parser/AbstractParserEventStream.h"
#include "AttachContextGenerator.h"
#include "../tools/parser/chunking/BuildContextGenerator.h"
#include "BuildContextGenerator.h"
#include "../tools/parser/chunking/CheckContextGenerator.h"
#include "CheckContextGenerator.h"
#include "../tools/dictionary/Dictionary.h"
#include "../tools/parser/HeadRules.h"
#include "../tools/parser/Parse.h"
#include "../tools/parser/ParserEventTypeEnum.h"
#include "../tools/util/ObjectStream.h"
#include "../model/Event.h"
#include "../tools/util/InvalidFormatException.h"
#include <string>
#include <map>
#include <vector>
#include <stdexcept>

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
            namespace treeinsert
            {


                using opennlp::maxent::io::SuffixSensitiveGISModelReader;
                using opennlp::model::AbstractModel;
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
                using opennlp::tools::util::Span;

                class ParserEventStream : public AbstractParserEventStream
                {

              protected:
                  AttachContextGenerator *attachContextGenerator;
                  BuildContextGenerator *buildContextGenerator;
                  CheckContextGenerator *checkContextGenerator;

              private:
                  static const bool debug = false;

              public:
                  ParserEventStream(ObjectStream<Parse*> *d, HeadRules *rules, ParserEventTypeEnum etype, Dictionary *dict);

                  virtual void init();

                  ParserEventStream(ObjectStream<Parse*> *d, HeadRules *rules, ParserEventTypeEnum etype);

                  /// <summary>
                  /// Returns a set of parent nodes which consist of the immediate
                  /// parent of the specified node and any of its parent which
                  /// share the same syntactic type. </summary>
                  /// <param name="node"> The node whose parents are to be returned. </param>
                  /// <returns> a set of parent nodes. </returns>
              private:
                  Map<Parse*, int> *getNonAdjoinedParent(Parse *node);

                  int indexOf(Parse *child, Parse *parent);

                  int nonPunctChildCount(Parse *node);
                  /*
                  private Set getNonAdjoinedParent(Parse node) {
                    Set parents = new HashSet();
                    Parse parent = node.getParent();
                    do {
                      parents.add(parent);
                      parent = parent.getParent();
                    }
                    while(parent.getType().equals(node.getType()));
                    return parents;
                  }
                  */

              protected:
                  virtual bool lastChild(Parse *child, Parse *parent);

                  virtual void addParseEvents(std::vector<Event*> &parseEvents, Parse chunks[]);

                  static void main(std::string args[]) throw(java::io::IOException, InvalidFormatException);
                };
            }
        }
    }
}


#endif	//#ifndef PARSEREVENTSTREAM
