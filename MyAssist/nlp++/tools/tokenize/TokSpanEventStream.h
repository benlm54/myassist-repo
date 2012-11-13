#ifndef TOKSPANEVENTSTREAM
#define TOKSPANEVENTSTREAM

#include "TokenSample.h"
#include "../tools/util/AbstractEventStream.h"
#include "TokenContextGenerator.h"
#include "../tools/util/ObjectStream.h"
#include "../model/Event.h"
#include "AbstractEventStream<TokenSample>.h"
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
        namespace tokenize
        {


            using opennlp::model::Event;
            using opennlp::tools::tokenize::lang::Factory;
            using opennlp::tools::util::AbstractEventStream;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::Span;

            /// <summary>
            /// This class reads the <seealso cref="TokenSample"/>s from the given <seealso cref="Iterator"/>
            /// and converts the <seealso cref="TokenSample"/>s into <seealso cref="Event"/>s which
            /// can be used by the maxent library for training.
            /// </summary>
            class TokSpanEventStream : public AbstractEventStream<TokenSample*>
            {

          private:
              static Logger *logger;

              TokenContextGenerator *cg;

              bool skipAlphaNumerics;

              Pattern *const alphaNumeric;

              /// <summary>
              /// Initializes the current instance.
              /// </summary>
              /// <param name="tokenSamples"> </param>
              /// <param name="skipAlphaNumerics"> </param>
              /// <param name="cg"> </param>
          public:
              TokSpanEventStream(ObjectStream<TokenSample*> *tokenSamples, bool skipAlphaNumerics, Pattern *alphaNumeric, TokenContextGenerator *cg);

              /// <summary>
              /// Initializes the current instance.
              /// </summary>
              /// <param name="tokenSamples"> </param>
              /// <param name="skipAlphaNumerics"> </param>
              /// <param name="cg"> </param>
              TokSpanEventStream(ObjectStream<TokenSample*> *tokenSamples, bool skipAlphaNumerics, TokenContextGenerator *cg);

              /// <summary>
              /// Initializes the current instance.
              /// </summary>
              /// <param name="tokenSamples"> </param>
              /// <param name="skipAlphaNumerics"> </param>
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              TokSpanEventStream(ObjectStream<TokenSample*> *tokenSamples, bool skipAlphaNumerics); //this(tokenSamples, skipAlphaNumerics, new DefaultTokenContextGenerator());

              /// <summary>
              /// Adds training events to the event stream for each of the specified tokens.
              /// </summary>
              /// <param name="tokens"> character offsets into the specified text. </param>
              /// <param name="text"> The text of the tokens. </param>
          protected:
              virtual Iterator<Event*> *createEvents(TokenSample *tokenSample);
            };

        }
    }
}


#endif	//#ifndef TOKSPANEVENTSTREAM
