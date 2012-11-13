#ifndef GENERICMODELWRITER
#define GENERICMODELWRITER

#include "AbstractModelWriter.h"
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


        using opennlp::maxent::io::BinaryGISModelWriter;
        using opennlp::maxent::io::PlainTextGISModelWriter;
        using opennlp::model::AbstractModel::ModelType;
        using opennlp::perceptron::BinaryPerceptronModelWriter;
        using opennlp::perceptron::PlainTextPerceptronModelWriter;

        class GenericModelWriter : public AbstractModelWriter
        {

      private:
          AbstractModelWriter *delegateWriter;

      public:
          GenericModelWriter(AbstractModel *model, File *file) throw(IOException);

          GenericModelWriter(AbstractModel *model, DataOutputStream *dos);

      private:
          void init(AbstractModel *model, DataOutputStream *dos);

          void init(AbstractModel *model, BufferedWriter *bw);

      public:
          virtual void close() throw(IOException);

          virtual void persist() throw(IOException);

          virtual void writeDouble(double d) throw(IOException);

          virtual void writeInt(int i) throw(IOException);

          virtual void writeUTF(const std::string &s) throw(IOException);

        };

    }
}


#endif	//#ifndef GENERICMODELWRITER
