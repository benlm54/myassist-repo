#include "ChunkerME.h"
#include "model/EventStream.h"
#include "tools/chunker/ChunkerEventStream.h"
#include "model/AbstractModel.h"
#include "model/TrainUtil.h"
#include "tools/util/model/ModelUtil.h"
#include "tools/chunker/DefaultChunkerContextGenerator.h"

namespace opennlp
{
    namespace tools
    {
        namespace chunker
        {
            using opennlp::model::AbstractModel;
            using opennlp::model::EventStream;
            using opennlp::model::MaxentModel;
            using opennlp::model::TrainUtil;
            using opennlp::tools::util::BeamSearch;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::Sequence;
            using opennlp::tools::util::SequenceValidator;
            using opennlp::tools::util::Span;
            using opennlp::tools::util::TrainingParameters;
            using opennlp::tools::util::model::ModelUtil;

            ChunkerME::ChunkerME(ChunkerModel *model, int beamSize, SequenceValidator<std::string> *sequenceValidator, ChunkerContextGenerator *contextGenerator)
            {
              this->model = model->getChunkerModel();
              beam = new BeamSearch<std::string>(beamSize, contextGenerator, this->model, sequenceValidator, 0);
            }

            ChunkerME::ChunkerME(ChunkerModel *model, int beamSize, SequenceValidator<std::string> *sequenceValidator)
            {
            }

            ChunkerME::ChunkerME(ChunkerModel *model, int beamSize)
            {
            }

            ChunkerME::ChunkerME(ChunkerModel *model)
            {
            }

            ChunkerME::ChunkerME(MaxentModel *mod)
            {
            }

            ChunkerME::ChunkerME(MaxentModel *mod, ChunkerContextGenerator *cg)
            {
            }

            ChunkerME::ChunkerME(MaxentModel *mod, ChunkerContextGenerator *cg, int beamSize)
            {
              beam = new BeamSearch<std::string>(beamSize, cg, mod);
              this->model = mod;
            }

            std::vector<std::string> ChunkerME::chunk(std::vector<std::string> &toks, std::vector<std::string> &tags)
            {
              bestSequence = beam->bestSequence(toks.toArray(new std::string[toks.size()]), new Object[] {tags.toArray(new std::string[tags.size()])});
              return bestSequence->getOutcomes();
            }

            std::string *ChunkerME::chunk(std::string toks[], std::string tags[])
            {
              bestSequence = beam->bestSequence(toks, new Object[] {tags});
              std::vector<std::string> c = bestSequence->getOutcomes();
              return c.toArray(new std::string[c.size()]);
            }

            Span *ChunkerME::chunkAsSpans(std::string toks[], std::string tags[])
            {
//ORIGINAL LINE: String[] preds = chunk(toks, tags);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              std::string *preds = chunk(toks, tags);
              return ChunkSample::phrasesAsSpanList(toks, tags, preds);
            }

            Sequence *ChunkerME::topKSequences(std::vector<std::string> &sentence, std::vector<std::string> &tags)
            {
              return topKSequences(sentence.toArray(new std::string[sentence.size()]), tags.toArray(new std::string[tags.size()]));
            }

            Sequence *ChunkerME::topKSequences(std::string sentence[], std::string tags[])
            {
              return beam->bestSequences(DEFAULT_BEAM_SIZE, sentence, new Object[] {tags});
            }

            Sequence *ChunkerME::topKSequences(std::string sentence[], std::string tags[], double minSequenceScore)
            {
              return beam->bestSequences(DEFAULT_BEAM_SIZE, sentence, new Object[] {tags},minSequenceScore);
            }

            void ChunkerME::probs(double probs[])
            {
              bestSequence->getProbs(probs);
            }

            double *ChunkerME::probs()
            {
              return bestSequence->getProbs();
            }

            opennlp::tools::chunker::ChunkerModel *ChunkerME::train(const std::string &lang, ObjectStream<ChunkSample*> *in_Renamed, ChunkerContextGenerator *contextGenerator, TrainingParameters *mlParams) throw(IOException)
            {

              Map<std::string, std::string> *manifestInfoEntries = std::map<std::string, std::string>();

              EventStream *es = new ChunkerEventStream(in_Renamed, contextGenerator);

              AbstractModel *maxentModel = TrainUtil::train(es, mlParams->getSettings(), manifestInfoEntries);

              return new ChunkerModel(lang, maxentModel, manifestInfoEntries);
            }

            opennlp::tools::chunker::ChunkerModel *ChunkerME::train(const std::string &lang, ObjectStream<ChunkSample*> *in_Renamed, int cutoff, int iterations, ChunkerContextGenerator *contextGenerator) throw(IOException)
            {
              return train(lang, in_Renamed, contextGenerator, ModelUtil::createTrainingParameters(iterations, cutoff));
            }

            opennlp::tools::chunker::ChunkerModel *ChunkerME::train(const std::string &lang, ObjectStream<ChunkSample*> *in_Renamed, int cutoff, int iterations) throw(IOException, ObjectStreamException)
            {
              return train(lang, in_Renamed, cutoff, iterations, new DefaultChunkerContextGenerator());
            }
        }
    }
}
