#include "POSTaggerCrossValidator.h"
#include "tools/util/eval/CrossValidationPartitioner.h"
#include "tools/postag/POSTaggerME.h"
#include "tools/cmdline/CmdLineUtil.h"
#include "tools/cmdline/TerminateToolException.h"
#include "tools/postag/POSModel.h"
#include "tools/postag/POSEvaluator.h"

namespace opennlp
{
    namespace tools
    {
        namespace postag
        {
            using opennlp::tools::cmdline::CmdLineUtil;
            using opennlp::tools::cmdline::TerminateToolException;
            using opennlp::tools::dictionary::Dictionary;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::TrainingParameters;
            using opennlp::tools::util::eval::CrossValidationPartitioner;
            using opennlp::tools::util::eval::Mean;
            using opennlp::tools::util::model::ModelType;
            using opennlp::tools::util::model::ModelUtil;

            POSTaggerCrossValidator::POSTaggerCrossValidator(const std::string &languageCode, ModelType modelType, POSDictionary *tagDictionary, Dictionary *ngramDictionary, int cutoff, int iterations) : languageCode(languageCode), params(ModelUtil::createTrainingParameters(iterations, cutoff))
            {
              InitializeInstanceFields();
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              this->params->put(TrainingParameters::ALGORITHM_PARAM, modelType::toString());
              this->tagDictionary = tagDictionary;
              this->ngramDictionary = ngramDictionary;
            }

            POSTaggerCrossValidator::POSTaggerCrossValidator(const std::string &languageCode, ModelType modelType, POSDictionary *tagDictionary, Dictionary *ngramDictionary)
            {
              InitializeInstanceFields();
            }

            POSTaggerCrossValidator::POSTaggerCrossValidator(const std::string &languageCode, TrainingParameters *trainParam, POSDictionary *tagDictionary, ...) : languageCode(languageCode), params(trainParam)
            {
              InitializeInstanceFields();
              this->tagDictionary = tagDictionary;
//JAVA TO C++ CONVERTER WARNING: Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
              delete this->ngramDictionary;
              this->ngramCutoff = 0;
              this->listeners = listeners;
            }

            POSTaggerCrossValidator::POSTaggerCrossValidator(const std::string &languageCode, TrainingParameters *trainParam, POSDictionary *tagDictionary, int ngramCutoff, ...) : languageCode(languageCode), params(trainParam)
            {
              InitializeInstanceFields();
              this->tagDictionary = tagDictionary;
//JAVA TO C++ CONVERTER WARNING: Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
              delete this->ngramDictionary;
              this->ngramCutoff = ngramCutoff;
              this->listeners = listeners;
            }

            POSTaggerCrossValidator::POSTaggerCrossValidator(const std::string &languageCode, TrainingParameters *trainParam, POSDictionary *tagDictionary, Dictionary *ngramDictionary, ...) : languageCode(languageCode), params(trainParam)
            {
              InitializeInstanceFields();
              this->tagDictionary = tagDictionary;
              this->ngramDictionary = ngramDictionary;
              this->ngramCutoff = 0;
              this->listeners = listeners;
            }

            void POSTaggerCrossValidator::evaluate(ObjectStream<POSSample*> *samples, int nFolds) throw(IOException, IOException)
            {

              CrossValidationPartitioner<POSSample*> *partitioner = new CrossValidationPartitioner<POSSample*>(samples, nFolds);

              while (partitioner->hasNext())
              {

                CrossValidationPartitioner::TrainingSampleStream<POSSample*> *trainingSampleStream = partitioner->next();

                Dictionary *ngramDict = 0;
                if (this->ngramDictionary == 0)
                {
                  if (this->ngramCutoff != 0)
                  {
                    System::err::print("Building ngram dictionary ... ");
                    try
                    {
                      ngramDict = POSTaggerME::buildNGramDictionary(trainingSampleStream, this->ngramCutoff);
                      trainingSampleStream->reset();
                    }
                    catch (IOException e)
                    {
                      CmdLineUtil::printTrainingIoError(e);
                      throw TerminateToolException(-1);
                    }
                    System::err::println("done");
                  }
                }
                else
                {
                  ngramDict = this->ngramDictionary;
                }

                POSModel *model = POSTaggerME::train(languageCode, trainingSampleStream, params, this->tagDictionary, ngramDict);

                POSEvaluator *evaluator = new POSEvaluator(new POSTaggerME(model), listeners);

                evaluator->evaluate(trainingSampleStream->getTestSampleStream());

                wordAccuracy->add(evaluator->getWordAccuracy(), evaluator->getWordCount());
                  partitioner++;
              }
            }

            double POSTaggerCrossValidator::getWordAccuracy()
            {
              return wordAccuracy->mean();
            }

            long long POSTaggerCrossValidator::getWordCount()
            {
              return wordAccuracy->count();
            }

            void POSTaggerCrossValidator::InitializeInstanceFields()
            {
                wordAccuracy = new opennlp::tools::util::eval::Mean();
            }
        }
    }
}
