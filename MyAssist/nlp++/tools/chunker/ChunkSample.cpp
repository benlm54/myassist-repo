#include "ChunkSample.h"
#include "StringBuilder.h"

namespace opennlp
{
    namespace tools
    {
        namespace chunker
        {
            using opennlp::tools::util::Span;

            ChunkSample::ChunkSample(std::string sentence[], std::string tags[], std::string preds[]) : sentence(Collections::unmodifiableList(std::vector<std::string>(Arrays::asList(sentence)))), tags(Collections::unmodifiableList(std::vector<std::string>(Arrays::asList(tags)))), preds(Collections::unmodifiableList(std::vector<std::string>(Arrays::asList(preds))))
            {

              validateArguments(sizeof(sentence) / sizeof(sentence[0]), sizeof(tags) / sizeof(tags[0]), sizeof(preds) / sizeof(preds[0]));

            }

            ChunkSample::ChunkSample(std::vector<std::string> &sentence, std::vector<std::string> &tags, std::vector<std::string> &preds) : sentence(Collections::unmodifiableList(std::vector<std::string>((sentence)))), tags(Collections::unmodifiableList(std::vector<std::string>((tags)))), preds(Collections::unmodifiableList(std::vector<std::string>((preds))))
            {

              validateArguments(sentence.size(), tags.size(), preds.size());

            }

            std::string *ChunkSample::getSentence()
            {
              return sentence.toArray(new std::string[sentence.size()]);
            }

            std::string *ChunkSample::getTags()
            {
              return tags.toArray(new std::string[tags.size()]);
            }

            std::string *ChunkSample::getPreds()
            {
              return preds.toArray(new std::string[preds.size()]);
            }

            Span *ChunkSample::getPhrasesAsSpanList()
            {
              return phrasesAsSpanList(getSentence(), getTags(), getPreds());
            }

            Span *ChunkSample::phrasesAsSpanList(std::string aSentence[], std::string aTags[], std::string aPreds[])
            {

              validateArguments(sizeof(aSentence) / sizeof(aSentence[0]), sizeof(aTags) / sizeof(aTags[0]), sizeof(aPreds) / sizeof(aPreds[0]));

              // initialize with the list maximum size
              std::vector<Span*> phrases = std::vector<Span*>(sizeof(aSentence) / sizeof(aSentence[0]));
              std::string startTag = "";
              int startIndex = 0;
              bool foundPhrase = false;

              for (int ci = 0, cn = sizeof(aPreds) / sizeof(aPreds[0]); ci < cn; ci++)
              {
                std::string pred = aPreds[ci];
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'startsWith' method:
                if (pred.startsWith("B-") || (pred != "I-" + startTag && pred != "O")) // start
                {
                  if (foundPhrase) // handle the last
                  {
                    phrases.push_back(new Span(startIndex, ci, startTag));
                  }
                  startIndex = ci;
                  startTag = pred.substr(2);
                  foundPhrase = true;
                } // middle
                else if (pred == "I-" + startTag)
                {
                  // do nothing
                } // end
                else if (foundPhrase)
                {
                  phrases.push_back(new Span(startIndex, ci, startTag));
                  foundPhrase = false;
                  startTag = "";
                }
              }
              if (foundPhrase) // leftover
              {
                phrases.push_back(new Span(startIndex, sizeof(aPreds) / sizeof(aPreds[0]), startTag));
              }

              return phrases.toArray(new Span[phrases.size()]);
            }

            void ChunkSample::validateArguments(int sentenceSize, int tagsSize, int predsSize) throw(IllegalArgumentException)
            {
              if (sentenceSize != tagsSize || tagsSize != predsSize)
                throw IllegalArgumentException("All arrays must have the same length!");
            }

            std::string ChunkSample::nicePrint()
            {

//ORIGINAL LINE: opennlp.tools.util.Span[] spans = getPhrasesAsSpanList();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                Span *spans = getPhrasesAsSpanList();

                StringBuilder *result = new StringBuilder(" ");

              for (int tokenIndex = 0; tokenIndex < sentence.size(); tokenIndex++)
              {
                for (int nameIndex = 0; nameIndex < spans->length; nameIndex++)
                {
                  if (spans[nameIndex]->getStart() == tokenIndex)
                  {
                    result->append("[" + spans[nameIndex]->getType())->append(" ");
                  }

                  if (spans[nameIndex]->getEnd() == tokenIndex)
                  {
                    result->append("]")->append(' ');
                  }
                }

                result->append(sentence[tokenIndex] + "_" + tags[tokenIndex] + ' ');
              }

              if (sentence.size() > 1)
                result->setLength(result->length() - 1);

              for (int nameIndex = 0; nameIndex < spans->length; nameIndex++)
              {
                if (spans[nameIndex]->getEnd() == sentence.size())
                {
                  result->append(']');
                }
              }

//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              return result->toString();
            }

            std::string ChunkSample::ToString()
            {

                  StringBuilder *chunkString = new StringBuilder();

                  for (int ci = 0; ci < preds.size(); ci++)
                  {
                      chunkString->append(sentence[ci] + " " + tags[ci] + " " + preds[ci] + "\n");
                  }
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                  return chunkString->toString();
            }

            bool ChunkSample::Equals(void *obj)
            {
              if (this == obj)
              {
                return true;
              }
              else if (dynamic_cast<ChunkSample*>(obj) != 0)
              {
                ChunkSample *a = static_cast<ChunkSample*>(obj);

                return Arrays::equals(getSentence(), a->getSentence()) && Arrays::equals(getTags(), a->getTags()) && Arrays::equals(getPreds(), a->getPreds());
              }
              else
              {
                return false;
              }
            }
        }
    }
}
