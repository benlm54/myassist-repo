#include "NameFinderCensus90NameStream.h"
#include "tools/util/StringUtil.h"

namespace opennlp
{
    namespace tools
    {
        namespace formats
        {
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::PlainTextByLineStream;
            using opennlp::tools::util::StringList;
            using opennlp::tools::util::StringUtil;

            NameFinderCensus90NameStream::NameFinderCensus90NameStream(ObjectStream<std::string> *lineStream) : locale(new Locale("en"); // locale is English), encoding(Charset::defaultCharset()), lineStream(lineStream)
            {
              // todo how do we find the encoding for an already open ObjectStream() ?
            }

            NameFinderCensus90NameStream::NameFinderCensus90NameStream(InputStream *in_Renamed, Charset *encoding) : locale(new Locale("en"); // locale is English), encoding(encoding), lineStream(gcnew PlainTextByLineStream(in_Renamed, this->encoding))
            {
            }

            opennlp::tools::util::StringList *NameFinderCensus90NameStream::read() throw(IOException)
            {
              std::string line = lineStream->read();
              StringList *name = 0;

              if ((line != "") && (!StringUtil::isEmpty(line)))
              {
                std::string name2;
                // find the location of the name separator in the line of data.
                int pos = line.find(' ');
                if ((pos != -1))
                {
                  std::string parsed = line.substr(0, pos);
                  // the data is in ALL CAPS ... so the easiest way is to convert
                  // back to standard mixed case.
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'startsWith' method:
                  if ((parsed.length() > 2) && (parsed.startsWith("MC")))
                  {
                    name2 = parsed.substr(0,1)->toUpperCase(locale) + parsed.substr(1, 1)->toLowerCase(locale) + parsed.substr(2, 1)->toUpperCase(locale) + parsed.substr(3)->toLowerCase(locale);
                  }
                  else
                  {
                    name2 = parsed.substr(0,1)->toUpperCase(locale) + parsed.substr(1)->toLowerCase(locale);
                  }
                  name = new StringList(new std::string[]{name2});
                }
              }

              return name;
            }

            void NameFinderCensus90NameStream::reset() throw(IOException, UnsupportedOperationException)
            {
              lineStream->reset();
            }

            void NameFinderCensus90NameStream::close() throw(IOException)
            {
              lineStream->close();
            }
        }
    }
}
