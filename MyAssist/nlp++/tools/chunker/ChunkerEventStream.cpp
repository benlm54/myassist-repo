#include "ChunkerEventStream.h"

namespace opennlp
{
    namespace tools
    {
        namespace chunker
        {
            using opennlp::model::Event;
            using opennlp::tools::util::ObjectStream;

            ChunkerEventStream::ChunkerEventStream(ObjectStream<ChunkSample*> *d, ChunkerContextGenerator *cg)
            {
              this->cg = cg;
              data = d;
              ei = 0;
              addNewEvents();
            }

            ChunkerEventStream::ChunkerEventStream(ObjectStream<ChunkSample*> *d)
            {
            }

            opennlp::model::Event *ChunkerEventStream::next()
            {

              hasNext();

              return events[ei++];
            }

            bool ChunkerEventStream::hasNext()
            {
              if (ei == events->length)
              {
                addNewEvents();
                ei = 0;
              }
              return ei < events->length;
            }

            void ChunkerEventStream::addNewEvents()
            {

              ChunkSample *sample;
              try
              {
                sample = data->read();
              }
              catch (IOException e)
              {
                throw std::exception(e);
              }

              if (sample != 0)
              {
                events = new Event[sizeof(sample->getSentence()) / sizeof(sample->getSentence()[0])];
//ORIGINAL LINE: String[] toksArray = sample.getSentence();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                std::string *toksArray = sample->getSentence();
//ORIGINAL LINE: String[] tagsArray = sample.getTags();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                std::string *tagsArray = sample->getTags();
//ORIGINAL LINE: String[] predsArray = sample.getPreds();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                std::string *predsArray = sample->getPreds();
                for (int ei = 0, el = events->length; ei < el; ei++)
                {
                  events[ei] = new Event(predsArray[ei], cg->getContext(ei,toksArray,tagsArray,predsArray));
                }
              }
              else
              {
                events = new Event[0];
              }
            }
        }
    }
}
