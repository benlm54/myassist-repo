#ifndef DOCUMENTSAMPLE
#define DOCUMENTSAMPLE

#include "StringBuilder.h"
#include <string>
#include <vector>

/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreemnets.  See the NOTICE file distributed with
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
        namespace doccat
        {


            using opennlp::tools::tokenize::WhitespaceTokenizer;

            /// <summary>
            /// Class which holds a classified document and its category.
            /// </summary>
            class DocumentSample
            {

          private:
              const std::string category;
              const std::vector<std::string> text;

          public:
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              DocumentSample(const std::string &category, const std::string &text); //this(category, WhitespaceTokenizer.INSTANCE.tokenize(text));

              DocumentSample(const std::string &category, std::string text[]);

              virtual std::string getCategory();

              virtual std::string *getText();

              virtual std::string ToString();

              virtual bool Equals(void *obj);
            };

        }
    }
}


#endif	//#ifndef DOCUMENTSAMPLE
