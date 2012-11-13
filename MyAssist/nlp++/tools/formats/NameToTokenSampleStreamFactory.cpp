#include "NameToTokenSampleStreamFactory.h"
#include "tools/cmdline/ArgumentParser.h"
#include "tools/namefind/NameSample.h"
#include "tools/tokenize/Detokenizer.h"
#include "tools/tokenize/DetokenizationDictionary.h"
#include "tools/tokenize/DictionaryDetokenizer.h"
#include "tools/cmdline/TerminateToolException.h"
#include "tools/formats/NameToTokenSampleStream.h"

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
            using opennlp::tools::namefind::NameSample;
            using opennlp::tools::tokenize::DetokenizationDictionary;
            using opennlp::tools::tokenize::Detokenizer;
            using opennlp::tools::tokenize::DictionaryDetokenizer;
            using opennlp::tools::tokenize::TokenSample;
            using opennlp::tools::util::ObjectStream;

            std::string NameToTokenSampleStreamFactory::getUsage()
            {
              return ArgumentParser::createUsage(Parameters::typeid);
            }

            bool NameToTokenSampleStreamFactory::validateArguments(std::string args[])
            {
              return ArgumentParser::validateArguments(args, Parameters::typeid);
            }

            opennlp::tools::util::ObjectStream<TokenSample*> *NameToTokenSampleStreamFactory::create(std::string args[])
            {
              Parameters *params = ArgumentParser::parse(args, Parameters::typeid);

              ObjectStream<NameSample*> *nameSampleStream = (new NameSampleStreamFactory())->create(params);

              // TODO: Move this to a factory method
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

              return new NameToTokenSampleStream(detokenizer, nameSampleStream);
            }
        }
    }
}
