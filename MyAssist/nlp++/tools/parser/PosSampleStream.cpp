#include "PosSampleStream.h"
#include "S.h"

namespace opennlp
{
    namespace tools
    {
        namespace parser
        {
            using opennlp::tools::postag::POSSample;
            using opennlp::tools::util::FilterObjectStream;
            using opennlp::tools::util::ObjectStream;

            PosSampleStream::PosSampleStream(ObjectStream<Parse*> *in_Renamed) : opennlp.tools.util.FilterObjectStream<Parse, opennlp.tools.postag.POSSample>(in)
            {
            }

            opennlp::tools::postag::POSSample *PosSampleStream::read() throw(IOException)
            {

              Parse *parse = samples->read();

              if (parse != 0)
              {

//ORIGINAL LINE: Parse[] nodes = parse.getTagNodes();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                Parse *nodes = parse->getTagNodes();

                std::string toks[nodes->length];
                std::string preds[nodes->length];

                for (int ti = 0; ti < nodes->length; ti++)
                {
                  Parse *tok = nodes[ti];
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                  toks[ti] = tok->toString();
                  preds[ti] = tok->getType();
                }

                return new POSSample(toks, preds);
              }
              else
              {
                return 0;
              }
            }
        }
    }
}
