#include "ChunkerMETool.h"
#include "tools/cmdline/CLI.h"
#include "tools/cmdline/TerminateToolException.h"
#include "tools/chunker/ChunkerModel.h"
#include "tools/cmdline/chunker/ChunkerModelLoader.h"
#include "tools/chunker/ChunkerME.h"
#include "tools/chunker/DefaultChunkerSequenceValidator.h"
#include "tools/util/ObjectStream.h"
#include "tools/util/PlainTextByLineStream.h"
#include "tools/cmdline/PerformanceMonitor.h"
#include "tools/postag/POSSample.h"
#include "tools/util/InvalidFormatException.h"
#include "tools/chunker/ChunkSample.h"
#include "tools/cmdline/CmdLineUtil.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace chunker
            {
                using opennlp::tools::chunker::ChunkSample;
                using opennlp::tools::chunker::ChunkerME;
                using opennlp::tools::chunker::ChunkerModel;
                using opennlp::tools::chunker::DefaultChunkerSequenceValidator;
                using opennlp::tools::cmdline::CLI;
                using opennlp::tools::cmdline::CmdLineTool;
                using opennlp::tools::cmdline::CmdLineUtil;
                using opennlp::tools::cmdline::PerformanceMonitor;
                using opennlp::tools::cmdline::TerminateToolException;
                using opennlp::tools::postag::POSSample;
                using opennlp::tools::util::InvalidFormatException;
                using opennlp::tools::util::ObjectStream;
                using opennlp::tools::util::PlainTextByLineStream;

                std::string ChunkerMETool::getName()
                {
                  return "ChunkerME";
                }

                std::string ChunkerMETool::getShortDescription()
                {
                  return "learnable chunker";
                }

                std::string ChunkerMETool::getHelp()
                {
                  return "Usage: " + CLI::CMD + " " + getName() + " model < sentences";
                }

                void ChunkerMETool::run(std::string args[])
                {
                  if (sizeof(args) / sizeof(args[0]) != 1)
                  {
                    std::cout << getHelp() << std::endl;
                    throw TerminateToolException(1);
                  }

                  ChunkerModel *model = (new ChunkerModelLoader())->load(new File(args[0]));

                  ChunkerME *chunker = new ChunkerME(model, ChunkerME::DEFAULT_BEAM_SIZE, new DefaultChunkerSequenceValidator());

                  ObjectStream<std::string> *lineStream = new PlainTextByLineStream(new InputStreamReader(System::in));

                  PerformanceMonitor *perfMon = new PerformanceMonitor(System::err, "sent");
                  perfMon->start();

                  try
                  {
                    std::string line;
                    while ((line = lineStream->read()) != "")
                    {

                      POSSample *posSample;
                      try
                      {
                        posSample = POSSample::parse(line);
                      }
                      catch (InvalidFormatException e)
                      {
                        System::err::println("Invalid format:");
                        System::err::println(line);
                        continue;
                      }

//ORIGINAL LINE: String[] chunks = chunker.chunk(posSample.getSentence(), posSample.getTags());
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                      std::string *chunks = chunker->chunk(posSample->getSentence(), posSample->getTags());

                      std::cout << (new ChunkSample(posSample->getSentence(), posSample->getTags(), chunks))->nicePrint() << std::endl;

                      perfMon->incrementCounter();
                    }
                  }
                  catch (IOException e)
                  {
                    CmdLineUtil::handleStdinIoError(e);
                  }

                  perfMon->stopAndPrintFinalResult();
                }
            }
        }
    }
}
