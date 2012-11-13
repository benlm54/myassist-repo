#ifndef FILEEVENTSTREAM
#define FILEEVENTSTREAM

#include "AbstractEventStream.h"
#include "Event.h"
#include "StringBuffer.h"
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


        using opennlp::maxent::GIS;
        using opennlp::maxent::io::SuffixSensitiveGISModelWriter;

        /// <summary>
        /// Class for using a file of events as an event stream.  The format of the file is one event perline with
        /// each line consisting of outcome followed by contexts (space delimited).
        /// </summary>
        class FileEventStream : public AbstractEventStream
        {

      public:
          BufferedReader *reader;
          std::string line;

          /// <summary>
          /// Creates a new file event stream from the specified file name. </summary>
          /// <param name="fileName"> the name fo the file containing the events. </param>
          /// <exception cref="IOException"> When the specified file can not be read. </exception>
          FileEventStream(const std::string &fileName, const std::string &encoding) throw(IOException);

//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
          FileEventStream(const std::string &fileName) throw(IOException); //this(fileName,nullptr);

          /// <summary>
          /// Creates a new file event stream from the specified file. </summary>
          /// <param name="file"> the file containing the events. </param>
          /// <exception cref="IOException"> When the specified file can not be read. </exception>
          FileEventStream(File *file) throw(IOException);

          virtual bool hasNext();

          virtual Event *next();

          /// <summary>
          /// Generates a string representing the specified event. </summary>
          /// <param name="event"> The event for which a string representation is needed. </param>
          /// <returns> A string representing the specified event. </returns>
          static std::string toLine(Event *event_Renamed);

          /// <summary>
          /// Trains and writes a model based on the events in the specified event file.
          /// the name of the model created is based on the event file name. </summary>
          /// <param name="args"> eventfile [iterations cuttoff] </param>
          /// <exception cref="IOException"> when the eventfile can not be read or the model file can not be written. </exception>
          static void main(std::string args[]) throw(IOException);
        };


    }
}


#endif	//#ifndef FILEEVENTSTREAM
