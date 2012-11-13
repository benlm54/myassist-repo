#ifndef DETAILEDFMEASURELISTENER
#define DETAILEDFMEASURELISTENER

#include "../tools/util/eval/EvaluationMonitor.h"
#include "../tools/util/Span.h"
#include "EvaluationMonitor<T>.h"
#include "const_iterator.h"
#include "StringBuilder.h"
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
        namespace cmdline
        {


            using opennlp::tools::util::Span;
            using opennlp::tools::util::eval::EvaluationMonitor;

            /// <summary>
            /// This listener will gather detailed information about the sample under evaluation and will
            /// allow detailed FMeasure for each outcome.
            /// <p>
            /// <b>Note:</b> Do not use this class, internal use only!
            /// </summary>
            template<typename T>
            class DetailedFMeasureListener : public EvaluationMonitor<T>
            {
          private:
              class F1Comparator : public Comparator<std::string>
              {
                      private:
                          DetailedFMeasureListener *const outerInstance;

                      public:
                          F1Comparator(DetailedFMeasureListener *outerInstance);

                virtual int compare(const std::string &o1, const std::string &o2);

              };

          private:
              class Stats
              {
                      private:
                          DetailedFMeasureListener *const outerInstance;

                      public:
                          Stats(DetailedFMeasureListener *outerInstance);


                // maybe we could use FMeasure class, but it wouldn't allow us to get
                // details like total number of false positives and true positives.

            private:
                int falsePositiveCounter;
                int truePositiveCounter;
                int targetCounter;

            public:
                virtual void incrementFalsePositive();

                virtual void incrementTruePositive();

                virtual void incrementTarget();

                virtual int getFalsePositives();

                virtual int getTruePositives();

                virtual int getTarget();

                /// <summary>
                /// Retrieves the arithmetic mean of the precision scores calculated for each
                /// evaluated sample.
                /// </summary>
                /// <returns> the arithmetic mean of all precision scores </returns>
                virtual double getPrecisionScore();

                /// <summary>
                /// Retrieves the arithmetic mean of the recall score calculated for each
                /// evaluated sample.
                /// </summary>
                /// <returns> the arithmetic mean of all recall scores </returns>
                virtual double getRecallScore();

                /// <summary>
                /// Retrieves the f-measure score.
                /// 
                /// f-measure = 2 * precision * recall / (precision + recall)
                /// </summary>
                /// <returns> the f-measure or -1 if precision + recall <= 0 </returns>
                virtual double getFMeasure();


              private:
                  void InitializeInstanceFields();
              };


          private:
              int samples;
              Stats *generalStats;
              Map<std::string, Stats*> *statsForOutcome;

          protected:
              virtual Span *asSpanArray(T sample) = 0;

          public:
              virtual void correctlyClassified(T reference, T prediction)
              {
                samples++;
                // add all true positives!
//ORIGINAL LINE: opennlp.tools.util.Span[] spans = asSpanArray(reference);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                Span *spans = asSpanArray(reference);
                for (Span::const_iterator span = spans->begin(); span != spans->end(); ++span)
                {
                  addTruePositive(span->getType());
                }
              }

              virtual void missclassified(T reference, T prediction)
              {
                samples++;
//ORIGINAL LINE: opennlp.tools.util.Span[] references = asSpanArray(reference);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                Span *references = asSpanArray(reference);
//ORIGINAL LINE: opennlp.tools.util.Span[] predictions = asSpanArray(prediction);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                Span *predictions = asSpanArray(prediction);

                Set<Span*> *refSet = std::set<Span*>(Arrays::asList(references));
                Set<Span*> *predSet = std::set<Span*>(Arrays::asList(predictions));

                for (Set<Span*>::const_iterator ref = refSet->begin(); ref != refSet->end(); ++ref)
                {
                  if (predSet->contains(*ref))
                  {
                    addTruePositive((*ref)->getType());
                  }
                  else
                  {
                    addFalseNegative((*ref)->getType());
                  }
                }

                for (Set<Span*>::const_iterator pred = predSet->begin(); pred != predSet->end(); ++pred)
                {
                  if (!refSet->contains(*pred))
                  {
                    addFalsePositive((*pred)->getType());
                  }
                }
              }

          private:
              void addTruePositive(const std::string &type)
              {
                Stats *s = initStatsForOutcomeAndGet(type);
                s->incrementTruePositive();
                s->incrementTarget();

                generalStats->incrementTruePositive();
                generalStats->incrementTarget();
              }

              void addFalsePositive(const std::string &type)
              {
                Stats *s = initStatsForOutcomeAndGet(type);
                s->incrementFalsePositive();
                generalStats->incrementFalsePositive();
              }

              void addFalseNegative(const std::string &type)
              {
                Stats *s = initStatsForOutcomeAndGet(type);
                s->incrementTarget();
                generalStats->incrementTarget();

              }

              Stats *initStatsForOutcomeAndGet(const std::string &type)
              {
                if (!statsForOutcome->containsKey(type))
                {
                  statsForOutcome->put(type, new Stats(this));
                }
                return statsForOutcome->get(type);
              }

//JAVA TO C++ CONVERTER TODO TASK: Native C++ only allows initialization of static const integral fields in their declarations:
              static const std::string PERCENT = "%\u00207.2f%%";
//JAVA TO C++ CONVERTER TODO TASK: Native C++ only allows initialization of static const integral fields in their declarations:
              static const std::string FORMAT = "%12s: precision: " + PERCENT + ";  recall: " + PERCENT + "; F1: " + PERCENT + ".";
//JAVA TO C++ CONVERTER TODO TASK: Native C++ only allows initialization of static const integral fields in their declarations:
              static const std::string FORMAT_EXTRA = FORMAT + " [target: %3d; tp: %3d; fp: %3d]";

          public:
              virtual std::string createReport()
              {
                return createReport(Locale::getDefault());
              }

              virtual std::string createReport(Locale *locale)
              {
                StringBuilder *ret = new StringBuilder();
                int tp = generalStats->getTruePositives();
                int found = generalStats->getFalsePositives() + tp;
                ret->append("Evaluated " + samples + " samples with " + generalStats->getTarget() + " entities; found: " + found + " entities; correct: " + tp + ".\n");

                ret->append(std::string::format(locale, FORMAT, "TOTAL", zeroOrPositive(generalStats->getPrecisionScore() * 100), zeroOrPositive(generalStats->getRecallScore() * 100), zeroOrPositive(generalStats->getFMeasure() * 100)));
                ret->append("\n");
                SortedSet<std::string> *set_Renamed = new TreeSet<std::string>(new F1Comparator(this));
                set_Renamed->addAll(statsForOutcome->keySet());
                for (SortedSet<std::string>::const_iterator type = set_Renamed->begin(); type != set_Renamed->end(); ++type)
                {

                  ret->append(std::string::format(locale, FORMAT_EXTRA, *type, zeroOrPositive(statsForOutcome->get(*type)->getPrecisionScore() * 100), zeroOrPositive(statsForOutcome->get(*type)->getRecallScore() * 100), zeroOrPositive(statsForOutcome->get(*type)->getFMeasure() * 100), statsForOutcome->get(*type)->getTarget(), statsForOutcome->get(*type)->getTruePositives(), statsForOutcome->get(*type)->getFalsePositives()));
                  ret->append("\n");
                }

//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                return ret->toString();
              }

              virtual std::string ToString()
              {
                return createReport();
              }

          private:
              double zeroOrPositive(double v)
              {
                if (v < 0)
                {
                  return 0;
                }
                return v;
              }

              /// <summary>
              /// Store the statistics.
              /// </summary>

            private:
                void InitializeInstanceFields()
                {
                    samples = 0;
                    generalStats = new Stats(this);
                    statsForOutcome = std::map<std::string, Stats*>();
                }

public:
                DetailedFMeasureListener()
                {
                    InitializeInstanceFields();
                }
            };

        }
    }
}


#endif	//#ifndef DETAILEDFMEASURELISTENER
