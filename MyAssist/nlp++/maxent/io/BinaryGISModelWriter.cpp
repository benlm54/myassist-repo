#include "BinaryGISModelWriter.h"

namespace opennlp
{
    namespace maxent
    {
        namespace io
        {
            using opennlp::model::AbstractModel;

            BinaryGISModelWriter::BinaryGISModelWriter(AbstractModel *model, File *f) throw(IOException) : GISModelWriter(model)
            {


//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'endsWith' method:
              if (f->getName()->endsWith(".gz"))
              {
                output = new DataOutputStream(new GZIPOutputStream(new FileOutputStream(f)));
              }
              else
              {
                output = new DataOutputStream(new FileOutputStream(f));
              }
            }

            BinaryGISModelWriter::BinaryGISModelWriter(AbstractModel *model, DataOutputStream *dos) : GISModelWriter(model)
            {
              output = dos;
            }

            void BinaryGISModelWriter::writeUTF(const std::string &s) throw(IOException)
            {
              output->writeUTF(s);
            }

            void BinaryGISModelWriter::writeInt(int i) throw(IOException)
            {
              output->writeInt(i);
            }

            void BinaryGISModelWriter::writeDouble(double d) throw(IOException)
            {
              output->writeDouble(d);
            }

            void BinaryGISModelWriter::close() throw(IOException)
            {
              output->flush();
              output->close();
            }
        }
    }
}
