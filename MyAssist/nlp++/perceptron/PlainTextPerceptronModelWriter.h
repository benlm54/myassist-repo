#ifndef PLAINTEXTPERCEPTRONMODELWRITER
#define PLAINTEXTPERCEPTRONMODELWRITER

#include "PerceptronModelWriter.h"
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

        /// <summary>
        /// Model writer that saves models in plain text format.
        /// </summary>
        class PlainTextPerceptronModelWriter : public PerceptronModelWriter
        {
      public:
          BufferedWriter *output;

          /// <summary>
          /// Constructor which takes a PerceptronModel and a File and prepares itself to
          /// write the model to that file. Detects whether the file is gzipped or not
          /// based on whether the suffix contains ".gz".
          /// </summary>
          /// <param name="model"> The PerceptronModel which is to be persisted. </param>
          /// <param name="f"> The File in which the model is to be persisted. </param>
          PlainTextPerceptronModelWriter(AbstractModel *model, File *f) throw(IOException, FileNotFoundException);

          /// <summary>
          /// Constructor which takes a PerceptronModel and a BufferedWriter and prepares
          /// itself to write the model to that writer.
          /// </summary>
          /// <param name="model"> The PerceptronModel which is to be persisted. </param>
          /// <param name="bw"> The BufferedWriter which will be used to persist the model. </param>
          PlainTextPerceptronModelWriter(AbstractModel *model, BufferedWriter *bw);

          virtual void writeUTF(const std::string &s) throw(IOException);

          virtual void writeInt(int i) throw(IOException);

          virtual void writeDouble(double d) throw(IOException);

          virtual void close() throw(IOException);

        };

    }
}


#endif	//#ifndef PLAINTEXTPERCEPTRONMODELWRITER
