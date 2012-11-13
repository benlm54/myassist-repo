#include "SDEventStream.h"
#include "tools/util/Span.h"
#include "tools/sentdetect/SentenceDetectorME.h"
#include "const_iterator.h"

namespace opennlp
{
    namespace tools
    {
        namespace sentdetect
        {
            using opennlp::model::Event;
            using opennlp::tools::util::AbstractEventStream;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::Span;

            SDEventStream::SDEventStream(ObjectStream<SentenceSample*> *samples, SDContextGenerator *cg, EndOfSentenceScanner *scanner) : opennlp.tools.util.AbstractEventStream<SentenceSample>(samples)
            {

              this->cg = cg;
              this->scanner = scanner;
            }

            Iterator<Event*> *SDEventStream::createEvents(SentenceSample *sample)
            {

              Collection<Event*> *events = std::vector<Event*>();

              for (Span::const_iterator sentenceSpan = sample->getSentences()->begin(); sentenceSpan != sample->getSentences()->end(); ++sentenceSpan)
              {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                std::string sentenceString = sentenceSpan->getCoveredText(sample->getDocument())->toString();

                for (Iterator it = scanner->getPositions(sentenceString).begin(); it->hasNext();)
                {

                  int candidate = it->next();
                  std::string type = SentenceDetectorME::NO_SPLIT;
                  if (!it->hasNext())
                  {
                    type = SentenceDetectorME::SPLIT;
                  }

                  events->add(new Event(type, cg->getContext(sample->getDocument(), sentenceSpan->getStart() + candidate)));
                }
              }


              return events->begin();
            }
        }
    }
}
