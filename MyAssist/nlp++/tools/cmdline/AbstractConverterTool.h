#ifndef ABSTRACTCONVERTERTOOL
#define ABSTRACTCONVERTERTOOL

#include "CmdLineTool.h"
#include "CLI.h"
#include "ObjectStreamFactory.h"
#include "TerminateToolException.h"
#include "../tools/util/ObjectStream.h"
#include "CmdLineUtil.h"
#include "T.h"
#include <string>

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


            using opennlp::tools::util::ObjectStream;

            template<typename T>
            class AbstractConverterTool : public CmdLineTool
            {

          private:
              std::string createHelpString(const std::string &format, const std::string &usage)
              {
                return "Usage: " + CLI::CMD + " " + getName() + " " + format + " " + usage;
              }

          public:
              virtual std::string getHelp()
              {
                return createHelpString("format", "...");
              }

          protected:
              virtual ObjectStreamFactory<T> *createStreamFactory(const std::string &format) = 0;

          public:
              virtual void run(std::string args[])
              {

                std::string format = "";
                if (sizeof(args) / sizeof(args[0]) > 0)
                {
                  format = args[0];
                }
                else
                {
                  std::cout << getHelp() << std::endl;
                  throw TerminateToolException(1);
                }

                ObjectStreamFactory<T> *streamFactory = createStreamFactory(format);

                if (streamFactory == 0)
                {
                  // TODO: print list of available formats
                  System::err::println("Format is unkown: " + format);
                  throw TerminateToolException(-1);
                }

                std::string formatArgs[sizeof(args) / sizeof(args[0]) - 1];
                System::arraycopy(args, 1, formatArgs, 0, sizeof(formatArgs) / sizeof(formatArgs[0]));

                if (!streamFactory->validateArguments(formatArgs))
                {
                  System::err::println(createHelpString(format, streamFactory->getUsage()));
                  throw TerminateToolException(-1);
                }

                ObjectStream<T> *sampleStream = streamFactory->create(formatArgs);

                try
                {
                  void *sample;
                  while ((sample = sampleStream->read()) != 0)
                  {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                    std::cout << sample->toString() << std::endl;
                  }
                }
                catch (IOException e)
                {
                  CmdLineUtil::printTrainingIoError(e);
                  throw TerminateToolException(-1);
                }
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
                finally
                {
                  if (sampleStream != 0)
                    try
                    {
                      sampleStream->close();
                    }
                    catch (IOException e)
                    {
                      // sorry that this can fail
                    }
                }
              }
            };

        }
    }
}


#endif	//#ifndef ABSTRACTCONVERTERTOOL
