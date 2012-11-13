#include "PlainTextPerceptronModelWriter.h"

namespace opennlp
{
    namespace perceptron
    {
        using opennlp::model::AbstractModel;

        PlainTextPerceptronModelWriter::PlainTextPerceptronModelWriter(AbstractModel *model, File *f) throw(IOException, FileNotFoundException) : PerceptronModelWriter(model)
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

        PlainTextPerceptronModelWriter::PlainTextPerceptronModelWriter(AbstractModel *model, BufferedWriter *bw) : PerceptronModelWriter(model)
        {
          output = bw;
        }

        void PlainTextPerceptronModelWriter::writeUTF(const std::string &s) throw(IOException)
        {
          output->write(s);
          output->newLine();
        }

        void PlainTextPerceptronModelWriter::writeInt(int i) throw(IOException)
        {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
          output->write(int::toString(i));
          output->newLine();
        }

        void PlainTextPerceptronModelWriter::writeDouble(double d) throw(IOException)
        {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
          output->write(double::toString(d));
          output->newLine();
        }

        void PlainTextPerceptronModelWriter::close() throw(IOException)
        {
          output->flush();
          output->close();
        }
    }
}
