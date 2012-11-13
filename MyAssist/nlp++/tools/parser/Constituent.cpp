#include "Constituent.h"

namespace opennlp
{
    namespace tools
    {
        namespace parser
        {
            using opennlp::tools::util::Span;

            Constituent::Constituent(const std::string &label, Span *span)
            {
              this->label = label;
              this->span = span;
            }

            std::string Constituent::getLabel()
            {
              return label;
            }

            void Constituent::setLabel(const std::string &label)
            {
              this->label = label;
            }

            opennlp::tools::util::Span *Constituent::getSpan()
            {
              return span;
            }
        }
    }
}
