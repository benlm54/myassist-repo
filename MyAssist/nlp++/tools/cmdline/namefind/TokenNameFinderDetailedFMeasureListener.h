#ifndef TOKENNAMEFINDERDETAILEDFMEASURELISTENER
#define TOKENNAMEFINDERDETAILEDFMEASURELISTENER

#include "../tools/cmdline/DetailedFMeasureListener.h"
#include "../tools/namefind/NameSample.h"
#include "../tools/namefind/TokenNameFinderEvaluationMonitor.h"
#include "../tools/util/Span.h"
#include "NameSample>.h"

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
            namespace namefind
            {

                using opennlp::tools::cmdline::DetailedFMeasureListener;
                using opennlp::tools::namefind::NameSample;
                using opennlp::tools::namefind::TokenNameFinderEvaluationMonitor;
                using opennlp::tools::util::Span;

                class TokenNameFinderDetailedFMeasureListener : public DetailedFMeasureListener<NameSample*>, public TokenNameFinderEvaluationMonitor
                {

              protected:
                  virtual Span *asSpanArray(NameSample *sample);

                };

            }
        }
    }
}


#endif	//#ifndef TOKENNAMEFINDERDETAILEDFMEASURELISTENER
