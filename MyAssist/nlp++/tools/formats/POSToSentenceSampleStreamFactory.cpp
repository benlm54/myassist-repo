#include "POSToSentenceSampleStreamFactory.h"
#include "tools/cmdline/ArgumentParser.h"
#include "tools/postag/POSSample.h"
#include "tools/tokenize/Detokenizer.h"
#include "tools/tokenize/DetokenizationDictionary.h"
#include "tools/tokenize/DictionaryDetokenizer.h"
#include "tools/cmdline/TerminateToolException.h"
#include "tools/formats/POSToSentenceSampleStream.h"

namespace opennlp
{
    namespace tools
    {
        namespace formats
        {
            using opennlp::tools::cmdline::ArgumentParser;
            using opennlp::tools::cmdline::ObjectStreamFactory;
            using opennlp::tools::cmdline::TerminateToolException;
            using opennlp::tools::cmdline::params::DetokenizerParameter;
            using opennlp::tools::postag::POSSample;
            using opennlp::tools::sentdetect::SentenceSample;
            using opennlp::tools::tokenize::DetokenizationDictionary;
            using opennlp::tools::tokenize::Detokenizer;
            using opennlp::tools::tokenize::DictionaryDetokenizer;
            using opennlp::tools::util::ObjectStream;

            std::string POSToSentenceSampleStreamFactory::getUsage()
            {
              return ArgumentParser::createUsage(Parameters::typeid);
            }

            bool POSToSentenceSampleStreamFactory::validateArguments(std::string args[])
            {
              return ArgumentParser::validateArguments(args, Parameters::typeid);
            }

            opennlp::tools::util::ObjectStream<SentenceSample*> *POSToSentenceSampleStreamFactory::create(std::string args[])
            {
              Parameters *params = ArgumentParser::parse(args, Parameters::typeid);

              ObjectStream<POSSample*> *posSampleStream = (new WordTagSampleStreamFactory())->create(params);

              Detokenizer *detokenizer;
              try
              {
                detokenizer = new DictionaryDetokenizer(new DetokenizationDictionary(new FileInputStream(new File(params->getDetokenizer()))));
              }
              catch (IOException e)
              {
                System::err::println("Error while loading detokenizer dict: " + e->getMessage());
                throw TerminateToolException(-1);
              }

              return new POSToSentenceSampleStream(detokenizer, posSampleStream, 30);
            }
        }
    }
}
