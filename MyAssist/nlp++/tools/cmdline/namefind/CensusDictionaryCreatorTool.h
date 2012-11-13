#ifndef CENSUSDICTIONARYCREATORTOOL
#define CENSUSDICTIONARYCREATORTOOL

#include "../tools/cmdline/CmdLineTool.h"
#include "../tools/formats/BioNLP2004NameSampleStreamFactory.h"
#include "../tools/formats/Conll02NameSampleStreamFactory.h"
#include "../tools/formats/Conll03NameSampleStreamFactory.h"
#include "../tools/formats/ConllXPOSSampleStreamFactory.h"
#include "../tools/formats/ConllXSentenceSampleStreamFactory.h"
#include "../tools/formats/ConllXTokenSampleStreamFactory.h"
#include "../tools/formats/LeipzigDocumentSampleStreamFactory.h"
#include "../tools/formats/NameSampleStreamFactory.h"
#include "../tools/formats/NameToSentenceSampleStreamFactory.h"
#include "../tools/formats/NameToTokenSampleStreamFactory.h"
#include "../tools/formats/POSToSentenceSampleStreamFactory.h"
#include "../tools/formats/POSToTokenSampleStreamFactory.h"
#include "../tools/formats/WordTagSampleStreamFactory.h"
#include "../tools/formats/ad/ADChunkSampleStreamFactory.h"
#include "../tools/formats/ad/ADNameSampleStreamFactory.h"
#include "../tools/dictionary/Dictionary.h"
#include "../tools/util/ObjectStream.h"
#include "../tools/util/StringList.h"
#include <string>

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
        namespace cmdline
        {
            namespace namefind
            {


                using opennlp::tools::cmdline::ArgumentParser;
                using opennlp::tools::cmdline::ArgumentParser::OptionalParameter;
                using opennlp::tools::cmdline::ArgumentParser::ParameterDescription;
                using opennlp::tools::cmdline::CLI;
                using opennlp::tools::cmdline::CmdLineTool;
                using opennlp::tools::cmdline::CmdLineUtil;
                using opennlp::tools::cmdline::TerminateToolException;
                using opennlp::tools::dictionary::Dictionary;
                using opennlp::tools::formats::NameFinderCensus90NameStream;
                using opennlp::tools::util::ObjectStream;
                using opennlp::tools::util::StringList;

                /// <summary>
                /// This tool helps create a loadable dictionary for the {@code NameFinder},
                /// from data collected from US Census data.
                /// <p>
                /// Data for the US Census and names can be found here for the 1990 Census:
                /// <br>
                /// <a href="http://www.census.gov/genealogy/names/names_files.html">www.census.gov</a>
                /// </summary>
                class CensusDictionaryCreatorTool : public CmdLineTool
                {

                  /// <summary>
                  /// Create a list of expected parameters.
                  /// </summary>
              public:
                  class Parameters
                  {

                public:
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @ParameterDescription(valueName = "code") @OptionalParameter(defaultValue = "en") String getLang();
                    virtual std::string getLang() = 0;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @ParameterDescription(valueName = "charsetName") @OptionalParameter(defaultValue="UTF-8") String getEncoding();
                    virtual std::string getEncoding() = 0;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @ParameterDescription(valueName = "censusDict") String getCensusData();
                    virtual std::string getCensusData() = 0;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @ParameterDescription(valueName = "dict") String getDict();
                    virtual std::string getDict() = 0;
                  };

                  /// <summary>
                  /// Gets the name for the tool.
                  /// </summary>
                  /// <returns> {@code String}  a name to be used to call this class. </returns>
              public:
                  virtual std::string getName();

                  /// <summary>
                  /// Gets a short description for the tool.
                  /// </summary>
                  /// <returns> {@code String}  a short description describing the purpose of
                  ///    the tool to the user. </returns>
                  virtual std::string getShortDescription();

                  /// <summary>
                  /// Gets the expected usage of the tool as an example.
                  /// </summary>
                  /// <returns> {@code String}  a descriptive example on how to properly call
                  ///    the tool from the command line. </returns>
                  virtual std::string getHelp();

                  /// 
                  /// <param name="sampleStream"> </param>
                  /// <returns> a {@code Dictionary} class containing the name dictionary
                  ///    built from the input file. </returns>
                  /// <exception cref="IOException"> </exception>
                  static Dictionary *createDictionary(ObjectStream<StringList*> *sampleStream) throw(IOException);

                  /// <summary>
                  /// This method is much like the old main() method used in prior class
                  /// construction, and allows another main class to run() this classes method
                  /// to perform the operations.
                  /// </summary>
                  /// <param name="args">  a String[] array of arguments passed to the run method </param>
                  virtual void run(std::string args[]);
                };

            }
        }
    }
}


#endif	//#ifndef CENSUSDICTIONARYCREATORTOOL
