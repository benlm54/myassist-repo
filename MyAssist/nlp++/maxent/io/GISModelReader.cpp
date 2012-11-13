#include "GISModelReader.h"
#include "model/Context.h"
#include "maxent/GISModel.h"

namespace opennlp
{
    namespace maxent
    {
        namespace io
        {
            using opennlp::maxent::GISModel;
            using opennlp::model::AbstractModel;
            using opennlp::model::AbstractModelReader;
            using opennlp::model::Context;
            using opennlp::model::DataReader;

            GISModelReader::GISModelReader(File *file) throw(IOException) : opennlp.model.AbstractModelReader(file)
            {
            }

            GISModelReader::GISModelReader(DataReader *dataReader) : opennlp.model.AbstractModelReader(dataReader)
            {
            }

            opennlp::model::AbstractModel *GISModelReader::constructModel() throw(IOException)
            {
              int correctionConstant = getCorrectionConstant();
              double correctionParam = getCorrectionParameter();
//ORIGINAL LINE: String[] outcomeLabels = getOutcomes();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              std::string *outcomeLabels = getOutcomes();
//ORIGINAL LINE: int[][] outcomePatterns = getOutcomePatterns();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              int **outcomePatterns = getOutcomePatterns();
//ORIGINAL LINE: String[] predLabels = getPredicates();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              std::string *predLabels = getPredicates();
//ORIGINAL LINE: opennlp.model.Context[] params = getParameters(outcomePatterns);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              Context *params = getParameters(outcomePatterns);

              return new GISModel(params, predLabels, outcomeLabels, correctionConstant, correctionParam);
            }

            void GISModelReader::checkModelType() throw(IOException)
            {
              std::string modelType = readUTF();
              if (modelType != "GIS")
                std::cout << "Error: attempting to load a " + modelType + " model as a GIS model." + " You should expect problems." << std::endl;
            }

            int GISModelReader::getCorrectionConstant() throw(IOException)
            {
              return readInt();
            }

            double GISModelReader::getCorrectionParameter() throw(IOException)
            {
              return readDouble();
            }
        }
    }
}
