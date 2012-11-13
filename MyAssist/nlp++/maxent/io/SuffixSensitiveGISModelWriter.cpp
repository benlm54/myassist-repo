#include "SuffixSensitiveGISModelWriter.h"
#include "maxent/io/PlainTextGISModelWriter.h"

namespace opennlp
{
    namespace maxent
    {
        namespace io
        {
            using opennlp::model::AbstractModel;

            SuffixSensitiveGISModelWriter::SuffixSensitiveGISModelWriter(AbstractModel *model, File *f) throw(IOException) : GISModelWriter(model), suffixAppropriateWriter(new BinaryGISModelWriter(model, new DataOutputStream(output)))
            {


              OutputStream *output;
              std::string filename = f->getName();

              // handle the zipped/not zipped distinction
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'endsWith' method:
              if (filename.endsWith(".gz"))
              {
                output = new GZIPOutputStream(new FileOutputStream(f));
                filename = filename.substr(0,filename.length() - 3);
              }
              else
              {
                output = new DataOutputStream(new FileOutputStream(f));
              }

              // handle the different formats
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'endsWith' method:
              if (filename.endsWith(".bin"))
              {
              }
              else // default is ".txt"
              {
                suffixAppropriateWriter = new PlainTextGISModelWriter(model, new BufferedWriter(new OutputStreamWriter(output)));
              }
            }

            void SuffixSensitiveGISModelWriter::writeUTF(const std::string &s) throw(IOException)
            {
              suffixAppropriateWriter->writeUTF(s);
            }

            void SuffixSensitiveGISModelWriter::writeInt(int i) throw(IOException)
            {
              suffixAppropriateWriter->writeInt(i);
            }

            void SuffixSensitiveGISModelWriter::writeDouble(double d) throw(IOException)
            {
              suffixAppropriateWriter->writeDouble(d);
            }

            void SuffixSensitiveGISModelWriter::close() throw(IOException)
            {
              suffixAppropriateWriter->close();
            }
        }
    }
}
