#include "PlainTextByLineStream.h"

namespace opennlp
{
    namespace tools
    {
        namespace util
        {

            PlainTextByLineStream::PlainTextByLineStream(Reader *in_Renamed) : channel(delete this->channel), encoding("")
            {
              this->in_Renamed = new BufferedReader(in_Renamed);
            }

            PlainTextByLineStream::PlainTextByLineStream(InputStream *in_Renamed, const std::string &charsetName) throw(UnsupportedEncodingException)
            {
            }

            PlainTextByLineStream::PlainTextByLineStream(InputStream *in_Renamed, Charset *charset)
            {
            }

            PlainTextByLineStream::PlainTextByLineStream(FileChannel *channel, const std::string &charsetName) : channel(channel), encoding(charsetName)
            {

              // TODO: Why isn't reset called here ?
              in_Renamed = new BufferedReader(Channels::newReader(channel, encoding));
            }

            PlainTextByLineStream::PlainTextByLineStream(FileChannel *channel, Charset *encoding)
            {
            }

            std::string PlainTextByLineStream::read() throw(IOException)
            {
              return in_Renamed->readLine();
            }

            void PlainTextByLineStream::reset() throw(IOException)
            {

              if (channel == 0)
              {
                  in_Renamed->reset();
              }
              else
              {
                channel->position(0);
                in_Renamed = new BufferedReader(Channels::newReader(channel, encoding));
              }
            }

            void PlainTextByLineStream::close() throw(IOException)
            {
                if (channel == 0)
                {
                  in_Renamed->close();
                }
                else
                {
                 channel->close();
                }
            }
        }
    }
}
