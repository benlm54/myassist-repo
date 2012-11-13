#include "CheckContextGenerator.h"
#include "StringBuffer.h"

namespace opennlp
{
    namespace tools
    {
        namespace parser
        {
            namespace chunking
            {
                using opennlp::tools::parser::AbstractContextGenerator;
                using opennlp::tools::parser::Parse;

                CheckContextGenerator::CheckContextGenerator() : opennlp.tools.parser.AbstractContextGenerator()
                {
                }

                std::string *CheckContextGenerator::getContext(void *o)
                {
//ORIGINAL LINE: Object[] params = (Object[]) o;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                  void *params = static_cast<Object[]>(o);
                  return getContext(static_cast<Parse[]>(params[0]), static_cast<std::string>(params[1]), (static_cast<int>(params[2])), (static_cast<int>(params[3])));
                }

                std::string *CheckContextGenerator::getContext(Parse constituents[], const std::string &type, int start, int end)
                {
                  int ps = sizeof(constituents) / sizeof(constituents[0]);
                  std::vector<std::string> features = std::vector<std::string>(100);

                  //default
                  features.push_back("default");
                  //first constituent label
                  features.push_back("fl=" + constituents[0]->getLabel());
                  Parse *pstart = constituents[start];
                  Parse *pend = constituents[end];
                  checkcons(pstart, "begin", type, features);
                  checkcons(pend, "last", type, features);
                  StringBuffer *production = new StringBuffer(20);
                  StringBuffer *punctProduction = new StringBuffer(20);
                  production->append("p=")->append(type)->append("->");
                  punctProduction->append("pp=")->append(type)->append("->");
                  for (int pi = start; pi < end; pi++)
                  {
                    Parse *p = constituents[pi];
                    checkcons(p, pend, type, features);
                    production->append(p->getType())->append(",");
                    punctProduction->append(p->getType())->append(",");
                    Collection<Parse*> *nextPunct = p->getNextPunctuationSet();
                    if (nextPunct != 0)
                    {
                      for (Collection<Parse*>::const_iterator pit = nextPunct->begin(); pit != nextPunct->end(); ++pit)
                      {
                        Parse *punct = *pit;
                        punctProduction->append(punct->getType())->append(",");
                      }
                    }
                  }
                  production->append(pend->getType());
                  punctProduction->append(pend->getType());
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                  features.push_back(production->toString());
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                  features.push_back(punctProduction->toString());
                  Parse *p_2 = 0;
                  Parse *p_1 = 0;
                  Parse *p1 = 0;
                  Parse *p2 = 0;
                  Collection<Parse*> *p1s = constituents[end]->getNextPunctuationSet();
                  Collection<Parse*> *p2s = 0;
                  Collection<Parse*> *p_1s = constituents[start]->getPreviousPunctuationSet();
                  Collection<Parse*> *p_2s = 0;
                  if (start - 2 >= 0)
                  {
                    p_2 = constituents[start - 2];
                  }
                  if (start - 1 >= 0)
                  {
                    p_1 = constituents[start - 1];
                    p_2s = p_1->getPreviousPunctuationSet();
                  }
                  if (end + 1 < ps)
                  {
                    p1 = constituents[end + 1];
                    p2s = p1->getNextPunctuationSet();
                  }
                  if (end + 2 < ps)
                  {
                    p2 = constituents[end + 2];
                  }
                  surround(p_1, -1, type, p_1s, features);
                  surround(p_2, -2, type, p_2s, features);
                  surround(p1, 1, type, p1s, features);
                  surround(p2, 2, type, p2s, features);

                  return features.toArray(new std::string[features.size()]);
                }
            }
        }
    }
}
