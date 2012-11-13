#include "Cons.h"

namespace opennlp
{
    namespace tools
    {
        namespace parser
        {

            Cons::Cons(const std::string &cons, const std::string &consbo, int index, bool unigram) : cons(cons), consbo(consbo), index(index), unigram(unigram)
            {
            }
        }
    }
}
