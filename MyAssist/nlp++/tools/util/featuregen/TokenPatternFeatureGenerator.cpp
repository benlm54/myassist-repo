#include "TokenPatternFeatureGenerator.h"
#include "tools/util/featuregen/FeatureGeneratorUtil.h"
#include "StringBuffer.h"

namespace opennlp
{
    namespace tools
    {
        namespace util
        {
            namespace featuregen
            {
                using opennlp::tools::tokenize::SimpleTokenizer;
                using opennlp::tools::tokenize::Tokenizer;

                TokenPatternFeatureGenerator::TokenPatternFeatureGenerator()
                {
                    InitializeInstanceFields();
                }

                TokenPatternFeatureGenerator::TokenPatternFeatureGenerator(Tokenizer *supportTokenizer)
                {
                    InitializeInstanceFields();
                    tokenizer = supportTokenizer;
                }

                void TokenPatternFeatureGenerator::createFeatures(std::vector<std::string> &feats, std::string toks[], int index, std::string preds[])
                {

//ORIGINAL LINE: String[] tokenized = tokenizer.tokenize(toks[index]);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                  std::string *tokenized = tokenizer->tokenize(toks[index]);

                  if (tokenized->length == 1)
                  {
                    feats.push_back("st=" + toks[index].toLowerCase());
                    return;
                  }

                  feats.push_back("stn=" + tokenized->length);

                  StringBuffer *pattern = new StringBuffer();

                  for (int i = 0; i < tokenized->length; i++)
                  {

                    if (i < tokenized->length - 1)
                    {
                      feats.push_back("pt2=" + FeatureGeneratorUtil::tokenFeature(tokenized[i]) + FeatureGeneratorUtil::tokenFeature(tokenized[i + 1]));
                    }

                    if (i < tokenized->length - 2)
                    {
                      feats.push_back("pt3=" + FeatureGeneratorUtil::tokenFeature(tokenized[i]) + FeatureGeneratorUtil::tokenFeature(tokenized[i + 1]) + FeatureGeneratorUtil::tokenFeature(tokenized[i + 2]));
                    }

                    pattern->append(FeatureGeneratorUtil::tokenFeature(tokenized[i]));

                    if (!noLetters->matcher(tokenized[i])->find())
                    {
                      feats.push_back("st=" + tokenized[i].toLowerCase());
                    }
                  }

//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                  feats.push_back("pta=" + pattern->toString());
                }

                void TokenPatternFeatureGenerator::InitializeInstanceFields()
                {
                    noLetters = java::util::regex::Pattern::compile("[^a-zA-Z]");
                }
            }
        }
    }
}
