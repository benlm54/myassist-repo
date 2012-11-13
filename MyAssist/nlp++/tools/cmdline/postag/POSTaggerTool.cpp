#include "POSTaggerTool.h"
#include "tools/cmdline/CLI.h"
#include "tools/cmdline/TerminateToolException.h"
#include "tools/cmdline/postag/POSModelLoader.h"
#include "tools/postag/POSModel.h"
#include "tools/postag/POSTaggerME.h"
#include "tools/util/ObjectStream.h"
#include "tools/util/PlainTextByLineStream.h"
#include "tools/cmdline/PerformanceMonitor.h"
#include "tools/tokenize/WhitespaceTokenizer.h"
#include "tools/postag/POSSample.h"
#include "tools/cmdline/CmdLineUtil.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace postag
            {
                using opennlp::tools::cmdline::CLI;
                using opennlp::tools::cmdline::CmdLineTool;
                using opennlp::tools::cmdline::CmdLineUtil;
                using opennlp::tools::cmdline::PerformanceMonitor;
                using opennlp::tools::cmdline::TerminateToolException;
                using opennlp::tools::postag::POSModel;
                using opennlp::tools::postag::POSSample;
                using opennlp::tools::postag::POSTaggerME;
                using opennlp::tools::tokenize::WhitespaceTokenizer;
                using opennlp::tools::util::ObjectStream;
                using opennlp::tools::util::PlainTextByLineStream;

                std::string POSTaggerTool::getName()
                {
                  return "POSTagger";
                }

                std::string POSTaggerTool::getShortDescription()
                {
                  return "learnable part of speech tagger";
                }

                std::string POSTaggerTool::getHelp()
                {
                  return "Usage: " + CLI::CMD + " " + getName() + " model < sentences";
                }

                void POSTaggerTool::run(std::string args[])
                {

                  if (sizeof(args) / sizeof(args[0]) != 1)
                  {
                    std::cout << getHelp() << std::endl;
                    throw TerminateToolException(1);
                  }

                  POSModel *model = (new POSModelLoader())->load(new File(args[0]));

                  POSTaggerME *tagger = new POSTaggerME(model);

                  ObjectStream<std::string> *lineStream = new PlainTextByLineStream(new InputStreamReader(System::in));

                  PerformanceMonitor *perfMon = new PerformanceMonitor(System::err, "sent");
                  perfMon->start();

                  try
                  {
                    std::string line;
                    while ((line = lineStream->read()) != "")
                    {

//ORIGINAL LINE: String whitespaceTokenizerLine[] = opennlp.tools.tokenize.WhitespaceTokenizer.INSTANCE.tokenize(line);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                      std::string *whitespaceTokenizerLine = WhitespaceTokenizer::INSTANCE->tokenize(line);
//ORIGINAL LINE: String[] tags = tagger.tag(whitespaceTokenizerLine);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                      std::string *tags = tagger->tag(whitespaceTokenizerLine);

                      POSSample *sample = new POSSample(whitespaceTokenizerLine, tags);
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
