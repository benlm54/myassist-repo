#include "WhitespaceTokenStream.h"
#include "tools/util/Span.h"
#include "S.h"
#include "StringBuilder.h"
#include "const_iterator.h"

namespace opennlp
{
    namespace tools
    {
        namespace tokenize
        {
            using opennlp::tools::util::FilterObjectStream;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::Span;

            WhitespaceTokenStream::WhitespaceTokenStream(ObjectStream<TokenSample*> *tokens) : opennlp.tools.util.FilterObjectStream<TokenSample, String>(tokens)
            {
            }

            std::string WhitespaceTokenStream::read() throw(IOException)
            {
              TokenSample *tokenSample = samples->read();

              if (tokenSample != 0)
              {
                StringBuilder *whitespaceSeparatedTokenString = new StringBuilder();

                for (Span::const_iterator token = tokenSample->getTokenSpans()->begin(); token != tokenSample->getTokenSpans()->end(); ++token)
                {
                  whitespaceSeparatedTokenString->append(token->getCoveredText(tokenSample->getText()));
                  whitespaceSeparatedTokenString->append(' ');
                }

                // Shorten string by one to get rid of last space
                if (whitespaceSeparatedTokenString->length() > 0)
                {
                  whitespaceSeparatedTokenString->setLength(whitespaceSeparatedTokenString->length() - 1);
                }

//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                return whitespaceSeparatedTokenString->toString();
              }

              return 0;
            }
        }
    }
}
