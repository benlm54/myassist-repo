#include "DictionaryBuilderTool.h"
#include "tools/cmdline/ArgumentParser.h"
#include "tools/cmdline/CLI.h"
#include "tools/cmdline/TerminateToolException.h"
#include "tools/cmdline/CmdLineUtil.h"
#include "tools/dictionary/Dictionary.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace dictionary
            {
                using opennlp::tools::cmdline::ArgumentParser;
                using opennlp::tools::cmdline::CLI;
                using opennlp::tools::cmdline::CmdLineTool;
                using opennlp::tools::cmdline::CmdLineUtil;
                using opennlp::tools::cmdline::TerminateToolException;
                using opennlp::tools::dictionary::Dictionary;

                std::string DictionaryBuilderTool::getName()
                {
                  return "DictionaryBuilder";
                }

                std::string DictionaryBuilderTool::getShortDescription()
                {
                  return "builds a new dictionary";
                }

                std::string DictionaryBuilderTool::getHelp()
                {
                  return "Usage: " + CLI::CMD + " " + getName() + " " + ArgumentParser::createUsage(Params::typeid);

                }

                void DictionaryBuilderTool::run(std::string args[])
                {
                  if (!ArgumentParser::validateArguments(args, Params::typeid))
                  {
                    System::err::println(getHelp());
                    throw TerminateToolException(1);
                  }

                  Params *params = ArgumentParser::parse(args, Params::typeid);

                  File *dictInFile = params->getInputFile();
                  File *dictOutFile = params->getOutputFile();
                  Charset *encoding = params->getEncoding();

                  CmdLineUtil::checkInputFile("dictionary input file", dictInFile);
                  CmdLineUtil::checkOutputFile("dictionary output file", dictOutFile);

                  InputStreamReader *in_Renamed = 0;
                  OutputStream *out = 0;
                  try
                  {
                    in_Renamed = new InputStreamReader(new FileInputStream(dictInFile), encoding);
                    out = new FileOutputStream(dictOutFile);

                    Dictionary *dict = Dictionary::parseOneEntryPerLine(in_Renamed);
                    dict->serialize(out);

                  }
                  catch (IOException e)
                  {
                    CmdLineUtil::printTrainingIoError(e);
                    throw TerminateToolException(-1);
                  }
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
                  finally
                  {
                    try
                    {
                      in_Renamed->close();
                      out->close();
                    }
                    catch (IOException e)
                    {
                      // sorry that this can fail
                    }
                  }

                }
            }
        }
    }
}
