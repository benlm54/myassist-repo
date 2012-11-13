#include "TokenNameFinderTool.h"
#include "tools/cmdline/CLI.h"
#include "tools/cmdline/TerminateToolException.h"
#include "tools/namefind/NameFinderME.h"
#include "tools/cmdline/namefind/TokenNameFinderModelLoader.h"
#include "tools/namefind/TokenNameFinderModel.h"
#include "tools/util/ObjectStream.h"
#include "tools/util/PlainTextByLineStream.h"
#include "tools/cmdline/PerformanceMonitor.h"
#include "tools/tokenize/WhitespaceTokenizer.h"
#include "tools/util/Span.h"
#include "tools/namefind/NameSample.h"
#include "tools/cmdline/CmdLineUtil.h"
#include "const_iterator.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace namefind
            {
                using opennlp::tools::cmdline::CLI;
                using opennlp::tools::cmdline::CmdLineTool;
                using opennlp::tools::cmdline::CmdLineUtil;
                using opennlp::tools::cmdline::PerformanceMonitor;
                using opennlp::tools::cmdline::TerminateToolException;
                using opennlp::tools::namefind::NameFinderME;
                using opennlp::tools::namefind::NameSample;
                using opennlp::tools::namefind::TokenNameFinder;
                using opennlp::tools::namefind::TokenNameFinderModel;
                using opennlp::tools::tokenize::WhitespaceTokenizer;
                using opennlp::tools::util::ObjectStream;
                using opennlp::tools::util::PlainTextByLineStream;
                using opennlp::tools::util::Span;

                std::string TokenNameFinderTool::getName()
                {
                  return "TokenNameFinder";
                }

                std::string TokenNameFinderTool::getShortDescription()
                {
                  return "learnable name finder";
                }

                std::string TokenNameFinderTool::getHelp()
                {
                  return "Usage: " + CLI::CMD + " " + getName() + " model1 model2 ... modelN < sentences";
                }

                void TokenNameFinderTool::run(std::string args[])
                {

                  if (sizeof(args) / sizeof(args[0]) == 0)
                  {
                    std::cout << getHelp() << std::endl;
                    throw TerminateToolException(1);
                  }

                  NameFinderME nameFinders[sizeof(args) / sizeof(args[0])];

                  for (int i = 0; i < sizeof(nameFinders) / sizeof(nameFinders[0]); i++)
                  {
                    TokenNameFinderModel *model = (new TokenNameFinderModelLoader())->load(new File(args[i]));
                    nameFinders[i] = new NameFinderME(model);
                  }

                  ObjectStream<std::string> *untokenizedLineStream = new PlainTextByLineStream(new InputStreamReader(System::in));

                  PerformanceMonitor *perfMon = new PerformanceMonitor(System::err, "sent");
                  perfMon->start();

                  try
                  {
                    std::string line;
                    while ((line = untokenizedLineStream->read()) != "")
                    {
//ORIGINAL LINE: String whitespaceTokenizerLine[] = opennlp.tools.tokenize.WhitespaceTokenizer.INSTANCE.tokenize(line);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                      std::string *whitespaceTokenizerLine = WhitespaceTokenizer::INSTANCE->tokenize(line);

                      // A new line indicates a new document,
                      // adaptive data must be cleared for a new document

                      if (whitespaceTokenizerLine->length == 0)
                      {
                        for (int i = 0; i < sizeof(nameFinders) / sizeof(nameFinders[0]); i++)
                          nameFinders[i]->clearAdaptiveData();
                      }

                      std::vector<Span*> names = std::vector<Span*>();

                      for (NameFinderME::const_iterator nameFinder = nameFinders->begin(); nameFinder != nameFinders->end(); ++nameFinder)
                      {
                        Collections::addAll(names, nameFinder->find(whitespaceTokenizerLine));
                      }

                      // Simple way to drop intersecting spans, otherwise the
                      // NameSample is invalid
//ORIGINAL LINE: opennlp.tools.util.Span reducedNames[] = opennlp.tools.namefind.NameFinderME.dropOverlappingSpans(names.toArray(new opennlp.tools.util.Span[names.size()]));
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                      Span *reducedNames = NameFinderME::dropOverlappingSpans(names.toArray(new Span[names.size()]));

                      NameSample *nameSample = new NameSample(whitespaceTokenizerLine, reducedNames, false);

//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                      std::cout << nameSample->toString() << std::endl;

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
