#include "NameSampleSequenceStream.h"
#include "tools/namefind/NameFinderME.h"
#include "tools/namefind/TokenNameFinder.h"
#include "tools/namefind/TokenNameFinderModel.h"
#include "tools/namefind/NameFinderEventStream.h"
#include "tools/namefind/DefaultNameContextGenerator.h"

namespace opennlp
{
    namespace tools
    {
        namespace namefind
        {
            using opennlp::model::AbstractModel;
            using opennlp::model::Event;
            using opennlp::model::Sequence;
            using opennlp::model::SequenceStream;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::featuregen::AdaptiveFeatureGenerator;

            NameSampleSequenceStream::NameSampleSequenceStream(ObjectStream<NameSample*> *psi) throw(IOException)
            {
            }

            NameSampleSequenceStream::NameSampleSequenceStream(ObjectStream<NameSample*> *psi, AdaptiveFeatureGenerator *featureGen) throw(IOException)
            {
            }

            NameSampleSequenceStream::NameSampleSequenceStream(ObjectStream<NameSample*> *psi, NameContextGenerator *pcg) throw(IOException)
            {
              samples = std::vector<NameSample*>();

              NameSample *sample;
              while ((sample = psi->read()) != 0)
              {
                samples.push_back(sample);
              }

              System::err::println("Got " + samples.size() + " sequences");

              this->pcg = pcg;
            }

            Event *NameSampleSequenceStream::updateContext(Sequence *sequence, AbstractModel *model)
            {
              Sequence<NameSample*> *pss = sequence;
              TokenNameFinder *tagger = new NameFinderME(new TokenNameFinderModel("x-unspecified", model, Collections::emptyMap<std::string, void*>(), 0));
//ORIGINAL LINE: String[] sentence = pss.getSource().getSentence();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              std::string *sentence = pss->getSource()->getSentence();
//ORIGINAL LINE: String[] tags = NameFinderEventStream.generateOutcomes(tagger.find(sentence), nullptr, sentence.length);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              std::string *tags = NameFinderEventStream::generateOutcomes(tagger->find(sentence), 0, sentence->length);
              Event events[sentence->length];

              NameFinderEventStream::generateEvents(sentence,tags,pcg).toArray(events);

              return events;
            }

            Iterator<Sequence*> *NameSampleSequenceStream::iterator()
            {
              return new NameSampleSequenceIterator(samples.begin());
            }

            NameSampleSequenceIterator::NameSampleSequenceIterator(Iterator<NameSample*> *psi)
            {
              this->psi = psi;
              cg = new DefaultNameContextGenerator(0);
            }

            bool NameSampleSequenceIterator::hasNext()
            {
              return psi->hasNext();
            }

            opennlp::model::Sequence<NameSample*> *NameSampleSequenceIterator::next()
            {
              NameSample *sample = psi->next();

//ORIGINAL LINE: String sentence[] = sample.getSentence();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              std::string *sentence = sample->getSentence();
//ORIGINAL LINE: String tags[] = NameFinderEventStream.generateOutcomes(sample.getNames(), nullptr, sentence.length);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              std::string *tags = NameFinderEventStream::generateOutcomes(sample->getNames(), 0, sentence->length);
              Event events[sentence->length];

              for (int i = 0; i < sentence->length; i++)
              {

                // it is safe to pass the tags as previous tags because
                // the context generator does not look for non predicted tags
//ORIGINAL LINE: String[] context = cg.getContext(i, sentence, tags, nullptr);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                std::string *context = cg->getContext(i, sentence, tags, 0);

                events[i] = new Event(tags[i], context);
              }
              Sequence<NameSample*> *sequence = new Sequence<NameSample*>(events,sample);
              return sequence;
            }

            void NameSampleSequenceIterator::remove()
            {
              throw UnsupportedOperationException();
            }
        }
    }
}
