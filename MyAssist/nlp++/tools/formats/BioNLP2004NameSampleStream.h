#ifndef BIONLP2004NAMESAMPLESTREAM
#define BIONLP2004NAMESAMPLESTREAM

#include "../tools/namefind/NameSample.h"
#include "../tools/util/ObjectStream.h"
#include "NameSample>.h"
#include <string>
#include <vector>

/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

namespace opennlp
{
    namespace tools
    {
        namespace formats
        {


            using opennlp::tools::namefind::NameSample;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::PlainTextByLineStream;
            using opennlp::tools::util::Span;
            using opennlp::tools::util::StringUtil;

            /// <summary>
            /// Parser for the training files of the BioNLP/NLPBA 2004 shared task.
            /// <p>
            /// The data contains five named entity types: DNA, RNA, protein, cell_type and cell_line.<br>
            /// <p>
            /// Data can be found on this web site:<br>
            /// http://www-tsujii.is.s.u-tokyo.ac.jp/GENIA/ERtask/report.html
            /// <p>
            /// <b>Note:</b> Do not use this class, internal use only!
            /// </summary>
            class BioNLP2004NameSampleStream : public ObjectStream<NameSample*>
            {

          public:
              static const int GENERATE_DNA_ENTITIES = 0x01;
              static const int GENERATE_PROTEIN_ENTITIES = 0x01 << 1;
              static const int GENERATE_CELLTYPE_ENTITIES = 0x01 << 2;
              static const int GENERATE_CELLLINE_ENTITIES = 0x01 << 3;
              static const int GENERATE_RNA_ENTITIES = 0x01 << 4;

          private:
              const int types;

              ObjectStream<std::string> *const lineStream;

          public:
              BioNLP2004NameSampleStream(InputStream *in_Renamed, int types);

              virtual NameSample *read() throw(IOException);

              virtual void reset() throw(IOException, UnsupportedOperationException);

              virtual void close() throw(IOException);
            };

        }
    }
}


#endif	//#ifndef BIONLP2004NAMESAMPLESTREAM
