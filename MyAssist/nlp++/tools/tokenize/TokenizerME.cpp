#include "TokenizerME.h"
#include "tools/tokenize/WhitespaceTokenizer.h"
#include "model/EventStream.h"
#include "tools/tokenize/TokSpanEventStream.h"
#include "model/AbstractModel.h"
#include "model/TrainUtil.h"
#include "tools/util/model/ModelUtil.h"

namespace opennlp
{
    namespace tools
    {
        namespace tokenize
        {
            using opennlp::model::AbstractModel;
            using opennlp::model::EventStream;
            using opennlp::model::MaxentModel;
            using opennlp::model::TrainUtil;
            using opennlp::tools::dictionary::Dictionary;
            using opennlp::tools::tokenize::lang::Factory;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::Span;
            using opennlp::tools::util::TrainingParameters;
            using opennlp::tools::util::model::ModelUtil;
const std::string TokenizerME::SPLIT = "T";
const std::string TokenizerME::NO_SPLIT = "F";
java::util::regex::Pattern *const TokenizerME::alphaNumeric = java::util::regex::Pattern::compile(opennlp::tools::tokenize::lang::Factory::DEFAULT_ALPHANUMERIC);

            TokenizerME::TokenizerME(TokenizerModel *model)
            {
            }

            TokenizerME::TokenizerME(TokenizerModel *model, Factory *factory) : alphanumeric(factory->getAlphanumeric(languageCode)), cg(factory->createTokenContextGenerator(languageCode, getAbbreviations(model->getAbbreviations())))
            {
              std::string languageCode = model->getLanguage();


              this->model = model->getMaxentModel();
              useAlphaNumericOptimization_Renamed = model->useAlphaNumericOptimization();

              newTokens = std::vector<Span*>();
              tokProbs = std::vector<double>(50);
            }

            Set<std::string> *TokenizerME::getAbbreviations(Dictionary *abbreviations)
            {
              if (abbreviations == 0)
              {
                return Collections::emptySet<std::string>();
              }
              return abbreviations->asStringSet();
            }

            double *TokenizerME::getTokenProbabilities()
            {
              double tokProbArray[tokProbs.size()];
              for (int i = 0; i < sizeof(tokProbArray) / sizeof(tokProbArray[0]); i++)
              {
                tokProbArray[i] = tokProbs[i];
              }
              return tokProbArray;
            }

            Span *TokenizerME::tokenizePos(const std::string &d)
            {
//ORIGINAL LINE: opennlp.tools.util.Span[] tokens = WhitespaceTokenizer.INSTANCE.tokenizePos(d);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              Span *tokens = WhitespaceTokenizer::INSTANCE->tokenizePos(d);
              newTokens.clear();
              tokProbs.clear();
              for (int i = 0, il = tokens->length; i < il; i++)
              {
                Span *s = tokens[i];
                std::string tok = d.substr(s->getStart(), s->getEnd() - (s->getStart()));
                // Can't tokenize single characters
                if (tok.length() < 2)
                {
                  newTokens.push_back(s);
                  tokProbs.push_back(1);
                }
                else if (useAlphaNumericOptimization() && alphanumeric->matcher(tok)->matches())
                {
                  newTokens.push_back(s);
                  tokProbs.push_back(1);
                }
                else
                {
                  int start = s->getStart();
                  int end = s->getEnd();
                  const int origStart = s->getStart();
                  double tokenProb = 1.0;
                  for (int j = origStart + 1; j < end; j++)
                  {
//ORIGINAL LINE: double[] probs = model.eval(cg.getContext(tok, j - origStart));
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                    double *probs = model->eval(cg->getContext(tok, j - origStart));
                    std::string best = model->getBestOutcome(probs);
                    tokenProb *= probs[model->getIndex(best)];
                    if (best == TokenizerME::SPLIT)
                    {
                      newTokens.push_back(new Span(start, j));
                      tokProbs.push_back(tokenProb);
                      start = j;
                      tokenProb = 1.0;
                    }
                  }
                  newTokens.push_back(new Span(start, end));
                  tokProbs.push_back(tokenProb);
                }
              }

              Span spans[newTokens.size()];
              newTokens.toArray(spans);
              return spans;
            }

            opennlp::tools::tokenize::TokenizerModel *TokenizerME::train(const std::string &languageCode, ObjectStream<TokenSample*> *samples, bool useAlphaNumericOptimization, TrainingParameters *mlParams) throw(IOException)
            {
              return train(languageCode, samples, 0, useAlphaNumericOptimization, mlParams);
            }

            opennlp::tools::tokenize::TokenizerModel *TokenizerME::train(const std::string &languageCode, ObjectStream<TokenSample*> *samples, Dictionary *abbreviations, bool useAlphaNumericOptimization, TrainingParameters *mlParams) throw(IOException)
            {
              Factory *factory = new Factory();

              Map<std::string, std::string> *manifestInfoEntries = std::map<std::string, std::string>();

              EventStream *eventStream = new TokSpanEventStream(samples, useAlphaNumericOptimization, factory->getAlphanumeric(languageCode), factory->createTokenContextGenerator(languageCode, getAbbreviations(abbreviations)));

              AbstractModel *maxentModel = TrainUtil::train(eventStream, mlParams->getSettings(), manifestInfoEntries);

              return new TokenizerModel(languageCode, maxentModel, abbreviations, useAlphaNumericOptimization, manifestInfoEntries);
            }

            opennlp::tools::tokenize::TokenizerModel *TokenizerME::train(const std::string &languageCode, ObjectStream<TokenSample*> *samples, bool useAlphaNumericOptimization, int cutoff, int iterations) throw(IOException)
            {

              return train(languageCode, samples, useAlphaNumericOptimization, ModelUtil::createTrainingParameters(iterations, cutoff));
            }

            opennlp::tools::tokenize::TokenizerModel *TokenizerME::train(const std::string &languageCode, ObjectStream<TokenSample*> *samples, bool useAlphaNumericOptimization) throw(IOException, ObjectStreamException)
            {
              return train(languageCode, samples, useAlphaNumericOptimization, 5, 100);
            }

            bool TokenizerME::useAlphaNumericOptimization()
            {
              return useAlphaNumericOptimization_Renamed;
            }
        }
    }
}
