#include "CheckContextGenerator.h"
#include "tools/parser/Parser.h"
#include "tools/parser/chunking/Parser.h"
#include "tools/parser/treeinsert/Parser.h"
#include "StringBuffer.h"

namespace opennlp
{
    namespace tools
    {
        namespace parser
        {
            namespace treeinsert
            {
                using opennlp::tools::parser::AbstractContextGenerator;
                using opennlp::tools::parser::Parse;

                CheckContextGenerator::CheckContextGenerator(Set<std::string> *punctSet)
                {
                  this->punctSet = punctSet;
                  leftNodes = new Parse[2];
                }

                std::string *CheckContextGenerator::getContext(void *arg0)
                {
                  // TODO Auto-generated method stub
                  return 0;
                }

                std::string *CheckContextGenerator::getContext(Parse *parent, Parse constituents[], int index, bool trimFrontier)
                {
                  std::vector<std::string> features = std::vector<std::string>(100);
                  //default
                  features.push_back("default");
//ORIGINAL LINE: opennlp.tools.parser.Parse[] children = Parser.collapsePunctuation(parent.getChildren(),punctSet);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                  Parse *children = Parser::collapsePunctuation(parent->getChildren(),punctSet);
                  Parse *pstart = children[0];
                  Parse *pend = children[children->length - 1];
                  std::string type = parent->getType();
                  checkcons(pstart, "begin", type, features);
                  checkcons(pend, "last", type, features);
                  std::string production = "p=" + production(parent,false);
                  std::string punctProduction = "pp=" + production(parent,true);
                  features.push_back(production);
                  features.push_back(punctProduction);


                  Parse *p1 = 0;
                  Parse *p2 = 0;
                  Parse *p_1 = 0;
                  Parse *p_2 = 0;
                  Collection<Parse*> *p1s = constituents[index]->getNextPunctuationSet();
                  Collection<Parse*> *p2s = 0;
                  Collection<Parse*> *p_1s = constituents[index]->getPreviousPunctuationSet();
                  Collection<Parse*> *p_2s = 0;
                  std::vector<Parse*> rf;
                  if (index == 0)
                  {
                    rf = Collections::emptyList();
                  }
                  else
                  {
                    rf = Parser::getRightFrontier(constituents[0], punctSet);
                    if (trimFrontier)
                    {
                      int pi = rf.find(parent);
                      if (pi == -1)
                      {
                        throw std::exception("Parent not found in right frontier:" + parent + " rf=" + rf);
                      }
                      else
                      {
                        for (int ri = 0;ri <= pi;ri++)
                        {
                          //System.err.println(pi+" removing "+((Parse)rf.get(0)).getType()+" "+rf.get(0)+" "+(rf.size()-1)+" remain");
                          rf.remove(0);
                        }
                      }
                    }
                  }

                  getFrontierNodes(rf,leftNodes);
                  p_1 = leftNodes[0];
                  p_2 = leftNodes[1];
                  int ps = sizeof(constituents) / sizeof(constituents[0]);
                  if (p_1 != 0)
                  {
                    p_2s = p_1->getPreviousPunctuationSet();
                  }
                  if (index + 1 < ps)
                  {
                    p1 = constituents[index + 1];
                    p2s = p1->getNextPunctuationSet();
                  }
                  if (index + 2 < ps)
                  {
                    p2 = constituents[index + 2];
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
