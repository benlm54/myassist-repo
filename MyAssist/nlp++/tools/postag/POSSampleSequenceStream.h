#ifndef POSSAMPLESEQUENCESTREAM
#define POSSAMPLESEQUENCESTREAM

#include "../model/SequenceStream.h"
#include "POSContextGenerator.h"
#include "POSSample.h"
#include "../tools/util/ObjectStream.h"
#include "../model/AbstractModel.h"
#include "../model/Event.h"
#include "../model/Sequence.h"
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


            using opennlp::model::AbstractModel;
            using opennlp::model::Event;
            using opennlp::model::Sequence;
            using opennlp::model::SequenceStream;
            using opennlp::tools::util::ObjectStream;

            class POSSampleSequenceStream : public SequenceStream
            {

          private:
              POSContextGenerator *pcg;
              std::vector<POSSample*> samples;

          public:
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              POSSampleSequenceStream(ObjectStream<POSSample*> *psi) throw(IOException); //this(psi, new DefaultPOSContextGenerator(nullptr));

              POSSampleSequenceStream(ObjectStream<POSSample*> *psi, POSContextGenerator *pcg) throw(IOException);


//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @SuppressWarnings("unchecked") public opennlp.model.Event[] updateContext(opennlp.model.Sequence sequence, opennlp.model.AbstractModel model)
              virtual Event *updateContext(Sequence *sequence, AbstractModel *model);

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @SuppressWarnings("unchecked") public java.util.Iterator<opennlp.model.Sequence> iterator()
              virtual Iterator<Sequence*> *iterator();

            };

            class POSSampleSequenceIterator : public Iterator<Sequence*>
            {

          private:
              Iterator<POSSample*> *psi;
              POSContextGenerator *cg;

          public:
              POSSampleSequenceIterator(Iterator<POSSample*> *psi);

              virtual bool hasNext();

              virtual Sequence<POSSample*> *next();

              virtual void remove();

            };


        }
    }
}


#endif	//#ifndef POSSAMPLESEQUENCESTREAM
