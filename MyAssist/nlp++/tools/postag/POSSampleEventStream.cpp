#include "POSSampleEventStream.h"

namespace opennlp
{
    namespace tools
    {
        namespace postag
        {
            using opennlp::model::Event;
            using opennlp::tools::util::AbstractEventStream;
            using opennlp::tools::util::ObjectStream;

            POSSampleEventStream::POSSampleEventStream(ObjectStream<POSSample*> *samples, POSContextGenerator *cg) : opennlp.tools.util.AbstractEventStream<POSSample>(samples)
            {

              this->cg = cg;
            }

            POSSampleEventStream::POSSampleEventStream(ObjectStream<POSSample*> *samples)
            {
            }

            Iterator<Event*> *POSSampleEventStream::createEvents(POSSample *sample)
            {
//ORIGINAL LINE: String sentence[] = sample.getSentence();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              std::string *sentence = sample->getSentence();
//ORIGINAL LINE: String tags[] = sample.getTags();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              std::string *tags = sample->getTags();
              std::vector<Event*> events = generateEvents(sentence,tags,cg);
              return events.begin();
            }

            std::vector<Event*> POSSampleEventStream::generateEvents(std::string sentence[], std::string tags[], POSContextGenerator *cg)
            {
              std::vector<Event*> events = std::vector<Event*>(sizeof(sentence) / sizeof(sentence[0]));

              for (int i = 0; i < sizeof(sentence) / sizeof(sentence[0]); i++)
              {

                // it is safe to pass the tags as previous tags because
                // the context generator does not look for non predicted tags
//ORIGINAL LINE: String[] context = cg.getContext(i, sentence, tags, nullptr);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                std::string *context = cg->getContext(i, sentence, tags, 0);

                events.push_back(new Event(tags[i], context));
              }
              return events;
            }
        }
    }
}
