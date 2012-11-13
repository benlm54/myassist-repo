#ifndef PERFORMANCEMONITOR
#define PERFORMANCEMONITOR

#include "Runnable.h"
#include <string>

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


            /// <summary>
            /// The <seealso cref="PerformanceMonitor"/> measures increments to a counter.
            /// During the computation it prints out current and average throughput
            /// per second. After the computation is done it prints a final performance
            /// report.
            /// <p>
            /// <b>Note:</b>
            /// This class is not thread safe. <br>
            /// Do not use this class, internal use only!
            /// </summary>
            class PerformanceMonitor
            {

          private:
              ScheduledExecutorService *scheduler;

              const std::string unit;

//JAVA TO C++ CONVERTER TODO TASK: Java wildcard generics are not converted to C++:
//ORIGINAL LINE: private java.util.concurrent.ScheduledFuture<?> beeperHandle;
              ScheduledFuture<?> *beeperHandle;

              volatile long long startTime;

              volatile int counter;

              PrintStream *const out;

          public:
              PerformanceMonitor(PrintStream *out, const std::string &unit);

//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              PerformanceMonitor(const std::string &unit); //this(System.out, unit);

              virtual bool isStarted();

              virtual void incrementCounter(int increment);

              virtual void incrementCounter();

              virtual void start();


              virtual void startAndPrintThroughput();

                    private:
                        class RunnableAnonymousInnerClassHelper : public Runnable
                        {

                        private:
                            long long lastTimeStamp;
                            int lastCount;

                        public:
                            virtual void run();
                        };

          public:
              virtual void stopAndPrintFinalResult();

            private:
                void InitializeInstanceFields();
            };

        }
    }
}


#endif	//#ifndef PERFORMANCEMONITOR
