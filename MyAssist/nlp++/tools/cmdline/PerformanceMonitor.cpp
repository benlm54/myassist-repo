#include "PerformanceMonitor.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {

            PerformanceMonitor::PerformanceMonitor(PrintStream *out, const std::string &unit) : unit(unit), out(out)
            {
              InitializeInstanceFields();
            }

            PerformanceMonitor::PerformanceMonitor(const std::string &unit)
            {
              InitializeInstanceFields();
            }

            bool PerformanceMonitor::isStarted()
            {
              return startTime != -1;
            }

            void PerformanceMonitor::incrementCounter(int increment)
            {

              if (!isStarted())
                throw IllegalStateException("Must be started first!");

              if (increment < 0)
                throw IllegalArgumentException("increment must be zero or positive!");

              counter += increment;
            }

            void PerformanceMonitor::incrementCounter()
            {
              incrementCounter(1);
            }

            void PerformanceMonitor::start()
            {

              if (isStarted())
                throw IllegalStateException("Already started!");

              startTime = System::currentTimeMillis();
            }

            void PerformanceMonitor::startAndPrintThroughput()
            {

              start();

              Runnable * const beeper = new RunnableAnonymousInnerClassHelper();

             beeperHandle = scheduler->scheduleAtFixedRate(beeper, 1, 1, TimeUnit::SECONDS);
            }

            void PerformanceMonitor::RunnableAnonymousInnerClassHelper::run()
            {

              int deltaCount = outerInstance->counter - lastCount;

              long long timePassedSinceLastCount = System::currentTimeMillis() - lastTimeStamp;

              double currentThroughput;

              if (timePassedSinceLastCount > 0)
              {
                currentThroughput = deltaCount / (static_cast<double>(timePassedSinceLastCount) / 1000);
              }
              else
              {
                currentThroughput = 0;
              }

              long long totalTimePassed = System::currentTimeMillis() - outerInstance->startTime;

              double averageThroughput;
              if (totalTimePassed > 0)
              {
                averageThroughput = outerInstance->counter / ((static_cast<double>(totalTimePassed)) / 1000);
              }
              else
              {
                averageThroughput = 0;
              }

              outerInstance->out->printf("current: %.1f " + outerInstance->unit + "/s avg: %.1f " + outerInstance->unit + "/s total: %d " + outerInstance->unit + "%n", currentThroughput, averageThroughput, outerInstance->counter);

              lastTimeStamp = System::currentTimeMillis();
              lastCount = outerInstance->counter;
            }

            void PerformanceMonitor::stopAndPrintFinalResult()
            {

              if (!isStarted())
                throw IllegalStateException("Must be started first!");

              if (beeperHandle != 0)
              {
                // yeah we have time to finish current
                // printing if there is one
                beeperHandle->cancel(false);
              }

              scheduler->shutdown();

              long long timePassed = System::currentTimeMillis() - startTime;

              double average;
              if (timePassed > 0)
              {
                average = counter / (timePassed / 1000);
              }
              else
              {
                average = 0;
              }

              out->println();
              out->println();

              out->printf("Average: %.1f " + unit + "/s %n", average);
              out->println("Total: " + counter + " " + unit);
              out->println("Runtime: " + timePassed / 1000 + "s");
            }

            void PerformanceMonitor::InitializeInstanceFields()
            {
                scheduler = java::util::concurrent::Executors::newScheduledThreadPool(1);
                startTime = -1;
            }
        }
    }
}
