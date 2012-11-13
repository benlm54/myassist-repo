#include "PerceptronModel.h"
#include "perceptron/PerceptronModelReader.h"

namespace opennlp
{
    namespace perceptron
    {
        using opennlp::model::AbstractModel;
        using opennlp::model::Context;
        using opennlp::model::EvalParameters;
        using opennlp::model::IndexHashTable;

        PerceptronModel::PerceptronModel(Context params[], std::string predLabels[], IndexHashTable<std::string> *pmap, std::string outcomeNames[]) : opennlp.model.AbstractModel(params,predLabels,pmap,outcomeNames)
        {
          modelType = PERCEPTRON;
        }

        PerceptronModel::PerceptronModel(Context params[], std::string predLabels[], Map<std::string, int> *pmap, std::string outcomeNames[]) : opennlp.model.AbstractModel(params,predLabels,outcomeNames)
        {
          modelType = PERCEPTRON;
        }

        PerceptronModel::PerceptronModel(Context params[], std::string predLabels[], std::string outcomeNames[]) : opennlp.model.AbstractModel(params,predLabels,outcomeNames)
        {
          modelType = PERCEPTRON;
        }

        double *PerceptronModel::eval(std::string context[])
        {
          return eval(context,new double[evalParams->getNumOutcomes()]);
        }

        double *PerceptronModel::eval(std::string context[], float values[])
        {
          return eval(context,values,new double[evalParams->getNumOutcomes()]);
        }

        double *PerceptronModel::eval(std::string context[], double probs[])
        {
          return eval(context,0,probs);
        }

        double *PerceptronModel::eval(std::string context[], float values[], double outsums[])
        {
          int scontexts[sizeof(context) / sizeof(context[0])];
          Arrays::fill(outsums, 0);
          for (int i = 0; i < sizeof(context) / sizeof(context[0]); i++)
          {
            int ci = pmap->get_Renamed(context[i]);
            scontexts[i] = ci == 0 ? - 1 : ci;
          }
          return eval(scontexts,values,outsums,evalParams,true);
        }

        double *PerceptronModel::eval(int context[], double prior[], EvalParameters *model)
        {
          return eval(context,0,prior,model,true);
        }

        double *PerceptronModel::eval(int context[], float values[], double prior[], EvalParameters *model, bool normalize)
        {
//ORIGINAL LINE: opennlp.model.Context[] params = model.getParams();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          Context *params = model->getParams();
//ORIGINAL LINE: double[] activeParameters;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          double *activeParameters;
//ORIGINAL LINE: int[] activeOutcomes;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          int *activeOutcomes;
          double value = 1;
          for (int ci = 0; ci < sizeof(context) / sizeof(context[0]); ci++)
          {
            if (context[ci] >= 0)
            {
              Context *predParams = params[context[ci]];
              activeOutcomes = predParams->getOutcomes();
              activeParameters = predParams->getParameters();
              if (values != 0)
              {
                value = values[ci];
              }
              for (int ai = 0; ai < activeOutcomes->length; ai++)
              {
                int oid = activeOutcomes[ai];
                prior[oid] += activeParameters[ai] * value;
              }
            }
          }
          if (normalize)
          {
            int numOutcomes = model->getNumOutcomes();

            double maxPrior = 1;

            for (int oid = 0; oid < numOutcomes; oid++)
            {
              if (maxPrior < abs(prior[oid]))
                maxPrior = abs(prior[oid]);
            }

            double normal = 0.0;
            for (int oid = 0; oid < numOutcomes; oid++)
            {
              prior[oid] = exp(prior[oid] / maxPrior);
              normal += prior[oid];
            }

            for (int oid = 0; oid < numOutcomes; oid++)
              prior[oid] /= normal;
          }
          return prior;
        }

        void PerceptronModel::main(std::string args[]) throw(java::io::IOException)
        {
          if (sizeof(args) / sizeof(args[0]) == 0)
          {
            System::err::println("Usage: PerceptronModel modelname < contexts");
            exit(1);
          }
          AbstractModel *m = (new PerceptronModelReader(new File(args[0])))->getModel();
          BufferedReader *in_Renamed = new BufferedReader(new InputStreamReader(System::in));
          DecimalFormat *df = new DecimalFormat(".###");
          for (std::string line = in_Renamed->readLine(); line != ""; line = in_Renamed->readLine())
          {
//ORIGINAL LINE: String[] context = line.split(" ");
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'split' method:
            std::string *context = line.split(" ");
//ORIGINAL LINE: double[] dist = m.eval(context);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
            double *dist = m->eval(context);
            for (int oi = 0;oi < dist->length;oi++)
            {
              std::cout << "[" + m->getOutcome(oi) + " " + df->format(dist[oi]) + "] ";
            }
            std::cout << std::endl;
          }
        }
    }
}
