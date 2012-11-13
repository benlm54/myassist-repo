#include "AbstractContextGenerator.h"
#include "tools/parser/AbstractBottomUpParser.h"
#include "StringBuilder.h"
#include "StringBuffer.h"

namespace opennlp
{
    namespace tools
    {
        namespace parser
        {

const std::string AbstractContextGenerator::EOS = "eos";

            std::string AbstractContextGenerator::punct(Parse *punct, int i)
            {
              StringBuilder *feat = new StringBuilder(5);
              feat->append(i)->append("=");
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              feat->append(punct->toString());
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              return feat->toString();
            }

            std::string AbstractContextGenerator::punctbo(Parse *punct, int i)
            {
              StringBuffer *feat = new StringBuffer(5);
              feat->append(i)->append("=");
              feat->append(punct->getType());
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              return (feat->toString());
            }

            std::string AbstractContextGenerator::cons(Parse *p, int i)
            {
              StringBuffer *feat = new StringBuffer(20);
              feat->append(i)->append("=");
              if (p != 0)
              {
                if (useLabel && i < 0)
                {
                  feat->append(p->getLabel())->append("|");
                }
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                feat->append(p->getType())->append("|")->append(p->getHead()->toString());
              }
              else
              {
                feat->append(EOS);
              }
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              return (feat->toString());
            }

            std::string AbstractContextGenerator::consbo(Parse *p, int i)
            {
              StringBuffer *feat = new StringBuffer(20);
              feat->append(i)->append("*=");
              if (p != 0)
              {
                if (useLabel && i < 0)
                {
                  feat->append(p->getLabel())->append("|");
                }
                feat->append(p->getType());
              }
              else
              {
                feat->append(EOS);
              }
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              return (feat->toString());
            }

            std::string AbstractContextGenerator::production(Parse *p, bool includePunctuation)
            {
              StringBuffer *production = new StringBuffer(20);
              production->append(p->getType())->append("->");
//ORIGINAL LINE: Parse[] children = AbstractBottomUpParser.collapsePunctuation(p.getChildren(),punctSet);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              Parse *children = AbstractBottomUpParser::collapsePunctuation(p->getChildren(),punctSet);
              for (int ci = 0; ci < children->length; ci++)
              {
                production->append(children[ci]->getType());
                if (ci + 1 != children->length)
                {
                  production->append(",");
                  Collection<Parse*> *nextPunct = children[ci]->getNextPunctuationSet();
                  if (includePunctuation && nextPunct != 0)
                  {
                    //TODO: make sure multiple punctuation comes out the same
                    for (Collection<Parse*>::const_iterator pit = nextPunct->begin(); pit != nextPunct->end(); ++pit)
                    {
                      Parse *punct = *pit;
                      production->append(punct->getType())->append(",");
                    }
                  }
                }
              }
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              return production->toString();
            }

            void AbstractContextGenerator::cons2(std::vector<std::string> &features, Cons *c0, Cons *c1, Collection<Parse*> *punct1s, bool bigram)
            {
              if (punct1s != 0)
              {
                for (Collection<Parse*>::const_iterator pi = punct1s->begin(); pi != punct1s->end(); ++pi)
                {
                  Parse *p = *pi;
                        //        String punct = punct(p,c1.index);
                  std::string punctbo = punctbo(p,c1->index <= 0 ? c1->index - 1 : c1->index);

                  //punctbo(1);
                  features.push_back(punctbo);
                  if (c0->index == 0) //TODO look at removing case
                  {
                    //cons(0)punctbo(1)
                    if (c0->unigram)
                        features.push_back(c0->cons + "," + punctbo);
                    features.push_back(c0->consbo + "," + punctbo);
                  }
                  if (c1->index == 0) //TODO look at removing case
                  {
                    //punctbo(1)cons(1)
                    if (c1->unigram)
                        features.push_back(punctbo + "," + c1->cons);
                    features.push_back(punctbo + "," + c1->consbo);
                  }

                  //cons(0)punctbo(1)cons(1)
                  if (bigram)
                      features.push_back(c0->cons + "," + punctbo + "," + c1->cons);
                  if (c1->unigram)
                      features.push_back(c0->consbo + "," + punctbo + "," + c1->cons);
                  if (c0->unigram)
                      features.push_back(c0->cons + "," + punctbo + "," + c1->consbo);
                  features.push_back(c0->consbo + "," + punctbo + "," + c1->consbo);
                }
              }
              else
              {
                //cons(0),cons(1)
                if (bigram)
                    features.push_back(c0->cons + "," + c1->cons);
                if (c1->unigram)
                    features.push_back(c0->consbo + "," + c1->cons);
                if (c0->unigram)
                    features.push_back(c0->cons + "," + c1->consbo);
                features.push_back(c0->consbo + "," + c1->consbo);
              }
            }

            void AbstractContextGenerator::cons3(std::vector<std::string> &features, Cons *c0, Cons *c1, Cons *c2, Collection<Parse*> *punct1s, Collection<Parse*> *punct2s, bool trigram, bool bigram1, bool bigram2)
            {
              //  features.add("stage=cons(0),cons(1),cons(2)");
              if (punct1s != 0)
              {
                if (c0->index == -2)
                {
                  for (Collection<Parse*>::const_iterator pi = punct1s->begin(); pi != punct1s->end(); ++pi)
                  {
                    Parse *p = *pi;
                        //          String punct = punct(p,c1.index);
                    std::string punctbo = punctbo(p,c1->index <= 0 ? c1->index - 1 : c1->index);
                    //punct(-2)
                    //TODO consider changing
                    //features.add(punct);

                    //punctbo(-2)
                    features.push_back(punctbo);
                  }
                }
              }
              if (punct2s != 0)
              {
                if (c2->index == 2)
                {
                  for (Collection<Parse*>::const_iterator pi = punct2s->begin(); pi != punct2s->end(); ++pi)
                  {
                    Parse *p = *pi;
                        //          String punct = punct(p,c2.index);
                    std::string punctbo = punctbo(p,c2->index <= 0 ? c2->index - 1 : c2->index);
                    //punct(2)
                    //TODO consider changing
                    //features.add(punct);

                    //punctbo(2)
                    features.push_back(punctbo);
                  }
                }
                if (punct1s != 0)
                {
                  //cons(0),punctbo(1),cons(1),punctbo(2),cons(2)
                  for (Collection<Parse*>::const_iterator pi2 = punct2s->begin(); pi2 != punct2s->end(); ++pi2)
                  {
                    std::string punctbo2 = punctbo(*pi2,c2->index <= 0 ? c2->index - 1 : c2->index);
                    for (Collection<Parse*>::const_iterator pi1 = punct1s->begin(); pi1 != punct1s->end(); ++pi1)
                    {
                      std::string punctbo1 = punctbo(*pi1,c1->index <= 0 ? c1->index - 1 : c1->index);
                      if (trigram)
                          features.push_back(c0->cons + "," + punctbo1 + "," + c1->cons + "," + punctbo2 + "," + c2->cons);

                      if (bigram2)
                          features.push_back(c0->consbo + "," + punctbo1 + "," + c1->cons + "," + punctbo2 + "," + c2->cons);
                      if (c0->unigram && c2->unigram)
                          features.push_back(c0->cons + "," + punctbo1 + "," + c1->consbo + "," + punctbo2 + "," + c2->cons);
                      if (bigram1)
                          features.push_back(c0->cons + "," + punctbo1 + "," + c1->cons + "," + punctbo2 + "," + c2->consbo);

                      if (c2->unigram)
                          features.push_back(c0->consbo + "," + punctbo1 + "," + c1->consbo + "," + punctbo2 + "," + c2->cons);
                      if (c1->unigram)
                          features.push_back(c0->consbo + "," + punctbo1 + "," + c1->cons + "," + punctbo2 + "," + c2->consbo);
                      if (c0->unigram)
                          features.push_back(c0->cons + "," + punctbo1 + "," + c1->consbo + "," + punctbo2 + "," + c2->consbo);

                      features.push_back(c0->consbo + "," + punctbo1 + "," + c1->consbo + "," + punctbo2 + "," + c2->consbo);
                      if (zeroBackOff)
                      {
                        if (bigram1)
                            features.push_back(c0->cons + "," + punctbo1 + "," + c1->cons + "," + punctbo2);
                        if (c1->unigram)
                            features.push_back(c0->consbo + "," + punctbo1 + "," + c1->cons + "," + punctbo2);
                        if (c0->unigram)
                            features.push_back(c0->cons + "," + punctbo1 + "," + c1->consbo + "," + punctbo2);
                        features.push_back(c0->consbo + "," + punctbo1 + "," + c1->consbo + "," + punctbo2);
                      }
                    }
                  }
                }
                else //punct1s == null
                {
                  //cons(0),cons(1),punctbo(2),cons(2)
                  for (Collection<Parse*>::const_iterator pi2 = punct2s->begin(); pi2 != punct2s->end(); ++pi2)
                  {
                    std::string punctbo2 = punctbo(*pi2,c2->index <= 0 ? c2->index - 1 : c2->index);
                    if (trigram)
                        features.push_back(c0->cons + "," + c1->cons + "," + punctbo2 + "," + c2->cons);

                    if (bigram2)
                        features.push_back(c0->consbo + "," + c1->cons + "," + punctbo2 + "," + c2->cons);
                    if (c0->unigram && c2->unigram)
                        features.push_back(c0->cons + "," + c1->consbo + "," + punctbo2 + "," + c2->cons);
                    if (bigram1)
                        features.push_back(c0->cons + "," + c1->cons + "," + punctbo2 + "," + c2->consbo);

                    if (c2->unigram)
                        features.push_back(c0->consbo + "," + c1->consbo + "," + punctbo2 + "," + c2->cons);
                    if (c1->unigram)
                        features.push_back(c0->consbo + "," + c1->cons + "," + punctbo2 + "," + c2->consbo);
                    if (c0->unigram)
                        features.push_back(c0->cons + "," + c1->consbo + "," + punctbo2 + "," + c2->consbo);

                    features.push_back(c0->consbo + "," + c1->consbo + "," + punctbo2 + "," + c2->consbo);

                    if (zeroBackOff)
                    {
                      if (bigram1)
                          features.push_back(c0->cons + "," + c1->cons + "," + punctbo2);
                      if (c1->unigram)
                          features.push_back(c0->consbo + "," + c1->cons + "," + punctbo2);
                      if (c0->unigram)
                          features.push_back(c0->cons + "," + c1->consbo + "," + punctbo2);
                      features.push_back(c0->consbo + "," + c1->consbo + "," + punctbo2);
                    }
                  }
                }
              }
              else
              {
                if (punct1s != 0)
                {
                  //cons(0),punctbo(1),cons(1),cons(2)
                  for (Collection<Parse*>::const_iterator pi1 = punct1s->begin(); pi1 != punct1s->end(); ++pi1)
                  {
                    std::string punctbo1 = punctbo(*pi1,c1->index <= 0 ? c1->index - 1 : c1->index);
                    if (trigram)
                        features.push_back(c0->cons + "," + punctbo1 + "," + c1->cons + "," + c2->cons);

                    if (bigram2)
                        features.push_back(c0->consbo + "," + punctbo1 + "," + c1->cons + "," + c2->cons);
                    if (c0->unigram && c2->unigram)
                        features.push_back(c0->cons + "," + punctbo1 + "," + c1->consbo + "," + c2->cons);
                    if (bigram1)
                        features.push_back(c0->cons + "," + punctbo1 + "," + c1->cons + "," + c2->consbo);

                    if (c2->unigram)
                        features.push_back(c0->consbo + "," + punctbo1 + "," + c1->consbo + "," + c2->cons);
                    if (c1->unigram)
                        features.push_back(c0->consbo + "," + punctbo1 + "," + c1->cons + "," + c2->consbo);
                    if (c0->unigram)
                        features.push_back(c0->cons + "," + punctbo1 + "," + c1->consbo + "," + c2->consbo);

                    features.push_back(c0->consbo + "," + punctbo1 + "," + c1->consbo + "," + c2->consbo);

                    //zero backoff case covered by cons(0)cons(1)
                  }
                }
                else
                {
                  //cons(0),cons(1),cons(2)
                  if (trigram)
                      features.push_back(c0->cons + "," + c1->cons + "," + c2->cons);

                  if (bigram2)
                      features.push_back(c0->consbo + "," + c1->cons + "," + c2->cons);
                  if (c0->unigram && c2->unigram)
                      features.push_back(c0->cons + "," + c1->consbo + "," + c2->cons);
                  if (bigram1)
                      features.push_back(c0->cons + "," + c1->cons + "," + c2->consbo);

                  if (c2->unigram)
                      features.push_back(c0->consbo + "," + c1->consbo + "," + c2->cons);
                  if (c1->unigram)
                      features.push_back(c0->consbo + "," + c1->cons + "," + c2->consbo);
                  if (c0->unigram)
                      features.push_back(c0->cons + "," + c1->consbo + "," + c2->consbo);

                  features.push_back(c0->consbo + "," + c1->consbo + "," + c2->consbo);
                }
              }
            }

            void AbstractContextGenerator::surround(Parse *node, int i, const std::string &type, Collection<Parse*> *punctuation, std::vector<std::string> &features)
            {
              StringBuffer *feat = new StringBuffer(20);
              feat->append("s")->append(i)->append("=");
              if (punctuation != 0)
              {
                for (Collection<Parse*>::const_iterator pi = punctuation->begin(); pi != punctuation->end(); ++pi)
                {
                  Parse *punct = *pi;
                  if (node != 0)
                  {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                    feat->append(node->getHead()->toString())->append("|")->append(type)->append("|")->append(node->getType())->append("|")->append(punct->getType());
                  }
                  else
                  {
                    feat->append(type)->append("|")->append(EOS)->append("|")->append(punct->getType());
                  }
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                  features.push_back(feat->toString());

                  feat->setLength(0);
                  feat->append("s")->append(i)->append("*=");
                  if (node != 0)
                  {
                    feat->append(type)->append("|")->append(node->getType())->append("|")->append(punct->getType());
                  }
                  else
                  {
                    feat->append(type)->append("|")->append(EOS)->append("|")->append(punct->getType());
                  }
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                  features.push_back(feat->toString());

                  feat->setLength(0);
                  feat->append("s")->append(i)->append("*=");
                  feat->append(type)->append("|")->append(punct->getType());
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                  features.push_back(feat->toString());
                }
              }
              else
              {
                if (node != 0)
                {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                  feat->append(node->getHead()->toString())->append("|")->append(type)->append("|")->append(node->getType());
                }
                else
                {
                  feat->append(type)->append("|")->append(EOS);
                }
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                features.push_back(feat->toString());
                feat->setLength(0);
                feat->append("s")->append(i)->append("*=");
                if (node != 0)
                {
                  feat->append(type)->append("|")->append(node->getType());
                }
                else
                {
                  feat->append(type)->append("|")->append(EOS);
                }
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                features.push_back(feat->toString());
              }
            }

            void AbstractContextGenerator::checkcons(Parse *child, const std::string &i, const std::string &type, std::vector<std::string> &features)
            {
              StringBuffer *feat = new StringBuffer(20);
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              feat->append("c")->append(i)->append("=")->append(child->getType())->append("|")->append(child->getHead()->toString())->append("|")->append(type);
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              features.push_back(feat->toString());
              feat->setLength(0);
              feat->append("c")->append(i)->append("*=")->append(child->getType())->append("|")->append(type);
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              features.push_back(feat->toString());
            }

            void AbstractContextGenerator::checkcons(Parse *p1, Parse *p2, const std::string &type, std::vector<std::string> &features)
            {
              StringBuffer *feat = new StringBuffer(20);
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              feat->append("cil=")->append(type)->append(",")->append(p1->getType())->append("|")->append(p1->getHead()->toString())->append(",")->append(p2->getType())->append("|")->append(p2->getHead()->toString());
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              features.push_back(feat->toString());
              feat->setLength(0);
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              feat->append("ci*l=")->append(type)->append(",")->append(p1->getType())->append(",")->append(p2->getType())->append("|")->append(p2->getHead()->toString());
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              features.push_back(feat->toString());
              feat->setLength(0);
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              feat->append("cil*=")->append(type)->append(",")->append(p1->getType())->append("|")->append(p1->getHead()->toString())->append(",")->append(p2->getType());
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              features.push_back(feat->toString());
              feat->setLength(0);
              feat->append("ci*l*=")->append(type)->append(",")->append(p1->getType())->append(",")->append(p2->getType());
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              features.push_back(feat->toString());
            }

            void AbstractContextGenerator::getFrontierNodes(std::vector<Parse*> &rf, Parse nodes[])
            {
              int leftIndex = 0;
              int prevHeadIndex = -1;

              for (int fi = 0;fi < rf.size();fi++)
              {
                Parse *fn = rf[fi];
                int headIndex = fn->getHeadIndex();
                if (headIndex != prevHeadIndex)
                {
                  nodes[leftIndex] = fn;
                  leftIndex++;
                  prevHeadIndex = headIndex;
                  if (leftIndex == sizeof(nodes) / sizeof(nodes[0]))
                  {
                    break;
                  }
                }
              }
              for (int ni = leftIndex;ni < sizeof(nodes) / sizeof(nodes[0]);ni++)
              {
//JAVA TO C++ CONVERTER WARNING: Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
                delete nodes[ni];
              }
            }
        }
    }
}
