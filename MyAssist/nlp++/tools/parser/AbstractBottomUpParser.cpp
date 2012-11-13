#include "AbstractBottomUpParser.h"
#include "tools/util/ListHeap.h"
#include "tools/util/Sequence.h"
#include "tools/util/Span.h"
#include "tools/ngram/NGramModel.h"
#include "tools/util/StringList.h"
#include "tools/parser/chunking/ParserEventStream.h"
#include "const_iterator.h"

namespace opennlp
{
    namespace tools
    {
        namespace parser
        {
            using opennlp::tools::chunker::Chunker;
            using opennlp::tools::dictionary::Dictionary;
            using opennlp::tools::ngram::NGramModel;
            using opennlp::tools::parser::chunking::ParserEventStream;
            using opennlp::tools::postag::POSTagger;
            using opennlp::tools::util::Heap;
            using opennlp::tools::util::ListHeap;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::Sequence;
            using opennlp::tools::util::Span;
            using opennlp::tools::util::StringList;
            using opennlp::tools::util::TrainingParameters;
const double AbstractBottomUpParser::defaultAdvancePercentage = 0.95;
const std::string AbstractBottomUpParser::TOP_NODE = "TOP";
const std::string AbstractBottomUpParser::INC_NODE = "INC";
const std::string AbstractBottomUpParser::TOK_NODE = "TK";
const std::string AbstractBottomUpParser::START = "S-";
const std::string AbstractBottomUpParser::CONT = "C-";
const std::string AbstractBottomUpParser::OTHER = "O";
const std::string AbstractBottomUpParser::COMPLETE = "c";
const std::string AbstractBottomUpParser::INCOMPLETE = "i";

            AbstractBottomUpParser::AbstractBottomUpParser(POSTagger *tagger, Chunker *chunker, HeadRules *headRules, int beamSize, double advancePercentage)
            {
              InitializeInstanceFields();
              this->tagger = tagger;
              this->chunker = chunker;
              this->M = beamSize;
              this->K = beamSize;
              this->Q = advancePercentage;
              reportFailedParse = true;
              this->headRules = headRules;
              this->punctSet = headRules->getPunctuationTags();
              odh = new ListHeap<Parse*>(K);
              ndh = new ListHeap<Parse*>(K);
              completeParses = new ListHeap<Parse*>(K);
            }

            void AbstractBottomUpParser::setErrorReporting(bool errorReporting)
            {
              this->reportFailedParse = errorReporting;
            }

            void AbstractBottomUpParser::setParents(Parse *p)
            {
//ORIGINAL LINE: Parse[] children = p.getChildren();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              Parse *children = p->getChildren();
              for (int ci = 0; ci < children->length; ci++)
              {
                children[ci]->setParent(p);
                setParents(children[ci]);
              }
            }

            Parse *AbstractBottomUpParser::collapsePunctuation(Parse chunks[], Set<std::string> *punctSet)
            {
              std::vector<Parse*> collapsedParses = std::vector<Parse*>(sizeof(chunks) / sizeof(chunks[0]));
              int lastNonPunct = -1;
              int nextNonPunct = -1;
              for (int ci = 0,cn = sizeof(chunks) / sizeof(chunks[0]);ci < cn;ci++)
              {
                if (punctSet->contains(chunks[ci]->getType()))
                {
                  if (lastNonPunct >= 0)
                  {
                    chunks[lastNonPunct]->addNextPunctuation(chunks[ci]);
                  }
                  for (nextNonPunct = ci + 1;nextNonPunct < cn;nextNonPunct++)
                  {
                    if (!punctSet->contains(chunks[nextNonPunct]->getType()))
                    {
                      break;
                    }
                  }
                  if (nextNonPunct < cn)
                  {
                    chunks[nextNonPunct]->addPreviousPunctuation(chunks[ci]);
                  }
                }
                else
                {
                  collapsedParses.push_back(chunks[ci]);
                  lastNonPunct = ci;
                }
              }
              if (collapsedParses.size() == sizeof(chunks) / sizeof(chunks[0]))
              {
                return chunks;
              }
              //System.err.println("collapsedPunctuation: collapsedParses"+collapsedParses);
              return collapsedParses.toArray(new Parse[collapsedParses.size()]);
            }

            Parse *AbstractBottomUpParser::parse(Parse *tokens, int numParses)
            {
              if (createDerivationString)
                  tokens->setDerivation(new StringBuffer(100));
              odh->clear();
              ndh->clear();
              completeParses->clear();
              int derivationStage = 0; //derivation length
              int maxDerivationLength = 2 * tokens->getChildCount() + 3;
              odh->add(tokens);
              Parse *guess = 0;
              double minComplete = 2;
              double bestComplete = -100000; //approximating -infinity/0 in ln domain
              while (odh->size() > 0 && (completeParses->size() < M || (odh->first())->getProb() < minComplete) && derivationStage < maxDerivationLength)
              {
                ndh = new ListHeap<Parse*>(K);

                int derivationRank = 0;
//JAVA TO C++ CONVERTER TODO TASK: Java iterators are only converted within the context of 'while' and 'for' loops:
                for (Heap<Parse*>::const_iterator pi = odh->begin(); pi->hasNext() && derivationRank < K; derivationRank++) // forearch derivation
                {
//JAVA TO C++ CONVERTER TODO TASK: Java iterators are only converted within the context of 'while' and 'for' loops:
                  Parse *tp = pi->next();
                  //TODO: Need to look at this for K-best parsing cases
                  /*
                   if (tp.getProb() < bestComplete) { //this parse and the ones which follow will never win, stop advancing.
                   break;
                   }
                   */
                  if (guess == 0 && derivationStage == 2)
                  {
                    guess = tp;
                  }
                  if (debugOn)
                  {
                    std::cout << derivationStage + " " + derivationRank + " " + tp->getProb();
                    tp->show();
                    std::cout << std::endl;
                  }
//ORIGINAL LINE: Parse[] nd;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                  Parse *nd;
                  if (0 == derivationStage)
                  {
                    nd = advanceTags(tp);
                  }
                  else if (1 == derivationStage)
                  {
                    if (ndh->size() < K)
                    {
                      //System.err.println("advancing ts "+j+" "+ndh.size()+" < "+K);
                      nd = advanceChunks(tp,bestComplete);
                    }
                    else
                    {
                      //System.err.println("advancing ts "+j+" prob="+((Parse) ndh.last()).getProb());
                      nd = advanceChunks(tp,(ndh->last())->getProb());
                    }
                  }
                  else // i > 1
                  {
                    nd = advanceParses(tp, Q);
                  }
                  if (nd != 0)
                  {
                    for (int k = 0, kl = nd->length; k < kl; k++)
                    {
                      if (nd[k]->complete())
                      {
                        advanceTop(nd[k]);
                        if (nd[k]->getProb() > bestComplete)
                        {
                          bestComplete = nd[k]->getProb();
                        }
                        if (nd[k]->getProb() < minComplete)
                        {
                          minComplete = nd[k]->getProb();
                        }
                        completeParses->add(nd[k]);
                      }
                      else
                      {
                        ndh->add(nd[k]);
                      }
                    }
                  }
                  else
                  {
                    if (reportFailedParse)
                    {
                      System::err::println("Couldn't advance parse " + derivationStage + " stage " + derivationRank + "!\n");
                    }
                    advanceTop(tp);
                    completeParses->add(tp);
                  }
                }
                derivationStage++;
                odh = ndh;
              }
              if (completeParses->size() == 0)
              {
                if (reportFailedParse)
                    System::err::println("Couldn't find parse for: " + tokens);
                //Parse r = (Parse) odh.first();
                //r.show();
                //System.out.println();
                return new Parse[] {guess};
              }
              else if (numParses == 1)
              {
                return new Parse[] {completeParses->first()};
              }
              else
              {
                std::vector<Parse*> topParses = std::vector<Parse*>(numParses);
                while (!completeParses->isEmpty() && topParses.size() < numParses)
                {
                  Parse *tp = completeParses->extract();
                  topParses.push_back(tp);
                  //parses.remove(tp);
                }
                return topParses.toArray(new Parse[topParses.size()]);
              }
            }

            opennlp::tools::parser::Parse *AbstractBottomUpParser::parse(Parse *tokens)
            {
              Parse *p = parse(tokens,1)[0];
              setParents(p);
              return p;
            }

            Parse *AbstractBottomUpParser::advanceChunks(Parse *const p, double minChunkScore)
            {
              // chunk
//ORIGINAL LINE: Parse[] children = p.getChildren();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              Parse *children = p->getChildren();
              std::string words[children->length];
              std::string ptags[sizeof(words) / sizeof(words[0])];
              double probs[sizeof(words) / sizeof(words[0])];
              Parse *sp = 0;
              for (int i = 0, il = children->length; i < il; i++)
              {
                sp = children[i];
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                words[i] = sp->getHead()->toString();
                ptags[i] = sp->getType();
              }
              //System.err.println("adjusted mcs = "+(minChunkScore-p.getProb()));
//ORIGINAL LINE: opennlp.tools.util.Sequence[] cs = chunker.topKSequences(words, ptags,minChunkScore-p.getProb());
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              Sequence *cs = chunker->topKSequences(words, ptags,minChunkScore - p->getProb());
              Parse newParses[cs->length];
              for (int si = 0, sl = cs->length; si < sl; si++)
              {
                newParses[si] = static_cast<Parse*>(p->clone()); //copies top level
                if (createDerivationString)
                    newParses[si]->getDerivation()->append(si)->append(".");
//ORIGINAL LINE: String[] tags = cs[si].getOutcomes().toArray(new String[words.length]);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                std::string *tags = cs[si]->getOutcomes()->toArray(new std::string[sizeof(words) / sizeof(words[0])]);
                cs[si]->getProbs(probs);
                int start = -1;
                int end = 0;
                std::string type = "";
                //System.err.print("sequence "+si+" ");
                for (int j = 0; j <= tags->length; j++)
                {
                  //if (j != tags.length) {System.err.println(words[j]+" "+ptags[j]+" "+tags[j]+" "+probs.get(j));}
                  if (j != tags->length)
                  {
                    newParses[si]->addProb(log(probs[j]));
                  }
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'startsWith' method:
                  if (j != tags->length && tags[j].startsWith(CONT)) // if continue just update end chunking tag don't use contTypeMap
                  {
                    end = j;
                  }
                  else //make previous constituent if it exists
                  {
                    if (type != "")
                    {
                      //System.err.println("inserting tag "+tags[j]);
                      Parse *p1 = p->getChildren()[start];
                      Parse *p2 = p->getChildren()[end];
                      //System.err.println("Putting "+type+" at "+start+","+end+" for "+j+" "+newParses[si].getProb());
                      Parse cons[end - start + 1];
                      cons[0] = p1;
                      //cons[0].label="Start-"+type;
                      if (end - start != 0)
                      {
                        cons[end - start] = p2;
                        //cons[end-start].label="Cont-"+type;
                        for (int ci = 1; ci < end - start; ci++)
                        {
                          cons[ci] = p->getChildren()[ci + start];
                          //cons[ci].label="Cont-"+type;
                        }
                      }
                      Parse *chunk = new Parse(p1->getText(), new Span(p1->getSpan()->getStart(), p2->getSpan()->getEnd()), type, 1, headRules->getHead(cons, type));
                      chunk->isChunk(true);
                      newParses[si]->insert(chunk);
                    }
                    if (j != tags->length) //update for new constituent
                    {
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'startsWith' method:
                      if (tags[j].startsWith(START)) // don't use startTypeMap these are chunk tags
                      {
                        type = tags[j].substr(START.length());
                        start = j;
                        end = j;
                      }
                      else // other
                      {
                        type = "";
                      }
                    }
                  }
                }
                //newParses[si].show();System.out.println();
              }
              return newParses;
            }

            Parse *AbstractBottomUpParser::advanceTags(Parse *const p)
            {
//ORIGINAL LINE: Parse[] children = p.getChildren();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              Parse *children = p->getChildren();
              std::string words[children->length];
              double probs[sizeof(words) / sizeof(words[0])];
              for (int i = 0,il = children->length; i < il; i++)
              {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                words[i] = children[i]->toString();
              }
//ORIGINAL LINE: opennlp.tools.util.Sequence[] ts = tagger.topKSequences(words);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              Sequence *ts = tagger->topKSequences(words);
              if (ts->length == 0)
              {
                System::err::println("no tag sequence");
              }
              Parse newParses[ts->length];
              for (int i = 0; i < ts->length; i++)
              {
//ORIGINAL LINE: String[] tags = ts[i].getOutcomes().toArray(new String[words.length]);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                std::string *tags = ts[i]->getOutcomes()->toArray(new std::string[sizeof(words) / sizeof(words[0])]);
                ts[i]->getProbs(probs);
                newParses[i] = static_cast<Parse*>(p->clone()); //copies top level
                if (createDerivationString)
                    newParses[i]->getDerivation()->append(i)->append(".");
                for (int j = 0; j < sizeof(words) / sizeof(words[0]); j++)
                {
                  Parse *word = children[j];
                  //System.err.println("inserting tag "+tags[j]);
                  double prob = probs[j];
                  newParses[i]->insert(new Parse(word->getText(), word->getSpan(), tags[j], prob,j));
                  newParses[i]->addProb(log(prob));
                  //newParses[i].show();
                }
              }
              return newParses;
            }

            int AbstractBottomUpParser::mapParseIndex(int index, Parse nonPunctParses[], Parse parses[])
            {
              int parseIndex = index;
              while (parses[parseIndex] != nonPunctParses[index])
              {
                parseIndex++;
              }
              return parseIndex;
            }

            bool AbstractBottomUpParser::lastChild(Parse *child, Parse *parent, Set<std::string> *punctSet)
            {
//ORIGINAL LINE: Parse[] kids = collapsePunctuation(parent.getChildren(), punctSet);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              Parse *kids = collapsePunctuation(parent->getChildren(), punctSet);
              return (kids[kids->length - 1] == child);
            }

            opennlp::tools::dictionary::Dictionary *AbstractBottomUpParser::buildDictionary(ObjectStream<Parse*> *data, HeadRules *rules, TrainingParameters *params) throw(IOException)
            {

              int cutoff = 5;

              std::string cutoffString = params->getSettings("dict")->get(TrainingParameters::CUTOFF_PARAM);

              if (cutoffString != "")
              {
                // TODO: Maybe throw illegal argument exception if not parse able
                cutoff = StringConverterHelper::fromString<int>(cutoffString);
              }

              NGramModel *mdict = new NGramModel();
              Parse *p;
              while ((p = data->read()) != 0)
              {
                p->updateHeads(rules);
//ORIGINAL LINE: Parse[] pwords = p.getTagNodes();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                Parse *pwords = p->getTagNodes();
                std::string words[pwords->length];
                //add all uni-grams
                for (int wi = 0;wi < sizeof(words) / sizeof(words[0]);wi++)
                {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                  words[wi] = pwords[wi]->toString();
                }

                mdict->add(new StringList(words), 1, 1);
                //add tri-grams and bi-grams for inital sequence
//ORIGINAL LINE: Parse[] chunks = collapsePunctuation(opennlp.tools.parser.chunking.ParserEventStream.getInitialChunks(p),rules.getPunctuationTags());
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                Parse *chunks = collapsePunctuation(ParserEventStream::getInitialChunks(p),rules->getPunctuationTags());
                std::string cwords[chunks->length];
                for (int wi = 0;wi < sizeof(cwords) / sizeof(cwords[0]);wi++)
                {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                  cwords[wi] = chunks[wi]->getHead()->toString();
                }
                mdict->add(new StringList(cwords), 2, 3);

                //emulate reductions to produce additional n-grams
                int ci = 0;
                while (ci < chunks->length)
                {
                  //System.err.println("chunks["+ci+"]="+chunks[ci].getHead().toString()+" chunks.length="+chunks.length);
                  if (lastChild(chunks[ci], chunks[ci]->getParent(),rules->getPunctuationTags()))
                  {
                    //perform reduce
                    int reduceStart = ci;
                    while (reduceStart >= 0 && chunks[reduceStart]->getParent() == chunks[ci]->getParent())
                    {
                      reduceStart--;
                    }
                    reduceStart++;
                    chunks = ParserEventStream::reduceChunks(chunks,ci,chunks[ci]->getParent());
                    ci = reduceStart;
                    if (chunks->length != 0)
                    {
                      std::string window[5];
                      int wi = 0;
                      if (ci - 2 >= 0)
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                          window[wi++] = chunks[ci - 2]->getHead()->toString();
                      if (ci - 1 >= 0)
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                          window[wi++] = chunks[ci - 1]->getHead()->toString();
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                      window[wi++] = chunks[ci]->getHead()->toString();
                      if (ci + 1 < chunks->length)
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                          window[wi++] = chunks[ci + 1]->getHead()->toString();
                      if (ci + 2 < chunks->length)
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                          window[wi++] = chunks[ci + 2]->getHead()->toString();
                      if (wi < 5)
                      {
                        std::string subWindow[wi];
                        for (int swi = 0;swi < wi;swi++)
                        {
                          subWindow[swi] = window[swi];
                        }
                        window = subWindow;
                      }
                      if (sizeof(window) / sizeof(window[0]) >= 3)
                      {
                        mdict->add(new StringList(window), 2, 3);
                      }
                      else if (sizeof(window) / sizeof(window[0]) == 2)
                      {
                        mdict->add(new StringList(window), 2, 2);
                      }
                    }
                    ci = reduceStart - 1; //ci will be incremented at end of loop
                  }
                  ci++;
                }
              }
              //System.err.println("gas,and="+mdict.getCount((new TokenList(new String[] {"gas","and"}))));
              mdict->cutoff(cutoff, int::MAX_VALUE);
              return mdict->toDictionary(true);
            }

            opennlp::tools::dictionary::Dictionary *AbstractBottomUpParser::buildDictionary(ObjectStream<Parse*> *data, HeadRules *rules, int cutoff) throw(IOException)
            {

              TrainingParameters *params = new TrainingParameters();
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              params->put("dict", TrainingParameters::CUTOFF_PARAM, int::toString(cutoff));

              return buildDictionary(data, rules, params);
            }

            void AbstractBottomUpParser::InitializeInstanceFields()
            {
                createDerivationString = false;
                debugOn = false;
            }
        }
    }
}
