#include "DoccatTrainerTool.h"
#include "tools/cmdline/ArgumentParser.h"
#include "tools/cmdline/CLI.h"
#include "tools/cmdline/CmdLineUtil.h"
#include "tools/util/PlainTextByLineStream.h"
#include "tools/doccat/DocumentSampleStream.h"
#include "tools/cmdline/TerminateToolException.h"
#include "tools/util/TrainingParameters.h"
#include "tools/doccat/DoccatModel.h"
#include "tools/doccat/DocumentCategorizerME.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace doccat
            {
                using opennlp::tools::cmdline::ArgumentParser;
                using opennlp::tools::cmdline::CLI;
                using opennlp::tools::cmdline::CmdLineTool;
                using opennlp::tools::cmdline::CmdLineUtil;
                using opennlp::tools::cmdline::TerminateToolException;
                using opennlp::tools::cmdline::params::TrainingToolParams;
                using opennlp::tools::doccat::DoccatModel;
                using opennlp::tools::doccat::DocumentCategorizerME;
                using opennlp::tools::doccat::DocumentSample;
                using opennlp::tools::doccat::DocumentSampleStream;
                using opennlp::tools::util::ObjectStream;
                using opennlp::tools::util::PlainTextByLineStream;

                std::string DoccatTrainerTool::getName()
                {
                  return "DoccatTrainer";
                }

                std::string DoccatTrainerTool::getShortDescription()
                {
                  return "trainer for the learnable document categorizer";
                }

                std::string DoccatTrainerTool::getHelp()
                {
                  return "Usage: " + CLI::CMD + " " + getName() + " " + ArgumentParser::createUsage(TrainerToolParams::typeid);
                }

                opennlp::tools::util::ObjectStream<DocumentSample*> *DoccatTrainerTool::openSampleData(const std::string &sampleDataName, File *sampleDataFile, Charset *encoding)
                {
                  CmdLineUtil::checkInputFile(sampleDataName + " Data", sampleDataFile);

                  FileInputStream *sampleDataIn = CmdLineUtil::openInFile(sampleDataFile);

                  ObjectStream<std::string> *lineStream = new PlainTextByLineStream(sampleDataIn->getChannel(), encoding);

                  return new DocumentSampleStream(lineStream);
                }

                void DoccatTrainerTool::run(std::string args[])
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

                  CmdLineUtil::checkOutputFile("document categorizer model", modelOutFile);
                  ObjectStream<DocumentSample*> *sampleStream = openSampleData("Training", trainingDataInFile, params->getEncoding());

                  DoccatModel *model;
                  try
                  {
                    if (mlParams == 0)
                    {
                     model = DocumentCategorizerME::train(params->getLang(), sampleStream, params->getCutoff(), params->getIterations());
                    }
                    else
                    {
                      model = DocumentCategorizerME::train(params->getLang(), sampleStream, mlParams);
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

                  CmdLineUtil::writeModel("document categorizer", modelOutFile, model);
                }
            }
        }
    }
}
