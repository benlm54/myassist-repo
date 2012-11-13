#ifndef DETOKENIZATIONDICTIONARY
#define DETOKENIZATIONDICTIONARY

#include "../tools/util/InvalidFormatException.h"
#include "../tools/dictionary/serializer/EntryInserter.h"
#include "../tools/dictionary/serializer/Entry.h"
#include <string>
#include <map>

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
        namespace tokenize
        {


            using opennlp::tools::dictionary::serializer::Attributes;
            using opennlp::tools::dictionary::serializer::DictionarySerializer;
            using opennlp::tools::dictionary::serializer::Entry;
            using opennlp::tools::dictionary::serializer::EntryInserter;
            using opennlp::tools::util::InvalidFormatException;
            using opennlp::tools::util::StringList;

            class DetokenizationDictionary
            {

          public:
              enum Operation
              {

                /// <summary>
                /// Attaches the token to the token on the right side.
                /// </summary>
                MOVE_RIGHT,

                /// <summary>
                /// Attaches the token to the token on the left side. 
                /// </summary>
                MOVE_LEFT,

                /// <summary>
                /// Attaches the token token to the right token on first occurrence, and
                /// to the token on the left side on the second occurrence. 
                /// </summary>
                RIGHT_LEFT_MATCHING

//JAVA TO C++ CONVERTER TODO TASK: Enums cannot contain methods in C++:
//                public static Operation parse(String operation)
            //    {
            //
            //      if (MOVE_RIGHT.toString().equals(operation))
            //      {
            //        return MOVE_RIGHT;
            //      }
            //      else if (MOVE_LEFT.toString().equals(operation))
            //      {
            //        return MOVE_LEFT;
            //      }
            //      else if (RIGHT_LEFT_MATCHING.toString().equals(operation))
            //      {
            //        return RIGHT_LEFT_MATCHING;
            //      }
            //      else
            //      {
            //        return nullptr;
            //      }
            //    }
              };

          private:
              Map<std::string, DetokenizationDictionary::Operation> *const operationTable;
              /// <summary>
              /// Initializes the current instance. 
              /// </summary>
              /// <param name="tokens"> </param>
              /// <param name="operations"> </param>
          public:
              DetokenizationDictionary(std::string tokens[], DetokenizationDictionary::Operation operations[]) : operationTable(std::map<std::string, DetokenizationDictionary::Operation>());

              DetokenizationDictionary(InputStream *in_Renamed) throw(IOException, InvalidFormatException) : operationTable(std::map<std::string, DetokenizationDictionary::Operation>());

                    private:
                        class EntryInserterAnonymousInnerClassHelper : public EntryInserter
                        {
                        public:
                            virtual void insert(Entry *entry) throw(InvalidFormatException);
                        };

          public:
              virtual DetokenizationDictionary::Operation getOperation(const std::string &token);

              // serialize method
              virtual void serialize(OutputStream *out) throw(IOException);

                    private:
                        class IteratorAnonymousInnerClassHelper : public Iterator<Entry*>
                        {

                        public:
                            Iterator<std::string> *iterator;

                            virtual bool hasNext();

                            virtual Entry *next();

                            virtual void remove();
                        };
            };
        }
    }
}


#endif	//#ifndef DETOKENIZATIONDICTIONARY
