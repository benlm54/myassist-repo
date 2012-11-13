#ifndef GISMODELWRITER
#define GISMODELWRITER

#include "../model/AbstractModelWriter.h"
#include "../model/Context.h"
#include "../model/AbstractModel.h"
#include "../model/ComparablePredicate.h"
#include <string>
#include <vector>

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
            using opennlp::model::AbstractModelWriter;
            using opennlp::model::ComparablePredicate;
            using opennlp::model::Context;
            using opennlp::model::IndexHashTable;

            /// <summary>
            /// Abstract parent class for GISModel writers.  It provides the persist method
            /// which takes care of the structure of a stored document, and requires an
            /// extending class to define precisely how the data should be stored.
            /// </summary>
            class GISModelWriter : public AbstractModelWriter
            {
          protected:
//ORIGINAL LINE: protected opennlp.model.Context[] PARAMS;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              Context *PARAMS;
//ORIGINAL LINE: protected String[] OUTCOME_LABELS;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              std::string *OUTCOME_LABELS;
              int CORRECTION_CONSTANT;
              double CORRECTION_PARAM;
//ORIGINAL LINE: protected String[] PRED_LABELS;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              std::string *PRED_LABELS;

          public:
              GISModelWriter(AbstractModel *model);


              /// <summary>
              /// Writes the model to disk, using the <code>writeX()</code> methods provided
              /// by extending classes.
              /// 
              /// <p>
              /// If you wish to create a GISModelWriter which uses a different structure, it
              /// will be necessary to override the persist method in addition to
              /// implementing the <code>writeX()</code> methods.
              /// </summary>
              virtual void persist() throw(IOException);

          protected:
              virtual ComparablePredicate *sortValues();

              virtual std::vector compressOutcomes(ComparablePredicate sorted[]);
            };

        }
    }
}


#endif	//#ifndef GISMODELWRITER
