#include "SentenceDetectorME.h"
#include "tools/util/StringUtil.h"
#include "model/EventStream.h"
#include "tools/sentdetect/SDEventStream.h"
#include "model/AbstractModel.h"
#include "model/TrainUtil.h"
#include "tools/util/model/ModelUtil.h"
#include "StringBuffer.h"

namespace opennlp
{
    namespace tools
    {
        namespace sentdetect
        {
            using opennlp::model::AbstractModel;
            using opennlp::model::EventStream;
            using opennlp::model::MaxentModel;
            using opennlp::model::TrainUtil;
            using opennlp::tools::dictionary::Dictionary;
            using opennlp::tools::sentdetect::lang::Factory;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::Span;
            using opennlp::tools::util::StringUtil;
            using opennlp::tools::util::TrainingParameters;
            using opennlp::tools::util::model::ModelUtil;
const std::string SentenceDetectorME::SPLIT = "s";
const std::string SentenceDetectorME::NO_SPLIT = "n";
const double SentenceDetectorME::ONE = double(1);

            SentenceDetectorME::SentenceDetectorME(SentenceModel *model)
            {
              InitializeInstanceFields();
            }

            SentenceDetectorME::SentenceDetectorME(SentenceModel *model, Factory *factory) : cgen(factory->createSentenceContextGenerator(model->getLanguage(), getAbbreviations(model->getAbbreviations()))), scanner(factory->createEndOfSentenceScanner(model->getLanguage()))
            {
              InitializeInstanceFields();
              this->model = model->getMaxentModel();
              useTokenEnd = model->useTokenEnd();
            }

            Set<std::string> *SentenceDetectorME::getAbbreviations(Dictionary *abbreviations)
            {
              if (abbreviations == 0)
              {
                return Collections::emptySet<std::string>();
              }
              return abbreviations->asStringSet();
            }

            std::string *SentenceDetectorME::sentDetect(const std::string &s)
            {
//ORIGINAL LINE: opennlp.tools.util.Span[] spans = sentPosDetect(s);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              Span *spans = sentPosDetect(s);
//ORIGINAL LINE: String sentences[];
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              std::string *sentences;
              if (spans->length != 0)
              {

                sentences = new std::string[spans->length];

                for (int si = 0; si < spans->length; si++)
                {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                  sentences[si] = spans[si]->getCoveredText(s)->toString();
                }
              }
              else
              {
                sentences = new std::string[] {};
              }
              return sentences;
            }

            int SentenceDetectorME::getFirstWS(const std::string &s, int pos)
            {
              while (pos < s.length() && !StringUtil::isWhitespace(s[pos]))
                pos++;
              return pos;
            }

            int SentenceDetectorME::getFirstNonWS(const std::string &s, int pos)
            {
              while (pos < s.length() && StringUtil::isWhitespace(s[pos]))
                pos++;
              return pos;
            }

            Span *SentenceDetectorME::sentPosDetect(const std::string &s)
            {
              sentProbs.clear();
              StringBuffer *sb = new StringBuffer(s);
              std::vector<int> enders = scanner->getPositions(s);
              std::vector<int> positions = std::vector<int>(enders.size());

              for (int i = 0, end = enders.size(), index = 0; i < end; i++)
              {
                int candidate = enders[i];
                int cint = candidate;
                // skip over the leading parts of non-token final delimiters
                int fws = getFirstWS(s,cint + 1);
                if (i + 1 < end && enders[i + 1] < fws)
                {
                  continue;
                }

//ORIGINAL LINE: double[] probs = model.eval(cgen.getContext(sb, cint));
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                double *probs = model->eval(cgen->getContext(sb, cint));
                std::string bestOutcome = model->getBestOutcome(probs);

                if (bestOutcome == SPLIT && isAcceptableBreak(s, index, cint))
                {
                  if (index != cint)
                  {
                    if (useTokenEnd)
                    {
                      positions.push_back(getFirstNonWS(s, getFirstWS(s,cint + 1)));
                    }
                    else
                    {
                      positions.push_back(getFirstNonWS(s,cint));
                    }
                    sentProbs.push_back(double(probs[model->getIndex(bestOutcome)]));
                  }
                  index = cint + 1;
                }
              }

              int starts[positions.size()];
              for (int i = 0; i < sizeof(starts) / sizeof(starts[0]); i++)
              {
                starts[i] = positions[i];
              }

              // string does not contain sentence end positions
              if (sizeof(starts) / sizeof(starts[0]) == 0)
              {

                  // remove leading and trailing whitespace
                  int start = 0;
                  int end = s.length();

                  while (start < s.length() && StringUtil::isWhitespace(s[start]))
                    start++;

                  while (end > 0 && StringUtil::isWhitespace(s[end - 1]))
                    end--;

                  if ((end - start) > 0)
                  {
                    sentProbs.push_back(1);
                    return new Span[] {new Span(start, end)};
                  }
                  else
                    return new Span[0];
              }

              // Now convert the sent indexes to spans
              bool leftover = starts[sizeof(starts) / sizeof(starts[0]) - 1] != s.length();
              Span spans[leftover? sizeof(starts) / sizeof(starts[0]) + 1 : sizeof(starts) / sizeof(starts[0])];
              for (int si = 0;si < sizeof(starts) / sizeof(starts[0]);si++)
              {
                int start, end;
                if (si == 0)
                {
                  start = 0;

                  while (si < sizeof(starts) / sizeof(starts[0]) && StringUtil::isWhitespace(s[start]))
                    start++;
                }
                else
                {
                  start = starts[si - 1];
                }
                end = starts[si];
                while (end > 0 && StringUtil::isWhitespace(s[end - 1]))
                {
                  end--;
                }
                spans[si] = new Span(start,end);
              }

              if (leftover)
              {
                spans[sizeof(spans) / sizeof(spans[0]) - 1] = new Span(starts[sizeof(starts) / sizeof(starts[0]) - 1],s.length());
                sentProbs.push_back(ONE);
              }

              return spans;
            }

            double *SentenceDetectorME::getSentenceProbabilities()
            {
              double sentProbArray[sentProbs.size()];
              for (int i = 0; i < sizeof(sentProbArray) / sizeof(sentProbArray[0]); i++)
              {
                sentProbArray[i] = sentProbs[i];
              }
              return sentProbArray;
            }

            bool SentenceDetectorME::isAcceptableBreak(const std::string &s, int fromIndex, int candidateIndex)
            {
              return true;
            }

            opennlp::tools::sentdetect::SentenceModel *SentenceDetectorME::train(const std::string &languageCode, ObjectStream<SentenceSample*> *samples, bool useTokenEnd, Dictionary *abbreviations, TrainingParameters *mlParams) throw(IOException)
            {

              Map<std::string, std::string> *manifestInfoEntries = std::map<std::string, std::string>();

              Factory *factory = new Factory();

              // TODO: Fix the EventStream to throw exceptions when training goes wrong
              EventStream *eventStream = new SDEventStream(samples, factory->createSentenceContextGenerator(languageCode, getAbbreviations(abbreviations)), factory->createEndOfSentenceScanner(languageCode));

              AbstractModel *sentModel = TrainUtil::train(eventStream, mlParams->getSettings(), manifestInfoEntries);

              return new SentenceModel(languageCode, sentModel, useTokenEnd, abbreviations, manifestInfoEntries);
            }

            opennlp::tools::sentdetect::SentenceModel *SentenceDetectorME::train(const std::string &languageCode, ObjectStream<SentenceSample*> *samples, bool useTokenEnd, Dictionary *abbreviations, int cutoff, int iterations) throw(IOException)
            {
              return train(languageCode, samples, useTokenEnd, abbreviations, ModelUtil::createTrainingParameters(iterations, cutoff));
            }

            opennlp::tools::sentdetect::SentenceModel *SentenceDetectorME::train(const std::string &languageCode, ObjectStream<SentenceSample*> *samples, bool useTokenEnd, Dictionary *abbreviations) throw(IOException)
            {
              return train(languageCode, samples, useTokenEnd, abbreviations,5,100);
            }

            void SentenceDetectorME::InitializeInstanceFields()
            {
                sentProbs = std::vector<double>();
            }
        }
    }
}
