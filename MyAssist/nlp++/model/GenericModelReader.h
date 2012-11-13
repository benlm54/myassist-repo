#ifndef GENERICMODELREADER
#define GENERICMODELREADER

#include "AbstractModelReader.h"
#include "DataReader.h"
#include "AbstractModel.h"
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


        using opennlp::maxent::io::GISModelReader;
        using opennlp::perceptron::PerceptronModelReader;

        class GenericModelReader : public AbstractModelReader
        {

      private:
          AbstractModelReader *delegateModelReader;

      public:
          GenericModelReader(File *f) throw(IOException);

          GenericModelReader(DataReader *dataReader);

          virtual void checkModelType() throw(IOException);


          virtual AbstractModel *constructModel() throw(IOException);

          static void main(std::string args[]) throw(IOException);
        };

    }
}


#endif	//#ifndef GENERICMODELREADER
