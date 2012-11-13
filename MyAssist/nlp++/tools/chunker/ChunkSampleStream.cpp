#include "ChunkSampleStream.h"
#include "S.h"

namespace opennlp
{
    namespace tools
    {
        namespace chunker
        {
            using opennlp::tools::util::FilterObjectStream;
            using opennlp::tools::util::ObjectStream;

            ChunkSampleStream::ChunkSampleStream(ObjectStream<std::string> *samples) : opennlp.tools.util.FilterObjectStream<String, ChunkSample>(samples)
            {
            }

            opennlp::tools::chunker::ChunkSample *ChunkSampleStream::read() throw(IOException)
            {

              std::vector<std::string> toks = std::vector<std::string>();
              std::vector<std::string> tags = std::vector<std::string>();
              std::vector<std::string> preds = std::vector<std::string>();

              for (std::string line = samples->read(); line != "" && line != ""; line = samples->read())
              {
//ORIGINAL LINE: String[] parts = line.split(" ");
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'split' method:
                std::string *parts = line.split(" ");
                if (parts->length != 3)
                {
                  System::err::println("Skipping corrupt line: " + line);
                }
                else
                {
                  toks.push_back(parts[0]);
                  tags.push_back(parts[1]);
                  preds.push_back(parts[2]);
                }
              }

              if (toks.size() > 0)
              {
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
