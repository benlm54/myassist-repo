#ifndef FMEASURE
#define FMEASURE

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
        namespace util
        {
            namespace eval
            {


                /// <summary>
                /// The <seealso cref="FMeasure"/> is an utility class for evaluators
                /// which measure precision, recall and the resulting f-measure.
                /// 
                /// Evaluation results are the arithmetic mean of the precision
                /// scores calculated for each reference sample and
                /// the arithmetic mean of the recall scores calculated for
                /// each reference sample.
                /// </summary>
                class FMeasure
                {

                    /// <summary>
                    /// |selected| = true positives + false positives <br>
                    /// the count of selected (or retrieved) items  
                    /// </summary>
                private:
                    long long selected;

                    /// <summary>
                    /// |target| = true positives + false negatives <br>
                    /// the count of target (or correct) items 
                    /// </summary>
                    long long target;

                    long long truePositive;

                  /// <summary>
                  /// Retrieves the arithmetic mean of the precision scores
                  /// calculated for each evaluated sample.
                  /// </summary>
                  /// <returns> the arithmetic mean of all precision scores </returns>
              public:
                  double getPrecisionScore();

                  /// <summary>
                  /// Retrieves the arithmetic mean of the recall score
                  /// calculated for each evaluated sample.
                  /// </summary>
                  /// <returns> the arithmetic mean of all recall scores </returns>
                  double getRecallScore();

                  /// <summary>
                  /// Retrieves the f-measure score.
                  /// 
                  /// f-measure = 2 * precision * recall / (precision + recall)
                  /// </summary>
                  /// <returns> the f-measure or -1 if precision + recall <= 0 </returns>
                  double getFMeasure();

                  void updateScores(Object references[], Object predictions[]);

                  void mergeInto(FMeasure *measure);

                  /// <summary>
                  /// Creates a human read-able <seealso cref="String"/> representation.
                  /// </summary>
                  virtual std::string ToString();

                  /// <summary>
                  /// This method counts the number of objects which are equal and
                  /// occur in the references and predictions arrays.
                  /// 
                  /// These are the number of true positives.
                  /// </summary>
                  /// <param name="references"> the gold standard </param>
                  /// <param name="predictions"> the predictions
                  /// </param>
                  /// <returns> number of true positives </returns>
                  static int countTruePositives(Object references[], Object predictions[]);

                  /// <summary>
                  /// Calculates the precision score for the given reference and
                  /// predicted spans.
                  /// </summary>
                  /// <param name="references"> the gold standard spans </param>
                  /// <param name="predictions"> the predicted spans
                  /// </param>
                  /// <returns> the precision score or NaN if there are no predicted spans </returns>
                  static double precision(Object references[], Object predictions[]);

                  /// <summary>
                  /// Calculates the recall score for the given reference and
                  /// predicted spans.
                  /// </summary>
                  /// <param name="references"> the gold standard spans </param>
                  /// <param name="predictions"> the predicted spans
                  /// </param>
                  /// <returns> the recall score or NaN if there are no reference spans </returns>
                  static double recall(Object references[], Object predictions[]);
                };

            }
        }
    }
}


#endif	//#ifndef FMEASURE
