#include "POSSample.h"
#include "tools/tokenize/WhitespaceTokenizer.h"
#include "StringBuilder.h"

namespace opennlp
{
    namespace tools
    {
        namespace postag
        {
            using opennlp::tools::tokenize::WhitespaceTokenizer;
            using opennlp::tools::util::InvalidFormatException;

            POSSample::POSSample(std::string sentence[], std::string tags[])
            {
              this->sentence = Collections::unmodifiableList(std::vector<std::string>(Arrays::asList(sentence)));
              this->tags = Collections::unmodifiableList(std::vector<std::string>(Arrays::asList(tags)));

              checkArguments();
            }

            POSSample::POSSample(std::vector<std::string> &sentence, std::vector<std::string> &tags)
            {
              this->sentence = Collections::unmodifiableList(std::vector<std::string>(sentence));
              this->tags = Collections::unmodifiableList(std::vector<std::string>(tags));

              checkArguments();
            }

            void POSSample::checkArguments()
            {
              if (sentence.size() != tags.size())
                throw IllegalArgumentException("There must be exactly one tag for each token!");

                if (std::find(sentence.begin(), sentence.end(), 0) != sentence.end() || std::find(tags.begin(), tags.end(), 0) != tags.end())
                  throw IllegalArgumentException("null elements are not allowed!");
            }

            std::string *POSSample::getSentence()
            {
              return sentence.toArray(new std::string[sentence.size()]);
            }

            std::string *POSSample::getTags()
            {
              return tags.toArray(new std::string[tags.size()]);
            }

            std::string POSSample::ToString()
            {

              StringBuilder *result = new StringBuilder();

              for (int i = 0; i < sizeof(getSentence()) / sizeof(getSentence()[0]); i++)
              {
                result->append(getSentence()[i]);
                result->append('_');
                result->append(getTags()[i]);
                result->append(' ');
              }

              if (result->length() > 0)
              {
                // get rid of last space
                result->setLength(result->length() - 1);
              }

//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              return result->toString();
            }

            opennlp::tools::postag::POSSample *POSSample::parse(const std::string &sentenceString) throw(InvalidFormatException)
            {

//ORIGINAL LINE: String tokenTags[] = opennlp.tools.tokenize.WhitespaceTokenizer.INSTANCE.tokenize(sentenceString);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              std::string *tokenTags = WhitespaceTokenizer::INSTANCE->tokenize(sentenceString);

              std::string sentence[tokenTags->length];
              std::string tags[tokenTags->length];

              for (int i = 0; i < tokenTags->length; i++)
              {
                int split = tokenTags[i].rfind("_");

                if (split == -1)
                {
                  throw InvalidFormatException("Cannot find \"_\" inside token!");
                }

                sentence[i] = tokenTags[i].substr(0, split);
                tags[i] = tokenTags[i].substr(split + 1);
              }

              return new POSSample(sentence, tags);
            }

            bool POSSample::Equals(void *obj)
            {
              if (this == obj)
              {
                return true;
              }
              else if (dynamic_cast<POSSample*>(obj) != 0)
              {
                POSSample *a = static_cast<POSSample*>(obj);

                return Arrays::equals(getSentence(), a->getSentence()) && Arrays::equals(getTags(), a->getTags());
              }
              else
              {
                return false;
              }
            }
        }
    }
}
