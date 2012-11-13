#include "PerceptronModelReader.h"
#include "model/Context.h"
#include "perceptron/PerceptronModel.h"

namespace opennlp
{
    namespace perceptron
    {
        using opennlp::model::AbstractModel;
        using opennlp::model::AbstractModelReader;
        using opennlp::model::Context;
        using opennlp::model::DataReader;

        PerceptronModelReader::PerceptronModelReader(File *file) throw(IOException) : opennlp.model.AbstractModelReader(file)
        {
        }

        PerceptronModelReader::PerceptronModelReader(DataReader *dataReader) : opennlp.model.AbstractModelReader(dataReader)
        {
        }

        opennlp::model::AbstractModel *PerceptronModelReader::constructModel() throw(IOException)
        {
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

          return new PerceptronModel(params, predLabels, outcomeLabels);
        }

        void PerceptronModelReader::checkModelType() throw(IOException)
        {
          std::string modelType = readUTF();
          if (modelType != "Perceptron")
              std::cout << "Error: attempting to load a " + modelType + " model as a Perceptron model." + " You should expect problems." << std::endl;
        }
    }
}
