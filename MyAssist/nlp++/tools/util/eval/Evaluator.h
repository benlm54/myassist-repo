#ifndef EVALUATOR
#define EVALUATOR

#include "EvaluationMonitor.h"
#include "../tools/util/ObjectStream.h"
#include "T.h"
#include <vector>

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


                using opennlp::tools::util::ObjectStream;

                /// <summary>
                /// The <seealso cref="Evaluator"/> is an abstract base class for evaluators.
                /// 
                /// Evaluation results are the arithmetic mean of the
                /// scores calculated for each reference sample.
                /// </summary>
                template<typename T>
                class Evaluator
                {

              private:
                  std::vector<EvaluationMonitor<T>*> listeners;

              public:
//ORIGINAL LINE: public Evaluator(EvaluationMonitor<T>... aListeners)
//JAVA TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
                  Evaluator(...)
                  {
                    if (aListeners != 0)
                    {
                      std::vector<EvaluationMonitor<T>*> listenersList = std::vector<EvaluationMonitor<T>*>(aListeners::length);
                      for (unknown::const_iterator evaluationMonitor = aListeners.begin(); evaluationMonitor != aListeners.end(); ++evaluationMonitor)
                      {
                        if (evaluationMonitor != 0)
                        {
                          listenersList.push_back(evaluationMonitor);
                        }
                      }
                      listeners = Collections::unmodifiableList(listenersList);
                    }
                    else
                    {
                      listeners = Collections::emptyList();
                    }
                  }

                  /// <summary>
                  /// Evaluates the given reference sample object.
                  /// 
                  /// The implementation has to update the score after every invocation.
                  /// </summary>
                  /// <param name="reference"> the reference sample.
                  /// </param>
                  /// <returns> the predicted sample </returns>
              protected:
                  virtual T processSample(T reference)
                  {
                    // should be overridden by subclass... in the future we will make it abstract.
                    return 0;
                  }

                  /// <summary>
                  /// Evaluates the given reference object. The default implementation calls
                  /// <seealso cref="Evaluator#processSample(T)"/>
                  /// 
                  /// <p>
                  /// <b>note:</b> this method will be changed to private in the future.
                  /// Implementations should override <seealso cref="Evaluator#processSample(T)"/> instead.
                  /// If this method is override, the implementation has to update the score
                  /// after every invocation.
                  /// </p>
                  /// </summary>
                  /// <param name="sample">
                  ///          the sample to be evaluated </param>
              public:
                  virtual void evaluateSample(T sample)
                  {
                    T predicted = processSample(sample);
                    if (!listeners.empty())
                    {
                      if (sample->equals(predicted))
                      {
                        for (std::vector<EvaluationMonitor<T>*>::const_iterator listener = listeners.begin(); listener != listeners.end(); ++listener)
                        {
                          (*listener)->correctlyClassified(predicted, predicted);
                        }
                      }
                      else
                      {
                        for (std::vector<EvaluationMonitor<T>*>::const_iterator listener = listeners.begin(); listener != listeners.end(); ++listener)
                        {
                          (*listener)->missclassified(sample, predicted);
                        }
                      }
                    }
                  }

                  /// <summary>
                  /// Reads all sample objects from the stream
                  /// and evaluates each sample object with
                  /// <seealso cref="#evaluateSample(Object)"/> method.
                  /// </summary>
                  /// <param name="samples"> the stream of reference which
                  /// should be evaluated.
                  ///  </param>
                  virtual void evaluate(ObjectStream<T> *samples) throw(IOException)
                  {
                    T sample;
                    while ((sample = samples->read()) != 0)
                    {
                      evaluateSample(sample);
                    }
                  }
                };

            }
        }
    }
}


#endif	//#ifndef EVALUATOR
