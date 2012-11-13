#include "LeipzigDocumentSampleStreamFactory.h"
#include "tools/cmdline/ArgumentParser.h"
#include "tools/cmdline/CmdLineUtil.h"
#include "tools/formats/LeipzigDoccatSampleStream.h"
#include "tools/cmdline/TerminateToolException.h"

namespace opennlp
{
    namespace tools
    {
        namespace formats
        {
            using opennlp::tools::cmdline::ArgumentParser;
            using opennlp::tools::cmdline::ArgumentParser::ParameterDescription;
            using opennlp::tools::cmdline::CmdLineUtil;
            using opennlp::tools::cmdline::ObjectStreamFactory;
            using opennlp::tools::cmdline::TerminateToolException;
            using opennlp::tools::doccat::DocumentSample;
            using opennlp::tools::util::ObjectStream;

            std::string LeipzigDocumentSampleStreamFactory::getUsage()
            {
              return ArgumentParser::createUsage(Parameters::typeid);
            }

            bool LeipzigDocumentSampleStreamFactory::validateArguments(std::string args[])
            {
              return ArgumentParser::validateArguments(args, Parameters::typeid);
            }

            opennlp::tools::util::ObjectStream<DocumentSample*> *LeipzigDocumentSampleStreamFactory::create(std::string args[])
            {

              Parameters *params = ArgumentParser::parse(args, Parameters::typeid);

              try
              {
                return new LeipzigDoccatSampleStream(params->getLang(), 20, CmdLineUtil::openInFile(new File(params->getData())));
              }
              catch (IOException e)
              {
                System::err::println("Cannot open sample data: " + e->getMessage());
                throw TerminateToolException(-1);
              }
            }
        }
    }
}
