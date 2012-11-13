#ifndef POSSAMPLEEVENTSTREAM
#define POSSAMPLEEVENTSTREAM

#include "POSSample.h"
#include "../tools/util/AbstractEventStream.h"
#include "POSContextGenerator.h"
#include "../tools/util/ObjectStream.h"
#include "../model/Event.h"
#include "AbstractEventStream<POSSample>.h"
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
        namespace postag
        {


            using opennlp::model::Event;
            using opennlp::tools::util::AbstractEventStream;
            using opennlp::tools::util::ObjectStream;

            /// <summary>
            /// This class reads the <seealso cref="POSSample"/>s from the given <seealso cref="Iterator"/>
            /// and converts the <seealso cref="POSSample"/>s into <seealso cref="Event"/>s which
            /// can be used by the maxent library for training.
            /// </summary>
            class POSSampleEventStream : public AbstractEventStream<POSSample*>
            {

              /// <summary>
              /// The <seealso cref="POSContextGenerator"/> used
              /// to create the training <seealso cref="Event"/>s.
              /// </summary>
          private:
              POSContextGenerator *cg;

              /// <summary>
              /// Initializes the current instance with the given samples and the
              /// given <seealso cref="POSContextGenerator"/>.
              /// </summary>
              /// <param name="samples"> </param>
              /// <param name="cg"> </param>
          public:
              POSSampleEventStream(ObjectStream<POSSample*> *samples, POSContextGenerator *cg);

              /// <summary>
              /// Initializes the current instance with given samples
              /// and a <seealso cref="DefaultPOSContextGenerator"/>. </summary>
              /// <param name="samples"> </param>
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              POSSampleEventStream(ObjectStream<POSSample*> *samples); //this(samples, new DefaultPOSContextGenerator(nullptr));

          protected:
              virtual Iterator<Event*> *createEvents(POSSample *sample);

          public:
              static std::vector<Event*> generateEvents(std::string sentence[], std::string tags[], POSContextGenerator *cg);
            };

        }
    }
}


#endif	//#ifndef POSSAMPLEEVENTSTREAM
