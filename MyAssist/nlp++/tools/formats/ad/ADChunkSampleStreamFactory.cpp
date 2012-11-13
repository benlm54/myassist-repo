#include "ADChunkSampleStreamFactory.h"
#include "tools/cmdline/ArgumentParser.h"
#include "tools/cmdline/CmdLineUtil.h"
#include "tools/cmdline/TerminateToolException.h"
#include "tools/formats/ad/ADChunkSampleStream.h"

namespace opennlp
{
    namespace tools
    {
        namespace formats
        {
            namespace ad
            {
                using opennlp::tools::chunker::ChunkSample;
                using opennlp::tools::cmdline::ArgumentParser;
                using opennlp::tools::cmdline::ArgumentParser::OptionalParameter;
                using opennlp::tools::cmdline::ArgumentParser::ParameterDescription;
                using opennlp::tools::cmdline::CmdLineUtil;
                using opennlp::tools::cmdline::ObjectStreamFactory;
                using opennlp::tools::cmdline::TerminateToolException;
                using opennlp::tools::util::ObjectStream;

                std::string ADChunkSampleStreamFactory::getUsage()
                {
                  return ArgumentParser::createUsage(Parameters::typeid);
                }

                bool ADChunkSampleStreamFactory::validateArguments(std::string args[])
                {
                  return ArgumentParser::validateArguments(args, Parameters::typeid);
                }

                opennlp::tools::util::ObjectStream<ChunkSample*> *ADChunkSampleStreamFactory::create(std::string args[])
                {

                  Parameters *params = ArgumentParser::parse(args, Parameters::typeid);

                  Charset *encoding = CmdLineUtil::getEncodingParameter(args);

                  if (encoding == 0)
                  {
                    throw TerminateToolException(1);
                  }

                  ADChunkSampleStream *sampleStream = new ADChunkSampleStream(CmdLineUtil::openInFile(new File(params->getData())), encoding->name());

                  if (params->getStart() != 0 && params->getStart() > -1)
                  {
                    sampleStream->setStart(params->getStart());
                  }

                  if (params->getEnd() != 0 && params->getEnd() > -1)
                  {
                    sampleStream->setEnd(params->getEnd());
                  }

                  return sampleStream;
                }
            }
        }
    }
}
