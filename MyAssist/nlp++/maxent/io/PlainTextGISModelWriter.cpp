#include "PlainTextGISModelWriter.h"

namespace opennlp
{
    namespace maxent
    {
        namespace io
        {
            using opennlp::model::AbstractModel;

            PlainTextGISModelWriter::PlainTextGISModelWriter(AbstractModel *model, File *f) throw(IOException, FileNotFoundException) : GISModelWriter(model)
            {

//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'endsWith' method:
              if (f->getName()->endsWith(".gz"))
              {
                output = new BufferedWriter(new OutputStreamWriter(new GZIPOutputStream(new FileOutputStream(f))));
              }
              else
              {
                output = new BufferedWriter(new FileWriter(f));
              }
            }

            PlainTextGISModelWriter::PlainTextGISModelWriter(AbstractModel *model, BufferedWriter *bw) : GISModelWriter(model)
            {
              output = bw;
            }

            void PlainTextGISModelWriter::writeUTF(const std::string &s) throw(IOException)
            {
              output->write(s);
              output->newLine();
            }

            void PlainTextGISModelWriter::writeInt(int i) throw(IOException)
            {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              output->write(int::toString(i));
              output->newLine();
            }

            void PlainTextGISModelWriter::writeDouble(double d) throw(IOException)
            {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              output->write(double::toString(d));
              output->newLine();
            }

            void PlainTextGISModelWriter::close() throw(IOException)
            {
              output->flush();
              output->close();
            }
        }
    }
}
