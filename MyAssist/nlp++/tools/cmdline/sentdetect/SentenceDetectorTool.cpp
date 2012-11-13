#include "SentenceDetectorTool.h"
#include "tools/cmdline/CLI.h"
#include "tools/cmdline/TerminateToolException.h"
#include "tools/cmdline/sentdetect/SentenceModelLoader.h"
#include "tools/sentdetect/SentenceModel.h"
#include "tools/sentdetect/SentenceDetectorME.h"
#include "tools/util/ObjectStream.h"
#include "tools/util/ParagraphStream.h"
#include "tools/util/PlainTextByLineStream.h"
#include "tools/cmdline/PerformanceMonitor.h"
#include "tools/cmdline/CmdLineUtil.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace sentdetect
            {
                using opennlp::tools::cmdline::CLI;
                using opennlp::tools::cmdline::CmdLineTool;
                using opennlp::tools::cmdline::CmdLineUtil;
                using opennlp::tools::cmdline::PerformanceMonitor;
                using opennlp::tools::cmdline::TerminateToolException;
                using opennlp::tools::sentdetect::SentenceDetectorME;
                using opennlp::tools::sentdetect::SentenceModel;
                using opennlp::tools::util::ObjectStream;
                using opennlp::tools::util::ParagraphStream;
                using opennlp::tools::util::PlainTextByLineStream;

                std::string SentenceDetectorTool::getName()
                {
                  return "SentenceDetector";
                }

                std::string SentenceDetectorTool::getShortDescription()
                {
                  return "learnable sentence detector";
                }

                std::string SentenceDetectorTool::getHelp()
                {
                  return "Usage: " + CLI::CMD + " " + getName() + " model < sentences";
                }

                void SentenceDetectorTool::run(std::string args[])
                {

                  if (sizeof(args) / sizeof(args[0]) != 1)
                  {
                    std::cout << getHelp() << std::endl;
                    throw TerminateToolException(1);
                  }

                  SentenceModel *model = (new SentenceModelLoader())->load(new File(args[0]));

                  SentenceDetectorME *sdetector = new SentenceDetectorME(model);

                  ObjectStream<std::string> *paraStream = new ParagraphStream(new PlainTextByLineStream(new InputStreamReader(System::in)));

                  PerformanceMonitor *perfMon = new PerformanceMonitor(System::err, "sent");
                  perfMon->start();

                  try
                  {
                    std::string para;
                    while ((para = paraStream->read()) != "")
                    {

//ORIGINAL LINE: String[] sents = sdetector.sentDetect(para);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                      std::string *sents = sdetector->sentDetect(para);
                      for (std::string::const_iterator sentence = sents->begin(); sentence != sents->end(); ++sentence)
                      {
                        std::cout << *sentence << std::endl;
                      }

                      perfMon->incrementCounter(sents->length);

                      std::cout << std::endl;
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
