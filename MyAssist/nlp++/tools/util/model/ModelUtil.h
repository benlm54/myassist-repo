#ifndef MODELUTIL
#define MODELUTIL

#include "../model/AbstractModel.h"
#include "../model/MaxentModel.h"
#include "../tools/util/TrainingParameters.h"
#include <string>
#include <set>

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


                using opennlp::model::AbstractModel;
                using opennlp::model::GenericModelWriter;
                using opennlp::model::MaxentModel;
                using opennlp::tools::util::TrainingParameters;

                /// <summary>
                /// Utility class for handling of <seealso cref="MaxentModel"/>s.
                /// </summary>
                class ModelUtil
                {

              private:
                  ModelUtil();

                  /// <summary>
                  /// Writes the given model to the given <seealso cref="OutputStream"/>.
                  /// 
                  /// This methods does not closes the provided stream.
                  /// </summary>
                  /// <param name="model"> the model to be written </param>
                  /// <param name="out"> the stream the model should be written to
                  /// </param>
                  /// <exception cref="IOException"> </exception>
                  /// @throws <seealso cref="IllegalArgumentException"/> in case one of the parameters is null </exception>
              public:
                  static void writeModel(AbstractModel *model, OutputStream *const out) throw(IOException);

                            private:
                                class OutputStreamAnonymousInnerClassHelper : public OutputStream
                                {
                                public:
                                    virtual void write(int b) throw(IOException);
                                };

                  /// <summary>
                  /// Checks if the expected outcomes are all contained as outcomes in the given model.
                  /// </summary>
                  /// <param name="model"> </param>
                  /// <param name="expectedOutcomes">
                  /// </param>
                  /// <returns> true if all expected outcomes are the only outcomes of the model. </returns>
              public:
//ORIGINAL LINE: public static boolean validateOutcomes(opennlp.model.MaxentModel model, String... expectedOutcomes)
//JAVA TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
                  static bool validateOutcomes(MaxentModel *model, ...);

                  /// <summary>
                  /// Writes the provided <seealso cref="InputStream"/> into a byte array
                  /// which is returned
                  /// </summary>
                  /// <param name="in"> stream to read data for the byte array from </param>
                  /// <returns> byte array with the contents of the stream
                  /// </returns>
                  /// <exception cref="IOException"> if an exception is thrown while reading
                  ///     from the provided <seealso cref="InputStream"/> </exception>
                  static char *read(InputStream *in_Renamed) throw(IOException);

                  static void addCutoffAndIterations(Map<std::string, std::string> *manifestInfoEntries, int cutoff, int iterations);

                  /// <summary>
                  /// Note: Do not use this legacy support method, internal use only!
                  /// </summary>
                  /// <param name="iterations"> </param>
                  /// <param name="cutoff">
                  /// 
                  /// @return </param>
                  static TrainingParameters *createTrainingParameters(int iterations, int cutoff);
                };

            }
        }
    }
}


#endif	//#ifndef MODELUTIL
