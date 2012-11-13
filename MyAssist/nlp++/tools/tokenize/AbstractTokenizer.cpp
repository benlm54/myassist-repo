#include "AbstractTokenizer.h"
#include "tools/util/Span.h"

namespace opennlp
{
    namespace tools
    {
        namespace tokenize
        {
            using opennlp::tools::util::Span;

            std::string *AbstractTokenizer::tokenize(const std::string &s)
            {
              return Span::spansToStrings(tokenizePos(s), s);
            }
        }
    }
}
