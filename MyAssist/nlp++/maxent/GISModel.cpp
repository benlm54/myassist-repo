#include "GISModel.h"
#include "maxent/io/SuffixSensitiveGISModelReader.h"

namespace opennlp
{
    namespace maxent
    {
        using opennlp::model::AbstractModel;
        using opennlp::model::Context;
        using opennlp::model::EvalParameters;
        using opennlp::model::Prior;
        using opennlp::model::UniformPrior;

        GISModel::GISModel(Context params[], std::string predLabels[], std::string outcomeNames[], int correctionConstant, double correctionParam)
        {
        }

        GISModel::GISModel(Context params[], std::string predLabels[], std::string outcomeNames[], int correctionConstant, double correctionParam, Prior *prior) : opennlp.model.AbstractModel(params, predLabels, outcomeNames, correctionConstant, correctionParam)
        {
          this->prior = prior;
          prior->setLabels(outcomeNames, predLabels);
          modelType = MAXENT;
        }

        double *GISModel::eval(std::string context[])
        {
          return (eval(context, new double[evalParams->getNumOutcomes()]));
        }

        double *GISModel::eval(std::string context[], float values[])
        {
          return (eval(context, values, new double[evalParams->getNumOutcomes()]));
        }

        double *GISModel::eval(std::string context[], double outsums[])
        {
          return eval(context, 0, outsums);
        }

        double *GISModel::eval(std::string context[], float values[], double outsums[])
        {
          int scontexts[sizeof(context) / sizeof(context[0])];
          for (int i = 0; i < sizeof(context) / sizeof(context[0]); i++)
          {
            int ci = pmap->get_Renamed(context[i]);
            scontexts[i] = ci == 0 ? - 1 : ci;
          }
          prior->logPrior(outsums, scontexts, values);
          return GISModel::eval(scontexts, values, outsums, evalParams);
        }

        double *GISModel::eval(int context[], double prior[], EvalParameters *model)
        {
          return eval(context, 0, prior, model);
        }

        double *GISModel::eval(int context[], float values[], double prior[], EvalParameters *model)
        {
//ORIGINAL LINE: opennlp.model.Context[] params = model.getParams();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          Context *params = model->getParams();
          int numfeats[model->getNumOutcomes()];
//ORIGINAL LINE: int[] activeOutcomes;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          int *activeOutcomes;
//ORIGINAL LINE: double[] activeParameters;
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          double *activeParameters;
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
                numfeats[oid]++;
                prior[oid] += activeParameters[ai] * value;
              }
            }
          }

          double normal = 0.0;
          for (int oid = 0; oid < model->getNumOutcomes(); oid++)
          {
            if (model->getCorrectionParam() != 0)
            {
              prior[oid] = exp(prior[oid] * model->getConstantInverse() + ((1.0 - (static_cast<double>(numfeats[oid]) / model->getCorrectionConstant())) * model->getCorrectionParam()));
            }
            else
            {
              prior[oid] = exp(prior[oid] * model->getConstantInverse());
            }
            normal += prior[oid];
          }

          for (int oid = 0; oid < model->getNumOutcomes(); oid++)
          {
            prior[oid] /= normal;
          }
          return prior;
        }

        void GISModel::main(std::string args[]) throw(java::io::IOException)
        {
          if (sizeof(args) / sizeof(args[0]) == 0)
          {
            System::err::println("Usage: GISModel modelname < contexts");
            exit(1);
          }
          AbstractModel *m = (new opennlp::maxent::io::SuffixSensitiveGISModelReader(new File(args[0])))->getModel();
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
            for (int oi = 0; oi < dist->length; oi++)
            {
              std::cout << "[" + m->getOutcome(oi) + " " + df->format(dist[oi]) + "] ";
            }
            std::cout << std::endl;
          }
        }
    }
}
