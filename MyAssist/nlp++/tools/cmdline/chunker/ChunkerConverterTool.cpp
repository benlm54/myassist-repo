#include "ChunkerConverterTool.h"
#include "tools/formats/ad/ADChunkSampleStreamFactory.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace chunker
            {
                using opennlp::tools::chunker::ChunkSample;
                using opennlp::tools::cmdline::AbstractConverterTool;
                using opennlp::tools::cmdline::ObjectStreamFactory;
                using opennlp::tools::formats::ad::ADChunkSampleStreamFactory;
java::util::Map<std::string, opennlp::tools::cmdline::ObjectStreamFactory<opennlp::tools::chunker::ChunkSample*>*> *const ChunkerConverterTool::streamFactories = 0;

                ChunkerConverterTool::ChunkerConverterTool()
                {
                  Map<std::string, ObjectStreamFactory<ChunkSample*>*> *mutableStreamFactories = std::map<std::string, ObjectStreamFactory<ChunkSample*>*>();

                  mutableStreamFactories->put("ad", new ADChunkSampleStreamFactory());

                  streamFactories = Collections::unmodifiableMap(mutableStreamFactories);
                }

                std::string ChunkerConverterTool::getName()
                {
                  return "ChunkerConverter";
                }

                std::string ChunkerConverterTool::getShortDescription()
                {
                  return "converts foreign data formats to native format";
                }

                opennlp::tools::cmdline::ObjectStreamFactory<ChunkSample*> *ChunkerConverterTool::createStreamFactory(const std::string &format)
                {
                  return streamFactories->get(format);
                }
            }
        }
    }
}
