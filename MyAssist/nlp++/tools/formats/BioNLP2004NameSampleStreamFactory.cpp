#include "BioNLP2004NameSampleStreamFactory.h"
#include "tools/cmdline/ArgumentParser.h"
#include "tools/formats/BioNLP2004NameSampleStream.h"
#include "tools/cmdline/CmdLineUtil.h"

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
            using opennlp::tools::namefind::NameSample;
            using opennlp::tools::util::ObjectStream;

            std::string BioNLP2004NameSampleStreamFactory::getUsage()
            {
              return ArgumentParser::createUsage(Parameters::typeid);
            }

            bool BioNLP2004NameSampleStreamFactory::validateArguments(std::string args[])
            {
              return ArgumentParser::validateArguments(args, Parameters::typeid);
            }

            opennlp::tools::util::ObjectStream<NameSample*> *BioNLP2004NameSampleStreamFactory::create(std::string args[])
            {

              Parameters *params = ArgumentParser::parse(args, Parameters::typeid);
              int typesToGenerate = 0;

              if (params->getTypes().find("DNA") != string::npos)
              {
                typesToGenerate = typesToGenerate | BioNLP2004NameSampleStream::GENERATE_DNA_ENTITIES;
              }
              else if (params->getTypes().find("protein") != string::npos)
              {
                typesToGenerate = typesToGenerate | BioNLP2004NameSampleStream::GENERATE_PROTEIN_ENTITIES;
              }
              else if (params->getTypes().find("cell_type") != string::npos)
              {
                typesToGenerate = typesToGenerate | BioNLP2004NameSampleStream::GENERATE_CELLTYPE_ENTITIES;
              }
              else if (params->getTypes().find("cell_line") != string::npos)
              {
                typesToGenerate = typesToGenerate | BioNLP2004NameSampleStream::GENERATE_CELLLINE_ENTITIES;
              }
              else if (params->getTypes().find("RNA") != string::npos)
              {
                typesToGenerate = typesToGenerate | BioNLP2004NameSampleStream::GENERATE_RNA_ENTITIES;
              }

              return new BioNLP2004NameSampleStream(CmdLineUtil::openInFile(new File(params->getData())), typesToGenerate);
            }
        }
    }
}
