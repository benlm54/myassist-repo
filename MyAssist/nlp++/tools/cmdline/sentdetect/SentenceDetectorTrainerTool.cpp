#include "SentenceDetectorTrainerTool.h"
#include "tools/cmdline/ArgumentParser.h"
#include "tools/cmdline/CLI.h"
#include "tools/cmdline/CmdLineUtil.h"
#include "tools/util/PlainTextByLineStream.h"
#include "tools/sentdetect/SentenceSampleStream.h"
#include "tools/cmdline/TerminateToolException.h"
#include "tools/util/TrainingParameters.h"
#include "model/TrainUtil.h"
#include "tools/sentdetect/SentenceModel.h"
#include "tools/sentdetect/SentenceDetectorME.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace sentdetect
            {
                using opennlp::model::TrainUtil;
                using opennlp::tools::cmdline::ArgumentParser;
                using opennlp::tools::cmdline::CLI;
                using opennlp::tools::cmdline::CmdLineTool;
                using opennlp::tools::cmdline::CmdLineUtil;
                using opennlp::tools::cmdline::TerminateToolException;
                using opennlp::tools::cmdline::params::TrainingToolParams;
                using opennlp::tools::dictionary::Dictionary;
                using opennlp::tools::sentdetect::SentenceDetectorME;
                using opennlp::tools::sentdetect::SentenceModel;
                using opennlp::tools::sentdetect::SentenceSample;
                using opennlp::tools::sentdetect::SentenceSampleStream;
                using opennlp::tools::util::ObjectStream;
                using opennlp::tools::util::PlainTextByLineStream;

                std::string SentenceDetectorTrainerTool::getName()
                {
                  return "SentenceDetectorTrainer";
                }

                std::string SentenceDetectorTrainerTool::getShortDescription()
                {
                  return "trainer for the learnable sentence detector";
                }

                std::string SentenceDetectorTrainerTool::getHelp()
                {
                  return "Usage: " + CLI::CMD + " " + getName() + " " + ArgumentParser::createUsage(TrainerToolParams::typeid);
                }

                opennlp::tools::util::ObjectStream<SentenceSample*> *SentenceDetectorTrainerTool::openSampleData(const std::string &sampleDataName, File *sampleDataFile, Charset *encoding)
                {
                  CmdLineUtil::checkInputFile(sampleDataName + " Data", sampleDataFile);

                  FileInputStream *sampleDataIn = CmdLineUtil::openInFile(sampleDataFile);

                  ObjectStream<std::string> *lineStream = new PlainTextByLineStream(sampleDataIn->getChannel(), encoding);

                  return new SentenceSampleStream(lineStream);
                }

                opennlp::tools::dictionary::Dictionary *SentenceDetectorTrainerTool::loadDict(File *f) throw(IOException)
                {
                  Dictionary *dict = 0;
                  if (f != 0)
                  {
                    CmdLineUtil::checkInputFile("abb dict", f);
                    dict = new Dictionary(new FileInputStream(f));
                  }
                  return dict;
                }

                void SentenceDetectorTrainerTool::run(std::string args[])
                {
                  if (!ArgumentParser::validateArguments(args, TrainerToolParams::typeid))
                  {
                    System::err::println(getHelp());
                    throw TerminateToolException(1);
                  }

                  TrainerToolParams *params = ArgumentParser::parse(args, TrainerToolParams::typeid);


                  opennlp::tools::util::TrainingParameters *mlParams = CmdLineUtil::loadTrainingParameters(params->getParams(), false);

                  if (mlParams != 0)
                  {
                    if (TrainUtil::isSequenceTraining(mlParams->getSettings()))
                    {
                      System::err::println("Sequence training is not supported!");
                      throw TerminateToolException(-1);
                    }
                  }

                  File *trainingDataInFile = params->getData();
                  File *modelOutFile = params->getModel();

                  CmdLineUtil::checkOutputFile("sentence detector model", modelOutFile);
                  ObjectStream<SentenceSample*> *sampleStream = openSampleData("Training", trainingDataInFile, params->getEncoding());

                  SentenceModel *model;
                  try
                  {
                    Dictionary *dict = loadDict(params->getAbbDict());
                    if (mlParams == 0)
                    {
                      model = SentenceDetectorME::train(params->getLang(), sampleStream, true, dict, params->getCutoff(), params->getIterations());
                    }
                    else
                    {
                      model = SentenceDetectorME::train(params->getLang(), sampleStream, true, dict, mlParams);
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

                  CmdLineUtil::writeModel("sentence detector", modelOutFile, model);
                }
            }
        }
    }
}
