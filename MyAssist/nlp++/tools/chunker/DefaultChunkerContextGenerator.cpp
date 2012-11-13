#include "DefaultChunkerContextGenerator.h"

namespace opennlp
{
    namespace tools
    {
        namespace chunker
        {

            DefaultChunkerContextGenerator::DefaultChunkerContextGenerator()
            {
            }

            std::string *DefaultChunkerContextGenerator::getContext(int index, std::string sequence[], std::string priorDecisions[], Object additionalContext[])
            {
              return getContext(index,sequence,static_cast<std::string[]>(additionalContext[0]),priorDecisions);
            }

            std::string *DefaultChunkerContextGenerator::getContext(int i, std::string toks[], std::string tags[], std::string preds[])
            {
              // Words in a 5-word window
              std::string w_2, w_1, w0, w1, w2;

              // Tags in a 5-word window
              std::string t_2, t_1, t0, t1, t2;

              // Previous predictions
              std::string p_2, p_1;

              if (i < 2)
              {
                w_2 = "w_2=bos";
                t_2 = "t_2=bos";
                p_2 = "p_2=bos";
              }
              else
              {
                w_2 = "w_2=" + toks[i - 2];
                t_2 = "t_2=" + tags[i - 2];
                p_2 = "p_2" + preds[i - 2];
              }

              if (i < 1)
              {
                w_1 = "w_1=bos";
                t_1 = "t_1=bos";
                p_1 = "p_1=bos";
              }
              else
              {
                w_1 = "w_1=" + toks[i - 1];
                t_1 = "t_1=" + tags[i - 1];
                p_1 = "p_1=" + preds[i - 1];
              }

              w0 = "w0=" + toks[i];
              t0 = "t0=" + tags[i];

              if (i + 1 >= sizeof(toks) / sizeof(toks[0]))
              {
                w1 = "w1=eos";
                t1 = "t1=eos";
              }
              else
              {
                w1 = "w1=" + toks[i + 1];
                t1 = "t1=" + tags[i + 1];
              }

              if (i + 2 >= sizeof(toks) / sizeof(toks[0]))
              {
                w2 = "w2=eos";
                t2 = "t2=eos";
              }
              else
              {
                w2 = "w2=" + toks[i + 2];
                t2 = "t2=" + tags[i + 2];
              }

              std::string features[41] = {w_2, w_1, w0, w1, w2, w_1 + w0, w0 + w1, t_2, t_1, t0, t1, t2, t_2 + t_1, t_1 + t0, t0 + t1, t1 + t2, t_2 + t_1 + t0, t_1 + t0 + t1, t0 + t1 + t2, p_2, p_1, p_2 + p_1, p_1 + t_2, p_1 + t_1, p_1 + t0, p_1 + t1, p_1 + t2, p_1 + t_2 + t_1, p_1 + t_1 + t0, p_1 + t0 + t1, p_1 + t1 + t2, p_1 + t_2 + t_1 + t0, p_1 + t_1 + t0 + t1, p_1 + t0 + t1 + t2, p_1 + w_2, p_1 + w_1, p_1 + w0, p_1 + w1, p_1 + w2, p_1 + w_1 + w0, p_1 + w0 + w1};

              return features;
            }
        }
    }
}
