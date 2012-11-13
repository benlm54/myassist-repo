#ifndef BEAMSEARCH
#define BEAMSEARCH

#include "BeamSearchContextGenerator.h"
#include "../model/MaxentModel.h"
#include "SequenceValidator.h"
#include "Cache.h"
#include "../model/Sequence.h"
#include "Sequence.h"
#include "Heap.h"
#include "ListHeap.h"
#include <string>
#include <vector>
#include <cmath>

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


            using opennlp::model::MaxentModel;

            /// <summary>
            /// Performs k-best search over sequence.  This is based on the description in
            /// Ratnaparkhi (1998), PhD diss, Univ. of Pennsylvania.
            /// </summary>
            /// <seealso cref= Sequence </seealso>
            /// <seealso cref= SequenceValidator </seealso>
            /// <seealso cref= BeamSearchContextGenerator </seealso>
            template<typename T>
            class BeamSearch
            {

          private:
//ORIGINAL LINE: private static final Object[] EMPTY_ADDITIONAL_CONTEXT = new Object[0];
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//JAVA TO C++ CONVERTER TODO TASK: Native C++ only allows initialization of static const integral fields in their declarations:
              static const void *EMPTY_ADDITIONAL_CONTEXT = new Object[0];

          protected:
              int size;
              BeamSearchContextGenerator<T> *cg;
              MaxentModel *model;
          private:
              SequenceValidator<T> *validator;

//ORIGINAL LINE: private double[] probs;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              double *probs;
              Cache *contextsCache;
              static const int zeroLog = -100000;

              /// <summary>
              /// Creates new search object.
              /// </summary>
              /// <param name="size"> The size of the beam (k). </param>
              /// <param name="cg"> the context generator for the model. </param>
              /// <param name="model"> the model for assigning probabilities to the sequence outcomes. </param>
          public:
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              BeamSearch(int size, BeamSearchContextGenerator<T> *cg, MaxentModel *model) //this(size, cg, model, nullptr, 0);
              {
              }

//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              BeamSearch(int size, BeamSearchContextGenerator<T> *cg, MaxentModel *model, int cacheSize) //this(size, cg, model, nullptr, cacheSize);
              {
              }

              BeamSearch(int size, BeamSearchContextGenerator<T> *cg, MaxentModel *model, SequenceValidator<T> *validator, int cacheSize)
              {

                this->size = size;
                this->cg = cg;
                this->model = model;
                this->validator = validator;

                if (cacheSize > 0)
                {
                  contextsCache = new Cache(cacheSize);
                }

                this->probs = new double[model->getNumOutcomes()];
              }

              /// <summary>
              /// Note:
              /// This method will be private in the future because clients can now
              /// pass a validator to validate the sequence.
              /// </summary>
              /// <seealso cref= SequenceValidator </seealso>
          private:
              bool validSequence(int i, T inputSequence[], std::string outcomesSequence[], const std::string &outcome)
              {

                if (validator != 0)
                {
                  return validator->validSequence(i, inputSequence, outcomesSequence, outcome);
                }
                else
                {
                  return true;
                }
              }

          public:
              virtual Sequence *bestSequences(int numSequences, T sequence[], Object additionalContext[])
              {
                return bestSequences(numSequences, sequence, additionalContext, zeroLog);
              }

              /// <summary>
              /// Returns the best sequence of outcomes based on model for this object.
              /// </summary>
              /// <param name="numSequences"> The maximum number of sequences to be returned. </param>
              /// <param name="sequence"> The input sequence. </param>
              /// <param name="additionalContext"> An Object[] of additional context.  This is passed to the context generator blindly with the assumption that the context are appropiate. </param>
              /// <param name="minSequenceScore"> A lower bound on the score of a returned sequence. </param>
              /// <returns> An array of the top ranked sequences of outcomes. </returns>
              virtual Sequence *bestSequences(int numSequences, T sequence[], Object additionalContext[], double minSequenceScore)
              {

                Heap<Sequence*> *prev = new ListHeap<Sequence*>(size);
                Heap<Sequence*> *next = new ListHeap<Sequence*>(size);
                Heap<Sequence*> *tmp;
                prev->add(new Sequence());

                if (additionalContext == 0)
                {
                  additionalContext = EMPTY_ADDITIONAL_CONTEXT;
                }

                for (int i = 0; i < sizeof(sequence) / sizeof(sequence[0]); i++)
                {
                  int sz = __min(size, prev->size());

                  for (int sc = 0; prev->size() > 0 && sc < sz; sc++)
                  {
                    Sequence *top = prev->extract();
                    std::vector<std::string> tmpOutcomes = top->getOutcomes();
//ORIGINAL LINE: String[] outcomes = tmpOutcomes.toArray(new String[tmpOutcomes.size()]);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                    std::string *outcomes = tmpOutcomes.toArray(new std::string[tmpOutcomes.size()]);
//ORIGINAL LINE: String[] contexts = cg.getContext(i, sequence, outcomes, additionalContext);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                    std::string *contexts = cg->getContext(i, sequence, outcomes, additionalContext);
//ORIGINAL LINE: double[] scores;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                    double *scores;
                    if (contextsCache != 0)
                    {
                      scores = static_cast<double[]>(contextsCache->get_Renamed(contexts));
                      if (scores == 0)
                      {
                        scores = model->eval(contexts, probs);
                        contextsCache->put(contexts,scores);
                      }
                    }
                    else
                    {
                      scores = model->eval(contexts, probs);
                    }

                    double temp_scores[scores->length];
                    for (int c = 0; c < scores->length; c++)
                    {
                      temp_scores[c] = scores[c];
                    }

                    Arrays::sort(temp_scores);

                    double min = temp_scores[__max(0,scores->length - size)];

                    for (int p = 0; p < scores->length; p++)
                    {
                      if (scores[p] < min)
                        continue; //only advance first "size" outcomes
                      std::string out = model->getOutcome(p);
                      if (validSequence(i, sequence, outcomes, out))
                      {
                        Sequence *ns = new Sequence(top, out, scores[p]);
                        if (ns->getScore() > minSequenceScore)
                        {
                          next->add(ns);
                        }
                      }
                    }

                    if (next->size() == 0) //if no advanced sequences, advance all valid
                    {
                      for (int p = 0; p < scores->length; p++)
                      {
                        std::string out = model->getOutcome(p);
                        if (validSequence(i, sequence, outcomes, out))
                        {
                          Sequence *ns = new Sequence(top, out, scores[p]);
                          if (ns->getScore() > minSequenceScore)
                          {
                            next->add(ns);
                          }
                        }
                      }
                    }
                  }

                  //    make prev = next; and re-init next (we reuse existing prev set once we clear it)
                  prev->clear();
                  tmp = prev;
                  prev = next;
                  next = tmp;
                }

                int numSeq = __min(numSequences, prev->size());
                Sequence topSequences[numSeq];

                for (int seqIndex = 0; seqIndex < numSeq; seqIndex++)
                {
                  topSequences[seqIndex] = prev->extract();
                }

                return topSequences;
              }

              /// <summary>
              /// Returns the best sequence of outcomes based on model for this object.
              /// </summary>
              /// <param name="sequence"> The input sequence. </param>
              /// <param name="additionalContext"> An Object[] of additional context.  This is passed to the context generator blindly with the assumption that the context are appropiate.
              /// </param>
              /// <returns> The top ranked sequence of outcomes or null if no sequence could be found </returns>
              virtual Sequence *bestSequence(T sequence[], Object additionalContext[])
              {
//ORIGINAL LINE: Sequence sequences[] = bestSequences(1, sequence, additionalContext,zeroLog);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                Sequence *sequences = bestSequences(1, sequence, additionalContext,zeroLog);

                if (sequences->length > 0)
                  return sequences[0];
                else
                  return 0;
              }
            };

        }
    }
}


#endif	//#ifndef BEAMSEARCH
