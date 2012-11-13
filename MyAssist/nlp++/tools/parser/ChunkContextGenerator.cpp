#include "ChunkContextGenerator.h"
#include "StringBuffer.h"

namespace opennlp
{
    namespace tools
    {
        namespace parser
        {
            using opennlp::tools::chunker::ChunkerContextGenerator;
            using opennlp::tools::util::Cache;
const std::string ChunkContextGenerator::EOS = "eos";

            ChunkContextGenerator::ChunkContextGenerator()
            {
            }

            ChunkContextGenerator::ChunkContextGenerator(int cacheSize)
            {
              if (cacheSize > 0)
              {
                contextsCache = new Cache(cacheSize);
              }
            }

            std::string *ChunkContextGenerator::getContext(void *o)
            {
//ORIGINAL LINE: Object[] data = (Object[]) o;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              void *data = static_cast<Object[]>(o);
              return getContext((static_cast<int>(data[0])), static_cast<std::string[]>(data[1]), static_cast<std::string[]>(data[2]), static_cast<std::string[]>(data[3]));
            }

            std::string *ChunkContextGenerator::getContext(int i, std::string words[], std::string prevDecisions[], Object ac[])
            {
              return getContext(i,words,static_cast<std::string[]>(ac[0]),prevDecisions);
            }

            std::string *ChunkContextGenerator::getContext(int i, std::string words[], std::string tags[], std::string preds[])
            {
              std::vector<std::string> features = std::vector<std::string>(19);
              int x0 = i;
              int x_2 = x0 - 2;
              int x_1 = x0 - 1;
              int x2 = x0 + 2;
              int x1 = x0 + 1;

              std::string w_2, w_1, w0, w1, w2;
              std::string t_2, t_1, t0, t1, t2;
              std::string p_2, p_1;

              // chunkandpostag(-2)
              if (x_2 >= 0)
              {
                t_2 = tags[x_2];
                p_2 = preds[x_2];
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                w_2 = words[x_2].toString();
              }
              else
              {
                t_2 = EOS;
                p_2 = EOS;
                w_2 = EOS;
              }

              // chunkandpostag(-1)
              if (x_1 >= 0)
              {
                t_1 = tags[x_1];
                p_1 = preds[x_1];
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                w_1 = words[x_1].toString();
              }
              else
              {
                t_1 = EOS;
                p_1 = EOS;
                w_1 = EOS;
              }

              // chunkandpostag(0)
              t0 = tags[x0];
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              w0 = words[x0].toString();

              // chunkandpostag(1)
              if (x1 < sizeof(tags) / sizeof(tags[0]))
              {
                t1 = tags[x1];
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                w1 = words[x1].toString();
              }
              else
              {
                t1 = EOS;
                w1 = EOS;
              }

              // chunkandpostag(2)
              if (x2 < sizeof(tags) / sizeof(tags[0]))
              {
                t2 = tags[x2];
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                w2 = words[x2].toString();
              }
              else
              {
                t2 = EOS;
                w2 = EOS;
              }

              std::string cacheKey = x0 + t_2 + t1 + t0 + t1 + t2 + p_2 + p_1;
              if (contextsCache != 0)
              {
                if (wordsKey == words)
                {
//ORIGINAL LINE: String[] contexts = (String[]) contextsCache.get(cacheKey);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                  std::string *contexts = static_cast<std::string[]>(contextsCache->get_Renamed(cacheKey));
                  if (contexts != 0)
                  {
                    return contexts;
                  }
                }
                else
                {
                  contextsCache->clear();
                  wordsKey = words;
                }
              }

              std::string ct_2 = chunkandpostag(-2, w_2, t_2, p_2);
              std::string ctbo_2 = chunkandpostagbo(-2, t_2, p_2);
              std::string ct_1 = chunkandpostag(-1, w_1, t_1, p_1);
              std::string ctbo_1 = chunkandpostagbo(-1, t_1, p_1);
              std::string ct0 = chunkandpostag(0, w0, t0, 0);
              std::string ctbo0 = chunkandpostagbo(0, t0, 0);
              std::string ct1 = chunkandpostag(1, w1, t1, 0);
              std::string ctbo1 = chunkandpostagbo(1, t1, 0);
              std::string ct2 = chunkandpostag(2, w2, t2, 0);
              std::string ctbo2 = chunkandpostagbo(2, t2, 0);

              features.push_back("default");
              features.push_back(ct_2);
              features.push_back(ctbo_2);
              features.push_back(ct_1);
              features.push_back(ctbo_1);
              features.push_back(ct0);
              features.push_back(ctbo0);
              features.push_back(ct1);
              features.push_back(ctbo1);
              features.push_back(ct2);
              features.push_back(ctbo2);

              //chunkandpostag(-1,0)
              features.push_back(ct_1 + "," + ct0);
              features.push_back(ctbo_1 + "," + ct0);
              features.push_back(ct_1 + "," + ctbo0);
              features.push_back(ctbo_1 + "," + ctbo0);

              //chunkandpostag(0,1)
              features.push_back(ct0 + "," + ct1);
              features.push_back(ctbo0 + "," + ct1);
              features.push_back(ct0 + "," + ctbo1);
              features.push_back(ctbo0 + "," + ctbo1);
//ORIGINAL LINE: String contexts[] = features.toArray(new String[features.size()]);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              std::string *contexts = features.toArray(new std::string[features.size()]);
              if (contextsCache != 0)
              {
                contextsCache->put(cacheKey,contexts);
              }
              return (contexts);
            }

            std::string ChunkContextGenerator::chunkandpostag(int i, const std::string &tok, const std::string &tag, const std::string &chunk)
            {
              StringBuffer *feat = new StringBuffer(20);
              feat->append(i)->append("=")->append(tok)->append("|")->append(tag);
              if (i < 0)
              {
                feat->append("|")->append(chunk);
              }
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              return (feat->toString());
            }

            std::string ChunkContextGenerator::chunkandpostagbo(int i, const std::string &tag, const std::string &chunk)
            {
              StringBuffer *feat = new StringBuffer(20);
              feat->append(i)->append("*=")->append(tag);
              if (i < 0)
              {
                feat->append("|")->append(chunk);
              }
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              return (feat->toString());
            }
        }
    }
}
