#include "TokenNameFinderTrainerTool.h"
#include "tools/cmdline/ArgumentParser.h"
#include "tools/cmdline/CLI.h"
#include "tools/cmdline/CmdLineUtil.h"
#include "tools/util/PlainTextByLineStream.h"
#include "tools/namefind/NameSampleDataStream.h"
#include "tools/util/model/ModelUtil.h"
#include "tools/cmdline/TerminateToolException.h"
#include "tools/namefind/TokenNameFinderModel.h"
#include "tools/util/model/ArtifactSerializer.h"
#include "tools/util/InvalidFormatException.h"
#include "tools/util/TrainingParameters.h"
#include "tools/namefind/NameFinderME.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace namefind
            {
                using opennlp::tools::cmdline::ArgumentParser;
                using opennlp::tools::cmdline::CLI;
                using opennlp::tools::cmdline::CmdLineTool;
                using opennlp::tools::cmdline::CmdLineUtil;
                using opennlp::tools::cmdline::TerminateToolException;
                using opennlp::tools::cmdline::params::TrainingToolParams;
                using opennlp::tools::namefind::NameSample;
                using opennlp::tools::namefind::NameSampleDataStream;
                using opennlp::tools::namefind::TokenNameFinderModel;
                using opennlp::tools::util::InvalidFormatException;
                using opennlp::tools::util::ObjectStream;
                using opennlp::tools::util::PlainTextByLineStream;
                using opennlp::tools::util::model::ArtifactSerializer;
                using opennlp::tools::util::model::ModelUtil;

                std::string TokenNameFinderTrainerTool::getName()
                {
                  return "TokenNameFinderTrainer";
                }

                std::string TokenNameFinderTrainerTool::getShortDescription()
                {
                  return "trainer for the learnable name finder";
                }

                std::string TokenNameFinderTrainerTool::getHelp()
                {
                  return "Usage: " + CLI::CMD + " " + getName() + " " + ArgumentParser::createUsage(TrainerToolParams::typeid);
                }

                opennlp::tools::util::ObjectStream<NameSample*> *TokenNameFinderTrainerTool::openSampleData(const std::string &sampleDataName, File *sampleDataFile, Charset *encoding)
                {
                  CmdLineUtil::checkInputFile(sampleDataName + " Data", sampleDataFile);

                  FileInputStream *sampleDataIn = CmdLineUtil::openInFile(sampleDataFile);

                  ObjectStream<std::string> *lineStream = new PlainTextByLineStream(sampleDataIn->getChannel(), encoding);

                  return new NameSampleDataStream(lineStream);
                }

                char *TokenNameFinderTrainerTool::openFeatureGeneratorBytes(const std::string &featureGenDescriptorFile)
                {
                  if (featureGenDescriptorFile != "")
                  {
                    return openFeatureGeneratorBytes(new File(featureGenDescriptorFile));
                  }
                  return 0;
                }

                char *TokenNameFinderTrainerTool::openFeatureGeneratorBytes(File *featureGenDescriptorFile)
                {
//ORIGINAL LINE: byte featureGeneratorBytes[] = nullptr;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                  char *featureGeneratorBytes = 0;
                  // load descriptor file into memory
                  if (featureGenDescriptorFile != 0)
                  {
                    InputStream *bytesIn = CmdLineUtil::openInFile(featureGenDescriptorFile);

                    try
                    {
                      featureGeneratorBytes = ModelUtil::read(bytesIn);
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
                        bytesIn->close();
                      }
                      catch (IOException e)
                      {
                        // sorry that this can fail
                      }
                    }
                  }
                  return featureGeneratorBytes;
                }

                Map<std::string, void*> *TokenNameFinderTrainerTool::loadResources(File *resourcePath)
                {
                  Map<std::string, void*> *resources = std::map<std::string, void*>();

                  if (resourcePath != 0)
                  {

                    Map<std::string, ArtifactSerializer*> *artifactSerializers = TokenNameFinderModel::createArtifactSerializers();

//ORIGINAL LINE: java.io.File resourceFiles[] = resourcePath.listFiles();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                    File *resourceFiles = resourcePath->listFiles();

                    // TODO: Filter files, also files with start with a dot
                    for (File::const_iterator resourceFile = resourceFiles->begin(); resourceFile != resourceFiles->end(); ++resourceFile)
                    {

                      // TODO: Move extension extracting code to method and
                      // write unit test for it

                      // extract file ending
                      std::string resourceName = resourceFile->getName();

                      int lastDot = resourceName.rfind('.');

                      if (lastDot == -1)
                      {
                        continue;
                      }

                      std::string ending = resourceName.substr(lastDot + 1);

                      // lookup serializer from map
                      ArtifactSerializer *serializer = artifactSerializers->get(ending);

                      // TODO: Do different? For now just ignore ....
                      if (serializer == 0)
                        continue;

                      InputStream *resoruceIn = CmdLineUtil::openInFile(resourceFile);

                      try
                      {
                        resources->put(resourceName, serializer->create(resoruceIn));
                      }
                      catch (InvalidFormatException e)
                      {
                        // TODO: Fix exception handling
                        e->printStackTrace();
                      }
                      catch (IOException e)
                      {
                        // TODO: Fix exception handling
                        e->printStackTrace();
                      }
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
                      finally
                      {
                        try
                        {
                          resoruceIn->close();
                        }
                        catch (IOException e)
                        {
                        }
                      }
                    }
                  }
                  return resources;
                }

                Map<std::string, void*> *TokenNameFinderTrainerTool::loadResources(const std::string &resourceDirectory)
                {

                  if (resourceDirectory != "")
                  {
                    File *resourcePath = new File(resourceDirectory);
                    return loadResources(resourcePath);
                  }

                  return std::map<std::string, void*>();
                }

                void TokenNameFinderTrainerTool::run(std::string args[])
                {

                  if (!ArgumentParser::validateArguments(args, TrainerToolParams::typeid))
                  {
                    System::err::println(getHelp());
                    throw TerminateToolException(1);
                  }

                  TrainerToolParams *params = ArgumentParser::parse(args, TrainerToolParams::typeid);

                  opennlp::tools::util::TrainingParameters *mlParams = CmdLineUtil::loadTrainingParameters(params->getParams(), true);

                  File *trainingDataInFile = params->getData();
                  File *modelOutFile = params->getModel();


//ORIGINAL LINE: byte featureGeneratorBytes[] = openFeatureGeneratorBytes(params.getFeaturegen());
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                  char *featureGeneratorBytes = openFeatureGeneratorBytes(params->getFeaturegen());


                  // TODO: Support Custom resources: 
                  //       Must be loaded into memory, or written to tmp file until descriptor 
                  //       is loaded which defines parses when model is loaded

                  Map<std::string, void*> *resources = loadResources(params->getResources());

                  CmdLineUtil::checkOutputFile("name finder model", modelOutFile);
                  ObjectStream<NameSample*> *sampleStream = openSampleData("Training", trainingDataInFile, params->getEncoding());

                  TokenNameFinderModel *model;
                  try
                  {
                    if (mlParams == 0)
                    {
                    model = opennlp::tools::namefind::NameFinderME::train(params->getLang(), params->getType(), sampleStream, featureGeneratorBytes, resources, params->getIterations(), params->getCutoff());
                    }
                    else
                    {
                      model = opennlp::tools::namefind::NameFinderME::train(params->getLang(), params->getType(), sampleStream, mlParams, featureGeneratorBytes, resources);
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

                  CmdLineUtil::writeModel("name finder", modelOutFile, model);
                }
            }
        }
    }
}
