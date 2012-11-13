#include "NameSample.h"
#include "tools/namefind/NameSampleDataStream.h"
#include "tools/tokenize/WhitespaceTokenizer.h"
#include "StringBuilder.h"

namespace opennlp
{
    namespace tools
    {
        namespace namefind
        {
            using opennlp::tools::tokenize::WhitespaceTokenizer;
            using opennlp::tools::util::Span;

            NameSample::NameSample(std::string sentence[], Span names[], std::string additionalContext[][], bool clearAdaptiveData) : sentence(Collections::unmodifiableList(std::vector<std::string>(Arrays::asList(sentence)))), names(new Span[0]), additionalContext(new std::string[sizeof(additionalContext) / sizeof(additionalContext[0])][]), isClearAdaptiveData(clearAdaptiveData)
            {

              if (sentence == 0)
              {
                throw IllegalArgumentException("sentence must not be null!");
              }

              if (names == 0)
              {
              }

              this->names = Collections::unmodifiableList(std::vector<Span*>(Arrays::asList(names)));

              if (additionalContext != 0)
              {

                for (int i = 0; i < sizeof(additionalContext) / sizeof(additionalContext[0]); i++)
                {
                  this->additionalContext[i] = new std::string[additionalContext[i].length];
                  System::arraycopy(additionalContext[i], 0, this->additionalContext[i], 0, additionalContext[i].length);
                }
              }
              else
              {
//JAVA TO C++ CONVERTER WARNING: Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
                delete[] this->additionalContext;
              }

              // TODO: Check that name spans are not overlapping, otherwise throw exception
            }

            NameSample::NameSample(std::string sentence[], Span names[], bool clearAdaptiveData)
            {
            }

            std::string *NameSample::getSentence()
            {
              return sentence.toArray(new std::string[sentence.size()]);
            }

            Span *NameSample::getNames()
            {
              return names.toArray(new Span[names.size()]);
            }

            std::string **NameSample::getAdditionalContext()
            {
              return additionalContext;
            }

            bool NameSample::isClearAdaptiveDataSet()
            {
              return isClearAdaptiveData;
            }

            bool NameSample::Equals(void *obj)
            {

              if (this == obj)
              {
                return true;
              }
              else if (dynamic_cast<NameSample*>(obj) != 0)
              {
                NameSample *a = static_cast<NameSample*>(obj);

                return Arrays::equals(getSentence(), a->getSentence()) && Arrays::equals(getNames(), a->getNames()) && Arrays::equals(getAdditionalContext(), a->getAdditionalContext()) && isClearAdaptiveDataSet() == a->isClearAdaptiveDataSet();
              }
              else
              {
                return false;
              }

            }

            std::string NameSample::ToString()
            {
              StringBuilder *result = new StringBuilder();

              // If adaptive data must be cleared insert an empty line
              // before the sample sentence line
              if (isClearAdaptiveDataSet())
                result->append("\n");

              for (int tokenIndex = 0; tokenIndex < sentence.size(); tokenIndex++)
              {
                // token

                for (int nameIndex = 0; nameIndex < names.size(); nameIndex++)
                {
                  if (names[nameIndex]->getStart() == tokenIndex)
                  {
                    // check if nameTypes is null, or if the nameType for this specific
                    // entity is empty. If it is, we leave the nameType blank.
                    if (names[nameIndex]->getType() == "")
                    {
                      result->append(NameSampleDataStream::START_TAG)->append(' ');
                    }
                    else
                    {
                      result->append(NameSampleDataStream::START_TAG_PREFIX)->append(names[nameIndex]->getType())->append("> ");
                    }
                  }

                  if (names[nameIndex]->getEnd() == tokenIndex)
                  {
                    result->append(NameSampleDataStream::END_TAG)->append(' ');
                  }
                }

                result->append(sentence[tokenIndex] + ' ');
              }

              if (sentence.size() > 1)
                result->setLength(result->length() - 1);

              for (int nameIndex = 0; nameIndex < names.size(); nameIndex++)
              {
                if (names[nameIndex]->getEnd() == sentence.size())
                {
                  result->append(' ')->append(NameSampleDataStream::END_TAG);
                }
              }

//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              return result->toString();
            }

            std::string NameSample::errorTokenWithContext(std::string sentence[], int index)
            {

              StringBuilder *errorString = new StringBuilder();

              // two token before
              if (index > 1)
                errorString->append(sentence[index - 2])->append(" ");

              if (index > 0)
                errorString->append(sentence[index - 1])->append(" ");

              // token itself
              errorString->append("###");
              errorString->append(sentence[index]);
              errorString->append("###")->append(" ");

              // two token after
              if (index + 1 < sizeof(sentence) / sizeof(sentence[0]))
                errorString->append(sentence[index + 1])->append(" ");

              if (index + 2 < sizeof(sentence) / sizeof(sentence[0]))
                errorString->append(sentence[index + 2]);

//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              return errorString->toString();
            }

java::util::regex::Pattern *const NameSample::START_TAG_PATTERN = java::util::regex::Pattern::compile("<START(:([^:>\\s]*))?>");

            opennlp::tools::namefind::NameSample *NameSample::parse(const std::string &taggedTokens, bool isClearAdaptiveData) throw(IOException)
              // TODO: Should throw another exception, and then convert it into an IOException in the stream
            {
//ORIGINAL LINE: String[] parts = opennlp.tools.tokenize.WhitespaceTokenizer.INSTANCE.tokenize(taggedTokens);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              std::string *parts = WhitespaceTokenizer::INSTANCE->tokenize(taggedTokens);

              std::vector<std::string> tokenList = std::vector<std::string>(parts->length);
              std::vector<Span*> nameList = std::vector<Span*>();

              std::string nameType = "";
              int startIndex = -1;
              int wordIndex = 0;

              // we check if at least one name has the a type. If no one has, we will
              // leave the NameType property of NameSample null.
              bool catchingName = false;

              for (int pi = 0; pi < parts->length; pi++)
              {
                Matcher *startMatcher = START_TAG_PATTERN->matcher(parts[pi]);
                if (startMatcher->matches())
                {
                  if (catchingName)
                  {
                    throw IOException("Found unexpected annotation" + " while handling a name sequence: " + errorTokenWithContext(parts, pi));
                  }
                  catchingName = true;
                  startIndex = wordIndex;
                  nameType = startMatcher->group(2);
                  if (nameType != "" && nameType.length() == 0)
                  {
                    throw IOException("Missing a name type: " + errorTokenWithContext(parts, pi));
                  }

                }
                else if (parts[pi] == NameSampleDataStream::END_TAG)
                {
                  if (catchingName == false)
                  {
                    throw IOException("Found unexpected annotation: " + errorTokenWithContext(parts, pi));
                  }
                  catchingName = false;
                  // create name
                  nameList.push_back(new Span(startIndex, wordIndex, nameType));

                }
                else
                {
                  tokenList.push_back(parts[pi]);
                  wordIndex++;
                }
              }
//ORIGINAL LINE: String[] sentence = tokenList.toArray(new String[tokenList.size()]);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              std::string *sentence = tokenList.toArray(new std::string[tokenList.size()]);
//ORIGINAL LINE: opennlp.tools.util.Span[] names = nameList.toArray(new opennlp.tools.util.Span[nameList.size()]);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              Span *names = nameList.toArray(new Span[nameList.size()]);

              return new NameSample(sentence, names, isClearAdaptiveData);
            }
        }
    }
}
