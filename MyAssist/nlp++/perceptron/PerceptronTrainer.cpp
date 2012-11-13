#include "PerceptronTrainer.h"
#include "perceptron/PerceptronModel.h"

namespace opennlp
{
    namespace perceptron
    {
        using opennlp::model::AbstractModel;
        using opennlp::model::DataIndexer;
        using opennlp::model::EvalParameters;
        using opennlp::model::MutableContext;
const double PerceptronTrainer::TOLERANCE_DEFAULT = .00001;

        void PerceptronTrainer::setTolerance(double tolerance)
        {

          if (tolerance < 0)
            throw IllegalArgumentException("tolerance must be a positive number!");

          this->tolerance = tolerance;
        }

        void PerceptronTrainer::setStepSizeDecrease(double decrease)
        {

          if (decrease < 0 || decrease > 100)
            throw IllegalArgumentException("decrease must be between 0 and 100");

          stepSizeDecrease = decrease;
        }

        void PerceptronTrainer::setSkippedAveraging(bool averaging)
        {
          useSkippedlAveraging = averaging;
        }

        opennlp::model::AbstractModel *PerceptronTrainer::trainModel(int iterations, DataIndexer *di, int cutoff)
        {
          return trainModel(iterations,di,cutoff,true);
        }

        opennlp::model::AbstractModel *PerceptronTrainer::trainModel(int iterations, DataIndexer *di, int cutoff, bool useAverage)
        {
          display("Incorporating indexed data for training...  \n");
          contexts = di->getContexts();
          values = di->getValues();
          numTimesEventsSeen = di->getNumTimesEventsSeen();
          numEvents = di->getNumEvents();
          numUniqueEvents = contexts->length;

          outcomeLabels = di->getOutcomeLabels();
          outcomeList = di->getOutcomeList();

          predLabels = di->getPredLabels();
          numPreds = predLabels->length;
          numOutcomes = outcomeLabels->length;

          display("done.\n");

          display("\tNumber of Event Tokens: " + numUniqueEvents + "\n");
          display("\t    Number of Outcomes: " + numOutcomes + "\n");
          display("\t  Number of Predicates: " + numPreds + "\n");

          display("Computing model parameters...\n");

//ORIGINAL LINE: opennlp.model.MutableContext[] finalParameters = findParameters(iterations, useAverage);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          MutableContext *finalParameters = findParameters(iterations, useAverage);

          display("...done.\n");

          /// <summary>
          ///************* Create and return the model ***************** </summary>
          return new PerceptronModel(finalParameters, predLabels, outcomeLabels);
        }

        MutableContext *PerceptronTrainer::findParameters(int iterations, bool useAverage)
        {

          display("Performing " + iterations + " iterations.\n");

          int allOutcomesPattern[numOutcomes];
          for (int oi = 0; oi < numOutcomes; oi++)
            allOutcomesPattern[oi] = oi;

          /// <summary>
          /// Stores the estimated parameter value of each predicate during iteration. </summary>
          MutableContext params[numPreds];
          for (int pi = 0; pi < numPreds; pi++)
          {
            params[pi] = new MutableContext(allOutcomesPattern,new double[numOutcomes]);
            for (int aoi = 0;aoi < numOutcomes;aoi++)
              params[pi]->setParameter(aoi, 0.0);
          }

          EvalParameters *evalParams = new EvalParameters(params,numOutcomes);

          /// <summary>
          /// Stores the sum of parameter values of each predicate over many iterations. </summary>
          MutableContext summedParams[numPreds];
          if (useAverage)
          {
            for (int pi = 0; pi < numPreds; pi++)
            {
              summedParams[pi] = new MutableContext(allOutcomesPattern,new double[numOutcomes]);
              for (int aoi = 0;aoi < numOutcomes;aoi++)
                summedParams[pi]->setParameter(aoi, 0.0);
            }
          }

          // Keep track of the previous three accuracies. The difference of
          // the mean of these and the current training set accuracy is used
          // with tolerance to decide whether to stop.
          double prevAccuracy1 = 0.0;
          double prevAccuracy2 = 0.0;
          double prevAccuracy3 = 0.0;

          // A counter for the denominator for averaging.
          int numTimesSummed = 0;

          double stepsize = 1;
          for (int i = 1; i <= iterations; i++)
          {

            // Decrease the stepsize by a small amount.
            if (stepSizeDecrease != 0)
              stepsize *= 1 - stepSizeDecrease;

            displayIteration(i);

            int numCorrect = 0;

            for (int ei = 0; ei < numUniqueEvents; ei++)
            {
              int targetOutcome = outcomeList[ei];

              for (int ni = 0; ni < this->numTimesEventsSeen[ei]; ni++)
              {

                // Compute the model's prediction according to the current parameters.
                double modelDistribution[numOutcomes];
                if (values != 0)
                  PerceptronModel::eval(contexts[ei], values[ei], modelDistribution, evalParams, false);
                else
                  PerceptronModel::eval(contexts[ei], 0, modelDistribution, evalParams, false);

                int maxOutcome = maxIndex(modelDistribution);

                // If the predicted outcome is different from the target
                // outcome, do the standard update: boost the parameters
                // associated with the target and reduce those associated
                // with the incorrect predicted outcome.
                if (maxOutcome != targetOutcome)
                {
                  for (int ci = 0; ci < contexts[ei].length; ci++)
                  {
                    int pi = contexts[ei][ci];
                    if (values == 0)
                    {
                      params[pi]->updateParameter(targetOutcome, stepsize);
                      params[pi]->updateParameter(maxOutcome, -stepsize);
                    }
                    else
                    {
                      params[pi]->updateParameter(targetOutcome, stepsize*values[ei][ci]);
                      params[pi]->updateParameter(maxOutcome, -stepsize*values[ei][ci]);
                    }
                  }
                }

                // Update the counts for accuracy.
                if (maxOutcome == targetOutcome)
                  numCorrect++;
              }
            }

            // Calculate the training accuracy and display.
            double trainingAccuracy = static_cast<double>(numCorrect) / numEvents;
            if (i < 10 || (i % 10) == 0)
              display(". (" + numCorrect + "/" + numEvents + ") " + trainingAccuracy + "\n");

            // TODO: Make averaging configurable !!!

            bool doAveraging;

            if (useAverage && useSkippedlAveraging && (i < 20 || isPerfectSquare(i)))
            {
              doAveraging = true;
            }
            else if (useAverage)
            {
              doAveraging = true;
            }
            else
            {
              doAveraging = false;
            }

            if (doAveraging)
            {
              numTimesSummed++;
              for (int pi = 0; pi < numPreds; pi++)
                for (int aoi = 0;aoi < numOutcomes;aoi++)
                  summedParams[pi]->updateParameter(aoi, params[pi]->getParameters()[aoi]);
            }

            // If the tolerance is greater than the difference between the
            // current training accuracy and all of the previous three
            // training accuracies, stop training.
            if (abs(prevAccuracy1 - trainingAccuracy) < tolerance && abs(prevAccuracy2 - trainingAccuracy) < tolerance && abs(prevAccuracy3 - trainingAccuracy) < tolerance)
            {
              display("Stopping: change in training set accuracy less than " + tolerance + "\n");
              break;
            }

            // Update the previous training accuracies.
            prevAccuracy1 = prevAccuracy2;
            prevAccuracy2 = prevAccuracy3;
            prevAccuracy3 = trainingAccuracy;
          }

          // Output the final training stats.
          trainingStats(evalParams);

          // Create averaged parameters
          if (useAverage)
          {
            for (int pi = 0; pi < numPreds; pi++)
              for (int aoi = 0;aoi < numOutcomes;aoi++)
                summedParams[pi]->setParameter(aoi, summedParams[pi]->getParameters()[aoi] / numTimesSummed);

            return summedParams;

          }
          else
          {

            return params;

          }

        }

        double PerceptronTrainer::trainingStats(EvalParameters *evalParams)
        {
          int numCorrect = 0;

          for (int ei = 0; ei < numUniqueEvents; ei++)
          {
            for (int ni = 0;ni < this->numTimesEventsSeen[ei];ni++)
            {

              double modelDistribution[numOutcomes];

              if (values != 0)
                PerceptronModel::eval(contexts[ei], values[ei], modelDistribution, evalParams,false);
              else
                PerceptronModel::eval(contexts[ei], 0, modelDistribution, evalParams, false);

              int max = maxIndex(modelDistribution);
              if (max == outcomeList[ei])
                numCorrect++;
            }
          }
          double trainingAccuracy = static_cast<double>(numCorrect) / numEvents;
          display("Stats: (" + numCorrect + "/" + numEvents + ") " + trainingAccuracy + "\n");
          return trainingAccuracy;
        }

        int PerceptronTrainer::maxIndex(double values[])
        {
          int max = 0;
          for (int i = 1; i < sizeof(values) / sizeof(values[0]); i++)
            if (values[i] > values[max])
              max = i;
          return max;
        }

        void PerceptronTrainer::display(const std::string &s)
        {
          if (printMessages)
            std::cout << s;
        }

        void PerceptronTrainer::displayIteration(int i)
        {
          if (i > 10 && (i % 10) != 0)
            return;

          if (i < 10)
            display("  " + i + ":  ");
          else if (i < 100)
            display(" " + i + ":  ");
          else
            display(i + ":  ");
        }

        bool PerceptronTrainer::isPerfectSquare(int n)
        {
          int root = static_cast<int>(sqrt(n));
          return root*root == n;
        }

        void PerceptronTrainer::InitializeInstanceFields()
        {
            printMessages = true;
            tolerance = TOLERANCE_DEFAULT;
        }
    }
}
