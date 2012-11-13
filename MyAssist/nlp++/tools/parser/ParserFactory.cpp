#include "ParserFactory.h"
#include "tools/parser/ParserType.h"
#include "tools/parser/AbstractBottomUpParser.h"

namespace opennlp
{
    namespace tools
    {
        namespace parser
        {

            ParserFactory::ParserFactory()
            {
            }

            opennlp::tools::parser::Parser *ParserFactory::create(ParserModel *model, int beamSize, double advancePercentage)
            {

              if (CHUNKING::equals(model->getParserType()))
              {
                return new opennlp::tools::parser::chunking::Parser(model, beamSize, advancePercentage);
              }
              else if (TREEINSERT::equals(model->getParserType()))
              {
                return new opennlp::tools::parser::treeinsert::Parser(model, beamSize, advancePercentage);
              }
              else
              {
                throw IllegalStateException("Unexpected ParserType: " + model->getParserType()::name());
              }
            }

            opennlp::tools::parser::Parser *ParserFactory::create(ParserModel *model)
            {
              return create(model, AbstractBottomUpParser::defaultBeamSize, AbstractBottomUpParser::defaultAdvancePercentage);
            }
        }
    }
}
