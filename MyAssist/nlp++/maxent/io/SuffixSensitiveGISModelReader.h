#ifndef SUFFIXSENSITIVEGISMODELREADER
#define SUFFIXSENSITIVEGISMODELREADER

#include "GISModelReader.h"
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
    namespace maxent
    {
        namespace io
        {


            using opennlp::model::AbstractModel;

            /// <summary>
            /// A reader for GIS models which inspects the filename and invokes the
            /// appropriate GISModelReader depending on the filename's suffixes.
            /// 
            /// <p>The following assumption are made about suffixes:
            ///    <li>.gz  --> the file is gzipped (must be the last suffix)
            ///    <li>.txt --> the file is plain text
            ///    <li>.bin --> the file is binary
            /// </summary>
            class SuffixSensitiveGISModelReader : public GISModelReader
            {
          protected:
              GISModelReader *suffixAppropriateReader;

              /// <summary>
              /// Constructor which takes a File and invokes the GISModelReader appropriate
              /// for the suffix.
              /// </summary>
              /// <param name="f">
              ///          The File in which the model is stored. </param>
          public:
              SuffixSensitiveGISModelReader(File *f) throw(IOException);

              // activate this if adding another type of reader which can't read model
              // information in the way that the default getModel() method in
              // GISModelReader does.
              //public GISModel getModel () throws java.io.IOException {
              //    return suffixAppropriateReader.getModel();
              //}

              /// <summary>
              /// To convert between different formats of the new style.
              /// 
              /// <p>
              /// java opennlp.maxent.io.SuffixSensitiveGISModelReader old_model_name
              /// new_model_name
              /// 
              /// <p>
              /// For example, to convert a model called "model.bin.gz" (which is thus saved
              /// in gzipped binary format) to one in (unzipped) text format:
              /// 
              /// <p>
              /// java opennlp.maxent.io.SuffixSensitiveGISModelReader model.bin.gz model.txt
              /// 
              /// <p>
              /// This particular example would of course be useful when you generally want
              /// to create models which take up less space (.bin.gz), but want to be able to
              /// inspect a few of them as plain text files.
              /// </summary>
              static void main(std::string args[]) throw(IOException);
            };

        }
    }
}


#endif	//#ifndef SUFFIXSENSITIVEGISMODELREADER
