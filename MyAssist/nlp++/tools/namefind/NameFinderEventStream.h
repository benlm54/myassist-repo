#ifndef NAMEFINDEREVENTSTREAM
#define NAMEFINDEREVENTSTREAM

#include "NameSample.h"
#include "../tools/util/AbstractEventStream.h"
#include "NameContextGenerator.h"
#include "../tools/util/featuregen/AdditionalContextFeatureGenerator.h"
#include "../tools/util/ObjectStream.h"
#include "../tools/util/Span.h"
#include "../model/Event.h"
#include "AbstractEventStream<NameSample>.h"
#include <string>
#include <vector>

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
        namespace namefind
        {


            using opennlp::model::Event;
            using opennlp::model::EventStream;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::PlainTextByLineStream;
            using opennlp::tools::util::Span;
            using opennlp::tools::util::featuregen::AdditionalContextFeatureGenerator;
            using opennlp::tools::util::featuregen::WindowFeatureGenerator;

            /// <summary>
            /// Class for creating an event stream out of data files for training an name
            /// finder.
            /// </summary>
            class NameFinderEventStream : public opennlp::tools::util::AbstractEventStream<NameSample*>
            {

          private:
              NameContextGenerator *contextGenerator;

              AdditionalContextFeatureGenerator *additionalContextFeatureGenerator;

              std::string type;

              /// <summary>
              /// Creates a new name finder event stream using the specified data stream and context generator. </summary>
              /// <param name="dataStream"> The data stream of events. </param>
              /// <param name="type"> null or overrides the type parameter in the provided samples </param>
              /// <param name="contextGenerator"> The context generator used to generate features for the event stream. </param>
          public:
              NameFinderEventStream(ObjectStream<NameSample*> *dataStream, const std::string &type, NameContextGenerator *contextGenerator);

//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              NameFinderEventStream(ObjectStream<NameSample*> *dataStream); //this(dataStream, nullptr, new DefaultNameContextGenerator());

              /// <summary>
              /// Generates the name tag outcomes (start, continue, other) for each token in a sentence
              /// with the specified length using the specified name spans. </summary>
              /// <param name="names"> Token spans for each of the names. </param>
              /// <param name="type"> null or overrides the type parameter in the provided samples </param>
              /// <param name="length"> The length of the sentence. </param>
              /// <returns> An array of start, continue, other outcomes based on the specified names and sentence length. </returns>
              static std::string *generateOutcomes(Span names[], const std::string &type, int length);

              static std::vector<Event*> generateEvents(std::string sentence[], std::string outcomes[], NameContextGenerator *cg);

          protected:
              virtual Iterator<Event*> *createEvents(NameSample *sample);


              /// <summary>
              /// Generated previous decision features for each token based on contents of the specified map. </summary>
              /// <param name="tokens"> The token for which the context is generated. </param>
              /// <param name="prevMap"> A mapping of tokens to their previous decisions. </param>
              /// <returns> An additional context array with features for each token. </returns>
          public:
              static std::string **additionalContext(std::string tokens[], Map<std::string, std::string> *prevMap);

              // Will be removed soon!
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated public static final void main(String[] args) throws java.io.IOException
              static void main(std::string args[]) throw(java::io::IOException);

            private:
                void InitializeInstanceFields();
            };

        }
    }
}


#endif	//#ifndef NAMEFINDEREVENTSTREAM
