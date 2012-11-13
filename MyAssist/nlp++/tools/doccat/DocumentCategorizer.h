#ifndef DOCUMENTCATEGORIZER
#define DOCUMENTCATEGORIZER

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

            /// <summary>
            /// Interface for classes which categorize documents.
            /// </summary>
            class DocumentCategorizer
            {

              /// <summary>
              /// Categorizes the given text.
              /// </summary>
              /// <param name="text"> </param>
          public:
              virtual double *categorize(std::string text[]) = 0;

              virtual std::string getBestCategory(double outcome[]) = 0;

              virtual int getIndex(const std::string &category) = 0;

              virtual std::string getCategory(int index) = 0;

              virtual int getNumberOfCategories() = 0;

              virtual double *categorize(const std::string &documentText) = 0;

              virtual std::string getAllResults(double results[]) = 0;
            };


        }
    }
}


#endif	//#ifndef DOCUMENTCATEGORIZER
