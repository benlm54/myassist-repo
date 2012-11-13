#ifndef CMDLINETOOL
#define CMDLINETOOL

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
            /// A tool which can be executed from the command line.
            /// <p>
            /// <b>Note:</b> Do not use this class, internal use only!
            /// </summary>
            class CmdLineTool
            {

              /// <summary>
              /// Retrieves the name of the training data tool. The name (used as command)
              /// must not contain white spaces.
              /// </summary>
              /// <returns> the name of the command line tool </returns>
          public:
              virtual std::string getName() = 0;

              /// <summary>
              /// Retrieves a short description of what the tool does.
              /// 
              /// @return
              /// </summary>
              virtual std::string getShortDescription() = 0;

              /// <summary>
              /// Retrieves a description on how to use the tool.
              /// 
              /// @return
              /// </summary>
              virtual std::string getHelp() = 0;

              /// <summary>
              /// Executes the tool with the given parameters.
              /// </summary>
              /// <param name="args"> </param>
              virtual void run(std::string args[]) = 0;
            };

        }
    }
}


#endif	//#ifndef CMDLINETOOL
