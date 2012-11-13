#include "TokSpanEventStream.h"
#include "tools/tokenize/lang/Factory.h"
#include "tools/util/Span.h"
#include "tools/tokenize/WhitespaceTokenizer.h"
#include "tools/tokenize/TokenizerME.h"

namespace opennlp
{
    namespace tools
    {
        namespace tokenize
        {
            using opennlp::model::Event;
            using opennlp::tools::tokenize::lang::Factory;
            using opennlp::tools::util::AbstractEventStream;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::Span;
java::util::logging::Logger *TokSpanEventStream::logger = java::util::logging::Logger::getLogger(TokSpanEventStream::typeid::getName());

            TokSpanEventStream::TokSpanEventStream(ObjectStream<TokenSample*> *tokenSamples, bool skipAlphaNumerics, Pattern *alphaNumeric, TokenContextGenerator *cg) : opennlp.tools.util.AbstractEventStream<TokenSample>(tokenSamples), alphaNumeric(alphaNumeric)
            {
              this->skipAlphaNumerics = skipAlphaNumerics;
              this->cg = cg;
            }

            TokSpanEventStream::TokSpanEventStream(ObjectStream<TokenSample*> *tokenSamples, bool skipAlphaNumerics, TokenContextGenerator *cg) : opennlp.tools.util.AbstractEventStream<TokenSample>(tokenSamples), alphaNumeric(factory::getAlphanumeric(0))
            {
              Factory *factory = new Factory();
              this->skipAlphaNumerics = skipAlphaNumerics;
              this->cg = cg;
            }

            TokSpanEventStream::TokSpanEventStream(ObjectStream<TokenSample*> *tokenSamples, bool skipAlphaNumerics)
            {
            }

            Iterator<Event*> *TokSpanEventStream::createEvents(TokenSample *tokenSample)
            {

              std::vector<Event*> events = std::vector<Event*>(50);

//ORIGINAL LINE: opennlp.tools.util.Span tokens[] = tokenSample.getTokenSpans();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              Span *tokens = tokenSample->getTokenSpans();
              std::string text = tokenSample->getText();

              if (tokens->length > 0)
              {

                int start = tokens[0]->getStart();
                int end = tokens[tokens->length - 1]->getEnd();

                std::string sent = text.substr(start, end - start);

//ORIGINAL LINE: opennlp.tools.util.Span[] candTokens = WhitespaceTokenizer.INSTANCE.tokenizePos(sent);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                Span *candTokens = WhitespaceTokenizer::INSTANCE->tokenizePos(sent);

                int firstTrainingToken = -1;
                int lastTrainingToken = -1;
                for (int ci = 0; ci < candTokens->length; ci++)
                {
                  Span *cSpan = candTokens[ci];
                  std::string ctok = sent.substr(cSpan->getStart(), cSpan->getEnd() - (cSpan->getStart()));
                  //adjust cSpan to text offsets
                  cSpan = new Span(cSpan->getStart() + start, cSpan->getEnd() + start);
                  //should we skip this token
                  if (ctok.length() > 1 && (!skipAlphaNumerics || !alphaNumeric->matcher(ctok)->matches()))
                  {

                    //find offsets of annotated tokens inside of candidate tokens
                    bool foundTrainingTokens = false;
                    for (int ti = lastTrainingToken + 1; ti < tokens->length; ti++)
                    {
                      if (cSpan->contains(tokens[ti]))
                      {
                        if (!foundTrainingTokens)
                        {
                          firstTrainingToken = ti;
                          foundTrainingTokens = true;
                        }
                        lastTrainingToken = ti;
                      }
                      else if (cSpan->getEnd() < tokens[ti]->getEnd())
                      {
                        break;
                      }
                      else if (tokens[ti]->getEnd() < cSpan->getStart())
                      {
                        //keep looking
                      }
                      else
                      {
                        if (logger->isLoggable(Level::WARNING))
                        {
                          logger->warning("Bad training token: " + tokens[ti] + " cand: " + cSpan + " token=" + text.substr(tokens[ti]->getStart(), tokens[ti]->getEnd() - (tokens[ti]->getStart())));
                        }
                      }
                    }

                    // create training data
                    if (foundTrainingTokens)
                    {

                      for (int ti = firstTrainingToken; ti <= lastTrainingToken; ti++)
                      {
                        Span *tSpan = tokens[ti];
                        int cStart = cSpan->getStart();
                        for (int i = tSpan->getStart() + 1; i < tSpan->getEnd(); i++)
                        {
//ORIGINAL LINE: String[] context = cg.getContext(ctok, i - cStart);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                          std::string *context = cg->getContext(ctok, i - cStart);
                          events.push_back(new Event(TokenizerME::NO_SPLIT, context));
                        }

                        if (tSpan->getEnd() != cSpan->getEnd())
                        {
//ORIGINAL LINE: String[] context = cg.getContext(ctok, tSpan.getEnd() - cStart);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                          std::string *context = cg->getContext(ctok, tSpan->getEnd() - cStart);
                          events.push_back(new Event(TokenizerME::SPLIT, context));
                        }
                      }
                    }
                  }
                }
              }

              return events.begin();
            }
        }
    }
}
