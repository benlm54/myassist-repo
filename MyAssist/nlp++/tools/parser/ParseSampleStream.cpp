#include "ParseSampleStream.h"
#include "S.h"

namespace opennlp
{
    namespace tools
    {
        namespace parser
        {
            using opennlp::tools::util::FilterObjectStream;
            using opennlp::tools::util::ObjectStream;

            ParseSampleStream::ParseSampleStream(ObjectStream<std::string> *in_Renamed) : opennlp.tools.util.FilterObjectStream<String, Parse>(in)
            {
            }

            opennlp::tools::parser::Parse *ParseSampleStream::read() throw(IOException)
            {

              std::string parse = samples->read();

              if (parse != "")
              {
                return Parse::parseParse(parse);
              }
              else
              {
                return 0;
              }
            }
        }
    }
}
