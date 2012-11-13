#include "POSSampleSequenceStream.h"
#include "tools/postag/POSModel.h"
#include "tools/postag/POSTagger.h"
#include "tools/postag/POSTaggerME.h"
#include "tools/postag/POSSampleEventStream.h"
#include "tools/postag/DefaultPOSContextGenerator.h"

namespace opennlp
{
    namespace tools
    {
        namespace postag
        {
            using opennlp::model::AbstractModel;
            using opennlp::model::Event;
            using opennlp::model::Sequence;
            using opennlp::model::SequenceStream;
            using opennlp::tools::util::ObjectStream;

            POSSampleSequenceStream::POSSampleSequenceStream(ObjectStream<POSSample*> *psi) throw(IOException)
            {
            }

            POSSampleSequenceStream::POSSampleSequenceStream(ObjectStream<POSSample*> *psi, POSContextGenerator *pcg) throw(IOException)
            {
              samples = std::vector<POSSample*>();

              POSSample *sample;
              while ((sample = psi->read()) != 0)
              {
                samples.push_back(sample);
              }
              System::err::println("Got " + samples.size() + " sequences");
              this->pcg = pcg;
            }

            Event *POSSampleSequenceStream::updateContext(Sequence *sequence, AbstractModel *model)
            {
              Sequence<POSSample*> *pss = sequence;
              POSTagger *tagger = new POSTaggerME(new POSModel("x-unspecified", model, 0, 0));
//ORIGINAL LINE: String[] sentence = pss.getSource().getSentence();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              std::string *sentence = pss->getSource()->getSentence();
//ORIGINAL LINE: String[] tags = tagger.tag(pss.getSource().getSentence());
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              std::string *tags = tagger->tag(pss->getSource()->getSentence());
              Event events[sentence->length];
              POSSampleEventStream::generateEvents(sentence,tags,pcg).toArray(events);
              return events;
            }

            Iterator<Sequence*> *POSSampleSequenceStream::iterator()
            {
              return new POSSampleSequenceIterator(samples.begin());
            }

            POSSampleSequenceIterator::POSSampleSequenceIterator(Iterator<POSSample*> *psi)
            {
              this->psi = psi;
              cg = new DefaultPOSContextGenerator(0);
            }

            bool POSSampleSequenceIterator::hasNext()
            {
              return psi->hasNext();
            }

            opennlp::model::Sequence<POSSample*> *POSSampleSequenceIterator::next()
            {
              POSSample *sample = psi->next();

//ORIGINAL LINE: String sentence[] = sample.getSentence();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              std::string *sentence = sample->getSentence();
//ORIGINAL LINE: String tags[] = sample.getTags();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              std::string *tags = sample->getTags();
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
              Sequence<POSSample*> *sequence = new Sequence<POSSample*>(events,sample);
              return sequence;
            }

            void POSSampleSequenceIterator::remove()
            {
              throw UnsupportedOperationException();
            }
        }
    }
}
