#include "DefaultSDContextGenerator.h"
#include "tools/util/StringUtil.h"
#include "StringBuffer.h"
#include "CharSequence.h"
#include "StringBuilder.h"

namespace opennlp
{
    namespace tools
    {
        namespace sentdetect
        {
            using opennlp::tools::util::StringUtil;

            DefaultSDContextGenerator::DefaultSDContextGenerator(char eosCharacters[])
            {
            }

            DefaultSDContextGenerator::DefaultSDContextGenerator(Set<std::string> *inducedAbbreviations, char eosCharacters[])
            {
              this->inducedAbbreviations = inducedAbbreviations;
              this->eosCharacters = eosCharacters;
              buf = new StringBuffer();
              collectFeats = std::vector<std::string>();
            }

            std::string *DefaultSDContextGenerator::getContext(CharSequence *sb, int position)
            {

              /// <summary>
              /// String preceding the eos character in the eos token.
              /// </summary>
              std::string prefix;

              /// <summary>
              /// Space delimited token preceding token containing eos character.
              /// </summary>
              std::string previous;

              /// <summary>
              /// String following the eos character in the eos token.
              /// </summary>
              std::string suffix;

              /// <summary>
              /// Space delimited token following token containing eos character.
              /// </summary>
              std::string next;

              int lastIndex = sb->length() - 1;
              { // compute space previous and space next features.
                if (position > 0 && StringUtil::isWhitespace(sb[position - 1]))
                  collectFeats.push_back("sp");
                if (position < lastIndex && StringUtil::isWhitespace(sb[position + 1]))
                  collectFeats.push_back("sn");
                collectFeats.push_back("eos=" + sb[position]);
              }
              int prefixStart = previousSpaceIndex(sb, position);

              int c = position;
              { ///assign prefix, stop if you run into a period though otherwise stop at space
                while (--c > prefixStart)
                {
                  for (int eci = 0, ecl = eosCharacters->length; eci < ecl; eci++)
                  {
                    if (sb[c] == eosCharacters[eci])
                    {
                      prefixStart = c;
                      c++; // this gets us out of while loop.
                      break;
                    }
                  }
                }
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'trim' method:
                prefix = (new StringBuffer(sb->subSequence(prefixStart, position)))->toString()->trim();
              }
              int prevStart = previousSpaceIndex(sb, prefixStart);
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'trim' method:
              previous = (new StringBuffer(sb->subSequence(prevStart, prefixStart)))->toString()->trim();

              int suffixEnd = nextSpaceIndex(sb, position, lastIndex);
              {
                c = position;
                while (++c < suffixEnd)
                {
                  for (int eci = 0, ecl = eosCharacters->length; eci < ecl; eci++)
                  {
                    if (sb[c] == eosCharacters[eci])
                    {
                      suffixEnd = c;
                      c--; // this gets us out of while loop.
                      break;
                    }
                  }
                }
              }
              int nextEnd = nextSpaceIndex(sb, suffixEnd + 1, lastIndex + 1);
              if (position == lastIndex)
              {
                suffix = "";
                next = "";
              }
              else
              {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'trim' method:
                suffix = (new StringBuilder(sb->subSequence(position + 1, suffixEnd)))->toString()->trim();
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'trim' method:
                next = (new StringBuilder(sb->subSequence(suffixEnd + 1, nextEnd)))->toString()->trim();
              }

              collectFeatures(prefix,suffix,previous,next);

              std::string context[collectFeats.size()];
              context = collectFeats.toArray(context);
              collectFeats.clear();
              return context;
            }

            void DefaultSDContextGenerator::collectFeatures(const std::string &prefix, const std::string &suffix, const std::string &previous, const std::string &next)
            {
              buf->append("x=");
              buf->append(prefix);
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              collectFeats.push_back(buf->toString());
              buf->setLength(0);
              if (prefix != "")
              {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                collectFeats.push_back(int::toString(prefix.length()));
                if (isFirstUpper(prefix))
                {
                  collectFeats.push_back("xcap");
                }
                if (inducedAbbreviations->contains(prefix))
                {
                  collectFeats.push_back("xabbrev");
                }
              }

              buf->append("v=");
              buf->append(previous);
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              collectFeats.push_back(buf->toString());
              buf->setLength(0);
              if (previous != "")
              {
                if (isFirstUpper(previous))
                {
                  collectFeats.push_back("vcap");
                }
                if (inducedAbbreviations->contains(previous))
                {
                  collectFeats.push_back("vabbrev");
                }
              }

              buf->append("s=");
              buf->append(suffix);
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              collectFeats.push_back(buf->toString());
              buf->setLength(0);
              if (suffix != "")
              {
                if (isFirstUpper(suffix))
                {
                  collectFeats.push_back("scap");
                }
                if (inducedAbbreviations->contains(suffix))
                {
                  collectFeats.push_back("sabbrev");
                }
              }

              buf->append("n=");
              buf->append(next);
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              collectFeats.push_back(buf->toString());
              buf->setLength(0);
              if (next != "")
              {
                if (isFirstUpper(next))
                {
                  collectFeats.push_back("ncap");
                }
                if (inducedAbbreviations->contains(next))
                {
                  collectFeats.push_back("nabbrev");
                }
              }
            }

            bool DefaultSDContextGenerator::isFirstUpper(const std::string &s)
            {
              return isupper(s[0]);
            }

            int DefaultSDContextGenerator::previousSpaceIndex(CharSequence *sb, int seek)
            {
              seek--;
              while (seek > 0 && !StringUtil::isWhitespace(sb[seek]))
              {
                seek--;
              }
              if (seek > 0 && StringUtil::isWhitespace(sb[seek]))
              {
                while (seek > 0 && StringUtil::isWhitespace(sb[seek - 1]))
                  seek--;
                return seek;
              }
              return 0;
            }

            int DefaultSDContextGenerator::nextSpaceIndex(CharSequence *sb, int seek, int lastIndex)
            {
              seek++;
              char c;
              while (seek < lastIndex)
              {
                c = sb[seek];
                if (StringUtil::isWhitespace(c))
                {
                  while (sb->length() > seek + 1 && StringUtil::isWhitespace(sb[seek + 1]))
                    seek++;
                  return seek;
                }
                seek++;
              }
              return lastIndex;
            }
        }
    }
}
