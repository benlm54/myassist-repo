#ifndef TRAININGPARAMETERS
#define TRAININGPARAMETERS

#include <string>
#include <map>

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
        namespace util
        {


            class TrainingParameters
            {

          public:
              static const std::string ALGORITHM_PARAM;

              static const std::string ITERATIONS_PARAM;
              static const std::string CUTOFF_PARAM;

          private:
              Map<std::string, std::string> *parameters;

          public:
              TrainingParameters();

              TrainingParameters(InputStream *in_Renamed) throw(IOException);

              /// <summary>
              /// Retrieves the training algorithm name for a given name space.
              /// </summary>
              /// <returns> the name or null if not set. </returns>
              virtual std::string algorithm(const std::string &namespace_Renamed);

              /// <summary>
              /// Retrieves the training algorithm name.
              /// </summary>
              /// <returns> the name or null if not set. </returns>
              virtual std::string algorithm();

              /// <summary>
              /// Retrieves a map with the training parameters which have the passed name space.
              /// </summary>
              /// <param name="namespace">
              /// </param>
              /// <returns> a parameter map which can be passed to the train and validate methods. </returns>
              virtual Map<std::string, std::string> *getSettings(const std::string &namespace_Renamed);

              /// <summary>
              /// Retrieves all parameters without a name space.
              /// </summary>
              /// <returns> the settings map </returns>
              virtual Map<std::string, std::string> *getSettings();

              // reduces the params to contain only the params in the name space
              virtual TrainingParameters *getParameters(const std::string &namespace_Renamed);

              virtual void put(const std::string &namespace_Renamed, const std::string &key, const std::string &value);

              virtual void put(const std::string &key, const std::string &value);

              virtual void serialize(OutputStream *out) throw(IOException);

            private:
                void InitializeInstanceFields();
            };

        }
    }
}


#endif	//#ifndef TRAININGPARAMETERS
