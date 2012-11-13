#ifndef PLAINTEXTFILEDATAREADER
#define PLAINTEXTFILEDATAREADER

#include "DataReader.h"
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


        class PlainTextFileDataReader : public DataReader
        {

      private:
          BufferedReader *input;

      public:
          PlainTextFileDataReader(File *f) throw(IOException);

          PlainTextFileDataReader(InputStream *in_Renamed);

          PlainTextFileDataReader(BufferedReader *in_Renamed);

          virtual double readDouble() throw(IOException);

          virtual int readInt() throw(IOException);

          virtual std::string readUTF() throw(IOException);

        };

    }
}


#endif	//#ifndef PLAINTEXTFILEDATAREADER
