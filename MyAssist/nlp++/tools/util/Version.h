#ifndef VERSION
#define VERSION

#include <string>
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
        namespace util
        {


            /// <summary>
            /// The <seealso cref="Version"/> class represents the OpenNlp Tools library version.
            /// <p>
            /// The version has three parts:
            /// <ul>
            /// <li>Major: OpenNlp Tools libraries with a different major version are not interchangeable.</li>
            /// <li>Minor: OpenNlp Tools libraries with an identical major version, but different
            ///     minor version may be interchangeable. See release notes for further details.</li>
            /// <li>Revision: OpenNlp Tools libraries with same major and minor version, but a different
            ///     revision, are fully interchangeable.</li>
            /// </ul>
            /// </summary>
            class Version
            {

          private:
              static const std::string DEV_VERSION_STRING; //"0.0.0-SNAPSHOT";

          public:
              static Version *const DEV_VERSION;

          private:
              static const std::string SNAPSHOT_MARKER;

              const int major;

              const int minor;

              const int revision;

              const bool snapshot;

              /// <summary>
              /// Initializes the current instance with the provided
              /// versions.
              /// </summary>
              /// <param name="major"> </param>
              /// <param name="minor"> </param>
              /// <param name="revision"> </param>
              /// <param name="snapshot"> </param>
          public:
              Version(int major, int minor, int revision, bool snapshot);

              /// <summary>
              /// Initializes the current instance with the provided
              /// versions. The version will not be a snapshot version.
              /// </summary>
              /// <param name="major"> </param>
              /// <param name="minor"> </param>
              /// <param name="revision"> </param>
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              Version(int major, int minor, int revision); //this(major, minor, revision, false);


              /// <summary>
              /// Retrieves the major version.
              /// </summary>
              /// <returns> major version </returns>
              virtual int getMajor();

              /// <summary>
              /// Retrieves the minor version.
              /// </summary>
              /// <returns> minor version </returns>
              virtual int getMinor();

              /// <summary>
              /// Retrieves the revision version.
              /// </summary>
              /// <returns> revision version </returns>
              virtual int getRevision();

              virtual bool isSnapshot();

              /// <summary>
              /// Retrieves the version string.
              /// 
              /// The <seealso cref="#parse(String)"/> method can create an instance
              /// of <seealso cref="Version"/> with the returned version value string.
              /// </summary>
              /// <returns> the version value string </returns>
              virtual std::string ToString();

              virtual bool Equals(void *o);

              /// <summary>
              /// Return a new <seealso cref="Version"/> initialized to the value
              /// represented by the specified <seealso cref="String"/>
              /// </summary>
              /// <param name="version"> the string to be parsed
              /// </param>
              /// <returns> the version represented by the string value
              /// </returns>
              /// <exception cref="NumberFormatException"> if the string does
              /// not contain a valid version </exception>
              static Version *parse(const std::string &version);

              /// <summary>
              /// Retrieves the current version of the OpenNlp Tools library.
              /// </summary>
              /// <returns> the current version </returns>
              static Version *currentVersion();
            };

        }
    }
}


#endif	//#ifndef VERSION
