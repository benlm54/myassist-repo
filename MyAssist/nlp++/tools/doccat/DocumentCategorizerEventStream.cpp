#include "DocumentCategorizerEventStream.h"
#include "tools/doccat/BagOfWordsFeatureGenerator.h"

namespace opennlp
{
    namespace tools
    {
        namespace doccat
        {
            using opennlp::model::Event;
            using opennlp::tools::util::AbstractEventStream;
            using opennlp::tools::util::ObjectStream;

            DocumentCategorizerEventStream::DocumentCategorizerEventStream(ObjectStream<DocumentSample*> *data, ...) : opennlp.tools.util.AbstractEventStream<DocumentSample>(data)
            {

              mContextGenerator = new DocumentCategorizerContextGenerator(featureGenerators);
            }

            DocumentCategorizerEventStream::DocumentCategorizerEventStream(ObjectStream<DocumentSample*> *samples) : opennlp.tools.util.AbstractEventStream<DocumentSample>(samples)
            {

              mContextGenerator = new DocumentCategorizerContextGenerator(new BagOfWordsFeatureGenerator());
            }

            Iterator<Event*> *DocumentCategorizerEventStream::createEvents(DocumentSample *const sample)
            {

              return new IteratorAnonymousInnerClassHelper();
            }

            bool DocumentCategorizerEventStream::IteratorAnonymousInnerClassHelper::hasNext()
            {
              return isVirgin;
            }

            opennlp::model::Event *DocumentCategorizerEventStream::IteratorAnonymousInnerClassHelper::next()
            {

              isVirgin = false;

              return new Event(sample::getCategory(), outerInstance->mContextGenerator->getContext(sample::getText()));
            }

            void DocumentCategorizerEventStream::IteratorAnonymousInnerClassHelper::remove()
            {
              throw UnsupportedOperationException();
            }
        }
    }
}
