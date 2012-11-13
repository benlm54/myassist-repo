#include "TokenizerStream.h"
#include "tools/util/Span.h"

namespace opennlp
{
    namespace tools
    {
        namespace tokenize
        {
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::Span;

            TokenizerStream::TokenizerStream(Tokenizer *tokenizer, ObjectStream<std::string> *input)
            {
              this->tokenizer = tokenizer;
              this->input = input;
            }

            opennlp::tools::tokenize::TokenSample *TokenizerStream::read() throw(IOException)
            {
              std::string inputString = input->read();

              if (inputString != "")
              {
//ORIGINAL LINE: opennlp.tools.util.Span tokens[] = tokenizer.tokenizePos(inputString);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                Span *tokens = tokenizer->tokenizePos(inputString);

                return new TokenSample(inputString, tokens);
              }

              return 0;
            }

            void TokenizerStream::close() throw(IOException)
            {
              input->close();
            }

            void TokenizerStream::reset() throw(IOException, UnsupportedOperationException)
            {
              input->reset();
            }
        }
    }
}
