#ifndef CHUNKERDETAILEDFMEASURELISTENER
#define CHUNKERDETAILEDFMEASURELISTENER

#include "../tools/chunker/ChunkerEvaluationMonitor.h"
#include "../tools/chunker/ChunkSample.h"
#include "../tools/cmdline/DetailedFMeasureListener.h"
#include "../tools/util/Span.h"
#include "ChunkSample>.h"

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
            namespace chunker
            {

                using opennlp::tools::chunker::ChunkSample;
                using opennlp::tools::chunker::ChunkerEvaluationMonitor;
                using opennlp::tools::cmdline::DetailedFMeasureListener;
                using opennlp::tools::util::Span;

                class ChunkerDetailedFMeasureListener : public DetailedFMeasureListener<ChunkSample*>, public ChunkerEvaluationMonitor
                {

              protected:
                  virtual Span *asSpanArray(ChunkSample *sample);


                };

            }
        }
    }
}


#endif	//#ifndef CHUNKERDETAILEDFMEASURELISTENER
