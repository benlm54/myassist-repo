#ifndef EVALUATIONERRORPRINTER
#define EVALUATIONERRORPRINTER

#include "../tools/util/eval/EvaluationMonitor.h"
#include "../tools/util/Span.h"
#include "EvaluationMonitor<T>.h"
#include <string>
#include <vector>

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
            /// <b>Note:</b> Do not use this class, internal use only!
            /// </summary>
            template<typename T>
            class EvaluationErrorPrinter : public EvaluationMonitor<T>
            {

          private:
              PrintStream *printStream;

          protected:
              EvaluationErrorPrinter(OutputStream *outputStream)
              {
                this->printStream = new PrintStream(outputStream);
              }

              // for the sentence detector
              virtual void printError(Span references[], Span predictions[], T referenceSample, T predictedSample, const std::string &sentence)
              {
                std::vector<Span*> falseNegatives = std::vector<Span*>();
                std::vector<Span*> falsePositives = std::vector<Span*>();

                findErrors(references, predictions, falseNegatives, falsePositives);

                if (falsePositives.size() + falseNegatives.size() > 0)
                {

                  printSamples(referenceSample, predictedSample);

                  printErrors(falsePositives, falseNegatives, sentence);

                }
              }

              // for namefinder, chunker...
              virtual void printError(Span references[], Span predictions[], T referenceSample, T predictedSample, std::string sentenceTokens[])
              {
                std::vector<Span*> falseNegatives = std::vector<Span*>();
                std::vector<Span*> falsePositives = std::vector<Span*>();

                findErrors(references, predictions, falseNegatives, falsePositives);

                if (falsePositives.size() + falseNegatives.size() > 0)
                {

                  printSamples(referenceSample, predictedSample);

                  printErrors(falsePositives, falseNegatives, sentenceTokens);

                }
              }

              // for pos tagger
              virtual void printError(std::string references[], std::string predictions[], T referenceSample, T predictedSample, std::string sentenceTokens[])
              {
                std::vector<std::string> filteredDoc = std::vector<std::string>();
                std::vector<std::string> filteredRefs = std::vector<std::string>();
                std::vector<std::string> filteredPreds = std::vector<std::string>();

                for (int i = 0; i < sizeof(references) / sizeof(references[0]); i++)
                {
                  if (references[i] != predictions[i])
                  {
                    filteredDoc.push_back(sentenceTokens[i]);
                    filteredRefs.push_back(references[i]);
                    filteredPreds.push_back(predictions[i]);
                  }
                }

                if (filteredDoc.size() > 0)
                {

                  printSamples(referenceSample, predictedSample);

                  printErrors(filteredDoc, filteredRefs, filteredPreds);

                }
              }

              /// <summary>
              /// Auxiliary method to print tag errors
              /// </summary>
              /// <param name="filteredDoc">
              ///          the document tokens which were tagged wrong </param>
              /// <param name="filteredRefs">
              ///          the reference tags </param>
              /// <param name="filteredPreds">
              ///          the predicted tags </param>
          private:
              void printErrors(std::vector<std::string> &filteredDoc, std::vector<std::string> &filteredRefs, std::vector<std::string> &filteredPreds)
              {
                printStream->println("Errors: {");
                printStream->println("Tok: Ref | Pred");
                printStream->println("---------------");
                for (int i = 0; i < filteredDoc.size(); i++)
                {
                  printStream->println(filteredDoc[i] + ": " + filteredRefs[i] + " | " + filteredPreds[i]);
                }
                printStream->println("}\n");
              }

              /// <summary>
              /// Auxiliary method to print span errors
              /// </summary>
              /// <param name="falsePositives">
              ///          false positives span </param>
              /// <param name="falseNegatives">
              ///          false negative span </param>
              /// <param name="doc">
              ///          the document text </param>
              void printErrors(std::vector<Span*> &falsePositives, std::vector<Span*> &falseNegatives, const std::string &doc)
              {
                printStream->println("False positives: {");
                for (std::vector<Span*>::const_iterator span = falsePositives.begin(); span != falsePositives.end(); ++span)
                {
                  printStream->println((*span)->getCoveredText(doc));
                }
                printStream->println("} False negatives: {");
                for (std::vector<Span*>::const_iterator span = falseNegatives.begin(); span != falseNegatives.end(); ++span)
                {
                  printStream->println((*span)->getCoveredText(doc));
                }
                printStream->println("}\n");
              }

              /// <summary>
              /// Auxiliary method to print span errors
              /// </summary>
              /// <param name="falsePositives">
              ///          false positives span </param>
              /// <param name="falseNegatives">
              ///          false negative span </param>
              /// <param name="toks">
              ///          the document tokens </param>
              void printErrors(std::vector<Span*> &falsePositives, std::vector<Span*> &falseNegatives, std::string toks[])
              {
                printStream->println("False positives: {");
                printStream->println(print(falsePositives, toks));
                printStream->println("} False negatives: {");
                printStream->println(print(falseNegatives, toks));
                printStream->println("}\n");
              }

              /// <summary>
              /// Auxiliary method to print spans
              /// </summary>
              /// <param name="spans">
              ///          the span list </param>
              /// <param name="toks">
              ///          the tokens array </param>
              /// <returns> the spans as string </returns>
              std::string print(std::vector<Span*> &spans, std::string toks[])
              {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                return Arrays->toString(Span::spansToStrings(spans.toArray(new Span[spans.size()]), toks));
              }

              /// <summary>
              /// Auxiliary method to print expected and predicted samples.
              /// </summary>
              /// <param name="referenceSample">
              ///          the reference sample </param>
              /// <param name="predictedSample">
              ///          the predicted sample </param>
              template<typename S>
              void printSamples(S referenceSample, S predictedSample)
              {
                std::string details = "Expected: {\n" + referenceSample + "}\nPredicted: {\n" + predictedSample + "}";
                printStream->println(details);
              }

              /// <summary>
              /// Outputs falseNegatives and falsePositives spans from the references and
              /// predictions list.
              /// </summary>
              /// <param name="references"> </param>
              /// <param name="predictions"> </param>
              /// <param name="falseNegatives">
              ///          [out] the false negatives list </param>
              /// <param name="falsePositives">
              ///          [out] the false positives list </param>
              void findErrors(Span references[], Span predictions[], std::vector<Span*> &falseNegatives, std::vector<Span*> &falsePositives)
              {

                falseNegatives.addAll(Arrays::asList(references));
                falsePositives.addAll(Arrays::asList(predictions));

                for (int referenceIndex = 0; referenceIndex < sizeof(references) / sizeof(references[0]); referenceIndex++)
                {

                  Span *referenceName = references[referenceIndex];

                  for (int predictedIndex = 0; predictedIndex < sizeof(predictions) / sizeof(predictions[0]); predictedIndex++)
                  {
                    if (referenceName->equals(predictions[predictedIndex]))
                    {
                      // got it, remove from fn and fp
                      falseNegatives.remove(referenceName);
                      falsePositives.remove(predictions[predictedIndex]);
                    }
                  }
                }
              }

          public:
              virtual void correctlyClassified(T reference, T prediction)
              {
                // do nothing
              }

              virtual void missclassified(T reference, T prediction) = 0;

            };

        }
    }
}


#endif	//#ifndef EVALUATIONERRORPRINTER
