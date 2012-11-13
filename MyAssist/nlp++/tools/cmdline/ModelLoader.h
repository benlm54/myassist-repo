#ifndef MODELLOADER
#define MODELLOADER

#include "CmdLineUtil.h"
#include "../tools/util/InvalidFormatException.h"
#include "TerminateToolException.h"
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


            using opennlp::tools::util::InvalidFormatException;

            /// <summary>
            /// Loads a model and does all the error handling for the command line tools.
            /// <p>
            /// <b>Note:</b> Do not use this class, internal use only!
            /// </summary>
            /// @param <T> </param>
            template<typename T>
            class ModelLoader
            {

          private:
              const std::string modelName;

          protected:
              ModelLoader(const std::string &modelName) : modelName(modelName)
              {

                if (modelName == "")
                  throw IllegalArgumentException("modelName must not be null!");

              }

              virtual T loadModel(InputStream *modelIn) = 0;

          public:
              virtual T load(File *modelFile)
              {

                long long beginModelLoadingTime = System::currentTimeMillis();

                CmdLineUtil::checkInputFile(modelName + " model", modelFile);

                System::err::print("Loading " + modelName + " model ... ");

                InputStream *modelIn = new BufferedInputStream(CmdLineUtil::openInFile(modelFile), CmdLineUtil::IO_BUFFER_SIZE);

                T model;

                try
                {
                  model = loadModel(modelIn);
                }
                catch (InvalidFormatException e)
                {
                  System::err::println("failed");
                  System::err::println("Model has invalid format: " + e->getMessage());
                  throw TerminateToolException(-1);
                }
                catch (IOException e)
                {
                  System::err::println("failed");
                  System::err::println("IO error while loading model: " + e->getMessage());
                  throw TerminateToolException(-1);
                }
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
                finally
                {
                  // will not be null because openInFile would 
                  // terminate in this case
                  try
                  {
                    modelIn->close();
                  }
                  catch (IOException e)
                  {
                    // sorry that this can fail
                  }
                }

                long long modelLoadingDuration = System::currentTimeMillis() - beginModelLoadingTime;

                System::err::printf("done (%.3fs)\n", modelLoadingDuration / 1000);

                return model;
              }
            };

        }
    }
}


#endif	//#ifndef MODELLOADER
