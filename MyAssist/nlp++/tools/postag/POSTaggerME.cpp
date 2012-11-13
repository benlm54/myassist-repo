#include "POSTaggerME.h"
#include "tools/postag/DefaultPOSContextGenerator.h"
#include "model/TrainUtil.h"
#include "model/EventStream.h"
#include "tools/postag/POSSampleEventStream.h"
#include "tools/postag/POSSampleSequenceStream.h"
#include "tools/ngram/NGramModel.h"
#include "tools/util/StringList.h"
#include "StringBuffer.h"

namespace opennlp
{
    namespace tools
    {
        namespace postag
        {
            using opennlp::model::AbstractModel;
            using opennlp::model::EventStream;
            using opennlp::model::TrainUtil;
            using opennlp::tools::chunker::ChunkerContextGenerator;
            using opennlp::tools::dictionary::Dictionary;
            using opennlp::tools::ngram::NGramModel;
            using opennlp::tools::util::BeamSearch;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::Sequence;
            using opennlp::tools::util::SequenceValidator;
            using opennlp::tools::util::StringList;
            using opennlp::tools::util::TrainingParameters;
            using opennlp::tools::util::model::ModelType;

            POSTaggerME::PosSequenceValidator::PosSequenceValidator(POSDictionary *tagDictionary)
            {
              this->tagDictionary = tagDictionary;
            }

            bool POSTaggerME::PosSequenceValidator::validSequence(int i, std::string inputSequence[], std::string outcomesSequence[], const std::string &outcome)
            {
              if (tagDictionary == 0)
              {
                return true;
              }
              else
              {
//ORIGINAL LINE: String[] tags = tagDictionary.getTags(inputSequence[i].toString());
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                std::string *tags = tagDictionary->getTags(inputSequence[i].toString());
                if (tags == 0)
                {
                  return true;
                }
                else
                {
                  return Arrays::asList(tags)->contains(outcome);
                }
              }
            }

            POSTaggerME::POSTaggerME(POSModel *model, int beamSize, int cacheSize, SequenceValidator<std::string> *sequenceValidator)
            {
              InitializeInstanceFields();
              posModel = model->getPosModel();
              contextGen = new DefaultPOSContextGenerator(beamSize, model->getNgramDictionary());
              tagDictionary = model->getTagDictionary();
              size = beamSize;
              beam = new BeamSearch<std::string>(size, contextGen, posModel, sequenceValidator, cacheSize);
            }

            POSTaggerME::POSTaggerME(POSModel *model, int beamSize, int cacheSize)
            {
              InitializeInstanceFields();
            }

            POSTaggerME::POSTaggerME(POSModel *model)
            {
              InitializeInstanceFields();
            }

            POSTaggerME::POSTaggerME(AbstractModel *model, TagDictionary *tagdict)
            {
              InitializeInstanceFields();
            }

            POSTaggerME::POSTaggerME(AbstractModel *model, Dictionary *dict)
            {
              InitializeInstanceFields();
            }

            POSTaggerME::POSTaggerME(AbstractModel *model, Dictionary *dict, TagDictionary *tagdict)
            {
                InitializeInstanceFields();
            }

            POSTaggerME::POSTaggerME(AbstractModel *model, POSContextGenerator *cg)
            {
              InitializeInstanceFields();
            }

            POSTaggerME::POSTaggerME(AbstractModel *model, POSContextGenerator *cg, TagDictionary *tagdict)
            {
                InitializeInstanceFields();
            }

            POSTaggerME::POSTaggerME(int beamSize, AbstractModel *model, POSContextGenerator *cg, TagDictionary *tagdict)
            {
              InitializeInstanceFields();
              size = beamSize;
              posModel = model;
              contextGen = cg;
              beam = new BeamSearch<std::string>(size, cg, model);
              tagDictionary = tagdict;
            }

            int POSTaggerME::getNumTags()
            {
              return posModel->getNumOutcomes();
            }

            std::vector<std::string> POSTaggerME::tag(std::vector<std::string> &sentence)
            {
              bestSequence = beam->bestSequence(sentence.toArray(new std::string[sentence.size()]), 0);
              return bestSequence->getOutcomes();
            }

            std::string *POSTaggerME::tag(std::string sentence[])
            {
              bestSequence = beam->bestSequence(sentence, 0);
              std::vector<std::string> t = bestSequence->getOutcomes();
              return t.toArray(new std::string[t.size()]);
            }

            std::string **POSTaggerME::tag(int numTaggings, std::string sentence[])
            {
//ORIGINAL LINE: opennlp.tools.util.Sequence[] bestSequences = beam.bestSequences(numTaggings, sentence,nullptr);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              Sequence *bestSequences = beam->bestSequences(numTaggings, sentence,0);
//ORIGINAL LINE: String[][] tags = new String[bestSequences.length][];
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              std::string **tags = new std::string*[bestSequences->length][];
              for (int si = 0;si < tags->length;si++)
              {
                std::vector<std::string> t = bestSequences[si]->getOutcomes();
                tags[si] = t.toArray(new std::string[t.size()]);
              }
              return tags;
            }

            Sequence *POSTaggerME::topKSequences(std::vector<std::string> &sentence)
            {
              return beam->bestSequences(size, sentence.toArray(new std::string[sentence.size()]), 0);
            }

            Sequence *POSTaggerME::topKSequences(std::string sentence[])
            {
              return beam->bestSequences(size, sentence, 0);
            }

            void POSTaggerME::probs(double probs[])
            {
              bestSequence->getProbs(probs);
            }

            double *POSTaggerME::probs()
            {
              return bestSequence->getProbs();
            }

            std::string POSTaggerME::tag(const std::string &sentence)
            {
              std::vector<std::string> toks = std::vector<std::string>();
              StringTokenizer *st = new StringTokenizer(sentence);
              while (st->hasMoreTokens())
                toks.push_back(st->nextToken());
              std::vector<std::string> tags = tag(toks);
              StringBuffer *sb = new StringBuffer();
              for (int i = 0; i < tags.size(); i++)
                sb->append(toks[i] + "/" + tags[i] + " ");
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'trim' method:
              return sb->toString()->trim();
            }

            std::string *POSTaggerME::getOrderedTags(std::vector<std::string> &words, std::vector<std::string> &tags, int index)
            {
              return getOrderedTags(words,tags,index,0);
            }

            std::string *POSTaggerME::getOrderedTags(std::vector<std::string> &words, std::vector<std::string> &tags, int index, double tprobs[])
            {
//ORIGINAL LINE: double[] probs = posModel.eval(contextGen.getContext(index, words.toArray(new String[words.size()]), tags.toArray(new String[tags.size()]),nullptr));
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              double *probs = posModel->eval(contextGen->getContext(index, words.toArray(new std::string[words.size()]), tags.toArray(new std::string[tags.size()]),0));

              std::string orderedTags[probs->length];
              for (int i = 0; i < probs->length; i++)
              {
                int max = 0;
                for (int ti = 1; ti < probs->length; ti++)
                {
                  if (probs[ti] > probs[max])
                  {
                    max = ti;
                  }
                }
                orderedTags[i] = posModel->getOutcome(max);
                if (tprobs != 0)
                {
                  tprobs[i] = probs[max];
                }
                probs[max] = 0;
              }
              return orderedTags;


            }

            opennlp::tools::postag::POSModel *POSTaggerME::train(const std::string &languageCode, ObjectStream<POSSample*> *samples, TrainingParameters *trainParams, POSDictionary *tagDictionary, Dictionary *ngramDictionary) throw(IOException)
            {

              POSContextGenerator *contextGenerator = new DefaultPOSContextGenerator(ngramDictionary);

              Map<std::string, std::string> *manifestInfoEntries = std::map<std::string, std::string>();

              AbstractModel *posModel;

              if (!TrainUtil::isSequenceTraining(trainParams->getSettings()))
              {

                EventStream *es = new POSSampleEventStream(samples, contextGenerator);

                posModel = TrainUtil::train(es, trainParams->getSettings(), manifestInfoEntries);
              }
              else
              {
                POSSampleSequenceStream *ss = new POSSampleSequenceStream(samples, contextGenerator);

                posModel = TrainUtil::train(ss, trainParams->getSettings(), manifestInfoEntries);
              }

              return new POSModel(languageCode, posModel, tagDictionary, ngramDictionary, manifestInfoEntries);
            }

            opennlp::tools::postag::POSModel *POSTaggerME::train(const std::string &languageCode, ObjectStream<POSSample*> *samples, ModelType modelType, POSDictionary *tagDictionary, Dictionary *ngramDictionary, int cutoff, int iterations) throw(IOException)
            {

              TrainingParameters *params = new TrainingParameters();

//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              params->put(TrainingParameters::ALGORITHM_PARAM, modelType::toString());
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              params->put(TrainingParameters::ITERATIONS_PARAM, int::toString(iterations));
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              params->put(TrainingParameters::CUTOFF_PARAM, int::toString(cutoff));

              return train(languageCode, samples, params, tagDictionary, ngramDictionary);
            }

            opennlp::tools::dictionary::Dictionary *POSTaggerME::buildNGramDictionary(ObjectStream<POSSample*> *samples, int cutoff) throw(IOException)
            {

              NGramModel *ngramModel = new NGramModel();

              POSSample *sample;
              while ((sample = samples->read()) != 0)
              {
//ORIGINAL LINE: String[] words = sample.getSentence();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                std::string *words = sample->getSentence();

                if (words->length > 0)
                  ngramModel->add(new StringList(words), 1, 1);
              }

              ngramModel->cutoff(cutoff, int::MAX_VALUE);

              return ngramModel->toDictionary(true);
            }

            void POSTaggerME::InitializeInstanceFields()
            {
                useClosedClassTagsFilter = false;
            }
        }
    }
}
