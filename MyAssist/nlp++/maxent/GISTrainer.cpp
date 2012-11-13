#include "GISTrainer.h"
#include "model/OnePassDataIndexer.h"
#include "model/UniformPrior.h"
#include "synchronized.h"
#include "InterruptedException.h"

namespace opennlp
{
    namespace maxent
    {
        using opennlp::model::DataIndexer;
        using opennlp::model::EvalParameters;
        using opennlp::model::EventStream;
        using opennlp::model::MutableContext;
        using opennlp::model::OnePassDataIndexer;
        using opennlp::model::Prior;
        using opennlp::model::UniformPrior;

        GISTrainer::ModelExpactationComputeTask::ModelExpactationComputeTask(GISTrainer *outerInstance, int threadIndex, int startIndex, int length) : startIndex(startIndex), length(length), threadIndex(threadIndex), outerInstance(outerInstance)
        {
                    InitializeInstanceFields();
        }

        opennlp::maxent::GISTrainer::ModelExpactationComputeTask *GISTrainer::ModelExpactationComputeTask::call()
        {

          const double modelDistribution[outerInstance->numOutcomes];


          for (int ei = startIndex; ei < startIndex + length; ei++)
          {

            // TODO: check interruption status here, if interrupted set a poisoned flag and return

            if (outerInstance->values != 0)
            {
              outerInstance->prior->logPrior(modelDistribution, outerInstance->contexts[ei], outerInstance->values[ei]);
              GISModel::eval(outerInstance->contexts[ei], outerInstance->values[ei], modelDistribution, outerInstance->evalParams);
            }
            else
            {
              outerInstance->prior->logPrior(modelDistribution,outerInstance->contexts[ei]);
              GISModel::eval(outerInstance->contexts[ei], modelDistribution, outerInstance->evalParams);
            }
            for (int j = 0; j < outerInstance->contexts[ei]->length; j++)
            {
              int pi = outerInstance->contexts[ei][j];
              if (outerInstance->predicateCounts[pi] >= outerInstance->cutoff)
              {
//ORIGINAL LINE: int[] activeOutcomes = modelExpects[threadIndex][pi].getOutcomes();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                int *activeOutcomes = outerInstance->modelExpects[threadIndex][pi]->getOutcomes();
                for (int aoi = 0;aoi < activeOutcomes->length;aoi++)
                {
                  int oi = activeOutcomes[aoi];

                  // numTimesEventsSeen must also be thread safe
                  if (outerInstance->values != 0 && outerInstance->values[ei] != 0)
                  {
                    outerInstance->modelExpects[threadIndex][pi]->updateParameter(aoi,modelDistribution[oi] * outerInstance->values[ei][j] * outerInstance->numTimesEventsSeen[ei]);
                  }
                  else
                  {
                    outerInstance->modelExpects[threadIndex][pi]->updateParameter(aoi,modelDistribution[oi] * outerInstance->numTimesEventsSeen[ei]);
                  }
                }
              }
            }

            loglikelihood += log(modelDistribution[outerInstance->outcomeList[ei]]) * outerInstance->numTimesEventsSeen[ei];

            numEvents += outerInstance->numTimesEventsSeen[ei];
            if (outerInstance->printMessages)
            {
              int max = 0;
              for (int oi = 1; oi < outerInstance->numOutcomes; oi++)
              {
                if (modelDistribution[oi] > modelDistribution[max])
                {
                  max = oi;
                }
              }
              if (max == outerInstance->outcomeList[ei])
              {
                numCorrect += outerInstance->numTimesEventsSeen[ei];
              }
            }

          }

          return this;
        }

        int GISTrainer::ModelExpactationComputeTask::getNumEvents()
        {
          return numEvents;
        }

        int GISTrainer::ModelExpactationComputeTask::getNumCorrect()
        {
          return numCorrect;
        }

        double GISTrainer::ModelExpactationComputeTask::getLoglikelihood()
        {
          return loglikelihood;
        }

        void GISTrainer::ModelExpactationComputeTask::InitializeInstanceFields()
        {
            loglikelihood = 0;
            numEvents = 0;
            numCorrect = 0;
        }

const double GISTrainer::LLThreshold = 0.0001;

        GISTrainer::GISTrainer() : printMessages(false)
        {
          InitializeInstanceFields();
        }

        GISTrainer::GISTrainer(bool printMessages) : printMessages(printMessages)
        {
          InitializeInstanceFields();
        }

        void GISTrainer::setSmoothing(bool smooth)
        {
          useSimpleSmoothing = smooth;
        }

        void GISTrainer::setSmoothingObservation(double timesSeen)
        {
          _smoothingObservation = timesSeen;
        }

        void GISTrainer::setGaussianSigma(double sigmaValue)
        {
          useGaussianSmoothing = true;
          sigma = sigmaValue;
        }

        opennlp::maxent::GISModel *GISTrainer::trainModel(EventStream *eventStream, int iterations, int cutoff) throw(IOException)
        {
          return trainModel(iterations, new OnePassDataIndexer(eventStream,cutoff),cutoff);
        }

        opennlp::maxent::GISModel *GISTrainer::trainModel(int iterations, DataIndexer *di, int cutoff)
        {
          return trainModel(iterations,di,new UniformPrior(),cutoff,1);
        }

        opennlp::maxent::GISModel *GISTrainer::trainModel(int iterations, DataIndexer *di, Prior *modelPrior, int cutoff, int threads)
        {

          if (threads <= 0)
            throw IllegalArgumentException("threads must be at leat one or greater!");

          modelExpects = new MutableContext[threads][];

          /// <summary>
          ///************ Incorporate all of the needed info ***************** </summary>
          display("Incorporating indexed data for training...  \n");
          contexts = di->getContexts();
          values = di->getValues();
          this->cutoff = cutoff;
          predicateCounts = di->getPredCounts();
          numTimesEventsSeen = di->getNumTimesEventsSeen();
          numUniqueEvents = contexts->length;
          this->prior = modelPrior;
          //printTable(contexts);

          // determine the correction constant and its inverse
          double correctionConstant = 0;
          for (int ci = 0; ci < contexts->length; ci++)
          {
            if (values == 0 || values[ci] == 0)
            {
              if (contexts[ci].length > correctionConstant)
              {
                correctionConstant = contexts[ci].length;
              }
            }
            else
            {
              float cl = values[ci][0];
              for (int vi = 1;vi < values[ci].length;vi++)
              {
                cl += values[ci][vi];
              }

              if (cl > correctionConstant)
              {
                correctionConstant = cl;
              }
            }
          }
          display("done.\n");

          outcomeLabels = di->getOutcomeLabels();
          outcomeList = di->getOutcomeList();
          numOutcomes = outcomeLabels->length;

          predLabels = di->getPredLabels();
          prior->setLabels(outcomeLabels,predLabels);
          numPreds = predLabels->length;

          display("\tNumber of Event Tokens: " + numUniqueEvents + "\n");
          display("\t    Number of Outcomes: " + numOutcomes + "\n");
          display("\t  Number of Predicates: " + numPreds + "\n");

          // set up feature arrays
          float predCount[numPreds][numOutcomes];
          for (int ti = 0; ti < numUniqueEvents; ti++)
          {
            for (int j = 0; j < contexts[ti].length; j++)
            {
              if (values != 0 && values[ti] != 0)
              {
                predCount[contexts[ti][j]][outcomeList[ti]] += numTimesEventsSeen[ti]*values[ti][j];
              }
              else
              {
                predCount[contexts[ti][j]][outcomeList[ti]] += numTimesEventsSeen[ti];
              }
            }
          }

          //printTable(predCount);
//JAVA TO C++ CONVERTER WARNING: Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
          delete di; // don't need it anymore

          // A fake "observation" to cover features which are not detected in
          // the data.  The default is to assume that we observed "1/10th" of a
          // feature during training.
          const double smoothingObservation = _smoothingObservation;

          // Get the observed expectations of the features. Strictly speaking,
          // we should divide the counts by the number of Tokens, but because of
          // the way the model's expectations are approximated in the
          // implementation, this is cancelled out when we compute the next
          // iteration of a parameter, making the extra divisions wasteful.
          params = new MutableContext[numPreds];
          for (int i = 0; i < modelExpects->length; i++)
            modelExpects[i] = new MutableContext[numPreds];
          observedExpects = new MutableContext[numPreds];

          // The model does need the correction constant and the correction feature. The correction constant
          // is only needed during training, and the correction feature is not necessary.
          // For compatibility reasons the model contains form now on a correction constant of 1, 
          // and a correction param 0.
          evalParams = new EvalParameters(params,0,1,numOutcomes);
          int activeOutcomes[numOutcomes];
//ORIGINAL LINE: int[] outcomePattern;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          int *outcomePattern;
          int allOutcomesPattern[numOutcomes];
          for (int oi = 0; oi < numOutcomes; oi++)
          {
            allOutcomesPattern[oi] = oi;
          }
          int numActiveOutcomes = 0;
          for (int pi = 0; pi < numPreds; pi++)
          {
            numActiveOutcomes = 0;
            if (useSimpleSmoothing)
            {
              numActiveOutcomes = numOutcomes;
              outcomePattern = allOutcomesPattern;
            }
            else //determine active outcomes
            {
              for (int oi = 0; oi < numOutcomes; oi++)
              {
                if (predCount[pi][oi] > 0 && predicateCounts[pi] >= cutoff)
                {
                  activeOutcomes[numActiveOutcomes] = oi;
                  numActiveOutcomes++;
                }
              }
              if (numActiveOutcomes == numOutcomes)
              {
                outcomePattern = allOutcomesPattern;
              }
              else
              {
                outcomePattern = new int[numActiveOutcomes];
                for (int aoi = 0;aoi < numActiveOutcomes;aoi++)
                {
                  outcomePattern[aoi] = activeOutcomes[aoi];
                }
              }
            }
            params[pi] = new MutableContext(outcomePattern,new double[numActiveOutcomes]);
            for (int i = 0; i < modelExpects->length; i++)
              modelExpects[i][pi] = new MutableContext(outcomePattern,new double[numActiveOutcomes]);
            observedExpects[pi] = new MutableContext(outcomePattern,new double[numActiveOutcomes]);
            for (int aoi = 0;aoi < numActiveOutcomes;aoi++)
            {
              int oi = outcomePattern[aoi];
              params[pi]->setParameter(aoi, 0.0);
              for (int i = 0; i < modelExpects->length; i++)
                modelExpects[i][pi]->setParameter(aoi, 0.0);
              if (predCount[pi][oi] > 0)
              {
                  observedExpects[pi]->setParameter(aoi, predCount[pi][oi]);
              }
              else if (useSimpleSmoothing)
              {
                observedExpects[pi]->setParameter(aoi,smoothingObservation);
              }
            }
          }

          predCount = 0; // don't need it anymore

          display("...done.\n");

          /// <summary>
          ///*************** Find the parameters *********************** </summary>
          if (threads == 1)
            display("Computing model parameters ...\n");
          else
            display("Computing model parameters in " + threads + " threads...\n");

          findParameters(iterations, correctionConstant);

          /// <summary>
          ///************* Create and return the model ***************** </summary>
          // To be compatible with old models the correction constant is always 1
          return new GISModel(params, predLabels, outcomeLabels, 1, evalParams->getCorrectionParam());

        }

        void GISTrainer::findParameters(int iterations, double correctionConstant)
        {
          double prevLL = 0.0;
          double currLL = 0.0;
          display("Performing " + iterations + " iterations.\n");
          for (int i = 1; i <= iterations; i++)
          {
            if (i < 10)
              display("  " + i + ":  ");
            else if (i < 100)
              display(" " + i + ":  ");
            else
              display(i + ":  ");
            currLL = nextIteration(correctionConstant);
            if (i > 1)
            {
              if (prevLL > currLL)
              {
                System::err::println("Model Diverging: loglikelihood decreased");
                break;
              }
              if (currLL - prevLL < LLThreshold)
              {
                break;
              }
            }
            prevLL = currLL;
          }

          // kill a bunch of these big objects now that we don't need them
//JAVA TO C++ CONVERTER WARNING: Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
          delete[] observedExpects;
//JAVA TO C++ CONVERTER WARNING: Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
          delete[] modelExpects;
//JAVA TO C++ CONVERTER WARNING: Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
          delete[] numTimesEventsSeen;
//JAVA TO C++ CONVERTER WARNING: Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
          delete[] contexts;
        }

        double GISTrainer::gaussianUpdate(int predicate, int oid, int n, double correctionConstant)
        {
          double param = params[predicate]->getParameters()[oid];
          double x0 = 0.0;
          double modelValue = modelExpects[0][predicate]->getParameters()[oid];
          double observedValue = observedExpects[predicate]->getParameters()[oid];
          for (int i = 0; i < 50; i++)
          {
            double tmp = modelValue * exp(correctionConstant * x0);
            double f = tmp + (param + x0) / sigma - observedValue;
            double fp = tmp * correctionConstant + 1 / sigma;
            if (fp == 0)
            {
              break;
            }
            double x = x0 - f / fp;
            if (abs(x - x0) < 0.000001)
            {
              x0 = x;
              break;
            }
            x0 = x;
          }
          return x0;
        }

        double GISTrainer::nextIteration(double correctionConstant)
        {
          // compute contribution of p(a|b_i) for each feature and the new
          // correction parameter
          double loglikelihood = 0.0;
          int numEvents = 0;
          int numCorrect = 0;

          int numberOfThreads = modelExpects->length;

          ExecutorService *executor = Executors::newFixedThreadPool(numberOfThreads);

          int taskSize = numUniqueEvents / numberOfThreads;

          int leftOver = numUniqueEvents % numberOfThreads;

//JAVA TO C++ CONVERTER TODO TASK: Java wildcard generics are not converted to C++:
//ORIGINAL LINE: java.util.List<java.util.concurrent.Future<?>> futures = new java.util.ArrayList<java.util.concurrent.Future<?>>();
          std::vector<Future<?>> futures = std::vector<Future<?>>();

          for (int i = 0; i < numberOfThreads; i++)
          {
            if (i != numberOfThreads - 1)
              futures.push_back(executor->submit(new ModelExpactationComputeTask(this, i, i*taskSize, taskSize)));
            else
              futures.push_back(executor->submit(new ModelExpactationComputeTask(this, i, i*taskSize, taskSize + leftOver)));
          }

//JAVA TO C++ CONVERTER TODO TASK: Java wildcard generics are not converted to C++:
//ORIGINAL LINE: for (java.util.concurrent.Future<?> future : futures)
          for (std::vector<Future<?>>::const_iterator future = futures.begin(); future != futures.end(); ++future)
          {
            ModelExpactationComputeTask *finishedTask = 0;
            try
            {
              finishedTask = static_cast<ModelExpactationComputeTask*>((*future)->)get();
            }
            catch (InterruptedException e)
            {
              // TODO: We got interrupted, but that is currently not really supported!
              // For now we just print the exception and fail hard. We hopefully soon
              // handle this case properly!
              e->printStackTrace();
              throw IllegalStateException("Interruption is not supported!", e);
            }
            catch (ExecutionException e)
            {
              // Only runtime exception can be thrown during training, if one was thrown
              // it should be re-thrown. That could for example be a NullPointerException
              // which is caused through a bug in our implementation.
              throw std::exception(e->getCause());
            }

            // When they are done, retrieve the results ...
            numEvents += finishedTask->getNumEvents();
            numCorrect += finishedTask->getNumCorrect();
            loglikelihood += finishedTask->getLoglikelihood();
          }

          executor->shutdown();

          display(".");

          // merge the results of the two computations
          for (int pi = 0; pi < numPreds; pi++)
          {
//ORIGINAL LINE: int[] activeOutcomes = params[pi].getOutcomes();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
            int *activeOutcomes = params[pi]->getOutcomes();

            for (int aoi = 0;aoi < activeOutcomes->length;aoi++)
            {
              for (int i = 1; i < modelExpects->length; i++)
              {
                modelExpects[0][pi]->updateParameter(aoi, modelExpects[i][pi]->getParameters()[aoi]);
              }
            }
          }

          display(".");

          // compute the new parameter values
          for (int pi = 0; pi < numPreds; pi++)
          {
//ORIGINAL LINE: double[] observed = observedExpects[pi].getParameters();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
            double *observed = observedExpects[pi]->getParameters();
//ORIGINAL LINE: double[] model = modelExpects[0][pi].getParameters();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
            double *model = modelExpects[0][pi]->getParameters();
//ORIGINAL LINE: int[] activeOutcomes = params[pi].getOutcomes();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
            int *activeOutcomes = params[pi]->getOutcomes();
            for (int aoi = 0;aoi < activeOutcomes->length;aoi++)
            {
              if (useGaussianSmoothing)
              {
                params[pi]->updateParameter(aoi,gaussianUpdate(pi,aoi,numEvents,correctionConstant));
              }
              else
              {
                if (model[aoi] == 0)
                {
                  System::err::println("Model expects == 0 for " + predLabels[pi] + " " + outcomeLabels[aoi]);
                }
                //params[pi].updateParameter(aoi,(Math.log(observed[aoi]) - Math.log(model[aoi])));
                params[pi]->updateParameter(aoi,((log(observed[aoi]) - log(model[aoi])) / correctionConstant));
              }

              for (int i = 0; i < modelExpects->length; i++)
                modelExpects[i][pi]->setParameter(aoi,0.0); // re-initialize to 0.0's

            }
          }

          display(". loglikelihood=" + loglikelihood + "\t" + (static_cast<double>(numCorrect) / numEvents) + "\n");

          return loglikelihood;
        }

        void GISTrainer::display(const std::string &s)
        {
          if (printMessages)
            std::cout << s;
        }

        void GISTrainer::InitializeInstanceFields()
        {
            useSimpleSmoothing = false;
            useGaussianSmoothing = false;
            sigma = 2.0;
            _smoothingObservation = 0.1;
        }
    }
}
