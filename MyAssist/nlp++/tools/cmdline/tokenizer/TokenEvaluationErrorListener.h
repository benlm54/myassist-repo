#ifndef TOKENEVALUATIONERRORLISTENER
#define TOKENEVALUATIONERRORLISTENER

#include "../tools/cmdline/EvaluationErrorPrinter.h"
#include "../tools/tokenize/TokenizerEvaluationMonitor.h"
#include "../tools/tokenize/TokenSample.h"
#include "TokenSample>.h"

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
            namespace tokenizer
            {


                using opennlp::tools::cmdline::EvaluationErrorPrinter;
                using opennlp::tools::tokenize::TokenSample;
                using opennlp::tools::tokenize::TokenizerEvaluationMonitor;
                using opennlp::tools::util::eval::EvaluationMonitor;

                /// <summary>
                /// A default implementation of <seealso cref="EvaluationMonitor"/> that prints
                /// to an output stream.
                /// 
                /// </summary>
                class TokenEvaluationErrorListener : public EvaluationErrorPrinter<TokenSample*>, public TokenizerEvaluationMonitor
                {

                  /// <summary>
                  /// Creates a listener that will print to System.err
                  /// </summary>
              public:
                  TokenEvaluationErrorListener();

                  /// <summary>
                  /// Creates a listener that will print to a given <seealso cref="OutputStream"/>
                  /// </summary>
                  TokenEvaluationErrorListener(OutputStream *outputStream);

                  virtual void missclassified(TokenSample *reference, TokenSample *prediction);

                };

            }
        }
    }
}


#endif	//#ifndef TOKENEVALUATIONERRORLISTENER
