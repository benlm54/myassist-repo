#include "TokenSample.h"
#include "tools/tokenize/WhitespaceTokenizer.h"
#include "StringBuilder.h"
#include "DetokenizationOperation.h"
#include "const_iterator.h"

namespace opennlp
{
    namespace tools
    {
        namespace tokenize
        {
            using opennlp::tools::tokenize::Detokenizer::DetokenizationOperation;
            using opennlp::tools::util::Span;
const std::string TokenSample::DEFAULT_SEPARATOR_CHARS = "<SPLIT>";

            TokenSample::TokenSample(const std::string &text, Span tokenSpans[]) : separatorChars(DEFAULT_SEPARATOR_CHARS) : text(text), tokenSpans(Collections::unmodifiableList(std::vector<Span*>(Arrays::asList(tokenSpans))))
            {

              if (text == "")
                throw IllegalArgumentException("text must not be null!");

              if (tokenSpans == 0)
                throw IllegalArgumentException("tokenSpans must not be null! ");


              for (int i = 0; i < sizeof(tokenSpans) / sizeof(tokenSpans[0]); i++)
              {
                if (tokenSpans[i]->getStart() < 0 || tokenSpans[i]->getStart() > text.length() || tokenSpans[i]->getEnd() > text.length() || tokenSpans[i]->getEnd() < 0)
                {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                  throw IllegalArgumentException("Span " + tokenSpans[i]->toString() + " is out of bounds!");
                }
              }
            }

            TokenSample::TokenSample(Detokenizer *detokenizer, std::string tokens[]) : separatorChars(DEFAULT_SEPARATOR_CHARS) : text(sentence->toString()), tokenSpans(Collections::unmodifiableList(mergedTokenSpans))
            {

              StringBuilder *sentence = new StringBuilder();

//ORIGINAL LINE: opennlp.tools.tokenize.Detokenizer.DetokenizationOperation[] operations = detokenizer.detokenize(tokens);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              DetokenizationOperation *operations = detokenizer->detokenize(tokens);

              std::vector<Span*> mergedTokenSpans = std::vector<Span*>();

              for (int i = 0; i < operations->length; i++)
              {

                bool isSeparateFromPreviousToken = i > 0 && !DetokenizationOperation::MERGE_TO_RIGHT::equals(operations[i - 1]) && !DetokenizationOperation::MERGE_TO_LEFT::equals(operations[i]);

                if (isSeparateFromPreviousToken)
                {
                  sentence->append(' ');
                }

                int beginIndex = sentence->length();
                sentence->append(tokens[i]);
                mergedTokenSpans.push_back(new Span(beginIndex, sentence->length()));
              }

            }

            std::string TokenSample::getText()
            {
              return text;
            }

            Span *TokenSample::getTokenSpans()
            {
              return tokenSpans.toArray(new Span[tokenSpans.size()]);
            }

            std::string TokenSample::ToString()
            {

              StringBuilder *sentence = new StringBuilder();

              int lastEndIndex = -1;
              for (std::vector<Span*>::const_iterator token = tokenSpans.begin(); token != tokenSpans.end(); ++token)
              {

                if (lastEndIndex != -1)
                {

                  // If there are no chars between last token
                  // and this token insert the separator chars
                  // otherwise insert a space

                  std::string separator = "";
                  if (lastEndIndex == (*token)->getStart())
                    separator = separatorChars;
                  else
                    separator = " ";

                  sentence->append(separator);
                }

                sentence->append((*token)->getCoveredText(text));

                lastEndIndex = (*token)->getEnd();
              }

//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              return sentence->toString();
            }

            void TokenSample::addToken(StringBuilder *sample, std::vector<Span*> &tokenSpans, const std::string &token, bool isNextMerged)
            {

              int tokenSpanStart = sample->length();
              sample->append(token);
              int tokenSpanEnd = sample->length();

              tokenSpans.push_back(new Span(tokenSpanStart, tokenSpanEnd));

              if (!isNextMerged)
                  sample->append(" ");
            }

            opennlp::tools::tokenize::TokenSample *TokenSample::parse(const std::string &sampleString, const std::string &separatorChars)
            {

              if (sampleString == "" || separatorChars == "")
                  throw IllegalArgumentException("arguments must not be null!");

//ORIGINAL LINE: opennlp.tools.util.Span whitespaceTokenSpans[] = WhitespaceTokenizer.INSTANCE.tokenizePos(sampleString);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              Span *whitespaceTokenSpans = WhitespaceTokenizer::INSTANCE->tokenizePos(sampleString);

              // Pre-allocate 20% for newly created tokens
              std::vector<Span*> realTokenSpans = std::vector<Span*>(static_cast<int>(whitespaceTokenSpans->length * 1.2));

              StringBuilder *untaggedSampleString = new StringBuilder();

              for (Span::const_iterator whiteSpaceTokenSpan = whitespaceTokenSpans->begin(); whiteSpaceTokenSpan != whitespaceTokenSpans->end(); ++whiteSpaceTokenSpan)
              {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                std::string whitespaceToken = whiteSpaceTokenSpan->getCoveredText(sampleString)->toString();

                bool wasTokenReplaced = false;

                int tokStart = 0;
                int tokEnd = -1;
                while ((tokEnd = whitespaceToken.find(separatorChars, tokStart)) > -1)
                {

                  std::string token = whitespaceToken.substr(tokStart, tokEnd - tokStart);

                  addToken(untaggedSampleString, realTokenSpans, token, true);

                  tokStart = tokEnd + separatorChars.length();
                  wasTokenReplaced = true;
                }

                if (wasTokenReplaced)
                {
                  // If the token contains the split chars at least once
                  // a span for the last token must still be added
                  std::string token = whitespaceToken.substr(tokStart);

                  addToken(untaggedSampleString, realTokenSpans, token, false);
                }
                else
                {
                  // If it does not contain the split chars at lest once
                  // just copy the original token span

                  addToken(untaggedSampleString, realTokenSpans, whitespaceToken, false);
                }
              }

//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              return new TokenSample(untaggedSampleString->toString(), realTokenSpans.toArray(new Span[realTokenSpans.size()]));
            }

            bool TokenSample::Equals(void *obj)
            {
              if (this == obj)
              {
                return true;
              }
              else if (dynamic_cast<TokenSample*>(obj) != 0)
              {
                TokenSample *a = static_cast<TokenSample*>(obj);

                return getText() == a->getText() && Arrays::equals(getTokenSpans(), a->getTokenSpans());
              }
              else
              {
                return false;
              }
            }
        }
    }
}
