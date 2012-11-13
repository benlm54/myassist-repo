#ifndef CMDLINEUTIL
#define CMDLINEUTIL

#include "../tools/util/model/BaseModel.h"
#include "../tools/util/TrainingParameters.h"
#include "NumberFormatException.h"
#include <string>
#include <vector>
#include <algorithm>
#include "stringconverter.h"

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


            using opennlp::model::TrainUtil;
            using opennlp::tools::util::TrainingParameters;
            using opennlp::tools::util::model::BaseModel;

            /// <summary>
            /// Util class for the command line interface.
            /// <p>
            /// <b>Note:</b> Do not use this class, internal use only!
            /// </summary>
            class CmdLineUtil
            {

         public:
             static const int IO_BUFFER_SIZE = 1024 * 1024;

          private:
              CmdLineUtil();

              /// <summary>
              /// Check that the given input file is valid.
              /// <p>
              /// To pass the test it must:<br>
              /// - exist<br>
              /// - not be a directory<br>
              /// - accessibly<br>
              /// </summary>
              /// <param name="name"> the name which is used to refer to the file in an error message, it
              /// should start with a capital letter.
              /// </param>
              /// <param name="inFile"> the particular file to check to qualify an input file
              /// </param>
              /// <exception cref="TerminateToolException">  if test does not pass this exception is
              /// thrown and an error message is printed to the console. </exception>
          public:
              static void checkInputFile(const std::string &name, File *inFile);

              /// <summary>
              /// Tries to ensure that it is possible to write to an output file. 
              /// <p>
              /// The method does nothing if it is possible to write otherwise
              /// it prints an appropriate error message and a <seealso cref="TerminateToolException"/> is thrown.
              /// <p>
              /// Computing the contents of an output file (e.g. ME model) can be very time consuming.
              /// Prior to this computation it should be checked once that writing this output file is
              /// possible to be able to fail fast if not. If this validation is only done after a time
              /// consuming computation it could frustrate the user.
              /// </summary>
              /// <param name="name"> </param>
              /// <param name="outFile"> </param>
              static void checkOutputFile(const std::string &name, File *outFile);

              static FileInputStream *openInFile(File *file);

              /// <summary>
              /// Writes a <seealso cref="BaseModel"/> to disk. Occurring errors are printed to the console
              /// to inform the user.
              /// </summary>
              /// <param name="modelName"> type of the model, name is used in error messages. </param>
              /// <param name="modelFile"> output file of the model </param>
              /// <param name="model"> the model itself which should be written to disk </param>
              static void writeModel(const std::string &modelName, File *modelFile, BaseModel *model);

              /// <summary>
              /// Retrieves the specified parameters from the given arguments.
              /// </summary>
              /// <param name="param"> </param>
              /// <param name="args">
              /// @return </param>
              static std::string getParameter(const std::string &param, std::string args[]);

              /// <summary>
              /// Retrieves the specified parameters from the specified arguments.
              /// </summary>
              /// <param name="param"> </param>
              /// <param name="args">
              /// @return </param>
              static int getIntParameter(const std::string &param, std::string args[]);

              /// <summary>
              /// Retrieves the specified parameters from the specified arguments.
              /// </summary>
              /// <param name="param"> </param>
              /// <param name="args">
              /// @return </param>
              static double getDoubleParameter(const std::string &param, std::string args[]);

              /// <summary>
              /// Retrieves the "-encoding" parameter.
              /// </summary>
              /// <param name="param"> </param>
              /// <param name="args">
              /// </param>
              /// <returns> the encoding or if invalid the VM is killed. </returns>
              static Charset *getEncodingParameter(std::string args[]);

              static void checkLanguageCode(const std::string &code);

              static bool containsParam(const std::string &param, std::string args[]);

              static void printTrainingIoError(IOException *e);

              static void handleStdinIoError(IOException *e);

              // its optional, passing null is allowed
              static TrainingParameters *loadTrainingParameters(const std::string &paramFile, bool supportSequenceTraining);
            };

        }
    }
}


#endif	//#ifndef CMDLINEUTIL
