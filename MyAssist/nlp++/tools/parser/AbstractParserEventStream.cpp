#include "AbstractParserEventStream.h"
#include "tools/parser/ChunkContextGenerator.h"
#include "tools/postag/DefaultPOSContextGenerator.h"
#include "tools/parser/chunking/Parser.h"
#include "tools/parser/AbstractBottomUpParser.h"

namespace opennlp
{
    namespace tools
    {
        namespace parser
        {
            using opennlp::model::Event;
            using opennlp::tools::chunker::ChunkerContextGenerator;
            using opennlp::tools::dictionary::Dictionary;
            using opennlp::tools::parser::chunking::Parser;
            using opennlp::tools::postag::DefaultPOSContextGenerator;
            using opennlp::tools::postag::POSContextGenerator;
            using opennlp::tools::util::ObjectStream;

            AbstractParserEventStream::AbstractParserEventStream(ObjectStream<Parse*> *d, HeadRules *rules, ParserEventTypeEnum etype, Dictionary *dict) : opennlp.tools.util.AbstractEventStream<Parse>(d)
            {
              this->dict = dict;
              if (etype == CHUNK)
              {
                this->chunkerContextGenerator = new ChunkContextGenerator();
              }
              else if (etype == TAG)
              {
                this->tagContextGenerator = new DefaultPOSContextGenerator(0);
              }
              this->rules = rules;
              punctSet = rules->getPunctuationTags();
              this->etype = etype;

              init();
            }

            Iterator<Event*> *AbstractParserEventStream::createEvents(Parse *sample)
            {
              std::vector<Event*> newEvents = std::vector<Event*>();

              Parse::pruneParse(sample);
              if (fixPossesives)
              {
                Parse::fixPossesives(sample);
              }
              sample->updateHeads(rules);
//ORIGINAL LINE: Parse[] chunks = getInitialChunks(sample);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              Parse *chunks = getInitialChunks(sample);
              if (etype == TAG)
              {
                addTagEvents(newEvents, chunks);
              }
              else if (etype == CHUNK)
              {
                addChunkEvents(newEvents, chunks);
              }
              else
              {
                addParseEvents(newEvents, Parser::collapsePunctuation(chunks,punctSet));
              }

              return newEvents.begin();
            }

            void AbstractParserEventStream::init()
            {
              fixPossesives = false;
            }

            AbstractParserEventStream::AbstractParserEventStream(ObjectStream<Parse*> *d, HeadRules *rules, ParserEventTypeEnum etype)
            {
            }

            Parse *AbstractParserEventStream::getInitialChunks(Parse *p)
            {
              std::vector<Parse*> chunks = std::vector<Parse*>();
              getInitialChunks(p, chunks);
              return chunks.toArray(new Parse[chunks.size()]);
            }

            void AbstractParserEventStream::getInitialChunks(Parse *p, std::vector<Parse*> &ichunks)
            {
              if (p->isPosTag())
              {
                ichunks.push_back(p);
              }
              else
              {
//ORIGINAL LINE: Parse[] kids = p.getChildren();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                Parse *kids = p->getChildren();
                bool allKidsAreTags = true;
                for (int ci = 0, cl = kids->length; ci < cl; ci++)
                {
                  if (!kids[ci]->isPosTag())
                  {
                    allKidsAreTags = false;
                    break;
                  }
                }
                if (allKidsAreTags)
                {
                  ichunks.push_back(p);
                }
                else
                {
                  for (int ci = 0, cl = kids->length; ci < cl; ci++)
                  {
                    getInitialChunks(kids[ci], ichunks);
                  }
                }
              }
            }

            void AbstractParserEventStream::addChunkEvents(std::vector<Event*> &chunkEvents, Parse chunks[])
            {
              std::vector<std::string> toks = std::vector<std::string>();
              std::vector<std::string> tags = std::vector<std::string>();
              std::vector<std::string> preds = std::vector<std::string>();
              for (int ci = 0, cl = sizeof(chunks) / sizeof(chunks[0]); ci < cl; ci++)
              {
                Parse *c = chunks[ci];
                if (c->isPosTag())
                {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                  toks.push_back(c->toString());
                  tags.push_back(c->getType());
                  preds.push_back(Parser::OTHER);
                }
                else
                {
                  bool start = true;
                  std::string ctype = c->getType();
//ORIGINAL LINE: Parse[] kids = c.getChildren();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                  Parse *kids = c->getChildren();
                  for (int ti = 0,tl = kids->length;ti < tl;ti++)
                  {
                    Parse *tok = kids[ti];
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                    toks.push_back(tok->toString());
                    tags.push_back(tok->getType());
                    if (start)
                    {
                      preds.push_back(Parser::START + ctype);
                      start = false;
                    }
                    else
                    {
                      preds.push_back(Parser::CONT + ctype);
                    }
                  }
                }
              }
              for (int ti = 0, tl = toks.size(); ti < tl; ti++)
              {
                chunkEvents.push_back(new Event(preds[ti], chunkerContextGenerator->getContext(ti, toks.toArray(new std::string[toks.size()]), tags.toArray(new std::string[tags.size()]), preds.toArray(new std::string[preds.size()]))));
              }
            }

            void AbstractParserEventStream::addTagEvents(std::vector<Event*> &tagEvents, Parse chunks[])
            {
              std::vector<std::string> toks = std::vector<std::string>();
              std::vector<std::string> preds = std::vector<std::string>();
              for (int ci = 0, cl = sizeof(chunks) / sizeof(chunks[0]); ci < cl; ci++)
              {
                Parse *c = chunks[ci];
                if (c->isPosTag())
                {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                  toks.push_back(c->toString());
                  preds.push_back(c->getType());
                }
                else
                {
//ORIGINAL LINE: Parse[] kids = c.getChildren();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                  Parse *kids = c->getChildren();
                  for (int ti = 0,tl = kids->length;ti < tl;ti++)
                  {
                    Parse *tok = kids[ti];
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                    toks.push_back(tok->toString());
                    preds.push_back(tok->getType());
                  }
                }
              }
              for (int ti = 0, tl = toks.size(); ti < tl; ti++)
              {
                tagEvents.push_back(new Event(preds[ti], tagContextGenerator->getContext(ti, toks.toArray(new std::string[toks.size()]), preds.toArray(new std::string[preds.size()]), 0)));
              }
            }

            bool AbstractParserEventStream::lastChild(Parse *child, Parse *parent)
            {
//ORIGINAL LINE: Parse[] kids = AbstractBottomUpParser.collapsePunctuation(parent.getChildren(),punctSet);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              Parse *kids = AbstractBottomUpParser::collapsePunctuation(parent->getChildren(),punctSet);
              return (kids[kids->length - 1] == child);
            }
        }
    }
}
