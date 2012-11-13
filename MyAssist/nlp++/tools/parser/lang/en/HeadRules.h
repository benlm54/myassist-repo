#ifndef HEADRULES
#define HEADRULES

#include "../tools/parser/GapLabeler.h"
#include "../tools/parser/Parse.h"
#include "../tools/parser/Constituent.h"
#include <string>
#include <map>
#include <stack>
#include <set>
#include "stringconverter.h"

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
        namespace parser
        {
            namespace lang
            {
                namespace en
                {


                    using opennlp::tools::parser::Constituent;
                    using opennlp::tools::parser::GapLabeler;
                    using opennlp::tools::parser::Parse;
                    using opennlp::tools::parser::chunking::Parser;

                    /// <summary>
                    /// Class for storing the English head rules associated with parsing.
                    /// </summary>
                    class HeadRules : public opennlp::tools::parser::HeadRules, public GapLabeler
                    {

                  private:
                      class HeadRule
                      {
                    public:
                        bool leftToRight;
//ORIGINAL LINE: public String[] tags;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                        std::string *tags;
                        HeadRule(bool l2r, std::string tags[]);

                        virtual bool Equals(void *obj);
                      };

                  private:
                      Map<std::string, HeadRule*> *headRules;
                      Set<std::string> *punctSet;

                      /// <summary>
                      /// Creates a new set of head rules based on the specified head rules file.
                      /// </summary>
                      /// <param name="ruleFile"> the head rules file.
                      /// </param>
                      /// <exception cref="IOException"> if the head rules file can not be read. </exception>
                  public:
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated public HeadRules(String ruleFile) throws java.io.IOException
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
                      HeadRules(const std::string &ruleFile) throw(IOException); //this(new BufferedReader(new FileReader(ruleFile)));

                      /// <summary>
                      /// Creates a new set of head rules based on the specified reader.
                      /// </summary>
                      /// <param name="rulesReader"> the head rules reader.
                      /// </param>
                      /// <exception cref="IOException"> if the head rules reader can not be read. </exception>
                      HeadRules(Reader *rulesReader) throw(IOException);

                      virtual Set<std::string> *getPunctuationTags();

                      virtual Parse *getHead(Parse constituents[], const std::string &type);

                  private:
                      void readHeadRules(BufferedReader *str) throw(IOException);

                  public:
                      virtual void labelGaps(std::stack<Constituent*> &stack);

                      /// <summary>
                      /// Writes the head rules to the writer in a format suitable for loading
                      /// the head rules again with the constructor. The encoding must be
                      /// taken into account while working with the writer and reader.
                      /// <p> 
                      /// After the entries have been written, the writer is flushed.
                      /// The writer remains open after this method returns.
                      /// </summary>
                      /// <param name="writer"> </param>
                      /// <exception cref="IOException"> </exception>
                      virtual void serialize(Writer *writer) throw(IOException);

                      virtual bool Equals(void *obj);
                    };

                }
            }
        }
    }
}


#endif	//#ifndef HEADRULES
