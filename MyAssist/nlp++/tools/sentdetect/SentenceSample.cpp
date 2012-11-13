#include "SentenceSample.h"
#include "tools/cmdline/tokenizer/DictionaryDetokenizerTool.h"
#include "StringBuilder.h"
#include "DetokenizationOperation.h"

namespace opennlp
{
    namespace tools
    {
        namespace sentdetect
        {
            using opennlp::tools::cmdline::tokenizer::DictionaryDetokenizerTool;
            using opennlp::tools::tokenize::Detokenizer;
            using opennlp::tools::tokenize::Detokenizer::DetokenizationOperation;
            using opennlp::tools::util::Span;

            SentenceSample::SentenceSample(const std::string &document, ...) : document(document), sentences(Collections::unmodifiableList(std::vector<Span*>(Arrays::asList(sentences))))
            {
            }

            SentenceSample::SentenceSample(Detokenizer *detokenizer, std::string sentences[][]) : document(documentBuilder->toString()), sentences(Collections::unmodifiableList(spans))
            {

              std::vector<Span*> spans = std::vector<Span*>(sizeof(sentences) / sizeof(sentences[0]));

              StringBuilder *documentBuilder = new StringBuilder();

              for (std::string::const_iterator sentenceTokens = sentences->begin(); sentenceTokens != sentences->end(); ++sentenceTokens)
              {

//ORIGINAL LINE: opennlp.tools.tokenize.Detokenizer.DetokenizationOperation operations[] = detokenizer.detokenize(*sentenceTokens);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                Detokenizer::DetokenizationOperation *operations = detokenizer->detokenize(*sentenceTokens);

                std::string sampleSentence = DictionaryDetokenizerTool::detokenize(*sentenceTokens, operations);

                int beginIndex = documentBuilder->length();
                documentBuilder->append(sampleSentence);

                spans.push_back(new Span(beginIndex, documentBuilder->length()));
              }

            }

            std::string SentenceSample::getDocument()
            {
              return document;
            }

            Span *SentenceSample::getSentences()
            {
              return sentences.toArray(new Span[sentences.size()]);
            }

            std::string SentenceSample::ToString()
            {

              StringBuilder *documentBuilder = new StringBuilder();

              for (std::vector<Span*>::const_iterator sentSpan = sentences.begin(); sentSpan != sentences.end(); ++sentSpan)
              {
                documentBuilder->append((*sentSpan)->getCoveredText(document));
                documentBuilder->append("\n");
              }

//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              return documentBuilder->toString();
            }

            bool SentenceSample::Equals(void *obj)
            {
              if (this == obj)
              {
                return true;
              }
              else if (dynamic_cast<SentenceSample*>(obj) != 0)
              {
                SentenceSample *a = static_cast<SentenceSample*>(obj);

                return getDocument() == a->getDocument() && Arrays::equals(getSentences(), a->getSentences());
              }
              else
              {
                return false;
              }
            }
        }
    }
}
