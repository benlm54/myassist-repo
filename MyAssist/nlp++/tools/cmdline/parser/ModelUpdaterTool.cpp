#include "ModelUpdaterTool.h"
#include "tools/cmdline/ArgumentParser.h"
#include "tools/cmdline/CLI.h"
#include "tools/cmdline/TerminateToolException.h"
#include "tools/cmdline/parser/ParserModelLoader.h"
#include "tools/cmdline/parser/ParserTrainerTool.h"
#include "tools/cmdline/CmdLineUtil.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace parser
            {
                using opennlp::tools::cmdline::ArgumentParser;
                using opennlp::tools::cmdline::CLI;
                using opennlp::tools::cmdline::CmdLineTool;
                using opennlp::tools::cmdline::CmdLineUtil;
                using opennlp::tools::cmdline::TerminateToolException;
                using opennlp::tools::cmdline::params::TrainingToolParams;
                using opennlp::tools::parser::Parse;
                using opennlp::tools::parser::ParserModel;
                using opennlp::tools::util::ObjectStream;

                std::string ModelUpdaterTool::getHelp()
                {
                  return "Usage: " + CLI::CMD + " " + getName() + " " + ArgumentParser::createUsage(ModelUpdaterParams::typeid);
                }

                void ModelUpdaterTool::run(std::string args[])
                {

                  if (!ArgumentParser::validateArguments(args, ModelUpdaterParams::typeid))
                  {
                    System::err::println(getHelp());
                    throw TerminateToolException(1);
                  }

                  ModelUpdaterParams *params = ArgumentParser::parse(args, ModelUpdaterParams::typeid);

                  // Load model to be updated
                  File *modelFile = params->getModel();
                  ParserModel *originalParserModel = (new ParserModelLoader())->load(modelFile);

                  ObjectStream<Parse*> *parseSamples = ParserTrainerTool::openTrainingData(params->getData(), params->getEncoding());

                  ParserModel *updatedParserModel;
                  try
                  {
                    updatedParserModel = trainAndUpdate(originalParserModel, parseSamples, params);
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
                      parseSamples->close();
                    }
                    catch (IOException e)
                    {
                      // sorry that this can fail
                    }
                  }

                  CmdLineUtil::writeModel("parser", modelFile, updatedParserModel);
                }
            }
        }
    }
}
