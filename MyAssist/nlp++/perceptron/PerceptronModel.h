#ifndef PERCEPTRONMODEL
#define PERCEPTRONMODEL

#include "../model/AbstractModel.h"
#include "../model/Context.h"
#include "../model/IndexHashTable.h"
#include "../model/EvalParameters.h"
#include <string>
#include <cmath>

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
    namespace perceptron
    {


        using opennlp::model::AbstractModel;
        using opennlp::model::Context;
        using opennlp::model::EvalParameters;
        using opennlp::model::IndexHashTable;

        class PerceptronModel : public AbstractModel
        {

      public:
          PerceptronModel(Context params[], std::string predLabels[], IndexHashTable<std::string> *pmap, std::string outcomeNames[]);

          /// @deprecated use the constructor with the <seealso cref="IndexHashTable"/> instead! 
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated("use the constructor with the <seealso cref="opennlp.model.IndexHashTable"/> instead!") public PerceptronModel(opennlp.model.Context[] params, String[] predLabels, java.util.Map<String,Integer> pmap, String[] outcomeNames)
          PerceptronModel(Context params[], std::string predLabels[], Map<std::string, int> *pmap, std::string outcomeNames[]);

          PerceptronModel(Context params[], std::string predLabels[], std::string outcomeNames[]);

          virtual double *eval(std::string context[]);

          virtual double *eval(std::string context[], float values[]);

          virtual double *eval(std::string context[], double probs[]);

          virtual double *eval(std::string context[], float values[], double outsums[]);

          static double *eval(int context[], double prior[], EvalParameters *model);

          static double *eval(int context[], float values[], double prior[], EvalParameters *model, bool normalize);

          static void main(std::string args[]) throw(java::io::IOException);
        };

    }
}


#endif	//#ifndef PERCEPTRONMODEL
