#include "ConllXPOSSampleStreamFactory.h"
#include "tools/cmdline/ArgumentParser.h"
#include "tools/cmdline/CmdLineUtil.h"
#include "tools/util/PlainTextByLineStream.h"
#include "tools/formats/ConllXPOSSampleStream.h"
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
            using opennlp::tools::postag::POSSample;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::PlainTextByLineStream;

            std::string ConllXPOSSampleStreamFactory::getUsage()
            {
              return ArgumentParser::createUsage(Parameters::typeid);
            }

            bool ConllXPOSSampleStreamFactory::validateArguments(std::string args[])
            {
              return ArgumentParser::validateArguments(args, Parameters::typeid);
            }

            opennlp::tools::util::ObjectStream<POSSample*> *ConllXPOSSampleStreamFactory::create(Parameters *params)
            {
              ObjectStream<std::string> *lineStream;
              try
              {
                lineStream = new PlainTextByLineStream(new InputStreamReader(CmdLineUtil::openInFile(new File(params->getData())), params->getEncoding()));

                return new ConllXPOSSampleStream(lineStream);
              }
              catch (UnsupportedEncodingException e)
              {
                System::err::println("Encoding not supported: " + params->getEncoding());
                throw TerminateToolException(-1);
              }
            }

            opennlp::tools::util::ObjectStream<POSSample*> *ConllXPOSSampleStreamFactory::create(std::string args[])
            {

              Parameters *params = ArgumentParser::parse(args, Parameters::typeid);

              return create(params);
            }
        }
    }
}
