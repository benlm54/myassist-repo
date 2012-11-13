#include "AttachContextGenerator.h"
#include "tools/parser/Cons.h"
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
                using opennlp::tools::parser::Cons;
                using opennlp::tools::parser::Parse;

                AttachContextGenerator::AttachContextGenerator(Set<std::string> *punctSet)
                {
                  this->punctSet = punctSet;
                }

                std::string *AttachContextGenerator::getContext(void *o)
                {
//ORIGINAL LINE: Object[] parts = (Object[]) o;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                  void *parts = static_cast<Object[]>(o);
                  return getContext(static_cast<Parse[]>(parts[0]),(static_cast<int>(parts[1])),static_cast<std::vector>(parts[2]),(static_cast<int>(parts[3])));
                }

                bool AttachContextGenerator::containsPunct(Collection<Parse*> *puncts, const std::string &punct)
                {
                  if (puncts != 0)
                  {
                    for (Collection<Parse*>::const_iterator pi = puncts->begin(); pi != puncts->end(); ++pi)
                    {
                      Parse *p = *pi;
                      if (p->getType() == punct)
                      {
                        return true;
                      }
                    }
                  }
                  return false;
                }

                std::string *AttachContextGenerator::getContext(Parse constituents[], int index, std::vector<Parse*> &rightFrontier, int rfi)
                {
                  std::vector<std::string> features = std::vector<std::string>(100);
                  int nodeDistance = rfi;
                  Parse *fn = rightFrontier[rfi];
                  Parse *fp = 0;
                  if (rfi + 1 < rightFrontier.size())
                  {
                    fp = rightFrontier[rfi + 1];
                  }
                  Parse *p_1 = 0;
                  if (rightFrontier.size() > 0)
                  {
                    p_1 = rightFrontier[0];
                  }
                  Parse *p0 = constituents[index];
                  Parse *p1 = 0;
                  if (index + 1 < sizeof(constituents) / sizeof(constituents[0]))
                  {
                    p1 = constituents[index + 1];
                  }

                  Collection<Parse*> *punct1s = 0;
                  Collection<Parse*> *punct_1s = 0;
                  Collection<Parse*> *punct_1fs = 0;
                  punct_1fs = fn->getPreviousPunctuationSet();
                  punct_1s = p0->getPreviousPunctuationSet();
                  punct1s = p0->getNextPunctuationSet();

                  std::string consfp = cons(fp,-3);
                  std::string consf = cons(fn,-2);
                  std::string consp_1 = cons(p_1,-1);
                  std::string consp0 = cons(p0,0);
                  std::string consp1 = cons(p1,1);

                  std::string consbofp = consbo(fp,-3);
                  std::string consbof = consbo(fn,-2);
                  std::string consbop_1 = consbo(p_1,-1);
                  std::string consbop0 = consbo(p0,0);
                  std::string consbop1 = consbo(p1,1);

                  Cons *cfp = new Cons(consfp,consbofp,-3,true);
                  Cons *cf = new Cons(consf,consbof,-2,true);
                  Cons *c_1 = new Cons(consp_1,consbop_1,-1,true);
                  Cons *c0 = new Cons(consp0,consbop0,0,true);
                  Cons *c1 = new Cons(consp1,consbop1,1,true);

                  //default
                  features.push_back("default");

                  //unigrams
                  features.push_back(consfp);
                  features.push_back(consbofp);
                  features.push_back(consf);
                  features.push_back(consbof);
                  features.push_back(consp_1);
                  features.push_back(consbop_1);
                  features.push_back(consp0);
                  features.push_back(consbop0);
                  features.push_back(consp1);
                  features.push_back(consbop1);

                  //productions
                  std::string prod = production(fn,false);
                  //String punctProd = production(fn,true,punctSet);
                  features.push_back("pn=" + prod);
                  features.push_back("pd=" + prod + "," + p0->getType());
                  features.push_back("ps=" + fn->getType() + "->" + fn->getType() + "," + p0->getType());
                  if (punct_1s != 0)
                  {
                    StringBuffer *punctBuf = new StringBuffer(5);
                    for (Collection<Parse*>::const_iterator pi = punct_1s->begin(); pi != punct_1s->end(); ++pi)
                    {
                      Parse *punct = *pi;
                      punctBuf->append(punct->getType())->append(",");
                    }
                    //features.add("ppd="+punctProd+","+punctBuf.toString()+p0.getType());
                    //features.add("pps="+fn.getType()+"->"+fn.getType()+","+punctBuf.toString()+p0.getType());
                  }

                  //bi-grams
                  //cons(fn),cons(0)
                  cons2(features,cfp,c0,punct_1s,true);
                  cons2(features,cf,c0,punct_1s,true);
                  cons2(features,c_1,c0,punct_1s,true);
                  cons2(features,c0,c1,punct1s,true);
                  cons3(features,cf,c_1,c0,0,punct_1s,true,true,true);
                  cons3(features,cf,c0,c1,punct_1s,punct1s,true,true,true);
                  cons3(features,cfp,cf,c0,0,punct_1s,true,true,true);
                  /*
                  for (int ri=0;ri<rfi;ri++) {
                    Parse jn = (Parse) rightFrontier.get(ri);
                    features.add("jn="+jn.getType());
                  }
                  */
                  int headDistance = (p0->getHeadIndex() - fn->getHeadIndex());
                  features.push_back("hd=" + headDistance);
                  features.push_back("nd=" + nodeDistance);

                  features.push_back("nd=" + p0->getType() + "." + nodeDistance);
                  features.push_back("hd=" + p0->getType() + "." + headDistance);
                  //features.add("fs="+rightFrontier.size());
                  //paired punct features
                  if (containsPunct(punct_1s,"''"))
                  {
                    if (containsPunct(punct_1fs,"``"))
                    {
                      features.push_back("quotematch"); //? not generating feature correctly

                    }
                    else
                    {
                      //features.add("noquotematch");
                    }
                  }
                  return features.toArray(new std::string[features.size()]);
                }
            }
        }
    }
}
