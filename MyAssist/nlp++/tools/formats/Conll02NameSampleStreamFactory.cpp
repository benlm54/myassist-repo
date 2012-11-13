#include "Conll02NameSampleStreamFactory.h"
#include "tools/cmdline/ArgumentParser.h"
#include "tools/formats/Conll02NameSampleStream.h"
#include "tools/cmdline/TerminateToolException.h"
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
            using opennlp::tools::formats::Conll02NameSampleStream::LANGUAGE;
            using opennlp::tools::namefind::NameSample;
            using opennlp::tools::util::ObjectStream;

            std::string Conll02NameSampleStreamFactory::getUsage()
            {
              return ArgumentParser::createUsage(Parameters::typeid);
            }

            bool Conll02NameSampleStreamFactory::validateArguments(std::string args[])
            {
              return ArgumentParser::validateArguments(args, Parameters::typeid);
            }

            opennlp::tools::util::ObjectStream<NameSample*> *Conll02NameSampleStreamFactory::create(std::string args[])
            {

              Parameters *params = ArgumentParser::parse(args, Parameters::typeid);

              LANGUAGE lang;
              if ((std::string("nl")) == params->getLang())
              {
                lang = opennlp::tools::formats::Conll02NameSampleStream::NL;
              }
              else if ((std::string("es")) == params->getLang())
              {
                lang = opennlp::tools::formats::Conll02NameSampleStream::ES;
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


              return new Conll02NameSampleStream(lang, CmdLineUtil::openInFile(new File(params->getData())), typesToGenerate);
            }
        }
    }
}
