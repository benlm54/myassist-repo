#include "POSTaggerTrainerTool.h"
#include "tools/cmdline/ArgumentParser.h"
#include "tools/cmdline/CLI.h"
#include "tools/cmdline/CmdLineUtil.h"
#include "tools/util/PlainTextByLineStream.h"
#include "tools/postag/WordTagSampleStream.h"
#include "tools/cmdline/TerminateToolException.h"
#include "tools/util/TrainingParameters.h"
#include "model/TrainUtil.h"
#include "tools/dictionary/Dictionary.h"
#include "tools/postag/POSTaggerME.h"
#include "tools/postag/POSModel.h"
#include "tools/postag/POSDictionary.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace postag
            {
                using opennlp::model::TrainUtil;
                using opennlp::tools::cmdline::ArgumentParser;
                using opennlp::tools::cmdline::CLI;
                using opennlp::tools::cmdline::CmdLineTool;
                using opennlp::tools::cmdline::CmdLineUtil;
                using opennlp::tools::cmdline::TerminateToolException;
                using opennlp::tools::cmdline::params::TrainingToolParams;
                using opennlp::tools::dictionary::Dictionary;
                using opennlp::tools::postag::POSDictionary;
                using opennlp::tools::postag::POSModel;
                using opennlp::tools::postag::POSSample;
                using opennlp::tools::postag::POSTaggerME;
                using opennlp::tools::postag::WordTagSampleStream;
                using opennlp::tools::util::ObjectStream;
                using opennlp::tools::util::PlainTextByLineStream;
                using opennlp::tools::util::model::ModelType;

                std::string POSTaggerTrainerTool::getName()
                {
                  return "POSTaggerTrainer";
                }

                std::string POSTaggerTrainerTool::getShortDescription()
                {
                  return "trains a model for the part-of-speech tagger";
                }

                std::string POSTaggerTrainerTool::getHelp()
                {
                  return "Usage: " + CLI::CMD + " " + getName() + " " + ArgumentParser::createUsage(TrainerToolParams::typeid);
                }

                opennlp::tools::util::ObjectStream<POSSample*> *POSTaggerTrainerTool::openSampleData(const std::string &sampleDataName, File *sampleDataFile, Charset *encoding)
                {
                  CmdLineUtil::checkInputFile(sampleDataName + " Data", sampleDataFile);

                  FileInputStream *sampleDataIn = CmdLineUtil::openInFile(sampleDataFile);

                  ObjectStream<std::string> *lineStream = new PlainTextByLineStream(sampleDataIn->getChannel(), encoding);

                  return new WordTagSampleStream(lineStream);
                }

                void POSTaggerTrainerTool::run(std::string args[])
                {
                  if (!ArgumentParser::validateArguments(args, TrainerToolParams::typeid))
                  {
                    System::err::println(getHelp());
                    throw TerminateToolException(1);
                  }

                  TrainerToolParams *params = ArgumentParser::parse(args, TrainerToolParams::typeid);

                  opennlp::tools::util::TrainingParameters *mlParams = CmdLineUtil::loadTrainingParameters(params->getParams(), true);

                  if (mlParams != 0 && !TrainUtil::isValid(mlParams->getSettings()))
                  {
                    System::err::println("Training parameters file is invalid!");
                    throw TerminateToolException(-1);
                  }

                  File *trainingDataInFile = params->getData();
                  File *modelOutFile = params->getModel();

                  CmdLineUtil::checkOutputFile("pos tagger model", modelOutFile);
                  ObjectStream<POSSample*> *sampleStream = openSampleData("Training", trainingDataInFile, params->getEncoding());


                  Dictionary *ngramDict = 0;

                  int ngramCutoff = params->getNgram();

                  if (ngramCutoff != 0)
                  {
                    System::err::print("Building ngram dictionary ... ");
                    try
                    {
                      ngramDict = POSTaggerME::buildNGramDictionary(sampleStream, ngramCutoff);
                      sampleStream->reset();
                    }
                    catch (IOException e)
                    {
                      CmdLineUtil::printTrainingIoError(e);
                      throw TerminateToolException(-1);
                    }
                    System::err::println("done");
                  }

                  POSModel *model;
                  try
                  {

                    // TODO: Move to util method ...
                    POSDictionary *tagdict = 0;
                    if (params->getDict() != 0)
                    {
                      tagdict = POSDictionary::create(new FileInputStream(params->getDict()));
                    }

                    if (mlParams == 0)
                    {
                      // depending on model and sequence choose training method
                      model = POSTaggerME::train(params->getLang(), sampleStream, getModelType(params->getType()), tagdict, ngramDict, params->getCutoff(), params->getIterations());
                    }
                    else
                    {
                      model = POSTaggerME::train(params->getLang(), sampleStream, mlParams, tagdict, ngramDict);
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

                  CmdLineUtil::writeModel("pos tagger", modelOutFile, model);
                }

                opennlp::model::AbstractModel::ModelType POSTaggerTrainerTool::getModelType(const std::string &modelString)
                {
                  ModelType model;
                  if (modelString == "")
                    modelString = "maxent";

                  if (modelString == "maxent")
                  {
                    model = opennlp::tools::util::model::MAXENT;
                  }
                  else if (modelString == "perceptron")
                  {
                    model = opennlp::tools::util::model::PERCEPTRON;
                  }
                  else if (modelString == "perceptron_sequence")
                  {
                    model = opennlp::tools::util::model::PERCEPTRON_SEQUENCE;
                  }
                  else
                  {
                    model = 0;
                  }
                  return model;
                }
            }
        }
    }
}
