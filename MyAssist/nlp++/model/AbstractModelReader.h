#ifndef ABSTRACTMODELREADER
#define ABSTRACTMODELREADER

#include "DataReader.h"
#include "AbstractModel.h"
#include "Context.h"
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
    namespace model
    {



        class AbstractModelReader
        {

          /// <summary>
          /// The number of predicates contained in the model.
          /// </summary>
      protected:
          int NUM_PREDS;
          DataReader *dataReader;

      public:
          AbstractModelReader(File *f) throw(IOException);

//JAVA TO C++ CONVERTER TODO TASK: No base class can be determined:
          AbstractModelReader(DataReader *dataReader); //super();

          /// <summary>
          /// Implement as needed for the format the model is stored in.
          /// </summary>
          virtual int readInt() throw(IOException);

          /// <summary>
          /// Implement as needed for the format the model is stored in.
          /// </summary>
          virtual double readDouble() throw(IOException);

          /// <summary>
          /// Implement as needed for the format the model is stored in.
          /// </summary>
          virtual std::string readUTF() throw(IOException);

          virtual AbstractModel *getModel() throw(IOException);

          virtual void checkModelType() = 0;

          virtual AbstractModel *constructModel() = 0;

      protected:
          virtual std::string *getOutcomes() throw(IOException);

          virtual int **getOutcomePatterns() throw(IOException);

          virtual std::string *getPredicates() throw(IOException);

          /// <summary>
          /// Reads the parameters from a file and populates an array of context objects. </summary>
          /// <param name="outcomePatterns"> The outcomes patterns for the model.  The first index refers to which 
          /// outcome pattern (a set of outcomes that occurs with a context) is being specified.  The
          /// second index specifies the number of contexts which use this pattern at index 0, and the
          /// index of each outcomes which make up this pattern in indicies 1-n. </param>
          /// <returns> An array of context objects. </returns>
          /// <exception cref="java.io.IOException"> when the model file does not match the outcome patterns or can not be read. </exception>
          virtual Context *getParameters(int outcomePatterns[][]) throw(IOException);

        };

    }
}


#endif	//#ifndef ABSTRACTMODELREADER
