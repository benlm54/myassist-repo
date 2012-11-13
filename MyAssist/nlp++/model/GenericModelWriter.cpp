#include "GenericModelWriter.h"
#include "perceptron/BinaryPerceptronModelWriter.h"
#include "maxent/io/BinaryGISModelWriter.h"
#include "perceptron/PlainTextPerceptronModelWriter.h"
#include "maxent/io/PlainTextGISModelWriter.h"

namespace opennlp
{
    namespace model
    {
        using opennlp::maxent::io::BinaryGISModelWriter;
        using opennlp::maxent::io::PlainTextGISModelWriter;
        using opennlp::model::AbstractModel::ModelType;
        using opennlp::perceptron::BinaryPerceptronModelWriter;
        using opennlp::perceptron::PlainTextPerceptronModelWriter;

        GenericModelWriter::GenericModelWriter(AbstractModel *model, File *file) throw(IOException)
        {
          std::string filename = file->getName();
          OutputStream *os;
          // handle the zipped/not zipped distinction
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'endsWith' method:
          if (filename.endsWith(".gz"))
          {
            os = new GZIPOutputStream(new FileOutputStream(file));
            filename = filename.substr(0,filename.length() - 3);
          }
          else
          {
            os = new FileOutputStream(file);
          }

          // handle the different formats
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'endsWith' method:
          if (filename.endsWith(".bin"))
          {
            init(model,new DataOutputStream(os));
          }
          else // filename ends with ".txt"
          {
            init(model,new BufferedWriter(new OutputStreamWriter(os)));
          }
        }

        GenericModelWriter::GenericModelWriter(AbstractModel *model, DataOutputStream *dos)
        {
          init(model,dos);
        }

        void GenericModelWriter::init(AbstractModel *model, DataOutputStream *dos)
        {
          if (model->getModelType() == opennlp::model::AbstractModel::PERCEPTRON)
          {
            delegateWriter = new BinaryPerceptronModelWriter(model,dos);
          }
          else if (model->getModelType() == opennlp::model::AbstractModel::MAXENT)
          {
            delegateWriter = new BinaryGISModelWriter(model,dos);
          }
        }

        void GenericModelWriter::init(AbstractModel *model, BufferedWriter *bw)
        {
          if (model->getModelType() == opennlp::model::AbstractModel::PERCEPTRON)
          {
            delegateWriter = new PlainTextPerceptronModelWriter(model,bw);
          }
          else if (model->getModelType() == opennlp::model::AbstractModel::MAXENT)
          {
            delegateWriter = new PlainTextGISModelWriter(model,bw);
          }
        }

        void GenericModelWriter::close() throw(IOException)
        {
          delegateWriter->close();
        }

        void GenericModelWriter::persist() throw(IOException)
        {
          delegateWriter->persist();
        }

        void GenericModelWriter::writeDouble(double d) throw(IOException)
        {
          delegateWriter->writeDouble(d);
        }

        void GenericModelWriter::writeInt(int i) throw(IOException)
        {
          delegateWriter->writeInt(i);
        }

        void GenericModelWriter::writeUTF(const std::string &s) throw(IOException)
        {
          delegateWriter->writeUTF(s);
        }
    }
}
