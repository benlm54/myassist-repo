#include "BinaryPerceptronModelWriter.h"

namespace opennlp
{
    namespace perceptron
    {
        using opennlp::model::AbstractModel;

        BinaryPerceptronModelWriter::BinaryPerceptronModelWriter(AbstractModel *model, File *f) throw(IOException) : PerceptronModelWriter(model)
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

        BinaryPerceptronModelWriter::BinaryPerceptronModelWriter(AbstractModel *model, DataOutputStream *dos) : PerceptronModelWriter(model)
        {
          output = dos;
        }

        void BinaryPerceptronModelWriter::writeUTF(const std::string &s) throw(IOException)
        {
          output->writeUTF(s);
        }

        void BinaryPerceptronModelWriter::writeInt(int i) throw(IOException)
        {
          output->writeInt(i);
        }

        void BinaryPerceptronModelWriter::writeDouble(double d) throw(IOException)
        {
          output->writeDouble(d);
        }

        void BinaryPerceptronModelWriter::close() throw(IOException)
        {
          output->flush();
          output->close();
        }
    }
}
