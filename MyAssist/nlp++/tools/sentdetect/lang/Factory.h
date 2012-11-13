#ifndef FACTORY
#define FACTORY

#include "../tools/sentdetect/EndOfSentenceScanner.h"
#include "../tools/sentdetect/SDContextGenerator.h"
#include <string>

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
        namespace sentdetect
        {
            namespace lang
            {


                using opennlp::tools::sentdetect::DefaultEndOfSentenceScanner;
                using opennlp::tools::sentdetect::DefaultSDContextGenerator;
                using opennlp::tools::sentdetect::EndOfSentenceScanner;
                using opennlp::tools::sentdetect::SDContextGenerator;
                using opennlp::tools::sentdetect::lang::th::SentenceContextGenerator;

                class Factory
                {

              public:
                  virtual EndOfSentenceScanner *createEndOfSentenceScanner(const std::string &languageCode);

                  virtual SDContextGenerator *createSentenceContextGenerator(const std::string &languageCode, Set<std::string> *abbreviations);

                  virtual SDContextGenerator *createSentenceContextGenerator(const std::string &languageCode);
                };
            }
        }
    }
}


#endif	//#ifndef FACTORY
