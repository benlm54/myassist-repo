#ifndef TRAINUTIL
#define TRAINUTIL

#include "AbstractModel.h"
#include "EventStream.h"
#include "SequenceStream.h"
#include "NumberFormatException.h"
#include <string>
#include "stringconverter.h"

/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

namespace opennlp
{
    namespace model
    {


        using opennlp::perceptron::PerceptronTrainer;
        using opennlp::perceptron::SimplePerceptronSequenceTrainer;

        class TrainUtil
        {

      public:
          static const std::string ALGORITHM_PARAM;

          static const std::string MAXENT_VALUE;
          static const std::string PERCEPTRON_VALUE;
          static const std::string PERCEPTRON_SEQUENCE_VALUE;


          static const std::string CUTOFF_PARAM;
      private:
          static const int CUTOFF_DEFAULT = 5;

      public:
          static const std::string ITERATIONS_PARAM;
      private:
          static const int ITERATIONS_DEFAULT = 100;

      public:
          static const std::string DATA_INDEXER_PARAM;
          static const std::string DATA_INDEXER_ONE_PASS_VALUE;
          static const std::string DATA_INDEXER_TWO_PASS_VALUE;


      private:
          static std::string getStringParam(Map<std::string, std::string> *trainParams, const std::string &key, const std::string &defaultValue, Map<std::string, std::string> *reportMap);

          static int getIntParam(Map<std::string, std::string> *trainParams, const std::string &key, int defaultValue, Map<std::string, std::string> *reportMap);

          static double getDoubleParam(Map<std::string, std::string> *trainParams, const std::string &key, double defaultValue, Map<std::string, std::string> *reportMap);

          static bool getBooleanParam(Map<std::string, std::string> *trainParams, const std::string &key, bool defaultValue, Map<std::string, std::string> *reportMap);

      public:
          static bool isValid(Map<std::string, std::string> *trainParams);



          // TODO: Need a way to report results and settings back for inclusion in model ...

          static AbstractModel *train(EventStream *events, Map<std::string, std::string> *trainParams, Map<std::string, std::string> *reportMap) throw(IOException);

          /// <summary>
          /// Detects if the training algorithm requires sequence based feature generation
          /// or not.
          /// </summary>
          static bool isSequenceTraining(Map<std::string, std::string> *trainParams);

          static AbstractModel *train(SequenceStream *events, Map<std::string, std::string> *trainParams, Map<std::string, std::string> *reportMap) throw(IOException);
        };

    }
}


#endif	//#ifndef TRAINUTIL
