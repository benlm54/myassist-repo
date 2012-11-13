#include "ModelUtil.h"
#include "model/GenericModelWriter.h"
#include "tools/util/model/BaseModel.h"

namespace opennlp
{
    namespace tools
    {
        namespace util
        {
            namespace model
            {
                using opennlp::model::AbstractModel;
                using opennlp::model::GenericModelWriter;
                using opennlp::model::MaxentModel;
                using opennlp::tools::util::TrainingParameters;

                ModelUtil::ModelUtil()
                {
                  // not intended to be instantiated
                }

                void ModelUtil::writeModel(AbstractModel *model, OutputStream *const out) throw(IOException)
                {

                  if (model == 0)
                    throw IllegalArgumentException("model parameter must not be null!");

                  if (out == 0)
                    throw IllegalArgumentException("out parameter must not be null!");

                  GenericModelWriter *modelWriter = new GenericModelWriter(model, new DataOutputStream(new OutputStreamAnonymousInnerClassHelper();
                  modelWriter->persist();
                }

                void ModelUtil::OutputStreamAnonymousInnerClassHelper::write(int b) throw(IOException)
                {
                  out::write(b);
                }

                bool ModelUtil::validateOutcomes(MaxentModel *model, ...)
                {

                  bool result = true;

                  if (expectedOutcomes->length == model->getNumOutcomes())
                  {

                    Set<std::string> *expectedOutcomesSet = std::set<std::string>();
                    expectedOutcomesSet->addAll(Arrays::asList(expectedOutcomes));

                    for (int i = 0; i < model->getNumOutcomes(); i++)
                    {
                      if (!expectedOutcomesSet->contains(model->getOutcome(i)))
                      {
                        result = false;
                        break;
                      }
                    }
                  }
                  else
                  {
                    result = false;
                  }

                  return result;
                }

                char *ModelUtil::read(InputStream *in_Renamed) throw(IOException)
                {
                  ByteArrayOutputStream *byteArrayOut = new ByteArrayOutputStream();

                  int length;
                  char buffer[1024];
                  while ((length = in_Renamed->read(buffer)) > 0)
                  {
                    byteArrayOut->write(buffer, 0, length);
                  }
                  byteArrayOut->close();

                  return byteArrayOut->toByteArray();
                }

                void ModelUtil::addCutoffAndIterations(Map<std::string, std::string> *manifestInfoEntries, int cutoff, int iterations)
                {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                  manifestInfoEntries->put(BaseModel::TRAINING_CUTOFF_PROPERTY, int::toString(cutoff));
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                  manifestInfoEntries->put(BaseModel::TRAINING_ITERATIONS_PROPERTY, int::toString(iterations));
                }

                opennlp::tools::util::TrainingParameters *ModelUtil::createTrainingParameters(int iterations, int cutoff)
                {
                  TrainingParameters *mlParams = new TrainingParameters();
                  mlParams->put(TrainingParameters::ALGORITHM_PARAM, "MAXENT");
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                  mlParams->put(TrainingParameters::ITERATIONS_PARAM, int::toString(iterations));
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                  mlParams->put(TrainingParameters::CUTOFF_PARAM, int::toString(cutoff));

                  return mlParams;
                }
            }
        }
    }
}
