#include "ConllXTokenSampleStreamFactory.h"
#include "tools/cmdline/ArgumentParser.h"
#include "tools/postag/POSSample.h"
#include "tools/tokenize/Detokenizer.h"
#include "tools/tokenize/DetokenizationDictionary.h"
#include "tools/tokenize/DictionaryDetokenizer.h"
#include "tools/cmdline/TerminateToolException.h"
#include "tools/formats/POSToTokenSampleStream.h"

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
            using opennlp::tools::tokenize::DetokenizationDictionary;
            using opennlp::tools::tokenize::Detokenizer;
            using opennlp::tools::tokenize::DictionaryDetokenizer;
            using opennlp::tools::tokenize::TokenSample;
            using opennlp::tools::util::ObjectStream;

            std::string ConllXTokenSampleStreamFactory::getUsage()
            {
              return ArgumentParser::createUsage(Parameters::typeid);
            }

            bool ConllXTokenSampleStreamFactory::validateArguments(std::string args[])
            {
              return ArgumentParser::validateArguments(args, Parameters::typeid);
            }

            opennlp::tools::util::ObjectStream<TokenSample*> *ConllXTokenSampleStreamFactory::create(std::string args[])
            {

              Parameters *params = ArgumentParser::parse(args, Parameters::typeid);

              ObjectStream<POSSample*> *samples = (new ConllXPOSSampleStreamFactory())->create(params);

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

              return new POSToTokenSampleStream(detokenizer,samples);
            }
        }
    }
}
