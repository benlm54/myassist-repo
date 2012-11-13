#include "Span.h"
#include "CharSequence.h"
#include "StringBuffer.h"

namespace opennlp
{
    namespace tools
    {
        namespace util
        {

            Span::Span(int s, int e, const std::string &type) : start(s), end(e), type(type)
            {

              if (s < 0 || e < 0)
                throw IllegalArgumentException("start and end index must be zero or greater!");

              if (s > e)
                throw IllegalArgumentException("start index must not be larger than end index!");

            }

            Span::Span(int s, int e)
            {
            }

            Span::Span(Span *span, int offset)
            {
            }

            int Span::getStart()
            {
              return start;
            }

            int Span::getEnd()
            {
              return end;
            }

            std::string Span::getType()
            {
              return type;
            }

            int Span::length()
            {
              return end - start;
            }

            bool Span::contains(Span *s)
            {
              return start <= s->getStart() && s->getEnd() <= end;
            }

            bool Span::contains(int index)
            {
              return start <= index && index < end;
            }

            bool Span::startsWith(Span *s)
            {
              return getStart() == s->getStart() && contains(s);
            }

            bool Span::intersects(Span *s)
            {
              int sstart = s->getStart();
              //either s's start is in this or this' start is in s
              return this->contains(s) || s->contains(this) || getStart() <= sstart && sstart < getEnd() || sstart <= getStart() && getStart() < s->getEnd();
            }

            bool Span::crosses(Span *s)
            {
              int sstart = s->getStart();
              //either s's start is in this or this' start is in s
              return !this->contains(s) && !s->contains(this) && (getStart() <= sstart && sstart < getEnd() || sstart <= getStart() && getStart() < s->getEnd());
            }

            CharSequence *Span::getCoveredText(CharSequence *text)
            {
              if (getEnd() > text->length())
              {
                throw IllegalArgumentException("The span " + toString() + " is outside the given text!");
              }

              return text->subSequence(getStart(), getEnd());
            }

            int Span::compareTo(Span *s)
            {
              if (getStart() < s->getStart())
              {
                return -1;
              }
              else if (getStart() == s->getStart())
              {
                if (getEnd() > s->getEnd())
                {
                  return -1;
                }
                else if (getEnd() < s->getEnd())
                {
                  return 1;
                }
                else
                {
                  return 0;
                }
              }
              else
              {
                return 1;
              }
            }

            int Span::GetHashCode()
            {
              int res = 23;
              res = res * 37 + getStart();
              res = res * 37 + getEnd();
              if (getType() == "")
              {
                res = res * 37;
              }
              else
              {
                res = res * 37 + getType().hashCode();
              }

              return res;
            }

            bool Span::Equals(void *o)
            {

              bool result;

              if (o == this)
              {
                result = true;
              }
              else if (dynamic_cast<Span*>(o) != 0)
              {
                Span *s = static_cast<Span*>(o);

                result = (getStart() == s->getStart()) && (getEnd() == s->getEnd()) && (getType() != "" ? type == s->getType() : true) && (s->getType() != "" ? s->getType() == getType() : true);
              }
              else
              {
                result = false;
              }

              return result;
            }

            std::string Span::ToString()
            {
              StringBuffer *toStringBuffer = new StringBuffer(15);
              toStringBuffer->append("[");
              toStringBuffer->append(getStart());
              toStringBuffer->append("..");
              toStringBuffer->append(getEnd());
              toStringBuffer->append(")");

//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              return toStringBuffer->toString();
            }

            std::string *Span::spansToStrings(Span spans[], CharSequence *s)
            {
              std::string tokens[sizeof(spans) / sizeof(spans[0])];

              for (int si = 0, sl = sizeof(spans) / sizeof(spans[0]); si < sl; si++)
              {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                tokens[si] = spans[si]->getCoveredText(s)->toString();
              }

              return tokens;
            }

            std::string *Span::spansToStrings(Span spans[], std::string tokens[])
            {
              std::string chunks[sizeof(spans) / sizeof(spans[0])];
              StringBuffer *cb = new StringBuffer();
              for (int si = 0, sl = sizeof(spans) / sizeof(spans[0]); si < sl; si++)
              {
                cb->setLength(0);
                for (int ti = spans[si]->getStart();ti < spans[si]->getEnd();ti++)
                {
                  cb->append(tokens[ti])->append(" ");
                }
                chunks[si] = cb->substr(0, cb->length() - 1);
              }
              return chunks;
            }
        }
    }
}
