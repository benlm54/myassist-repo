#include "CensusDictionaryCreatorTool.h"
#include "tools/cmdline/ArgumentParser.h"
#include "tools/cmdline/CLI.h"
#include "tools/cmdline/TerminateToolException.h"
#include "tools/cmdline/CmdLineUtil.h"
#include "tools/formats/NameFinderCensus90NameStream.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace namefind
            {
                using opennlp::tools::cmdline::ArgumentParser;
                using opennlp::tools::cmdline::ArgumentParser::OptionalParameter;
                using opennlp::tools::cmdline::ArgumentParser::ParameterDescription;
                using opennlp::tools::cmdline::CLI;
                using opennlp::tools::cmdline::CmdLineTool;
                using opennlp::tools::cmdline::CmdLineUtil;
                using opennlp::tools::cmdline::TerminateToolException;
                using opennlp::tools::dictionary::Dictionary;
                using opennlp::tools::formats::NameFinderCensus90NameStream;
                using opennlp::tools::util::ObjectStream;
                using opennlp::tools::util::StringList;

                std::string CensusDictionaryCreatorTool::getName()
                {

                  return "CensusDictionaryCreator";
                }

                std::string CensusDictionaryCreatorTool::getShortDescription()
                {

                  return "Converts 1990 US Census names into a dictionary";
                }

                std::string CensusDictionaryCreatorTool::getHelp()
                {

                  return "Usage: " + CLI::CMD + " " + getName() + " " + ArgumentParser::createUsage(Parameters::typeid);
                }

                opennlp::tools::dictionary::Dictionary *CensusDictionaryCreatorTool::createDictionary(ObjectStream<StringList*> *sampleStream) throw(IOException)
                {

                  Dictionary *mNameDictionary = new Dictionary(true);
                  StringList *entry;

                  entry = sampleStream->read();
                  while (entry != 0)
                  {
                    if (!mNameDictionary->contains(entry))
                    {
                      mNameDictionary->put(entry);
                    }
                    entry = sampleStream->read();
                  }

                  return mNameDictionary;
                }

                void CensusDictionaryCreatorTool::run(std::string args[])
                {

                  if (!ArgumentParser::validateArguments(args, Parameters::typeid))
                  {
                    System::err::println(getHelp());
                    throw TerminateToolException(1);
                  }

                  Parameters *params = ArgumentParser::parse(args, Parameters::typeid);

                  File *testData = new File(params->getCensusData());
                  File *dictOutFile = new File(params->getDict());

                  CmdLineUtil::checkInputFile("Name data", testData);
                  CmdLineUtil::checkOutputFile("Dictionary file", dictOutFile);

                  FileInputStream *sampleDataIn = CmdLineUtil::openInFile(testData);
                  ObjectStream<StringList*> *sampleStream = new NameFinderCensus90NameStream(sampleDataIn, Charset::forName(params->getEncoding()));

                  Dictionary *mDictionary;
                  try
                  {
                    std::cout << "Creating Dictionary..." << std::endl;
                    mDictionary = createDictionary(sampleStream);
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
                      sampleStream->close();
                    }
                    catch (IOException e)
                    {
                      // sorry this can fail..
                    }
                  }

                  std::cout << "Saving Dictionary..." << std::endl;

                  OutputStream *out = 0;

                  try
                  {
                    out = new FileOutputStream(dictOutFile);
                    mDictionary->serialize(out);
                  }
                  catch (IOException ex)
                  {
                    System::err::println("Error during write to dictionary file: " + ex->getMessage());
                    throw TerminateToolException(-1);
                  }
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
                  finally
                  {
                    if (out != 0)
                      try
                      {
                        out->close();
                      }
                      catch (IOException e)
                      {
                        // file might be damaged
                        System::err::println("Attention: Failed to correctly write dictionary:");
                        System::err::println(e->getMessage());
                        throw TerminateToolException(-1);
                      }
                  }
                }
            }
        }
    }
}
