#ifndef ARGUMENTPARSER
#define ARGUMENTPARSER

#include "InvocationHandler.h"
#include "T.h"
#include "Method.h"
#include "NumberFormatException.h"
#include "Class.h"
#include "const_iterator.h"
#include "StringBuilder.h"
#include "ParameterDescription.h"
#include "OptionalParameter.h"
#include <string>
#include <map>
#include <cctype>
#include "stringconverter.h"

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


            /// <summary>
            /// Parser for command line arguments. The parser creates a dynamic proxy which
            /// can be access via a command line argument interface.
            /// 
            /// <p>
            /// 
            /// The command line argument proxy interface must follow these conventions:<br>
            /// - Methods do not define arguments<br>
            /// - Method names must start with get<br>
            /// - Allowed return types are Integer, Boolean, String, File and Charset.<br>
            /// <p>
            /// <b>Note:</b> Do not use this class, internal use only!
            /// </summary>
            class ArgumentParser
            {
          private:
              class ArgumentFactory
              {

            public:
                static const std::string INVALID_ARG;

                virtual void *parseArgument(Method *method, const std::string &argName, const std::string &argValue) = 0;
              };

          private:
              class IntegerArgumentFactory : public ArgumentFactory
              {

            public:
                virtual void *parseArgument(Method *method, const std::string &argName, const std::string &argValue);
              };

          private:
              class BooleanArgumentFactory : public ArgumentFactory
              {

            public:
                virtual void *parseArgument(Method *method, const std::string &argName, const std::string &argValue);
              };

          private:
              class StringArgumentFactory : public ArgumentFactory
              {

            public:
                virtual void *parseArgument(Method *method, const std::string &argName, const std::string &argValue);
              };

          private:
              class FileArgumentFactory : public ArgumentFactory
              {

            public:
                virtual void *parseArgument(Method *method, const std::string &argName, const std::string &argValue);
              };

          private:
              class CharsetArgumentFactory : public ArgumentFactory
              {

            public:
                virtual void *parseArgument(Method *method, const std::string &argName, const std::string &charsetName);
              };

          private:
              class ArgumentProxy : public InvocationHandler
              {

            private:
                Map<std::string, void*> *const arguments;

            public:
                ArgumentProxy(Map<std::string, void*> *arguments);

                virtual void *invoke(void *proxy, Method *method, Object args[]) throw(Throwable);
              };


          public:
              Retention(RetentionPolicy : public :RUNTIME) class OptionalParameter : System::Attribute
              {
                      private:
                          ArgumentParser *const outerInstance;

                      public:
                          OptionalParameter(ArgumentParser *outerInstance);

                static const std::string DEFAULT_CHARSET;
                std::string defaultValue() default "";
              };

          public:
              Retention(RetentionPolicy : public :RUNTIME) class ParameterDescription : System::Attribute
              {
                      private:
                          ArgumentParser *const outerInstance;

                      public:
                          ParameterDescription(ArgumentParser *outerInstance);

                std::string valueName();
                std::string description() default "";
              };

          private:
              static Map<Class*, ArgumentFactory*> *const argumentFactories;

//JAVA TO C++ CONVERTER TODO TASK: Static constructors are not allowed in native C++:
              static ArgumentParser();

              ArgumentParser();

              template<typename T>
              static void checkProxyInterface(Class *proxyInterface);

              static std::string methodNameToParameter(const std::string &methodName);

              /// <summary>
              /// Creates a usage string which can be printed in case the user did specify the arguments
              /// incorrectly. Incorrectly is defined as <seealso cref="ArgumentParser#validateArguments(String[], Class)"/>
              /// returns false.
              /// </summary>
              /// <param name="argProxyInterface">
              /// </param>
              /// <returns> the help message usage string </returns>
          public:
              template<typename T>
              static std::string createUsage(Class *argProxyInterface);

              /// <summary>
              /// Tests if the argument are correct or incorrect. Incorrect means, that mandatory arguments are missing or
              /// there are unknown arguments. The argument value itself can also be incorrect, but this
              /// is checked by the <seealso cref="ArgumentParser#parse(String[], Class)"/> method and reported accordingly.
              /// </summary>
              /// <param name="args"> </param>
              /// <param name="argProxyInterface">
              /// @return </param>
              template<typename T>
              static bool validateArguments(std::string args[], Class *argProxyInterface);

              /// <summary>
              /// Parses the passed arguments and creates an instance of the proxy interface.
              /// <p>
              /// In case an argument value cannot be parsed a <seealso cref="TerminateToolException"/> is
              /// thrown which contains an error message which explains the problems.
              /// </summary>
              /// <param name="args"> </param>
              /// <param name="argProxyInterface">
              /// 
              /// @return
              /// </param>
              /// <exception cref="TerminateToolException"> if an argument value cannot be parsed. </exception>
              /// <exception cref="IllegalArgumentException"> if validateArguments returns false, if the proxy interface is not compatible. </exception>
              template<typename T>
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @SuppressWarnings("unchecked") public static <T> T parse(String args[] , Class argProxyInterface)
              static T parse(std::string args[], Class *argProxyInterface);
            };

        }
    }
}


#endif	//#ifndef ARGUMENTPARSER
