#include "CmdLineUtil.h"
#include "tools/cmdline/TerminateToolException.h"
#include "model/TrainUtil.h"
#include "NumberFormatException.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            using opennlp::model::TrainUtil;
            using opennlp::tools::util::TrainingParameters;
            using opennlp::tools::util::model::BaseModel;

            CmdLineUtil::CmdLineUtil()
            {
              // not intended to be instantiated
            }

            void CmdLineUtil::checkInputFile(const std::string &name, File *inFile)
            {

              bool isFailure;

              if (inFile->isDirectory())
              {
                System::err::println("The " + name + " file is a directory!");
                isFailure = true;
              }
              else if (!inFile->exists())
              {
                System::err::println("The " + name + " file does not exist!");
                isFailure = true;
              }
              else if (!inFile->canRead())
              {
                System::err::println("No permissions to read the " + name + " file!");
                isFailure = true;
              }
              else
              {
                isFailure = false;
              }

              if (isFailure)
              {
                System::err::println("Path: " + inFile->getAbsolutePath());
                throw TerminateToolException(-1);
              }
            }

            void CmdLineUtil::checkOutputFile(const std::string &name, File *outFile)
            {

              bool isFailure = true;

              if (outFile->exists())
              {

                // The file already exists, ensure that it is a normal file and that it is
                // possible to write into it

                if (outFile->isDirectory())
                {
                  System::err::println("The " + name + " file is a directory!");
                }
                else if (outFile->isFile())
                {
                  if (outFile->canWrite())
                  {
                    isFailure = false;
                  }
                  else
                  {
                    System::err::println("No permissions to write the " + name + " file!");
                  }
                }
                else
                {
                  System::err::println("The " + name + " file is not a normal file!");
                }
              }
              else
              {

                // The file does not exist ensure its parent
                // directory exists and has write permissions to create
                // a new file in it

                File *parentDir = outFile->getAbsoluteFile()->getParentFile();

                if (parentDir != 0 && parentDir->exists())
                {

                  if (parentDir->canWrite())
                  {
                    isFailure = false;
                  }
                  else
                  {
                    System::err::println("No permissions to create the " + name + " file!");
                  }
                }
                else
                {
                  System::err::println("The parent directory of the " + name + " file does not exist, " + "please create it first!");
                }

              }

              if (isFailure)
              {
                System::err::println("Path: " + outFile->getAbsolutePath());
                throw TerminateToolException(-1);
              }
            }

            FileInputStream *CmdLineUtil::openInFile(File *file)
            {
              try
              {
                return new FileInputStream(file);
              }
              catch (FileNotFoundException e)
              {
                System::err::println("File cannot be found: " + e->getMessage());
                throw TerminateToolException(-1);
              }
            }

            void CmdLineUtil::writeModel(const std::string &modelName, File *modelFile, BaseModel *model)
            {

              CmdLineUtil::checkOutputFile(modelName + " model", modelFile);

              System::err::print("Writing " + modelName + " model ... ");

              long long beginModelWritingTime = System::currentTimeMillis();

              OutputStream *modelOut = 0;
              try
              {
                modelOut = new BufferedOutputStream(new FileOutputStream(modelFile), IO_BUFFER_SIZE);
                model->serialize(modelOut);
              }
              catch (IOException e)
              {
                System::err::println("failed");
                System::err::println("Error during writing model file: " + e->getMessage());
                throw TerminateToolException(-1);
              }
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
              finally
              {
                if (modelOut != 0)
                {
                  try
                  {
                    modelOut->close();
                  }
                  catch (IOException e)
                  {
                    System::err::println("Failed to properly close model file: " + e->getMessage());
                  }
                }
              }

              long long modelWritingDuration = System::currentTimeMillis() - beginModelWritingTime;

              System::err::printf("done (%.3fs)\n", modelWritingDuration / 1000);

              System::err::println();

              System::err::println("Wrote " + modelName + " model to");
              System::err::println("path: " + modelFile->getAbsolutePath());

              System::err::println();
            }

            std::string CmdLineUtil::getParameter(const std::string &param, std::string args[])
            {
              for (int i = 0; i < sizeof(args) / sizeof(args[0]); i++)
              {
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'startsWith' method:
                if (args[i].startsWith("-") && args[i] == param)
                {
                  i++;
                  if (i < sizeof(args) / sizeof(args[0]))
                  {
                    return args[i];
                  }
                }
              }

              return 0;
            }

            int CmdLineUtil::getIntParameter(const std::string &param, std::string args[])
            {
              std::string value = getParameter(param, args);

              try
              {
                if (value != "")
                    return StringConverterHelper::fromString<int>(value);
              }
              catch (NumberFormatException e)
              {
              }

              return 0;
            }

            double CmdLineUtil::getDoubleParameter(const std::string &param, std::string args[])
            {
              std::string value = getParameter(param, args);

              try
              {
                if (value != "")
                    return StringConverterHelper::fromString<double>(value);
              }
              catch (NumberFormatException e)
              {
              }

              return 0;
            }

            Charset *CmdLineUtil::getEncodingParameter(std::string args[])
            {
              std::string charsetName = getParameter("-encoding", args);

              try
              {
                if (charsetName != "")
                {
                  if (Charset::isSupported(charsetName))
                  {
                    return Charset::forName(charsetName);
                  }
                  else
                  {
                    std::cout << "Error: Unsuppoted encoding " + charsetName + "." << std::endl;
                    throw TerminateToolException(-1);
                  }
                }
              }
              catch (IllegalCharsetNameException e)
              {
                std::cout << "Error: encoding name(" + e->getCharsetName() + ") is invalid." << std::endl;
                throw TerminateToolException(-1);
              }

              // TODO: Can still return null if encoding is not specified at all ...
              return 0;
            }

            void CmdLineUtil::checkLanguageCode(const std::string &code)
            {
              std::vector<std::string> languageCodes = std::vector<std::string>();
              languageCodes.addAll(Arrays::asList(Locale::getISOLanguages()));
              languageCodes.push_back("x-unspecified");

              if (!std::find(languageCodes.begin(), languageCodes.end(), code) != languageCodes.end())
              {
                System::err::println("Unkown language code, must be an ISO 639 code!");
                throw TerminateToolException(-1);
              }
            }

            bool CmdLineUtil::containsParam(const std::string &param, std::string args[])
            {
              for (int i = 0; i < sizeof(args) / sizeof(args[0]); i++)
              {
                if (args[i] == param)
                {
                  return true;
                }
              }

              return false;
            }

            void CmdLineUtil::printTrainingIoError(IOException *e)
            {
              System::err::println("IO error while reading training data or indexing data: " + e->getMessage());
            }

            void CmdLineUtil::handleStdinIoError(IOException *e)
            {
              System::err::println("IO Error while reading from stdin: " + e->getMessage());
              throw TerminateToolException(-1);
            }

            opennlp::tools::util::TrainingParameters *CmdLineUtil::loadTrainingParameters(const std::string &paramFile, bool supportSequenceTraining)
            {

              TrainingParameters *params = 0;

              if (paramFile != "")
              {

                checkInputFile("Training Parameter", new File(paramFile));

                InputStream *paramsIn = 0;
                try
                {
                  paramsIn = new FileInputStream(new File(paramFile));

                  params = new TrainingParameters(paramsIn);
                }
                catch (IOException e)
                {
                  // TODO: print error and exit
                  e->printStackTrace();
                }
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
                finally
                {
                  try
                  {
                    if (paramsIn != 0)
                      paramsIn->close();
                  }
                  catch (IOException e)
                  {
                  }
                }

                if (!TrainUtil::isValid(params->getSettings()))
                {
                  System::err::println("Training parameters file is invalid!");
                  throw TerminateToolException(-1);
                }

                if (!supportSequenceTraining && TrainUtil::isSequenceTraining(params->getSettings()))
                {
                  System::err::println("Sequence training is not supported!");
                  throw TerminateToolException(-1);
                }
              }

              return params;
            }
        }
    }
}
