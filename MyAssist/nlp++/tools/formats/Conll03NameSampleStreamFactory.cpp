#include "Conll03NameSampleStreamFactory.h"
#include "tools/cmdline/ArgumentParser.h"
#include "tools/formats/Conll03NameSampleStream.h"
#include "tools/cmdline/TerminateToolException.h"
#include "tools/formats/Conll02NameSampleStream.h"
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
            using opennlp::tools::cmdline::TerminateToolException;
            using opennlp::tools::formats::Conll03NameSampleStream::LANGUAGE;
            using opennlp::tools::namefind::NameSample;
            using opennlp::tools::util::ObjectStream;

            std::string Conll03NameSampleStreamFactory::getUsage()
            {
              return ArgumentParser::createUsage(Parameters::typeid);
            }

            bool Conll03NameSampleStreamFactory::validateArguments(std::string args[])
            {
              return ArgumentParser::validateArguments(args, Parameters::typeid);
            }

            opennlp::tools::util::ObjectStream<NameSample*> *Conll03NameSampleStreamFactory::create(std::string args[])
            {

              Parameters *params = ArgumentParser::parse(args, Parameters::typeid);

              // todo: support the other languages with this CoNLL.
              LANGUAGE lang;
              if ((std::string("en")) == params->getLang())
              {
                lang = opennlp::tools::formats::Conll03NameSampleStream::EN;
              }
              else if ((std::string("de")) == params->getLang())
              {
                lang = opennlp::tools::formats::Conll03NameSampleStream::DE;
              }
              else
              {
                System::err::println("Unsupported language: " + params->getLang());
                throw TerminateToolException(-1);
              }

              int typesToGenerate = 0;

              if (params->getTypes().find("per") != string::npos)
              {
                typesToGenerate = typesToGenerate | Conll02NameSampleStream::GENERATE_PERSON_ENTITIES;
              }
              if (params->getTypes().find("org") != string::npos)
              {
                typesToGenerate = typesToGenerate | Conll02NameSampleStream::GENERATE_ORGANIZATION_ENTITIES;
              }
              if (params->getTypes().find("loc") != string::npos)
              {
                typesToGenerate = typesToGenerate | Conll02NameSampleStream::GENERATE_LOCATION_ENTITIES;
              }
              if (params->getTypes().find("misc") != string::npos)
              {
                typesToGenerate = typesToGenerate | Conll02NameSampleStream::GENERATE_MISC_ENTITIES;
              }


              return new Conll03NameSampleStream(lang, CmdLineUtil::openInFile(new File(params->getData())), typesToGenerate);
            }
        }
    }
}
