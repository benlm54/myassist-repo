#ifndef DOCUMENTCATEGORIZEREVENTSTREAM
#define DOCUMENTCATEGORIZEREVENTSTREAM

#include "DocumentSample.h"
#include "../tools/util/AbstractEventStream.h"
#include "DocumentCategorizerContextGenerator.h"
#include "../tools/util/ObjectStream.h"
#include "../model/Event.h"
#include "AbstractEventStream<DocumentSample>.h"

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
        namespace doccat
        {


            using opennlp::model::Event;
            using opennlp::tools::util::AbstractEventStream;
            using opennlp::tools::util::ObjectStream;

            /// <summary>
            /// Iterator-like class for modeling document classification events.
            /// </summary>
            class DocumentCategorizerEventStream : public AbstractEventStream<DocumentSample*>
            {

          private:
              DocumentCategorizerContextGenerator *mContextGenerator;

              /// <summary>
              /// Initializes the current instance.
              /// </summary>
              /// <param name="data"> <seealso cref="ObjectStream"/> of <seealso cref="DocumentSample"/>s
              /// </param>
              /// <param name="featureGenerators"> </param>
          public:
//ORIGINAL LINE: public DocumentCategorizerEventStream(opennlp.tools.util.ObjectStream<DocumentSample> data, FeatureGenerator... featureGenerators)
//JAVA TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
              DocumentCategorizerEventStream(ObjectStream<DocumentSample*> *data, ...);

              /// <summary>
              /// Initializes the current instance.
              /// </summary>
              /// <param name="samples"> <seealso cref="ObjectStream"/> of <seealso cref="DocumentSample"/>s </param>
              DocumentCategorizerEventStream(ObjectStream<DocumentSample*> *samples);

          protected:
              virtual Iterator<Event*> *createEvents(DocumentSample *const sample);

                    private:
                        class IteratorAnonymousInnerClassHelper : public Iterator<Event*>
                        {

                        private:
                            bool isVirgin;

                        public:
                            virtual bool hasNext();

                            virtual Event *next();

                            virtual void remove();
                        };
            };

        }
    }
}


#endif	//#ifndef DOCUMENTCATEGORIZEREVENTSTREAM
