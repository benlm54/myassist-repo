#include "ADNameSampleStreamFactory.h"
#include "tools/cmdline/ArgumentParser.h"
#include "tools/cmdline/CmdLineUtil.h"
#include "tools/cmdline/TerminateToolException.h"
#include "tools/formats/ad/ADNameSampleStream.h"

namespace opennlp
{
    namespace tools
    {
        namespace formats
        {
            namespace ad
            {
                using opennlp::tools::cmdline::ArgumentParser;
                using opennlp::tools::cmdline::ArgumentParser::ParameterDescription;
                using opennlp::tools::cmdline::CmdLineUtil;
                using opennlp::tools::cmdline::ObjectStreamFactory;
                using opennlp::tools::cmdline::TerminateToolException;
                using opennlp::tools::namefind::NameSample;
                using opennlp::tools::util::ObjectStream;

                std::string ADNameSampleStreamFactory::getUsage()
                {
                  return ArgumentParser::createUsage(Parameters::typeid);
                }

                bool ADNameSampleStreamFactory::validateArguments(std::string args[])
                {
                  return ArgumentParser::validateArguments(args, Parameters::typeid);
                }

                opennlp::tools::util::ObjectStream<NameSample*> *ADNameSampleStreamFactory::create(std::string args[])
                {

                  Parameters *params = ArgumentParser::parse(args, Parameters::typeid);

                  Charset *encoding = CmdLineUtil::getEncodingParameter(args);

                  if (encoding == 0)
                  {
                    throw TerminateToolException(1);
                  }

                  return new ADNameSampleStream(CmdLineUtil::openInFile(new File(params->getData())), encoding->name());
                }
            }
        }
    }
}
