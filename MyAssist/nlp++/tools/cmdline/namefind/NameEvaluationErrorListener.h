#ifndef NAMEEVALUATIONERRORLISTENER
#define NAMEEVALUATIONERRORLISTENER

#include "../tools/cmdline/EvaluationErrorPrinter.h"
#include "../tools/namefind/NameSample.h"
#include "../tools/namefind/TokenNameFinderEvaluationMonitor.h"
#include "NameSample>.h"

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
        namespace cmdline
        {
            namespace namefind
            {


                using opennlp::tools::cmdline::EvaluationErrorPrinter;
                using opennlp::tools::namefind::NameSample;
                using opennlp::tools::namefind::TokenNameFinderEvaluationMonitor;
                using opennlp::tools::util::eval::EvaluationMonitor;

                /// <summary>
                /// A default implementation of <seealso cref="EvaluationMonitor"/> that prints
                /// to an output stream.
                /// 
                /// </summary>
                class NameEvaluationErrorListener : public EvaluationErrorPrinter<NameSample*>, public TokenNameFinderEvaluationMonitor
                {

                  /// <summary>
                  /// Creates a listener that will print to System.err
                  /// </summary>
              public:
                  NameEvaluationErrorListener();

                  /// <summary>
                  /// Creates a listener that will print to a given <seealso cref="OutputStream"/>
                  /// </summary>
                  NameEvaluationErrorListener(OutputStream *outputStream);

                  virtual void missclassified(NameSample *reference, NameSample *prediction);

                };

            }
        }
    }
}


#endif	//#ifndef NAMEEVALUATIONERRORLISTENER
