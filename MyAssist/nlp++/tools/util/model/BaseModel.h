#ifndef BASEMODEL
#define BASEMODEL

#include "ArtifactSerializer.h"
#include "../tools/util/InvalidFormatException.h"
#include "../tools/util/Version.h"
#include "Properties.h"
#include "NumberFormatException.h"
#include <string>
#include <map>

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
            namespace model
            {


                using opennlp::tools::util::InvalidFormatException;
                using opennlp::tools::util::Version;

                /// <summary>
                /// This model is a common based which can be used by the components
                /// model classes.
                /// 
                /// TODO:
                /// Provide sub classes access to serializers already in constructor
                /// </summary>
                class BaseModel
                {

              protected:
                  static const std::string MANIFEST_ENTRY;

              private:
                  static const std::string MANIFEST_VERSION_PROPERTY;
                  static const std::string COMPONENT_NAME_PROPERTY;
                  static const std::string VERSION_PROPERTY;
                  static const std::string TIMESTAMP_PROPERTY;
                  static const std::string LANGUAGE_PROPERTY;

              public:
                  static const std::string TRAINING_CUTOFF_PROPERTY;
                  static const std::string TRAINING_ITERATIONS_PROPERTY;
                  static const std::string TRAINING_EVENTHASH_PROPERTY;

              private:
                  Map<std::string, ArtifactSerializer*> *artifactSerializers;

              protected:
                  Map<std::string, void*> *const artifactMap;

              private:
                  const std::string componentName;

                  /// <summary>
                  /// Initializes the current instance.
                  /// </summary>
                  /// <param name="languageCode"> </param>
                  /// <param name="manifestInfoEntries"> additional information in the manifest </param>
              protected:
                  BaseModel(const std::string &componentName, const std::string &languageCode, Map<std::string, std::string> *manifestInfoEntries);

                  /// <summary>
                  /// Initializes the current instance.
                  /// </summary>
                  /// <param name="in">
                  /// </param>
                  /// <exception cref="IOException"> </exception>
                  /// <exception cref="InvalidFormatException"> </exception>
                  BaseModel(const std::string &componentName, InputStream *in_Renamed) throw(IOException, InvalidFormatException);

                  /// <summary>
                  /// Extracts the "." extension from an entry name.
                  /// </summary>
                  /// <param name="entry"> the entry name which contains the extension
                  /// </param>
                  /// <returns> the extension
                  /// </returns>
                  /// <exception cref="InvalidFormatException"> if no extension can be extracted </exception>
              private:
                  std::string getEntryExtension(const std::string &entry) throw(InvalidFormatException);

              protected:
                  virtual ArtifactSerializer *getArtifactSerializer(const std::string &resoruceName);

                  static Map<std::string, ArtifactSerializer*> *createArtifactSerializers();

                  /// <summary>
                  /// Registers all <seealso cref="ArtifactSerializer"/> for their artifact file name extensions.
                  /// The registered <seealso cref="ArtifactSerializer"/> are used to create and serialize
                  /// resources in the model package.
                  /// 
                  /// Override this method to register custom <seealso cref="ArtifactSerializer"/>s.
                  /// 
                  /// Note:
                  /// Subclasses should generally invoke super.createArtifactSerializers at the beginning
                  /// of this method.
                  /// 
                  /// This method is called during construction.
                  /// </summary>
                  /// <param name="serializers"> the key of the map is the file extension used to lookup
                  ///     the <seealso cref="ArtifactSerializer"/>. </param>
                  virtual void createArtifactSerializers(Map<std::string, ArtifactSerializer*> *serializers);

                  /// <summary>
                  /// Validates the parsed artifacts. If something is not
                  /// valid subclasses should throw an <seealso cref="InvalidFormatException"/>.
                  /// 
                  /// Note:
                  /// Subclasses should generally invoke super.validateArtifactMap at the beginning
                  /// of this method.
                  /// </summary>
                  /// <exception cref="InvalidFormatException"> </exception>
                  virtual void validateArtifactMap() throw(InvalidFormatException);

                  /// <summary>
                  /// Checks the artifact map. 
                  /// <p>
                  /// A subclass should call this method from a constructor which accepts the individual
                  /// artifact map items, to validate that these items form a valid model.
                  /// <p>
                  /// If the artifacts are not valid an IllegalArgumentException will be thrown.
                  /// </summary>
                  virtual void checkArtifactMap();

                  /// <summary>
                  /// Retrieves the value to the given key from the manifest.properties
                  /// entry.
                  /// </summary>
                  /// <param name="key">
                  /// </param>
                  /// <returns> the value </returns>
              public:
                  std::string getManifestProperty(const std::string &key);

                  /// <summary>
                  /// Sets a given value for a given key to the manifest.properties entry.
                  /// </summary>
                  /// <param name="key"> </param>
                  /// <param name="value"> </param>
              protected:
                  void setManifestProperty(const std::string &key, const std::string &value);

                  /// <summary>
                  /// Retrieves the language code of the material which
                  /// was used to train the model or x-unspecified if
                  /// non was set.
                  /// </summary>
                  /// <returns> the language code of this model </returns>
              public:
                  std::string getLanguage();

                  /// <summary>
                  /// Retrieves the OpenNLP version which was used
                  /// to create the model.
                  /// </summary>
                  /// <returns> the version </returns>
                  Version *getVersion();

                  /// <summary>
                  /// Serializes the model to the given <seealso cref="OutputStream"/>.
                  /// </summary>
                  /// <param name="out"> stream to write the model to </param>
                  /// <exception cref="IOException"> </exception>
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @SuppressWarnings("unchecked") public final void serialize(java.io.OutputStream out) throws java.io.IOException
                  void serialize(OutputStream *out) throw(IOException);

                private:
                    void InitializeInstanceFields();
                };

            }
        }
    }
}


#endif	//#ifndef BASEMODEL
