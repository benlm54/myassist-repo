#include "HeadRules.h"
#include "tools/parser/chunking/Parser.h"

namespace opennlp
{
    namespace tools
    {
        namespace parser
        {
            namespace lang
            {
                namespace en
                {
                    using opennlp::tools::parser::Constituent;
                    using opennlp::tools::parser::GapLabeler;
                    using opennlp::tools::parser::Parse;
                    using opennlp::tools::parser::chunking::Parser;

                    HeadRules::HeadRule::HeadRule(bool l2r, std::string tags[])
                    {
                      leftToRight = l2r;

                      for (std::string::const_iterator tag = tags->begin(); tag != tags->end(); ++tag)
                      {
                        if (*tag == 0)
                            throw IllegalArgumentException("tags must not contain null values!");
                      }

                      this->tags = tags;
                    }

                    bool HeadRules::HeadRule::Equals(void *obj)
                    {
                      if (obj == this)
                      {
                        return true;
                      }
                      else if (dynamic_cast<HeadRule*>(obj) != 0)
                      {
                        HeadRule *rule = static_cast<HeadRule*>(obj);

                        return (rule->leftToRight == leftToRight) && Arrays::equals(rule->tags, tags);
                      }
                      else
                      {
                        return false;
                      }
                    }

                    HeadRules::HeadRules(const std::string &ruleFile) throw(IOException)
                    {
                    }

                    HeadRules::HeadRules(Reader *rulesReader) throw(IOException)
                    {
                      BufferedReader *in_Renamed = new BufferedReader(rulesReader);
                      readHeadRules(in_Renamed);

                      punctSet = std::set<std::string>();
                      punctSet->add(".");
                      punctSet->add(",");
                      punctSet->add("``");
                      punctSet->add("''");
                      //punctSet.add(":");
                    }

                    Set<std::string> *HeadRules::getPunctuationTags()
                    {
                      return punctSet;
                    }

                    opennlp::tools::parser::Parse *HeadRules::getHead(Parse constituents[], const std::string &type)
                    {
                      if (constituents[0]->getType() == Parser::TOK_NODE)
                      {
                        return 0;
                      }
                      HeadRule *hr;
                      if (type == "NP" || type == "NX")
                      {
                        std::string tags1[7] = {"NN", "NNP", "NNPS", "NNS", "NX", "JJR", "POS"};
                        for (int ci = sizeof(constituents) / sizeof(constituents[0]) - 1; ci >= 0; ci--)
                        {
                          for (int ti = sizeof(tags1) / sizeof(tags1[0]) - 1; ti >= 0; ti--)
                          {
                            if (constituents[ci]->getType() == tags1[ti])
                            {
                              return constituents[ci]->getHead();
                            }
                          }
                        }
                        for (int ci = 0; ci < sizeof(constituents) / sizeof(constituents[0]); ci++)
                        {
                          if (constituents[ci]->getType() == "NP")
                          {
                            return constituents[ci]->getHead();
                          }
                        }
                        std::string tags2[3] = {"$", "ADJP", "PRN"};
                        for (int ci = sizeof(constituents) / sizeof(constituents[0]) - 1; ci >= 0; ci--)
                        {
                          for (int ti = sizeof(tags2) / sizeof(tags2[0]) - 1; ti >= 0; ti--)
                          {
                            if (constituents[ci]->getType() == tags2[ti])
                            {
                              return constituents[ci]->getHead();
                            }
                          }
                        }
                        std::string tags3[4] = {"JJ", "JJS", "RB", "QP"};
                        for (int ci = sizeof(constituents) / sizeof(constituents[0]) - 1; ci >= 0; ci--)
                        {
                          for (int ti = sizeof(tags3) / sizeof(tags3[0]) - 1; ti >= 0; ti--)
                          {
                            if (constituents[ci]->getType() == tags3[ti])
                            {
                              return constituents[ci]->getHead();
                            }
                          }
                        }
                        return constituents[sizeof(constituents) / sizeof(constituents[0]) - 1]->getHead();
                      }
                      else if ((hr = headRules->get(type)) != 0)
                      {
//ORIGINAL LINE: String[] tags = hr.tags;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                        std::string *tags = hr->tags;
                        int cl = sizeof(constituents) / sizeof(constituents[0]);
                        int tl = tags->length;
                        if (hr->leftToRight)
                        {
                          for (int ti = 0; ti < tl; ti++)
                          {
                            for (int ci = 0; ci < cl; ci++)
                            {
                              if (constituents[ci]->getType() == tags[ti])
                              {
                                return constituents[ci]->getHead();
                              }
                            }
                          }
                          return constituents[0]->getHead();
                        }
                        else
                        {
                          for (int ti = 0; ti < tl; ti++)
                          {
                            for (int ci = cl - 1; ci >= 0; ci--)
                            {
                              if (constituents[ci]->getType() == tags[ti])
                              {
                                return constituents[ci]->getHead();
                              }
                            }
                          }
                          return constituents[cl - 1]->getHead();
                        }
                      }
                      return constituents[sizeof(constituents) / sizeof(constituents[0]) - 1]->getHead();
                    }

                    void HeadRules::readHeadRules(BufferedReader *str) throw(IOException)
                    {
                      std::string line;
                      headRules = std::map<std::string, HeadRule*>(30);
                      while ((line = str->readLine()) != "")
                      {
                        StringTokenizer *st = new StringTokenizer(line);
                        std::string num = st->nextToken();
                        std::string type = st->nextToken();
                        std::string dir = st->nextToken();
                        std::string tags[StringConverterHelper::fromString<int>(num) - 2];
                        int ti = 0;
                        while (st->hasMoreTokens())
                        {
                          tags[ti] = st->nextToken();
                          ti++;
                        }
                        headRules->put(type, new HeadRule(dir == "1", tags));
                      }
                    }

                    void HeadRules::labelGaps(std::stack<Constituent*> &stack)
                    {
                      if (stack.size() > 4)
                      {
                        //Constituent con0 = (Constituent) stack.get(stack.size()-1);
                        Constituent *con1 = stack.get(stack.size() - 2);
                        Constituent *con2 = stack.get(stack.size() - 3);
                        Constituent *con3 = stack.get(stack.size() - 4);
                        Constituent *con4 = stack.get(stack.size() - 5);
                        //System.err.println("con0="+con0.label+" con1="+con1.label+" con2="+con2.label+" con3="+con3.label+" con4="+con4.label);
                        //subject extraction
                        if (con1->getLabel() == "NP" && con2->getLabel() == "S" && con3->getLabel() == "SBAR")
                        {
                          con1->setLabel(con1->getLabel() + "-G");
                          con2->setLabel(con2->getLabel() + "-G");
                          con3->setLabel(con3->getLabel() + "-G");
                        }
                        //object extraction
                        else if (con1->getLabel() == "NP" && con2->getLabel() == "VP" && con3->getLabel() == "S" && con4->getLabel() == "SBAR")
                        {
                          con1->setLabel(con1->getLabel() + "-G");
                          con2->setLabel(con2->getLabel() + "-G");
                          con3->setLabel(con3->getLabel() + "-G");
                          con4->setLabel(con4->getLabel() + "-G");
                        }
                      }
                    }

                    void HeadRules::serialize(Writer *writer) throw(IOException)
                    {

                      for (Map<std::string, HeadRule*>::const_iterator type = headRules->begin(); type != headRules->end(); ++type)
                      {

                        HeadRule *headRule = headRules->get(type->first);

                        // write num of tags
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                        writer->write(int::toString(headRule->tags->length + 2));
                        writer->write(' ');

                        // write type
                        writer->write(type->first);
                        writer->write(' ');

                        // write l2r true == 1
                        if (headRule->leftToRight)
                          writer->write("1");
                        else
                          writer->write("0");

                        // write tags
                        for (std::string::const_iterator tag = headRule->tags->begin(); tag != headRule->tags->end(); ++tag)
                        {
                          writer->write(' ');
                          writer->write(*tag);
                        }

                        writer->write('\n');
                      }

                      writer->flush();
                    }

                    bool HeadRules::Equals(void *obj)
                    {
                      if (obj == this)
                      {
                        return true;
                      }
                      else if (dynamic_cast<HeadRules*>(obj) != 0)
                      {
                        HeadRules *rules = static_cast<HeadRules*>(obj);

                        return rules->headRules->equals(headRules) && rules->punctSet->equals(punctSet);
                      }
                      else
                      {
                        return false;
                      }
                    }
                }
            }
        }
    }
}
