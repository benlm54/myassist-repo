#include "BuildContextGenerator.h"
#include "tools/parser/Parser.h"
#include "tools/parser/chunking/Parser.h"
#include "tools/parser/treeinsert/Parser.h"
#include "tools/parser/Cons.h"

namespace opennlp
{
    namespace tools
    {
        namespace parser
        {
            namespace treeinsert
            {
                using opennlp::tools::parser::AbstractContextGenerator;
                using opennlp::tools::parser::Cons;
                using opennlp::tools::parser::Parse;

                BuildContextGenerator::BuildContextGenerator() : opennlp.tools.parser.AbstractContextGenerator()
                {
                  leftNodes = new Parse[2];
                }

                std::string *BuildContextGenerator::getContext(void *o)
                {
//ORIGINAL LINE: Object[] parts = (Object[]) o;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                  void *parts = static_cast<Object[]>(o);
                  return getContext(static_cast<Parse[]>(parts[0]),(static_cast<int>(parts[1])));
                }

                std::string *BuildContextGenerator::getContext(Parse constituents[], int index)
                {
                  Parse *p_2 = 0;
                  Parse *p_1 = 0;
                  Parse *p0 = 0;
                  Parse *p1 = 0;
                  Parse *p2 = 0;
                  int ps = sizeof(constituents) / sizeof(constituents[0]);

                  p0 = constituents[index];
                  if (index + 1 < ps)
                  {
                    p1 = constituents[index + 1];
                  }
                  if (index + 2 < ps)
                  {
                    p2 = constituents[index + 2];
                  }

                  Collection<Parse*> *punct1s = 0;
                  Collection<Parse*> *punct_1s = 0;
                  Collection<Parse*> *punct2s = 0;
                  Collection<Parse*> *punct_2s = 0;

                  punct_1s = p0->getPreviousPunctuationSet();
                  punct1s = p0->getNextPunctuationSet();
                  if (p1 != 0)
                  {
                    punct2s = p1->getNextPunctuationSet();
                  }


                  std::vector<Parse*> rf;
                  if (index == 0)
                  {
                    rf = Collections::emptyList();
                  }
                  else
                  {
                    //this isn't a root node so, punctSet won't be used and can be passed as empty.
                    Set<std::string> *emptyPunctSet = Collections::emptySet();
                    rf = Parser::getRightFrontier(constituents[0], emptyPunctSet);
                  }
                  getFrontierNodes(rf,leftNodes);
                  p_1 = leftNodes[0];
                  p_2 = leftNodes[1];

                  if (p_1 != 0)
                  {
                    punct_2s = p_1->getPreviousPunctuationSet();
                  }

                  std::string consp_2 = cons(p_2, -2);
                  std::string consp_1 = cons(p_1, -1);
                  std::string consp0 = cons(p0, 0);
                  std::string consp1 = cons(p1, 1);
                  std::string consp2 = cons(p2, 2);

                  std::string consbop_2 = consbo(p_2, -2);
                  std::string consbop_1 = consbo(p_1, -1);
                  std::string consbop0 = consbo(p0, 0);
                  std::string consbop1 = consbo(p1, 1);
                  std::string consbop2 = consbo(p2, 2);

                  Cons *c_2 = new Cons(consp_2,consbop_2,-2,true);
                  Cons *c_1 = new Cons(consp_1,consbop_1,-1,true);
                  Cons *c0 = new Cons(consp0,consbop0,0,true);
                  Cons *c1 = new Cons(consp1,consbop1,1,true);
                  Cons *c2 = new Cons(consp2,consbop2,2,true);

                  std::vector<std::string> features = std::vector<std::string>();
                  features.push_back("default");

                  //unigrams
                  features.push_back(consp_2);
                  features.push_back(consbop_2);
                  features.push_back(consp_1);
                  features.push_back(consbop_1);
                  features.push_back(consp0);
                  features.push_back(consbop0);
                  features.push_back(consp1);
                  features.push_back(consbop1);
                  features.push_back(consp2);
                  features.push_back(consbop2);

                  //cons(0),cons(1)
                  cons2(features,c0,c1,punct1s,true);
                  //cons(-1),cons(0)
                  cons2(features,c_1,c0,punct_1s,true);
                  //features.add("stage=cons(0),cons(1),cons(2)");
                  cons3(features,c0,c1,c2,punct1s,punct2s,true,true,true);
                  cons3(features,c_2,c_1,c0,punct_2s,punct_1s,true,true,true);
                  cons3(features,c_1,c0,c1,punct_1s,punct_1s,true,true,true);

                  if (rf.empty())
                  {
                    features.push_back(EOS + "," + consp0);
                    features.push_back(EOS + "," + consbop0);
                  }

                  return features.toArray(new std::string[features.size()]);
                }
            }
        }
    }
}
