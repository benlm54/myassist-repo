#include "PlainTextFileDataReader.h"

namespace opennlp
{
    namespace model
    {

        PlainTextFileDataReader::PlainTextFileDataReader(File *f) throw(IOException)
        {
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'endsWith' method:
          if (f->getName()->endsWith(".gz"))
          {
            input = new BufferedReader(new InputStreamReader(new BufferedInputStream(new GZIPInputStream(new BufferedInputStream(new FileInputStream(f))))));
          }
          else
          {
            input = new BufferedReader(new InputStreamReader(new BufferedInputStream(new FileInputStream(f))));
          }
        }

        PlainTextFileDataReader::PlainTextFileDataReader(InputStream *in_Renamed)
        {
          input = new BufferedReader(new InputStreamReader(in_Renamed));
        }

        PlainTextFileDataReader::PlainTextFileDataReader(BufferedReader *in_Renamed)
        {
          input = in_Renamed;
        }

        double PlainTextFileDataReader::readDouble() throw(IOException)
        {
          return static_cast<double>(input->readLine());
        }

        int PlainTextFileDataReader::readInt() throw(IOException)
        {
          return static_cast<int>(input->readLine());
        }

        std::string PlainTextFileDataReader::readUTF() throw(IOException)
        {
          return input->readLine();
        }
    }
}
