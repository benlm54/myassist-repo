#include "ChunkSampleStream.h"
#include "tools/parser/chunking/Parser.h"
#include "S.h"

namespace opennlp
{
    namespace tools
    {
        namespace parser
        {
            using opennlp::tools::chunker::ChunkSample;
            using opennlp::tools::parser::chunking::Parser;
            using opennlp::tools::util::FilterObjectStream;
            using opennlp::tools::util::ObjectStream;

            ChunkSampleStream::ChunkSampleStream(ObjectStream<Parse*> *in_Renamed) : opennlp.tools.util.FilterObjectStream<Parse, opennlp.tools.chunker.ChunkSample>(in)
            {
            }

            void ChunkSampleStream::getInitialChunks(Parse *p, std::vector<Parse*> &ichunks)
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

            Parse *ChunkSampleStream::getInitialChunks(Parse *p)
            {
              std::vector<Parse*> chunks = std::vector<Parse*>();
              getInitialChunks(p, chunks);
              return chunks.toArray(new Parse[chunks.size()]);
            }

            opennlp::tools::chunker::ChunkSample *ChunkSampleStream::read() throw(IOException)
            {

              Parse *parse = samples->read();

              if (parse != 0)
              {
//ORIGINAL LINE: Parse[] chunks = getInitialChunks(parse);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                Parse *chunks = getInitialChunks(parse);
                std::vector<std::string> toks = std::vector<std::string>();
                std::vector<std::string> tags = std::vector<std::string>();
                std::vector<std::string> preds = std::vector<std::string>();
                for (int ci = 0, cl = chunks->length; ci < cl; ci++)
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

                return new ChunkSample(toks.toArray(new std::string[toks.size()]), tags.toArray(new std::string[tags.size()]), preds.toArray(new std::string[preds.size()]));
              }
              else
              {
                return 0;
              }
            }
        }
    }
}
