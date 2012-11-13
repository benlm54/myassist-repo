#include "Parse.h"
#include "tools/parser/AbstractBottomUpParser.h"
#include "tools/parser/Constituent.h"
#include "tools/parser/lang/en/HeadRules.h"
#include "StringBuffer.h"

namespace opennlp
{
    namespace tools
    {
        namespace parser
        {
            using opennlp::tools::util::Span;
const std::string Parse::BRACKET_LRB = "(";
const std::string Parse::BRACKET_RRB = ")";
const std::string Parse::BRACKET_LCB = "{";
const std::string Parse::BRACKET_RCB = "}";
java::util::regex::Pattern *Parse::typePattern = java::util::regex::Pattern::compile("^([^ =-]+)");
java::util::regex::Pattern *Parse::funTypePattern = java::util::regex::Pattern::compile("^[^ =-]+-([^ =-]+)");
java::util::regex::Pattern *Parse::tokenPattern = java::util::regex::Pattern::compile("^[^ ()]+ ([^ ()]+)\\s*\\)");
bool Parse::useFunctionTags = false;

            Parse::Parse(const std::string &text, Span *span, const std::string &type, double p, int index)
            {
              this->text = text;
              this->span = span;
              this->type = type;
              this->prob = p;
              this->head = this;
              this->headIndex = index;
              this->parts = std::list<Parse*>();
              this->label = "";
//JAVA TO C++ CONVERTER WARNING: Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
              delete this->parent;
            }

            Parse::Parse(const std::string &text, Span *span, const std::string &type, double p, Parse *h)
            {
              if (h != 0)
              {
                this->head = h;
                this->headIndex = h->headIndex;
              }
            }

            void *Parse::clone()
            {
              Parse *p = new Parse(this->text, this->span, this->type, this->prob, this->head);
              p->parts = std::list<Parse*>();
              p->parts->addAll(this->parts);

              if (derivation != 0)
              {
                p->derivation = new StringBuffer(100);
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                p->derivation->append(this->derivation->toString());
              }
              p->label = this->label;
              return (p);
            }

            opennlp::tools::parser::Parse *Parse::clone(Parse *node)
            {
              if (this == node)
              {
                return static_cast<Parse*>(this->clone());
              }
              else
              {
                Parse *c = static_cast<Parse*>(this->clone());
                Parse *lc = c->parts[parts.size() - 1];
                c->parts[parts.size() - 1] = lc->clone(node);
                return c;
              }
            }

            opennlp::tools::parser::Parse *Parse::cloneRoot(Parse *node, int parseIndex)
            {
              Parse *c = static_cast<Parse*>(this->clone());
              Parse *fc = c->parts[parseIndex];
              c->parts[parseIndex] = fc->clone(node);
              return c;
            }

            void Parse::useFunctionTags(bool uft)
            {
              useFunctionTags_Renamed = uft;
            }

            void Parse::setType(const std::string &type)
            {
              this->type = type;
            }

            std::string Parse::getType()
            {
              return type;
            }

            Collection<Parse*> *Parse::getPreviousPunctuationSet()
            {
              return prevPunctSet;
            }

            void Parse::addPreviousPunctuation(Parse *punct)
            {
              if (this->prevPunctSet == 0)
              {
                this->prevPunctSet = new TreeSet<Parse*>();
              }
              prevPunctSet->add(punct);
            }

            Collection<Parse*> *Parse::getNextPunctuationSet()
            {
              return nextPunctSet;
            }

            void Parse::addNextPunctuation(Parse *punct)
            {
              if (this->nextPunctSet == 0)
              {
                this->nextPunctSet = new TreeSet<Parse*>();
              }
              nextPunctSet->add(punct);
            }

            void Parse::setNextPunctuation(Collection<Parse*> *punctSet)
            {
              this->nextPunctSet = punctSet;
            }

            void Parse::setPrevPunctuation(Collection<Parse*> *punctSet)
            {
              this->prevPunctSet = punctSet;
            }

            void Parse::insert(Parse *const constituent)
            {
              Span *ic = constituent->span;
              if (span->contains(ic))
              {
                //double oprob=c.prob;
                int pi = 0;
                int pn = parts.size();
                for (; pi < pn; pi++)
                {
                  Parse *subPart = parts[pi];
                  //System.err.println("Parse.insert:con="+constituent+" sp["+pi+"] "+subPart+" "+subPart.getType());
                  Span *sp = subPart->span;
                  if (sp->getStart() >= ic->getEnd())
                  {
                    break;
                  }
                  // constituent contains subPart
                  else if (ic->contains(sp))
                  {
                    //System.err.println("Parse.insert:con contains subPart");
                    parts.remove(pi);
                    pi--;
                    constituent->parts->push_back(subPart);
                    subPart->setParent(constituent);
                    //System.err.println("Parse.insert: "+subPart.hashCode()+" -> "+subPart.getParent().hashCode());
                    pn = parts.size();
                  }
                  else if (sp->contains(ic))
                  {
                    //System.err.println("Parse.insert:subPart contains con");
                    subPart->insert(constituent);
                    return;
                  }
                }
                //System.err.println("Parse.insert:adding con="+constituent+" to "+this);
                parts.push_back(pi, constituent);
                constituent->setParent(this);
                //System.err.println("Parse.insert: "+constituent.hashCode()+" -> "+constituent.getParent().hashCode());
              }
              else
              {
                throw (InternalError("Inserting constituent not contained in the sentence!"));
              }
            }

            void Parse::show(StringBuffer *sb)
            {
              int start;
              start = span->getStart();
              if (type != AbstractBottomUpParser::TOK_NODE)
              {
                sb->append("(");
                sb->append(type + " ");
                //System.out.print(label+" ");
                //System.out.print(head+" ");
                //System.out.print(df.format(prob)+" ");
              }
              for (std::vector<Parse*>::const_iterator i = parts.begin(); i != parts.end(); ++i)
              {
                Parse *c = *i;
                Span *s = c->span;
                if (start < s->getStart())
                {
                  //System.out.println("pre "+start+" "+s.getStart());
                  sb->append(encodeToken(text.substr(start, s->getStart() - start)));
                }
                c->show(sb);
                start = s->getEnd();
              }
              if (start < span->getEnd())
              {
                sb->append(encodeToken(text.substr(start, span->getEnd() - start)));
              }
              if (type != AbstractBottomUpParser::TOK_NODE)
              {
                sb->append(")");
              }
            }

            void Parse::show()
            {
              StringBuffer *sb = new StringBuffer(text.length()*4);
              show(sb);
              std::cout << sb << std::endl;
            }

            double Parse::getTagSequenceProb()
            {
              //System.err.println("Parse.getTagSequenceProb: "+type+" "+this);
              if (parts.size() == 1 && (parts[0])->type == AbstractBottomUpParser::TOK_NODE)
              {
                //System.err.println(this+" "+prob);
                return (log(prob));
              }
              else if (parts.empty())
              {
                System::err::println("Parse.getTagSequenceProb: Wrong base case!");
                return (0.0);
              }
              else
              {
                double sum = 0.0;
                for (std::vector<Parse*>::const_iterator pi = parts.begin(); pi != parts.end(); ++pi)
                {
                  sum += *pi.getTagSequenceProb();
                }
                return sum;
              }
            }

            bool Parse::complete()
            {
              return (parts.size() == 1);
            }

            std::string Parse::ToString()
            {
              return (text.substr(span->getStart(), span->getEnd() - (span->getStart())));
            }

            std::string Parse::getText()
            {
              return text;
            }

            opennlp::tools::util::Span *Parse::getSpan()
            {
              return span;
            }

            double Parse::getProb()
            {
              return prob;
            }

            void Parse::addProb(double logProb)
            {
              this->prob += logProb;
            }

            Parse *Parse::getChildren()
            {
              return parts.toArray(new Parse[parts.size()]);
            }

            void Parse::setChild(int index, const std::string &label)
            {
              Parse *newChild = static_cast<Parse*>((parts[index])->clone());
              newChild->setLabel(label);
              parts[index] = newChild;
            }

            void Parse::add(Parse *daughter, HeadRules *rules)
            {
              if (daughter->prevPunctSet != 0)
              {
                parts.addAll(daughter->prevPunctSet);
              }
              parts.push_back(daughter);
              this->span = new Span(span->getStart(),daughter->getSpan()->getEnd());
              this->head = rules->getHead(getChildren(),type);
              if (head == 0)
              {
                System::err::println(parts);
              }
              this->headIndex = head->headIndex;
            }

            void Parse::remove(int index)
            {
              parts.remove(index);
              if (index == 0 || index == parts.size()) //size is orig last element
              {
                span = new Span((parts[0])->span->getStart(),(parts[parts.size() - 1])->span->getEnd());
              }
            }

            opennlp::tools::parser::Parse *Parse::adjoinRoot(Parse *node, HeadRules *rules, int parseIndex)
            {
              Parse *lastChild = parts[parseIndex];
              Parse *adjNode = new Parse(this->text,new Span(lastChild->getSpan()->getStart(),node->getSpan()->getEnd()),lastChild->getType(),1,rules->getHead(new Parse[]{lastChild,node},lastChild->getType()));
              adjNode->parts->push_back(lastChild);
              if (node->prevPunctSet != 0)
              {
                adjNode->parts->addAll(node->prevPunctSet);
              }
              adjNode->parts->push_back(node);
              parts[parseIndex] = adjNode;
              return adjNode;
            }

            opennlp::tools::parser::Parse *Parse::adjoin(Parse *sister, HeadRules *rules)
            {
              Parse *lastChild = parts[parts.size() - 1];
              Parse *adjNode = new Parse(this->text,new Span(lastChild->getSpan()->getStart(),sister->getSpan()->getEnd()),lastChild->getType(),1,rules->getHead(new Parse[]{lastChild,sister},lastChild->getType()));
              adjNode->parts->push_back(lastChild);
              if (sister->prevPunctSet != 0)
              {
                adjNode->parts->addAll(sister->prevPunctSet);
              }
              adjNode->parts->push_back(sister);
              parts[parts.size() - 1] = adjNode;
              this->span = new Span(span->getStart(),sister->getSpan()->getEnd());
              this->head = rules->getHead(getChildren(),type);
              this->headIndex = head->headIndex;
              return adjNode;
            }

            void Parse::expandTopNode(Parse *root)
            {
              bool beforeRoot = true;
              //System.err.println("expandTopNode: parts="+parts);
              for (int pi = 0,ai = 0;pi < parts.size();pi++,ai++)
              {
                Parse *node = parts[pi];
                if (node == root)
                {
                  beforeRoot = false;
                }
                else if (beforeRoot)
                {
                  root->parts->push_back(ai,node);
                  parts.remove(pi);
                  pi--;
                }
                else
                {
                  root->parts->push_back(node);
                  parts.remove(pi);
                  pi--;
                }
              }
              root->updateSpan();
            }

            int Parse::getChildCount()
            {
              return parts.size();
            }

            int Parse::indexOf(Parse *child)
            {
              return parts.find(child);
            }

            opennlp::tools::parser::Parse *Parse::getHead()
            {
              return head;
            }

            int Parse::getHeadIndex()
            {
              return headIndex;
            }

            std::string Parse::getLabel()
            {
              return label;
            }

            void Parse::setLabel(const std::string &label)
            {
              this->label = label;
            }

            std::string Parse::getType(const std::string &rest)
            {
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'startsWith' method:
              if (rest.startsWith("-LCB-"))
              {
                return "-LCB-";
              }
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'startsWith' method:
              else if (rest.startsWith("-RCB-"))
              {
                return "-RCB-";
              }
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'startsWith' method:
              else if (rest.startsWith("-LRB-"))
              {
                return "-LRB-";
              }
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'startsWith' method:
              else if (rest.startsWith("-RRB-"))
              {
                return "-RRB-";
              }
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'startsWith' method:
              else if (rest.startsWith("-NONE-"))
              {
                return "-NONE-";
              }
              else
              {
                Matcher *typeMatcher = typePattern->matcher(rest);
                if (typeMatcher->find())
                {
                  std::string type = typeMatcher->group(1);
                  if (useFunctionTags_Renamed)
                  {
                    Matcher *funMatcher = funTypePattern->matcher(rest);
                    if (funMatcher->find())
                    {
                      std::string ftag = funMatcher->group(1);
                      type = type + "-" + ftag;
                    }
                  }
                  return type;
                }
              }
              return 0;
            }

            std::string Parse::encodeToken(const std::string &token)
            {
              if (BRACKET_LRB == token)
              {
                return "-LRB-";
              }
              else if (BRACKET_RRB == token)
              {
                return "-RRB-";
              }
              else if (BRACKET_LCB == token)
              {
                return "-LCB-";
              }
              else if (BRACKET_RCB == token)
              {
                return "-RCB-";
              }

              return token;
            }

            std::string Parse::decodeToken(const std::string &token)
            {
              if ((std::string("-LRB-")) == token)
              {
                return BRACKET_LRB;
              }
              else if ((std::string("-RRB-")) == token)
              {
                return BRACKET_RRB;
              }
              else if ((std::string("-LCB-")) == token)
              {
                return BRACKET_LCB;
              }
              else if ((std::string("-RCB-")) == token)
              {
                return BRACKET_RCB;
              }

              return token;
            }

            std::string Parse::getToken(const std::string &rest)
            {
              Matcher *tokenMatcher = tokenPattern->matcher(rest);
              if (tokenMatcher->find())
              {
                return decodeToken(tokenMatcher->group(1));
              }
              return 0;
            }

            void Parse::updateHeads(HeadRules *rules)
            {
              if (parts.size() > 0 && parts.size() != 0)
              {
                for (int pi = 0,pn = parts.size();pi < pn;pi++)
                {
                  Parse *c = parts[pi];
                  c->updateHeads(rules);
                }
                this->head = rules->getHead(parts.toArray(new Parse[parts.size()]), type);
                if (head == 0)
                {
                  head = this;
                }
                else
                {
                  this->headIndex = head->headIndex;
                }
              }
              else
              {
                this->head = this;
              }
            }

            void Parse::updateSpan()
            {
              span = new Span((parts[0])->span->getStart(),(parts[parts.size() - 1])->span->getEnd());
            }

            void Parse::pruneParse(Parse *parse)
            {
              std::vector<Parse*> nodes = std::list<Parse*>();
              nodes.push_back(parse);
              while (nodes.size() != 0)
              {
                Parse *node = nodes.remove(0);
//ORIGINAL LINE: Parse[] children = node.getChildren();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                Parse *children = node->getChildren();
                if (children->length == 1 && node->getType() == children[0]->getType())
                {
                  int index = node->getParent()->parts->find(node);
                  children[0]->setParent(node->getParent());
                  node->getParent()->parts[index] = children[0];
//JAVA TO C++ CONVERTER WARNING: Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
                  delete node->parent;
                  node->parts->clear();
                }
                nodes.addAll(Arrays::asList(children));
              }
            }

            void Parse::fixPossesives(Parse *parse)
            {
//ORIGINAL LINE: Parse[] tags = parse.getTagNodes();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              Parse *tags = parse->getTagNodes();
              for (int ti = 0;ti < tags->length;ti++)
              {
                if (tags[ti]->getType() == "POS")
                {
                  if (ti + 1 < tags->length && tags[ti + 1]->getParent() == tags[ti]->getParent()->getParent())
                  {
                    int start = tags[ti + 1]->getSpan()->getStart();
                    int end = tags[ti + 1]->getSpan()->getEnd();
                    for (int npi = ti + 2;npi < tags->length;npi++)
                    {
                      if (tags[npi]->getParent() == tags[npi - 1]->getParent())
                      {
                        end = tags[npi]->getSpan()->getEnd();
                      }
                      else
                      {
                        break;
                      }
                    }
                    Parse *npPos = new Parse(parse->getText(),new Span(start,end),"NP",1,tags[ti + 1]);
                    parse->insert(npPos);
                  }
                }
              }
            }

            opennlp::tools::parser::Parse *Parse::parseParse(const std::string &parse)
            {
              return parseParse(parse,0);
            }

            opennlp::tools::parser::Parse *Parse::parseParse(const std::string &parse, GapLabeler *gl)
            {
              StringBuffer *text = new StringBuffer();
              int offset = 0;
              std::stack<Constituent*> stack = std::stack<Constituent*>();
              std::vector<Constituent*> cons = std::list<Constituent*>();
              for (int ci = 0, cl = parse.length(); ci < cl; ci++)
              {
                char c = parse[ci];
                if (c == '(')
                {
                  std::string rest = parse.substr(ci + 1);
                  std::string type = getType(rest);
                  if (type == "")
                  {
                    System::err::println("null type for: " + rest);
                  }
                  std::string token = getToken(rest);
                  stack.push(new Constituent(type, new Span(offset,offset)));
                  if (token != "")
                  {
                    if (type == "-NONE-" && gl != 0)
                    {
                      //System.err.println("stack.size="+stack.size());
                      gl->labelGaps(stack);
                    }
                    else
                    {
                      cons.push_back(new Constituent(AbstractBottomUpParser::TOK_NODE, new Span(offset, offset + token.length())));
                      text->append(token)->append(" ");
                      offset += token.length() + 1;
                    }
                  }
                }
                else if (c == ')')
                {
                  Constituent *con = stack.pop();
                  int start = con->getSpan()->getStart();
                  if (start < offset)
                  {
                    cons.push_back(new Constituent(con->getLabel(), new Span(start, offset - 1)));
                  }
                }
              }
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              std::string txt = text->toString();
              int tokenIndex = -1;
              Parse *p = new Parse(txt, new Span(0, txt.length()), AbstractBottomUpParser::TOP_NODE, 1,0);
              for (int ci = 0;ci < cons.size();ci++)
              {
                Constituent *con = cons[ci];
                std::string type = con->getLabel();
                if (type != AbstractBottomUpParser::TOP_NODE)
                {
                  if (type == AbstractBottomUpParser::TOK_NODE)
                  {
                    tokenIndex++;
                  }
                  Parse *c = new Parse(txt, con->getSpan(), type, 1,tokenIndex);
                  //System.err.println("insert["+ci+"] "+type+" "+c.toString()+" "+c.hashCode());
                  p->insert(c);
                  //codeTree(p);
                }
              }
              return p;
            }

            opennlp::tools::parser::Parse *Parse::getParent()
            {
              return parent;
            }

            void Parse::setParent(Parse *parent)
            {
              this->parent = parent;
            }

            bool Parse::isPosTag()
            {
              return (parts.size() == 1 && (parts[0])->getType() == AbstractBottomUpParser::TOK_NODE);
            }

            bool Parse::isFlat()
            {
              bool flat = true;
              for (int ci = 0;ci < parts.size();ci++)
              {
                flat &= (parts[ci])->isPosTag();
              }
              return flat;
            }

            void Parse::isChunk(bool ic)
            {
              this->isChunk_Renamed = ic;
            }

            bool Parse::isChunk()
            {
              return isChunk_Renamed;
            }

            Parse *Parse::getTagNodes()
            {
              std::vector<Parse*> tags = std::list<Parse*>();
              std::vector<Parse*> nodes = std::list<Parse*>();
              nodes.addAll(this->parts);
              while (nodes.size() != 0)
              {
                Parse *p = nodes.remove(0);
                if (p->isPosTag())
                {
                  tags.push_back(p);
                }
                else
                {
                  nodes.addAll(0,p->parts);
                }
              }
              return tags.toArray(new Parse[tags.size()]);
            }

            opennlp::tools::parser::Parse *Parse::getCommonParent(Parse *node)
            {
              if (this == node)
              {
                return parent;
              }
              Set<Parse*> *parents = std::set<Parse*>();
              Parse *cparent = this;
              while (cparent != 0)
              {
                parents->add(cparent);
                cparent = cparent->getParent();
              }
              while (node != 0)
              {
                if (parents->contains(node))
                {
                  return node;
                }
                node = node->getParent();
              }
              return 0;
            }

            bool Parse::Equals(void *o)
            {
              if (dynamic_cast<Parse*>(o) != 0)
              {
                Parse *p = static_cast<Parse*>(o);
                if (this->label == "")
                {
                  if (p->label != "")
                  {
                    return false;
                  }
                }
                else if (this->label != p->label)
                {
                  return false;
                }
                if (!this->span->equals(p->span))
                {
                  return false;
                }
                if (this->text != p->text)
                {
                  return false;
                }
                if (this->parts.size() != p->parts->size())
                {
                    return false;
                }
                for (int ci = 0;ci < parts.size();ci++)
                {
                  if (!parts[ci]->equals(p->parts[ci]))
                  {
                    return false;
                  }
                }
                return true;
              }
              return false;
            }

            int Parse::GetHashCode()
            {
              int result = 17;
              result = 37*result + span->hashCode();

              // TODO: This might lead to a performance regression
                        //    result = 37*result + label.hashCode();
              result = 37*result + text.hashCode();
              return result;
            }

            int Parse::compareTo(Parse *p)
            {
              if (this->getProb() > p->getProb())
              {
                return -1;
              }
              else if (this->getProb() < p->getProb())
              {
                return 1;
              }
              return 0;
            }

            StringBuffer *Parse::getDerivation()
            {
              return derivation;
            }

            void Parse::setDerivation(StringBuffer *derivation)
            {
              this->derivation = derivation;
            }

            void Parse::codeTree(Parse *p, int levels[])
            {
//ORIGINAL LINE: Parse[] kids = p.getChildren();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              Parse *kids = p->getChildren();
              StringBuffer *levelsBuff = new StringBuffer();
              levelsBuff->append("[");
              int nlevels[sizeof(levels) / sizeof(levels[0]) + 1];
              for (int li = 0;li < sizeof(levels) / sizeof(levels[0]);li++)
              {
                nlevels[li] = levels[li];
                levelsBuff->append(levels[li])->append(".");
              }
              for (int ki = 0;ki < kids->length;ki++)
              {
                nlevels[sizeof(levels) / sizeof(levels[0])] = ki;
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                std::cout << levelsBuff->toString() + ki + "] " + kids[ki]->getType() + " " + kids[ki]->hashCode() + " -> " + kids[ki]->getParent()->hashCode() + " " + kids[ki]->getParent()->getType() + " " + kids[ki]->toString() << std::endl;
                codeTree(kids[ki],nlevels);
              }
            }

            void Parse::showCodeTree()
            {
              codeTree(this,new int[0]);
            }

            void Parse::addNames(const std::string &tag, Span names[], Parse tokens[])
            {
              for (int ni = 0,nn = sizeof(names) / sizeof(names[0]);ni < nn;ni++)
              {
                Span *nameTokenSpan = names[ni];
                Parse *startToken = tokens[nameTokenSpan->getStart()];
                Parse *endToken = tokens[nameTokenSpan->getEnd()];
                Parse *commonParent = startToken->getCommonParent(endToken);
                //System.err.println("addNames: "+startToken+" .. "+endToken+" commonParent = "+commonParent);
                if (commonParent != 0)
                {
                  Span *nameSpan = new Span(startToken->getSpan()->getStart(),endToken->getSpan()->getEnd());
                  if (nameSpan->equals(commonParent->getSpan()))
                  {
                    commonParent->insert(new Parse(commonParent->getText(),nameSpan,tag,1.0,endToken->getHeadIndex()));
                  }
                  else
                  {
//ORIGINAL LINE: Parse[] kids = commonParent.getChildren();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                    Parse *kids = commonParent->getChildren();
                    bool crossingKids = false;
                    for (int ki = 0,kn = kids->length;ki < kn;ki++)
                    {
                      if (nameSpan->crosses(kids[ki]->getSpan()))
                      {
                        crossingKids = true;
                      }
                    }
                    if (!crossingKids)
                    {
                      commonParent->insert(new Parse(commonParent->getText(),nameSpan,tag,1.0,endToken->getHeadIndex()));
                    }
                    else
                    {
                      if (commonParent->getType() == "NP")
                      {
//ORIGINAL LINE: Parse[] grandKids = kids[0].getChildren();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                        Parse *grandKids = kids[0]->getChildren();
                        if (grandKids->length > 1 && nameSpan->contains(grandKids[grandKids->length - 1]->getSpan()))
                        {
                          commonParent->insert(new Parse(commonParent->getText(),commonParent->getSpan(),tag,1.0,commonParent->getHeadIndex()));
                        }
                      }
                    }
                  }
                }
              }
            }

            void Parse::main(std::string args[]) throw(IOException)
            {
              if (sizeof(args) / sizeof(args[0]) == 0)
              {
                System::err::println("Usage: Parse -fun -pos head_rules < train_parses");
                System::err::println("Reads training parses (one-sentence-per-line) and displays parse structure.");
                exit(1);
              }
              int ai = 0;
              bool fixPossesives = false;
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'startsWith' method:
              while (args[ai].startsWith("-") && ai < sizeof(args) / sizeof(args[0]))
              {
                if (args[ai] == "-fun")
                {
                  Parse::useFunctionTags(true);
                  ai++;
                }
                else if (args[ai] == "-pos")
                {
                  fixPossesives = true;
                  ai++;
                }
              }

              opennlp::tools::parser::lang::en::HeadRules *rules = new opennlp::tools::parser::lang::en::HeadRules(args[ai]);
              java::io::BufferedReader *in_Renamed = new java::io::BufferedReader(new java::io::InputStreamReader(System::in));

              for (std::string line = in_Renamed->readLine(); line != ""; line = in_Renamed->readLine())
              {
                Parse *p = Parse::parseParse(line,rules);
                Parse::pruneParse(p);
                if (fixPossesives)
                {
                  Parse::fixPossesives(p);
                }
                p->updateHeads(rules);
                p->show();
                //p.showCodeTree();
              }
            }
        }
    }
}
