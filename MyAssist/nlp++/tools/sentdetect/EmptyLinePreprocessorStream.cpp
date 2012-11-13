#include "EmptyLinePreprocessorStream.h"
#include "S.h"

namespace opennlp
{
    namespace tools
    {
        namespace sentdetect
        {
            using opennlp::tools::util::FilterObjectStream;
            using opennlp::tools::util::ObjectStream;

            EmptyLinePreprocessorStream::EmptyLinePreprocessorStream(ObjectStream<std::string> *in_Renamed) : opennlp.tools.util.FilterObjectStream<String, String>(in)
            {
              InitializeInstanceFields();
            }

            bool EmptyLinePreprocessorStream::isLineEmpty(const std::string &line)
            {
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'trim' method:
              return line.trim()->length() == 0;
            }

            std::string EmptyLinePreprocessorStream::read() throw(IOException)
            {

              std::string line = samples->read();

              if (lastLineWasEmpty)
              {
                lastLineWasEmpty = false;

                while (line != "" && isLineEmpty(line))
                {
                  line = samples->read();
                }
              }

              if (line != "" && isLineEmpty(line))
              {
                lastLineWasEmpty = true;
                line = "";
              }

              return line;
            }

            void EmptyLinePreprocessorStream::InitializeInstanceFields()
            {
                lastLineWasEmpty = true;
            }
        }
    }
}
