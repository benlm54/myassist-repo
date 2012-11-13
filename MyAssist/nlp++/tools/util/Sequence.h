#ifndef SEQUENCE
#define SEQUENCE

#include "Comparable<Sequence>.h"
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


            /// <summary>
            /// Represents a weighted sequence of outcomes. </summary>
            class Sequence : public Comparable<Sequence*>
            {
          private:
              double score;
              std::vector<std::string> outcomes;
              std::vector<double> probs;
              static const double ONE;

              /// <summary>
              /// Creates a new sequence of outcomes. </summary>
          public:
              Sequence();

              Sequence(Sequence *s);

              Sequence(Sequence *s, const std::string &outcome, double p);

              Sequence(std::vector<std::string> &outcomes);

              virtual int compareTo(Sequence *s);

              /// <summary>
              /// Adds an outcome and probability to this sequence. </summary>
              /// <param name="outcome"> the outcome to be added. </param>
              /// <param name="p"> the probability associated with this outcome. </param>
              virtual void add(const std::string &outcome, double p);

              /// <summary>
              /// Returns a list of outcomes for this sequence. </summary>
              /// <returns> a list of outcomes. </returns>
              virtual std::vector<std::string> getOutcomes();

              /// <summary>
              /// Returns an array of probabilities associated with the outcomes of this sequence. </summary>
              /// <returns> an array of probabilities. </returns>
              virtual double *getProbs();

              /// <summary>
              /// Returns the score of this sequence. </summary>
              /// <returns> The score of this sequence. </returns>
              virtual double getScore();

              /// <summary>
              /// Populates  an array with the probabilities associated with the outcomes of this sequence. </summary>
              /// <param name="ps"> a pre-allocated array to use to hold the values of the probabilities of the outcomes for this sequence. </param>
              virtual void getProbs(double ps[]);

              virtual std::string ToString();
            };

        }
    }
}


#endif	//#ifndef SEQUENCE
