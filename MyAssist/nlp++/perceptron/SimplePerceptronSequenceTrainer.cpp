#include "SimplePerceptronSequenceTrainer.h"
#include "model/DataIndexer.h"
#include "model/OnePassDataIndexer.h"
#include "model/SequenceStreamEventStream.h"
#include "perceptron/PerceptronModel.h"
#include "model/Event.h"
#include "const_iterator.h"

namespace opennlp
{
    namespace perceptron
    {
        using opennlp::model::AbstractModel;
        using opennlp::model::DataIndexer;
        using opennlp::model::Event;
        using opennlp::model::IndexHashTable;
        using opennlp::model::MutableContext;
        using opennlp::model::OnePassDataIndexer;
        using opennlp::model::Sequence;
        using opennlp::model::SequenceStream;
        using opennlp::model::SequenceStreamEventStream;
        using opennlp::model::TwoPassDataIndexer;

        opennlp::model::AbstractModel *SimplePerceptronSequenceTrainer::trainModel(int iterations, SequenceStream *sequenceStream, int cutoff, bool useAverage) throw(IOException)
        {
          this->iterations = iterations;
          this->sequenceStream = sequenceStream;
          DataIndexer *di = new OnePassDataIndexer(new SequenceStreamEventStream(sequenceStream),cutoff,false);
          numSequences = 0;
          for (SequenceStream::const_iterator s = sequenceStream->begin(); s != sequenceStream->end(); ++s)
          {
            numSequences++;
          }
          outcomeList = di->getOutcomeList();
          predLabels = di->getPredLabels();
          pmap = new IndexHashTable<std::string>(predLabels, 0.7);

          display("Incorporating indexed data for training...  \n");
          this->useAverage = useAverage;
          numEvents = di->getNumEvents();

          this->iterations = iterations;
          outcomeLabels = di->getOutcomeLabels();
          omap = std::map<std::string, int>();
          for (int oli = 0;oli < outcomeLabels->length;oli++)
          {
            omap->put(outcomeLabels[oli], oli);
          }
          outcomeList = di->getOutcomeList();

          numPreds = predLabels->length;
          numOutcomes = outcomeLabels->length;
          if (useAverage)
          {
//ORIGINAL LINE: updates = new int[numPreds][numOutcomes][3];
//JAVA TO C++ CONVERTER NOTE: The following call to the 'RectangularArrays' helper class reproduces the rectangular array initialization that is automatic in Java:
            updates = RectangularArrays::ReturnRectangularIntArray(numPreds, numOutcomes, 3);
          }

          display("done.\n");

          display("\tNumber of Event Tokens: " + numEvents + "\n");
          display("\t    Number of Outcomes: " + numOutcomes + "\n");
          display("\t  Number of Predicates: " + numPreds + "\n");


          params = new MutableContext[numPreds];
          if (useAverage)
              averageParams = new MutableContext[numPreds];

          allOutcomesPattern = new int[numOutcomes];
          for (int oi = 0; oi < numOutcomes; oi++)
          {
            allOutcomesPattern[oi] = oi;
          }

          for (int pi = 0; pi < numPreds; pi++)
          {
            params[pi] = new MutableContext(allOutcomesPattern,new double[numOutcomes]);
            if (useAverage)
                averageParams[pi] = new MutableContext(allOutcomesPattern,new double[numOutcomes]);
            for (int aoi = 0;aoi < numOutcomes;aoi++)
            {
              params[pi]->setParameter(aoi, 0.0);
              if (useAverage)
                  averageParams[pi]->setParameter(aoi, 0.0);
            }
          }
          modelDistribution = new double[numOutcomes];

          display("Computing model parameters...\n");
          findParameters(iterations);
          display("...done.\n");

          /// <summary>
          ///************* Create and return the model ***************** </summary>
//ORIGINAL LINE: String[] updatedPredLabels = predLabels;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          std::string *updatedPredLabels = predLabels;
          /*
          String[] updatedPredLabels = new String[pmap.size()];
          for (String pred : pmap.keySet()) {
            updatedPredLabels[pmap.get(pred)]=pred;
          }
          */
          if (useAverage)
          {
            return new PerceptronModel(averageParams, updatedPredLabels, outcomeLabels);
          }
          else
          {
            return new PerceptronModel(params, updatedPredLabels, outcomeLabels);
          }
        }

        void SimplePerceptronSequenceTrainer::findParameters(int iterations)
        {
          display("Performing " + iterations + " iterations.\n");
          for (int i = 1; i <= iterations; i++)
          {
            if (i < 10)
              display("  " + i + ":  ");
            else if (i < 100)
              display(" " + i + ":  ");
            else
              display(i + ":  ");
            nextIteration(i);
          }
          if (useAverage)
          {
            trainingStats(averageParams);
          }
          else
          {
            trainingStats(params);
          }
        }

        void SimplePerceptronSequenceTrainer::display(const std::string &s)
        {
          if (printMessages)
            std::cout << s;
        }

        void SimplePerceptronSequenceTrainer::nextIteration(int iteration)
        {
          iteration--; //move to 0-based index
          int numCorrect = 0;
          int oei = 0;
          int si = 0;
          Map<std::string, float> featureCounts[numOutcomes];
          for (int oi = 0;oi < numOutcomes;oi++)
          {
            featureCounts[oi] = std::map<std::string, float>();
          }
          PerceptronModel *model = new PerceptronModel(params,predLabels,pmap,outcomeLabels);
          for (SequenceStream::const_iterator sequence = sequenceStream->begin(); sequence != sequenceStream->end(); ++sequence)
          {
//ORIGINAL LINE: opennlp.model.Event[] taggerEvents = sequenceStream.updateContext(sequence, model);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
            Event *taggerEvents = sequenceStream->updateContext(sequence, model);
//ORIGINAL LINE: opennlp.model.Event[] events = sequence.getEvents();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
            Event *events = sequence->getEvents();
            bool update = false;
            for (int ei = 0;ei < events->length;ei++,oei++)
            {
              if (taggerEvents[ei]->getOutcome() != events[ei]->getOutcome())
              {
                update = true;
                //break;
              }
              else
              {
                numCorrect++;
              }
            }
            if (update)
            {
              for (int oi = 0;oi < numOutcomes;oi++)
              {
                featureCounts[oi]->clear();
              }
              //System.err.print("train:");for (int ei=0;ei<events.length;ei++) {System.err.print(" "+events[ei].getOutcome());} System.err.println();
              //training feature count computation
              for (int ei = 0;ei < events->length;ei++,oei++)
              {
//ORIGINAL LINE: String[] contextStrings = events[ei].getContext();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                std::string *contextStrings = events[ei]->getContext();
//ORIGINAL LINE: float values[] = events[ei].getValues();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                float *values = events[ei]->getValues();
                int oi = omap->get(events[ei]->getOutcome());
                for (int ci = 0;ci < contextStrings->length;ci++)
                {
                  float value = 1;
                  if (values != 0)
                  {
                    value = values[ci];
                  }
                  float c = featureCounts[oi]->get(contextStrings[ci]);
                  if (c == 0)
                  {
                    c = value;
                  }
                  else
                  {
                    c += value;
                  }
                  featureCounts[oi]->put(contextStrings[ci], c);
                }
              }
              //evaluation feature count computation
              //System.err.print("test: ");for (int ei=0;ei<taggerEvents.length;ei++) {System.err.print(" "+taggerEvents[ei].getOutcome());} System.err.println();
              for (int ei = 0;ei < taggerEvents->length;ei++)
              {
//ORIGINAL LINE: String[] contextStrings = taggerEvents[ei].getContext();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                std::string *contextStrings = taggerEvents[ei]->getContext();
//ORIGINAL LINE: float values[] =taggerEvents[ei].getValues();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                float *values = taggerEvents[ei]->getValues();
                int oi = omap->get(taggerEvents[ei]->getOutcome());
                for (int ci = 0;ci < contextStrings->length;ci++)
                {
                  float value = 1;
                  if (values != 0)
                  {
                    value = values[ci];
                  }
                  float c = featureCounts[oi]->get(contextStrings[ci]);
                  if (c == 0)
                  {
                    c = -1*value;
                  }
                  else
                  {
                    c -= value;
                  }
                  if (c == 0)
                  {
                    featureCounts[oi]->remove(contextStrings[ci]);
                  }
                  else
                  {
                    featureCounts[oi]->put(contextStrings[ci], c);
                  }
                }
              }
              for (int oi = 0;oi < numOutcomes;oi++)
              {
                for (Map<std::string, float>::const_iterator feature = featureCounts[oi]->begin(); feature != featureCounts[oi]->end(); ++feature)
                {
                  int pi = pmap->get_Renamed(feature->first);
                  if (pi != -1)
                  {
                    //System.err.println(si+" "+outcomeLabels[oi]+" "+feature+" "+featureCounts[oi].get(feature));
                    params[pi]->updateParameter(oi, featureCounts[oi]->get(feature->first));
                    if (useAverage)
                    {
                      if (updates[pi][oi][VALUE] != 0)
                      {
                        averageParams[pi]->updateParameter(oi,updates[pi][oi][VALUE]*(numSequences*(iteration - updates[pi][oi][ITER]) + (si - updates[pi][oi][EVENT])));
                        //System.err.println("p avp["+pi+"]."+oi+"="+averageParams[pi].getParameters()[oi]);
                      }
                      //System.err.println("p updates["+pi+"]["+oi+"]=("+updates[pi][oi][ITER]+","+updates[pi][oi][EVENT]+","+updates[pi][oi][VALUE]+") + ("+iteration+","+oei+","+params[pi].getParameters()[oi]+") -> "+averageParams[pi].getParameters()[oi]);
                      updates[pi][oi][VALUE] = static_cast<int>(params[pi]->getParameters()[oi]);
                      updates[pi][oi][ITER] = iteration;
                      updates[pi][oi][EVENT] = si;
                    }
                  }
                }
              }
              model = new PerceptronModel(params,predLabels,pmap,outcomeLabels);
            }
            si++;
          }
          //finish average computation
          double totIterations = static_cast<double>(iterations)*si;
          if (useAverage && iteration == iterations - 1)
          {
            for (int pi = 0; pi < numPreds; pi++)
            {
//ORIGINAL LINE: double[] predParams = averageParams[pi].getParameters();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              double *predParams = averageParams[pi]->getParameters();
              for (int oi = 0;oi < numOutcomes;oi++)
              {
                if (updates[pi][oi][VALUE] != 0)
                {
                  predParams[oi] += updates[pi][oi][VALUE]*(numSequences*(iterations - updates[pi][oi][ITER]) - updates[pi][oi][EVENT]);
                }
                if (predParams[oi] != 0)
                {
                  predParams[oi] /= totIterations;
                  averageParams[pi]->setParameter(oi, predParams[oi]);
                  //System.err.println("updates["+pi+"]["+oi+"]=("+updates[pi][oi][ITER]+","+updates[pi][oi][EVENT]+","+updates[pi][oi][VALUE]+") + ("+iterations+","+0+","+params[pi].getParameters()[oi]+") -> "+averageParams[pi].getParameters()[oi]);
                }
              }
            }
          }
          display(". (" + numCorrect + "/" + numEvents + ") " + (static_cast<double>(numCorrect) / numEvents) + "\n");
        }

        void SimplePerceptronSequenceTrainer::trainingStats(MutableContext params[])
        {
          int numCorrect = 0;
          int oei = 0;
          for (SequenceStream::const_iterator sequence = sequenceStream->begin(); sequence != sequenceStream->end(); ++sequence)
          {
//ORIGINAL LINE: opennlp.model.Event[] taggerEvents = sequenceStream.updateContext(sequence, new PerceptronModel(params,predLabels,pmap,outcomeLabels));
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
            Event *taggerEvents = sequenceStream->updateContext(sequence, new PerceptronModel(params,predLabels,pmap,outcomeLabels));
            for (int ei = 0;ei < taggerEvents->length;ei++,oei++)
            {
              int max = omap->get(taggerEvents[ei]->getOutcome());
              if (max == outcomeList[oei])
              {
                numCorrect++;
              }
            }
          }
          display(". (" + numCorrect + "/" + numEvents + ") " + (static_cast<double>(numCorrect) / numEvents) + "\n");
        }

        void SimplePerceptronSequenceTrainer::InitializeInstanceFields()
        {
            printMessages = true;
            VALUE = 0;
            ITER = 1;
            EVENT = 2;
        }
    }
}
