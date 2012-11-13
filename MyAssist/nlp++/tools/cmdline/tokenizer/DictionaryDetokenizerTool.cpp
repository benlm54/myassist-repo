#include "DictionaryDetokenizerTool.h"
#include "tools/cmdline/CLI.h"
#include "tools/cmdline/TerminateToolException.h"
#include "tools/cmdline/tokenizer/DetokenizationDictionaryLoader.h"
#include "tools/tokenize/DictionaryDetokenizer.h"
#include "tools/util/ObjectStream.h"
#include "tools/util/PlainTextByLineStream.h"
#include "tools/cmdline/PerformanceMonitor.h"
#include "tools/tokenize/WhitespaceTokenizer.h"
#include "tools/cmdline/CmdLineUtil.h"
#include "DetokenizationOperation.h"
#include "StringBuilder.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace tokenizer
            {
                using opennlp::tools::cmdline::CLI;
                using opennlp::tools::cmdline::CmdLineTool;
                using opennlp::tools::cmdline::CmdLineUtil;
                using opennlp::tools::cmdline::PerformanceMonitor;
                using opennlp::tools::cmdline::TerminateToolException;
                using opennlp::tools::tokenize::Detokenizer;
                using opennlp::tools::tokenize::Detokenizer::DetokenizationOperation;
                using opennlp::tools::tokenize::DictionaryDetokenizer;
                using opennlp::tools::tokenize::WhitespaceTokenizer;
                using opennlp::tools::util::ObjectStream;
                using opennlp::tools::util::PlainTextByLineStream;

                std::string DictionaryDetokenizerTool::getName()
                {
                  return "DictionaryDetokenizer";
                }

                std::string DictionaryDetokenizerTool::getShortDescription()
                {
                  return "";
                }

                std::string DictionaryDetokenizerTool::getHelp()
                {
                  return "Usage: " + CLI::CMD + " " + getName() + " detokenizerDictionary";
                }

                std::string DictionaryDetokenizerTool::detokenize(std::string tokens[], Detokenizer::DetokenizationOperation operations[])
                {

                  if (sizeof(tokens) / sizeof(tokens[0]) != sizeof(operations) / sizeof(operations[0]))
                    throw IllegalArgumentException("tokens and operations array must have same length!");


                  StringBuilder *untokenizedString = new StringBuilder();

                  for (int i = 0; i < sizeof(tokens) / sizeof(tokens[0]); i++)
                  {

                    // attach token to string buffer
                    untokenizedString->append(tokens[i]);

                    bool isAppendSpace;

                    // if this token is the last token do not attach a space
                    if (i + 1 == sizeof(operations) / sizeof(operations[0]))
                    {
                      isAppendSpace = false;
                    }
                    // if next token move left, no space after this token,
                    // its safe to access next token
                    else if (operations[i + 1]->equals(Detokenizer::DetokenizationOperation::MERGE_TO_LEFT))
                    {
                      isAppendSpace = false;
                    }
                    // if this token is move right, no space 
                    else if (operations[i]->equals(Detokenizer::DetokenizationOperation::MERGE_TO_RIGHT))
                    {
                      isAppendSpace = false;
                    }
                    else
                    {
                      isAppendSpace = true;
                    }

                    if (isAppendSpace)
                      untokenizedString->append(' ');
                  }

//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                  return untokenizedString->toString();
                }

                void DictionaryDetokenizerTool::run(std::string args[])
                {


                  if (sizeof(args) / sizeof(args[0]) != 1)
                  {
                    std::cout << getHelp() << std::endl;
                    throw TerminateToolException(1);
                  }

                  Detokenizer *detokenizer = new DictionaryDetokenizer((new DetokenizationDictionaryLoader())->load(new File(args[0])));

                  ObjectStream<std::string> *tokenizedLineStream = new PlainTextByLineStream(new InputStreamReader(System::in));

                  PerformanceMonitor *perfMon = new PerformanceMonitor(System::err, "sent");
                  perfMon->start();

                  try
                  {
                    std::string tokenizedLine;
                    while ((tokenizedLine = tokenizedLineStream->read()) != "")
                    {

                      // white space tokenize line
//ORIGINAL LINE: String tokens[] = opennlp.tools.tokenize.WhitespaceTokenizer.INSTANCE.tokenize(tokenizedLine);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                      std::string *tokens = WhitespaceTokenizer::INSTANCE->tokenize(tokenizedLine);

//ORIGINAL LINE: opennlp.tools.tokenize.Detokenizer.DetokenizationOperation operations[] = detokenizer.detokenize(tokens);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                      Detokenizer::DetokenizationOperation *operations = detokenizer->detokenize(tokens);

                      std::cout << detokenize(tokens, operations) << std::endl;

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
