#include "HashSumEventStream.h"

namespace opennlp
{
    namespace model
    {
        using opennlp::model::Event;
        using opennlp::model::EventStream;

        HashSumEventStream::HashSumEventStream(EventStream *eventStream) : eventStream(eventStream)
        {

          try
          {
            digest = MessageDigest::getInstance("MD5");
          }
          catch (NoSuchAlgorithmException e)
          {
            // should never happen, does all java runtimes have md5 ?!
           throw IllegalStateException(e);
          }
        }

        bool HashSumEventStream::hasNext() throw(IOException)
        {
          return eventStream->hasNext();
        }

        opennlp::model::Event *HashSumEventStream::next() throw(IOException)
        {

          Event *event_Renamed = eventStream->next();

          try
          {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
            digest->update(event_Renamed->toString()->getBytes("UTF-8"));
          }
          catch (UnsupportedEncodingException e)
          {
            throw IllegalStateException("UTF-8 encoding is not available!");
          }

          return event_Renamed;
        }

        BigInteger *HashSumEventStream::calculateHashSum()
        {

                //    if (hasNext())
                //      throw new IllegalStateException("stream must be consumed completely!");

          return new BigInteger(1, digest->digest());
        }

        void HashSumEventStream::remove()
        {
        }
    }
}
