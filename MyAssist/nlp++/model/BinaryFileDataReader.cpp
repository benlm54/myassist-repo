#include "BinaryFileDataReader.h"

namespace opennlp
{
    namespace model
    {

        BinaryFileDataReader::BinaryFileDataReader(File *f) throw(IOException)
        {
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'endsWith' method:
          if (f->getName()->endsWith(".gz"))
          {
            input = new DataInputStream(new BufferedInputStream(new GZIPInputStream(new BufferedInputStream(new FileInputStream(f)))));
          }
          else
          {
            input = new DataInputStream(new BufferedInputStream(new FileInputStream(f)));
          }
        }

        BinaryFileDataReader::BinaryFileDataReader(InputStream *in_Renamed)
        {
          input = new DataInputStream(in_Renamed);
        }

        BinaryFileDataReader::BinaryFileDataReader(DataInputStream *in_Renamed)
        {
          input = in_Renamed;
        }

        double BinaryFileDataReader::readDouble() throw(IOException)
        {
          return input->readDouble();
        }

        int BinaryFileDataReader::readInt() throw(IOException)
        {
          return input->readInt();
        }

        std::string BinaryFileDataReader::readUTF() throw(IOException)
        {
          return input->readUTF();
        }
    }
}
