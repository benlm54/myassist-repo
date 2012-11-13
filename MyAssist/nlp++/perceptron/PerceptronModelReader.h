#ifndef PERCEPTRONMODELREADER
#define PERCEPTRONMODELREADER

#include "../model/AbstractModelReader.h"
#include "../model/DataReader.h"
#include "../model/AbstractModel.h"
#include <string>

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
        using opennlp::model::AbstractModelReader;
        using opennlp::model::Context;
        using opennlp::model::DataReader;

        /// <summary>
        /// Abstract parent class for readers of Perceptron.
        /// 
        /// </summary>
        class PerceptronModelReader : public AbstractModelReader
        {

        public:
            PerceptronModelReader(File *file) throw(IOException);

            PerceptronModelReader(DataReader *dataReader);

            /// <summary>
            /// Retrieve a model from disk. It assumes that models are saved in the
            /// following sequence:
            /// 
            /// <br>Perceptron (model type identifier)
            /// <br>1. # of parameters (int)
            /// <br>2. # of outcomes (int)
            /// <br>  * list of outcome names (String)
            /// <br>3. # of different types of outcome patterns (int)
            /// <br>   * list of (int int[])
            /// <br>   [# of predicates for which outcome pattern is true] [outcome pattern]
            /// <br>4. # of predicates (int)
            /// <br>   * list of predicate names (String)
            /// 
            /// <p>If you are creating a reader for a format which won't work with this
            /// (perhaps a database or xml file), override this method and ignore the
            /// other methods provided in this abstract class.
            /// </summary>
            /// <returns> The PerceptronModel stored in the format and location specified to
            ///         this PerceptronModelReader (usually via its the constructor). </returns>
            virtual AbstractModel *constructModel() throw(IOException);

            virtual void checkModelType() throw(IOException);
        };

    }
}


#endif	//#ifndef PERCEPTRONMODELREADER
