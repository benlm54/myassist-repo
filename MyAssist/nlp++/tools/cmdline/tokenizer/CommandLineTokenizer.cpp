#include "CommandLineTokenizer.h"
#include "tools/util/ObjectStream.h"
#include "tools/util/PlainTextByLineStream.h"
#include "tools/tokenize/TokenizerStream.h"
#include "tools/tokenize/WhitespaceTokenStream.h"
#include "tools/cmdline/PerformanceMonitor.h"
#include "tools/cmdline/CmdLineUtil.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace tokenizer
            {
                using opennlp::tools::cmdline::CmdLineUtil;
                using opennlp::tools::cmdline::PerformanceMonitor;
                using opennlp::tools::tokenize::Tokenizer;
                using opennlp::tools::tokenize::TokenizerStream;
                using opennlp::tools::tokenize::WhitespaceTokenStream;
                using opennlp::tools::util::ObjectStream;
                using opennlp::tools::util::PlainTextByLineStream;

                CommandLineTokenizer::CommandLineTokenizer(Tokenizer *tokenizer) : tokenizer(tokenizer)
                {
                }

                void CommandLineTokenizer::process()
                {

                  ObjectStream<std::string> *untokenizedLineStream = new PlainTextByLineStream(new InputStreamReader(System::in));

                  ObjectStream<std::string> *tokenizedLineStream = new WhitespaceTokenStream(new TokenizerStream(tokenizer, untokenizedLineStream));

                  PerformanceMonitor *perfMon = new PerformanceMonitor(System::err, "sent");
                  perfMon->start();

                  try
                  {
                    std::string tokenizedLine;
                    while ((tokenizedLine = tokenizedLineStream->read()) != "")
                    {
                      std::cout << tokenizedLine << std::endl;
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
