#include "BuildContextGenerator.h"
#include "tools/util/StringList.h"
#include "tools/parser/Cons.h"
#include "tools/parser/Parser.h"
#include "tools/parser/chunking/Parser.h"
#include "tools/parser/treeinsert/Parser.h"

namespace opennlp
{
    namespace tools
    {
        namespace parser
        {
            namespace chunking
            {
                using opennlp::tools::dictionary::Dictionary;
                using opennlp::tools::parser::AbstractContextGenerator;
                using opennlp::tools::parser::Cons;
                using opennlp::tools::parser::Parse;
                using opennlp::tools::util::StringList;

                BuildContextGenerator::BuildContextGenerator() : opennlp.tools.parser.AbstractContextGenerator()
                {
                  zeroBackOff = false;
                  useLabel = true;
                }

                BuildContextGenerator::BuildContextGenerator(Dictionary *dict)
                {
                  this->dict = dict;
                  unigram = new std::string[1];
                  bigram = new std::string[2];
                  trigram = new std::string[3];
                }

                std::string *BuildContextGenerator::getContext(void *o)
                {
//ORIGINAL LINE: Object[] params = (Object[]) o;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                  void *params = static_cast<Object[]>(o);
                  return getContext(static_cast<Parse[]>(params[0]), (static_cast<int>(params[1])));
                }

                std::string *BuildContextGenerator::getContext(Parse constituents[], int index)
                {
                  std::vector<std::string> features = std::vector<std::string>(100);
                  int ps = sizeof(constituents) / sizeof(constituents[0]);

                  // cons(-2), cons(-1), cons(0), cons(1), cons(2)
                  // cons(-2)
                  Parse *p_2 = 0;
                  Parse *p_1 = 0;
                  Parse *p0 = 0;
                  Parse *p1 = 0;
                  Parse *p2 = 0;

                  Collection<Parse*> *punct1s = 0;
                  Collection<Parse*> *punct2s = 0;
                  Collection<Parse*> *punct_1s = 0;
                  Collection<Parse*> *punct_2s = 0;

                  if (index - 2 >= 0)
                  {
                    p_2 = constituents[index - 2];
                  }
                  if (index - 1 >= 0)
                  {
                    p_1 = constituents[index - 1];
                    punct_2s = p_1->getPreviousPunctuationSet();
                  }
                  p0 = constituents[index];
                  punct_1s = p0->getPreviousPunctuationSet();
                  punct1s = p0->getNextPunctuationSet();

                  if (index + 1 < ps)
                  {
                    p1 = constituents[index + 1];
                    punct2s = p1->getNextPunctuationSet();
                  }
                  if (index + 2 < ps)
                  {
                    p2 = constituents[index + 2];
                  }

                  bool u_2 = true;
                  bool u_1 = true;
                  bool u0 = true;
                  bool u1 = true;
                  bool u2 = true;
                  bool b_2_1 = true;
                  bool b_10 = true;
                  bool b01 = true;
                  bool b12 = true;
                  bool t_2_10 = true;
                  bool t_101 = true;
                  bool t012 = true;

                  if (dict != 0)
                  {

                    if (p_2 != 0)
                    {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                      unigram[0] = p_2->getHead()->toString();
                      u_2 = dict->contains(new StringList(unigram));
                    }

                    if (p2 != 0)
                    {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                      unigram[0] = p2->getHead()->toString();
                      u2 = dict->contains(new StringList(unigram));
                    }

//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                    unigram[0] = p0->getHead()->toString();
                    u0 = dict->contains(new StringList(unigram));

                    if (p_2 != 0 && p_1 != 0)
                    {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                      bigram[0] = p_2->getHead()->toString();
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                      bigram[1] = p_1->getHead()->toString();
                      b_2_1 = dict->contains(new StringList(bigram));

//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                      trigram[0] = p_2->getHead()->toString();
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                      trigram[1] = p_1->getHead()->toString();
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                      trigram[2] = p0->getHead()->toString();
                      t_2_10 = dict->contains(new StringList(trigram));
                    }
                    if (p_1 != 0 && p1 != 0)
                    {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                      trigram[0] = p_1->getHead()->toString();
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                      trigram[1] = p0->getHead()->toString();
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                      trigram[2] = p1->getHead()->toString();
                      t_101 = dict->contains(new StringList(trigram));
                    }
                    if (p_1 != 0)
                    {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                      unigram[0] = p_1->getHead()->toString();
                      u_1 = dict->contains(new StringList(unigram));

                      //extra check for 2==null case
                      b_2_1 = b_2_1 && u_1 & u_2;
                      t_2_10 = t_2_10 && u_1 & u_2 & u0;
                      t_101 = t_101 && u_1 & u0 && u1;

//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                      bigram[0] = p_1->getHead()->toString();
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                      bigram[1] = p0->getHead()->toString();
                      b_10 = dict->contains(new StringList(bigram)) && u_1 && u0;
                    }
                    if (p1 != 0 && p2 != 0)
                    {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                      bigram[0] = p1->getHead()->toString();
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                      bigram[1] = p2->getHead()->toString();
                      b12 = dict->contains(new StringList(bigram));

//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                      trigram[0] = p0->getHead()->toString();
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                      trigram[1] = p1->getHead()->toString();
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                      trigram[2] = p2->getHead()->toString();
                      t012 = dict->contains(new StringList(trigram));
                    }
                    if (p1 != 0)
                    {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                      unigram[0] = p1->getHead()->toString();
                      u1 = dict->contains(new StringList(unigram));

                      //extra check for 2==null case
                      b12 = b12 && u1 && u2;
                      t012 = t012 && u1 && u2 && u0;
                      t_101 = t_101 && u0 && u_1 && u1;

//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                      bigram[0] = p0->getHead()->toString();
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                      bigram[1] = p1->getHead()->toString();
                      b01 = dict->contains(new StringList(bigram));
                      b01 = b01 && u0 && u1;
                    }
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

                  Cons *c_2 = new Cons(consp_2,consbop_2,-2,u_2);
                  Cons *c_1 = new Cons(consp_1,consbop_1,-1,u_1);
                  Cons *c0 = new Cons(consp0,consbop0,0,u0);
                  Cons *c1 = new Cons(consp1,consbop1,1,u1);
                  Cons *c2 = new Cons(consp2,consbop2,2,u2);

                  //default
                  features.push_back("default");
                  //first constituent label
                  //features.add("fl="+constituents[0].getLabel());

                  // features.add("stage=cons(i)");
                  // cons(-2), cons(-1), cons(0), cons(1), cons(2)
                  if (u0)
                      features.push_back(consp0);
                  features.push_back(consbop0);

                  if (u_2)
                      features.push_back(consp_2);
                  features.push_back(consbop_2);
                  if (u_1)
                      features.push_back(consp_1);
                  features.push_back(consbop_1);
                  if (u1)
                      features.push_back(consp1);
                  features.push_back(consbop1);
                  if (u2)
                      features.push_back(consp2);
                  features.push_back(consbop2);

                  //cons(0),cons(1)
                  cons2(features,c0,c1,punct1s,b01);
                  //cons(-1),cons(0)
                  cons2(features,c_1,c0,punct_1s,b_10);
                  //features.add("stage=cons(0),cons(1),cons(2)");
                  cons3(features,c0,c1,c2,punct1s,punct2s,t012,b01,b12);
                  cons3(features,c_2,c_1,c0,punct_2s,punct_1s,t_2_10,b_2_1,b_10);
                  cons3(features,c_1,c0,c1,punct_1s,punct1s,t_101,b_10,b01);
                  //features.add("stage=other");
                  std::string p0Tag = p0->getType();
                  if (p0Tag == "-RRB-")
                  {
                    for (int pi = index - 1; pi >= 0; pi--)
                    {
                      Parse *p = constituents[pi];
                      if (p->getType() == "-LRB-")
                      {
                        features.push_back("bracketsmatch");
                        break;
                      }
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'startsWith' method:
                      if (p->getLabel().startsWith(Parser::START))
                      {
                        break;
                      }
                    }
                  }
                  if (p0Tag == "-RCB-")
                  {
                    for (int pi = index - 1; pi >= 0; pi--)
                    {
                      Parse *p = constituents[pi];
                      if (p->getType() == "-LCB-")
                      {
                        features.push_back("bracketsmatch");
                        break;
                      }
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'startsWith' method:
                      if (p->getLabel().startsWith(Parser::START))
                      {
                        break;
                      }
                    }
                  }
                  if (p0Tag == "''")
                  {
                    for (int pi = index - 1; pi >= 0; pi--)
                    {
                      Parse *p = constituents[pi];
                      if (p->getType() == "``")
                      {
                        features.push_back("quotesmatch");
                        break;
                      }
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'startsWith' method:
                      if (p->getLabel().startsWith(Parser::START))
                      {
                        break;
                      }
                    }
                  }
                  if (p0Tag == "'")
                  {
                    for (int pi = index - 1; pi >= 0; pi--)
                    {
                      Parse *p = constituents[pi];
                      if (p->getType() == "`")
                      {
                        features.push_back("quotesmatch");
                        break;
                      }
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'startsWith' method:
                      if (p->getLabel().startsWith(Parser::START))
                      {
                        break;
                      }
                    }
                  }
                  if (p0Tag == ",")
                  {
                    for (int pi = index - 1; pi >= 0; pi--)
                    {
                      Parse *p = constituents[pi];
                      if (p->getType() == ",")
                      {
                        features.push_back("iscomma");
                        break;
                      }
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'startsWith' method:
                      if (p->getLabel().startsWith(Parser::START))
                      {
                        break;
                      }
                    }
                  }
                  if (p0Tag == "." && index == ps - 1)
                  {
                    for (int pi = index - 1; pi >= 0; pi--)
                    {
                      Parse *p = constituents[pi];
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'startsWith' method:
                      if (p->getLabel().startsWith(Parser::START))
                      {
                        if (pi == 0)
                        {
                          features.push_back("endofsentence");
                        }
                        break;
                      }
                    }
                  }
                  return (features.toArray(new std::string[features.size()]));
                }
            }
        }
    }
}
