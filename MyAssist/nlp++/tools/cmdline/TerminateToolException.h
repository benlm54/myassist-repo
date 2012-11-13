#ifndef TERMINATETOOLEXCEPTION
#define TERMINATETOOLEXCEPTION

#include "RuntimeException.h"
#include <string>
#include <stdexcept>

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

            /// <summary>
            /// Exception to terminate the execution of a command line tool.
            /// <p>
            /// The exception should be thrown to indicate that the VM should be terminated with
            /// the specified error code, instead of just calling <seealso cref="System#exit(int)"/>.
            /// <p>
            /// <b>Note:</b> Do not use this class, internal use only!
            /// </summary>
            class TerminateToolException : public std::exception
            {

          private:
              static const long long serialVersionUID = 1LL;

              const int code;
              const std::string message;

          public:
              TerminateToolException(int code, const std::string &message);

//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              TerminateToolException(int code); //this(code, nullptr);

              virtual int getCode();

              virtual std::string getMessage();
            };

        }
    }
}


#endif	//#ifndef TERMINATETOOLEXCEPTION
