#include "ParserTool.h"
#include "tools/cmdline/CLI.h"
#include "tools/parser/AbstractBottomUpParser.h"
#include "tools/util/Span.h"
#include "tools/cmdline/TerminateToolException.h"
#include "tools/cmdline/parser/ParserModelLoader.h"
#include "tools/parser/ParserModel.h"
#include "tools/cmdline/CmdLineUtil.h"
#include "tools/parser/ParserFactory.h"
#include "tools/util/ObjectStream.h"
#include "tools/util/PlainTextByLineStream.h"
#include "tools/cmdline/PerformanceMonitor.h"
#include "StringBuffer.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {
            namespace parser
            {
                using opennlp::tools::cmdline::CLI;
                using opennlp::tools::cmdline::CmdLineTool;
                using opennlp::tools::cmdline::CmdLineUtil;
                using opennlp::tools::cmdline::PerformanceMonitor;
                using opennlp::tools::cmdline::TerminateToolException;
                using opennlp::tools::parser::AbstractBottomUpParser;
                using opennlp::tools::parser::Parse;
                using opennlp::tools::parser::ParserFactory;
                using opennlp::tools::parser::ParserModel;
                using opennlp::tools::util::ObjectStream;
                using opennlp::tools::util::PlainTextByLineStream;
                using opennlp::tools::util::Span;

                std::string ParserTool::getName()
                {
                  return "Parser";
                }

                std::string ParserTool::getShortDescription()
                {
                  return "performs full syntactic parsing";
                }

                std::string ParserTool::getHelp()
                {
                  return "Usage: " + CLI::CMD + " " + getName() + " [-bs n -ap n -k n] model < sentences \n" + "-bs n: Use a beam size of n.\n" + "-ap f: Advance outcomes in with at least f% of the probability mass.\n" + "-k n: Show the top n parses.  This will also display their log-probablities.";
                }

java::util::regex::Pattern *ParserTool::untokenizedParenPattern1 = java::util::regex::Pattern::compile("([^ ])([({)}])");
java::util::regex::Pattern *ParserTool::untokenizedParenPattern2 = java::util::regex::Pattern::compile("([({)}])([^ ])");

                Parse *ParserTool::parseLine(const std::string &line, opennlp::tools::parser::Parser *parser, int numParses)
                {
                  line = untokenizedParenPattern1->matcher(line)->replaceAll("$1 $2");
                  line = untokenizedParenPattern2->matcher(line)->replaceAll("$1 $2");
                  StringTokenizer *str = new StringTokenizer(line);
                  StringBuffer *sb = new StringBuffer();
                  std::vector<std::string> tokens = std::vector<std::string>();
                  while (str->hasMoreTokens())
                  {
                    std::string tok = str->nextToken();
                    tokens.push_back(tok);
                    sb->append(tok)->append(" ");
                  }
                  std::string text = sb->substr(0, sb->length() - 1);
                  Parse *p = new Parse(text, new Span(0, text.length()), AbstractBottomUpParser::INC_NODE, 0, 0);
                  int start = 0;
                  int i = 0;
                  for (std::vector<std::string>::const_iterator ti = tokens.begin(); ti != tokens.end(); ++ti)
                  {
                    std::string tok = *ti;
                    p->insert(new Parse(text, new Span(start, start + tok.length()), AbstractBottomUpParser::TOK_NODE, 0,i));
                    start += tok.length() + 1;
                  }
//ORIGINAL LINE: opennlp.tools.parser.Parse[] parses;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                  Parse *parses;
                  if (numParses == 1)
                  {
                    parses = new Parse[] {parser->parse(p)};
                  }
                  else
                  {
                    parses = parser->parse(p,numParses);
                  }
                  return parses;
                }

                void ParserTool::run(std::string args[])
                {

                  if (sizeof(args) / sizeof(args[0]) < 1)
                  {
                    std::cout << getHelp() << std::endl;
                    throw TerminateToolException(1);
                  }

                  ParserModel *model = (new ParserModelLoader())->load(new File(args[sizeof(args) / sizeof(args[0]) - 1]));

                  int beamSize = CmdLineUtil::getIntParameter("-bs", args);
                  if (beamSize == 0)
                      beamSize = AbstractBottomUpParser::defaultBeamSize;

                  int numParses = CmdLineUtil::getIntParameter("-k", args);
                  bool showTopK;
                  if (numParses == 0)
                  {
                    numParses = 1;
                    showTopK = false;
                  }
                  else
                  {
                    showTopK = true;
                  }

                  double advancePercentage = CmdLineUtil::getDoubleParameter("-ap", args);

                  if (advancePercentage == 0)
                    advancePercentage = AbstractBottomUpParser::defaultAdvancePercentage;

                  opennlp::tools::parser::Parser *parser = ParserFactory::create(model, beamSize, advancePercentage);

                  ObjectStream<std::string> *lineStream = new PlainTextByLineStream(new InputStreamReader(System::in));

                  PerformanceMonitor *perfMon = new PerformanceMonitor(System::err, "sent");
                  perfMon->start();

                  try
                  {
                    std::string line;
                    while ((line = lineStream->read()) != "")
                    {
                      if (line.length() == 0)
                      {
                        std::cout << std::endl;
                      }
                      else
                      {
//ORIGINAL LINE: opennlp.tools.parser.Parse[] parses = parseLine(line, parser, numParses);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                        Parse *parses = parseLine(line, parser, numParses);

                        for (int pi = 0,pn = parses->length;pi < pn;pi++)
                        {
                          if (showTopK)
                          {
                            std::cout << pi + " " + parses[pi]->getProb() + " ";
                          }

                          parses[pi]->show();

                          perfMon->incrementCounter();
                        }
                      }
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
