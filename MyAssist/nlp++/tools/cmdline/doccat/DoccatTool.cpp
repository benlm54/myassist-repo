#include "DoccatTool.h"
#include "tools/cmdline/CLI.h"
#include "tools/cmdline/TerminateToolException.h"
#include "tools/cmdline/doccat/DoccatModelLoader.h"
#include "tools/doccat/DoccatModel.h"
#include "tools/doccat/DocumentCategorizerME.h"
#include "tools/util/ObjectStream.h"
#include "tools/util/ParagraphStream.h"
#include "tools/util/PlainTextByLineStream.h"
#include "tools/cmdline/PerformanceMonitor.h"
#include "tools/doccat/DocumentSample.h"
#include "tools/cmdline/CmdLineUtil.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace doccat
            {
                using opennlp::tools::cmdline::CLI;
                using opennlp::tools::cmdline::CmdLineTool;
                using opennlp::tools::cmdline::CmdLineUtil;
                using opennlp::tools::cmdline::PerformanceMonitor;
                using opennlp::tools::cmdline::TerminateToolException;
                using opennlp::tools::doccat::DoccatModel;
                using opennlp::tools::doccat::DocumentCategorizerME;
                using opennlp::tools::doccat::DocumentSample;
                using opennlp::tools::util::ObjectStream;
                using opennlp::tools::util::ParagraphStream;
                using opennlp::tools::util::PlainTextByLineStream;

                std::string DoccatTool::getName()
                {
                  return "Doccat";
                }

                std::string DoccatTool::getShortDescription()
                {
                  return "learnable document categorizer";
                }

                std::string DoccatTool::getHelp()
                {
                  return "Usage: " + CLI::CMD + " " + getName() + " model < documents";
                }

                void DoccatTool::run(std::string args[])
                {

                  if (sizeof(args) / sizeof(args[0]) != 1)
                  {
                    std::cout << getHelp() << std::endl;
                    throw TerminateToolException(1);
                  }

                  DoccatModel *model = (new DoccatModelLoader())->load(new File(args[0]));

                  DocumentCategorizerME *doccat = new DocumentCategorizerME(model);

                  ObjectStream<std::string> *documentStream = new ParagraphStream(new PlainTextByLineStream(new InputStreamReader(System::in)));

                  PerformanceMonitor *perfMon = new PerformanceMonitor(System::err, "doc");
                  perfMon->start();

                  try
                  {
                    std::string document;
                    while ((document = documentStream->read()) != "")
                    {
//ORIGINAL LINE: double prob[] = doccat.categorize(document);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                      double *prob = doccat->categorize(document);
                      std::string category = doccat->getBestCategory(prob);

                      DocumentSample *sample = new DocumentSample(category, document);
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                      std::cout << sample->toString() << std::endl;

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
