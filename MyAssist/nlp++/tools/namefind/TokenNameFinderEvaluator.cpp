#include "TokenNameFinderEvaluator.h"
#include "tools/util/Span.h"
#include "tools/namefind/TokenNameFinderModel.h"
#include "tools/namefind/NameFinderME.h"
#include "tools/namefind/NameSampleDataStream.h"
#include "tools/util/PlainTextByLineStream.h"
#include "tools/cmdline/PerformanceMonitor.h"

namespace opennlp
{
    namespace tools
    {
        namespace namefind
        {
            using opennlp::tools::cmdline::PerformanceMonitor;
            using opennlp::tools::util::InvalidFormatException;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::PlainTextByLineStream;
            using opennlp::tools::util::Span;
            using opennlp::tools::util::eval::Evaluator;
            using opennlp::tools::util::eval::FMeasure;

            TokenNameFinderEvaluator::TokenNameFinderEvaluator(TokenNameFinder *nameFinder, ...) : opennlp.tools.util.eval.Evaluator<NameSample>(listeners)
            {
              InitializeInstanceFields();
              this->nameFinder = nameFinder;
            }

            opennlp::tools::namefind::NameSample *TokenNameFinderEvaluator::processSample(NameSample *reference)
            {

              if (reference->isClearAdaptiveDataSet())
              {
                nameFinder->clearAdaptiveData();
              }

//ORIGINAL LINE: opennlp.tools.util.Span predictedNames[] = nameFinder.find(reference.getSentence());
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              Span *predictedNames = nameFinder->find(reference->getSentence());
//ORIGINAL LINE: opennlp.tools.util.Span references[] = reference.getNames();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              Span *references = reference->getNames();

              fmeasure->updateScores(references, predictedNames);

              return new NameSample(reference->getSentence(), predictedNames, reference->isClearAdaptiveDataSet());
            }

            opennlp::tools::util::eval::FMeasure *TokenNameFinderEvaluator::getFMeasure()
            {
              return fmeasure;
            }

            void TokenNameFinderEvaluator::main(std::string args[]) throw(IOException, InvalidFormatException)
            {

              if (sizeof(args) / sizeof(args[0]) == 4)
              {

                std::cout << "Loading name finder model ..." << std::endl;
                InputStream *modelIn = new FileInputStream(args[3]);

                TokenNameFinderModel *model = new TokenNameFinderModel(modelIn);

                TokenNameFinder *nameFinder = new NameFinderME(model);

                std::cout << "Performing evaluation ..." << std::endl;
                TokenNameFinderEvaluator *evaluator = new TokenNameFinderEvaluator(nameFinder);

                NameSampleDataStream * const sampleStream = new NameSampleDataStream(new PlainTextByLineStream(new InputStreamReader(new FileInputStream(args[2]), args[1])));

                PerformanceMonitor * const monitor = new PerformanceMonitor("sent");

                monitor->startAndPrintThroughput();

                ObjectStream<NameSample*> *iterator = new ObjectStreamAnonymousInnerClassHelper();

                evaluator->evaluate(iterator);

                monitor->stopAndPrintFinalResult();

                std::cout << std::endl;
                std::cout << "F-Measure: " + evaluator->getFMeasure()->getFMeasure() << std::endl;
                std::cout << "Recall: " + evaluator->getFMeasure()->getRecallScore() << std::endl;
                std::cout << "Precision: " + evaluator->getFMeasure()->getPrecisionScore() << std::endl;
              }
              else
              {
                // usage: -encoding code test.file model.file
              }
            }

            opennlp::tools::namefind::NameSample *TokenNameFinderEvaluator::ObjectStreamAnonymousInnerClassHelper::read() throw(IOException)
            {
              monitor::incrementCounter();
              return sampleStream::read();
            }

            void TokenNameFinderEvaluator::ObjectStreamAnonymousInnerClassHelper::reset() throw(IOException)
            {
              sampleStream::reset();
            }

            void TokenNameFinderEvaluator::ObjectStreamAnonymousInnerClassHelper::close() throw(IOException)
            {
              sampleStream->close();
            }

            void TokenNameFinderEvaluator::InitializeInstanceFields()
            {
                fmeasure = new opennlp::tools::util::eval::FMeasure();
            }
        }
    }
}
