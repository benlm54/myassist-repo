#include "AbstractModelReader.h"
#include "model/BinaryFileDataReader.h"
#include "model/PlainTextFileDataReader.h"

namespace opennlp
{
    namespace model
    {

        AbstractModelReader::AbstractModelReader(File *f) throw(IOException)
        {
          std::string filename = f->getName();
          InputStream *input;
          // handle the zipped/not zipped distinction
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'endsWith' method:
          if (filename.endsWith(".gz"))
          {
            input = new GZIPInputStream(new FileInputStream(f));
            filename = filename.substr(0,filename.length() - 3);
          }
          else
          {
            input = new FileInputStream(f);
          }

          // handle the different formats
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'endsWith' method:
          if (filename.endsWith(".bin"))
          {
            this->dataReader = new BinaryFileDataReader(input);
          }
          else // filename ends with ".txt"
          {
            this->dataReader = new PlainTextFileDataReader(input);
          }
        }

        AbstractModelReader::AbstractModelReader(DataReader *dataReader)
        {
          this->dataReader = dataReader;
        }

        int AbstractModelReader::readInt() throw(IOException)
        {
          return dataReader->readInt();
        }

        double AbstractModelReader::readDouble() throw(IOException)
        {
          return dataReader->readDouble();
        }

        std::string AbstractModelReader::readUTF() throw(IOException)
        {
          return dataReader->readUTF();
        }

        opennlp::model::AbstractModel *AbstractModelReader::getModel() throw(IOException)
        {
          checkModelType();
          return constructModel();
        }

        std::string *AbstractModelReader::getOutcomes() throw(IOException)
        {
            int numOutcomes = readInt();
            std::string outcomeLabels[numOutcomes];
            for (int i = 0; i < numOutcomes; i++)
                outcomeLabels[i] = readUTF();
            return outcomeLabels;
        }

        int **AbstractModelReader::getOutcomePatterns() throw(IOException)
        {
            int numOCTypes = readInt();
//ORIGINAL LINE: int[][] outcomePatterns = new int[numOCTypes][];
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
            int **outcomePatterns = new int*[numOCTypes][];
            for (int i = 0; i < numOCTypes; i++)
            {
                StringTokenizer *tok = new StringTokenizer(readUTF(), " ");
                int infoInts[tok->countTokens()];
                for (int j = 0; tok->hasMoreTokens(); j++)
                {
                    infoInts[j] = static_cast<int>(tok->nextToken());
                }
                outcomePatterns[i] = infoInts;
            }
            return outcomePatterns;
        }

        std::string *AbstractModelReader::getPredicates() throw(IOException)
        {
            NUM_PREDS = readInt();
            std::string predLabels[NUM_PREDS];
            for (int i = 0; i < NUM_PREDS; i++)
                predLabels[i] = readUTF();
            return predLabels;
        }

        Context *AbstractModelReader::getParameters(int outcomePatterns[][]) throw(IOException)
        {
          Context params[NUM_PREDS];
          int pid = 0;
          for (int i = 0; i < sizeof(outcomePatterns) / sizeof(outcomePatterns[0]); i++)
          {
            //construct outcome pattern
            int outcomePattern[outcomePatterns[i].length - 1];
            for (int k = 1; k < outcomePatterns[i].length; k++)
            {
              outcomePattern[k - 1] = outcomePatterns[i][k];
            }
            //System.err.println("outcomePattern "+i+" of "+outcomePatterns.length+" with "+outcomePatterns[i].length+" outcomes ");
            //populate parameters for each context which uses this outcome pattern. 
            for (int j = 0; j < outcomePatterns[i][0]; j++)
            {
              double contextParameters[outcomePatterns[i].length - 1];
              for (int k = 1; k < outcomePatterns[i].length; k++)
              {
                contextParameters[k - 1] = readDouble();
              }
              params[pid] = new Context(outcomePattern,contextParameters);
              pid++;
            }
          }
          return params;
        }
    }
}
