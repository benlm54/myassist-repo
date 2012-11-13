#include "ChunkerTrainerTool.h"
#include "tools/cmdline/ArgumentParser.h"
#include "tools/cmdline/CLI.h"
#include "tools/cmdline/CmdLineUtil.h"
#include "tools/util/PlainTextByLineStream.h"
#include "tools/chunker/ChunkSampleStream.h"
#include "tools/cmdline/TerminateToolException.h"
#include "tools/util/TrainingParameters.h"
#include "tools/chunker/ChunkerModel.h"
#include "tools/chunker/ChunkerME.h"
#include "tools/chunker/DefaultChunkerContextGenerator.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace chunker
            {
                using opennlp::tools::chunker::ChunkSample;
                using opennlp::tools::chunker::ChunkSampleStream;
                using opennlp::tools::chunker::ChunkerME;
                using opennlp::tools::chunker::ChunkerModel;
                using opennlp::tools::chunker::DefaultChunkerContextGenerator;
                using opennlp::tools::cmdline::ArgumentParser;
                using opennlp::tools::cmdline::CLI;
                using opennlp::tools::cmdline::CmdLineTool;
                using opennlp::tools::cmdline::CmdLineUtil;
                using opennlp::tools::cmdline::TerminateToolException;
                using opennlp::tools::cmdline::params::TrainingToolParams;
                using opennlp::tools::util::ObjectStream;
                using opennlp::tools::util::PlainTextByLineStream;

                std::string ChunkerTrainerTool::getName()
                {
                  return "ChunkerTrainerME";
                }

                std::string ChunkerTrainerTool::getShortDescription()
                {
                  return "trainer for the learnable chunker";
                }

                std::string ChunkerTrainerTool::getHelp()
                {
                  return "Usage: " + CLI::CMD + " " + getName() + " " + ArgumentParser::createUsage(TrainerToolParams::typeid);
                }

                opennlp::tools::util::ObjectStream<ChunkSample*> *ChunkerTrainerTool::openSampleData(const std::string &sampleDataName, File *sampleDataFile, Charset *encoding)
                {
                  CmdLineUtil::checkInputFile(sampleDataName + " Data", sampleDataFile);

                  FileInputStream *sampleDataIn = CmdLineUtil::openInFile(sampleDataFile);

                  ObjectStream<std::string> *lineStream = new PlainTextByLineStream(sampleDataIn->getChannel(), encoding);

                  return new ChunkSampleStream(lineStream);
                }

                void ChunkerTrainerTool::run(std::string args[])
                {

                  if (!ArgumentParser::validateArguments(args, TrainerToolParams::typeid))
                  {
                    System::err::println(getHelp());
                    throw TerminateToolException(1);
                  }

                  TrainerToolParams *params = ArgumentParser::parse(args, TrainerToolParams::typeid);

                  opennlp::tools::util::TrainingParameters *mlParams = CmdLineUtil::loadTrainingParameters(params->getParams(), false);

                  File *trainingDataInFile = params->getData();
                  File *modelOutFile = params->getModel();

                  CmdLineUtil::checkOutputFile("sentence detector model", modelOutFile);
                  ObjectStream<ChunkSample*> *sampleStream = openSampleData("Training", trainingDataInFile, params->getEncoding());

                  ChunkerModel *model;
                  try
                  {
                    if (mlParams == 0)
                    {
                      model = ChunkerME::train(params->getLang(), sampleStream, params->getCutoff(), params->getIterations());
                    }
                    else
                    {
                      model = ChunkerME::train(params->getLang(), sampleStream, new DefaultChunkerContextGenerator(), mlParams);
                    }
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
                      // sorry that this can fail
                    }
                  }

                  CmdLineUtil::writeModel("chunker", modelOutFile, model);
                }
            }
        }
    }
}
