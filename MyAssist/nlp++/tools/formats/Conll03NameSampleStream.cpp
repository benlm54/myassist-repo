#include "Conll03NameSampleStream.h"
#include "tools/util/StringUtil.h"
#include "tools/util/Span.h"

namespace opennlp
{
    namespace tools
    {
        namespace formats
        {
            import static opennlp.tools.formats.Conll02NameSampleStream.extract;
            using opennlp::tools::namefind::NameSample;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::PlainTextByLineStream;
            using opennlp::tools::util::Span;
            using opennlp::tools::util::StringUtil;

            Conll03NameSampleStream::Conll03NameSampleStream(LANGUAGE lang, ObjectStream<std::string> *lineStream, int types) : lang(lang), lineStream(lineStream), types(types)
            {
            }

            Conll03NameSampleStream::Conll03NameSampleStream(LANGUAGE lang, InputStream *in_Renamed, int types) : lang(lang), lineStream(new PlainTextByLineStream(in_Renamed, "ISO-8859-1")), types(types)
            {

              try
              {
              }
              catch (UnsupportedEncodingException e)
              {
                // UTF-8 is available on all JVMs, will never happen
                throw IllegalStateException(e);
              }
            }

            opennlp::tools::namefind::NameSample *Conll03NameSampleStream::read() throw(IOException)
            {

              std::vector<std::string> sentence = std::vector<std::string>();
              std::vector<std::string> tags = std::vector<std::string>();

              bool isClearAdaptiveData = false;

              // Empty line indicates end of sentence

              std::string line;
              while ((line = lineStream->read()) != "" && !StringUtil::isEmpty(line))
              {

//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'startsWith' method:
                if (line.startsWith(Conll02NameSampleStream::DOCSTART))
                {
                  isClearAdaptiveData = true;
                  std::string emptyLine = lineStream->read();

                  if (!StringUtil::isEmpty(emptyLine))
                    throw IOException("Empty line after -DOCSTART- not empty!");

                  continue;
                }

//ORIGINAL LINE: String fields[] = line.split(" ");
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'split' method:
                std::string *fields = line.split(" ");

                // For English: WORD  POS-TAG SC-TAG NE-TAG
                if (EN::equals(lang) && (fields->length == 4))
                {
                  sentence.push_back(fields[0]);
                  tags.push_back(fields[3]); // 3 is NE-TAG
                }
                // For German: WORD  LEMA-TAG POS-TAG SC-TAG NE-TAG
                else if (DE::equals(lang) && (fields->length == 5))
                {
                  sentence.push_back(fields[0]);
                  tags.push_back(fields[4]); // 4 is NE-TAG
                }
                else
                {
                  throw IOException("Incorrect number of fields per line for language!");
                }
              }

              if (sentence.size() > 0)
              {

                // convert name tags into spans
                std::vector<Span*> names = std::vector<Span*>();

                int beginIndex = -1;
                int endIndex = -1;
                for (int i = 0; i < tags.size(); i++)
                {

                  std::string tag = tags[i];

//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'endsWith' method:
                  if (tag.endsWith("PER") && (types & Conll02NameSampleStream::GENERATE_PERSON_ENTITIES) == 0)
                    tag = "O";

//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'endsWith' method:
                  if (tag.endsWith("ORG") && (types & Conll02NameSampleStream::GENERATE_ORGANIZATION_ENTITIES) == 0)
                    tag = "O";

//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'endsWith' method:
                  if (tag.endsWith("LOC") && (types & Conll02NameSampleStream::GENERATE_LOCATION_ENTITIES) == 0)
                    tag = "O";

//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'endsWith' method:
                  if (tag.endsWith("MISC") && (types & Conll02NameSampleStream::GENERATE_MISC_ENTITIES) == 0)
                    tag = "O";

                  if (tag == "O")
                  {
                    // O means we don't have anything this round.
                    if (beginIndex != -1)
                    {
                      names.push_back(extract(beginIndex, endIndex, tags[beginIndex]));
                      beginIndex = -1;
                      endIndex = -1;
                    }
                  }
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'startsWith' method:
                  else if (tag.startsWith("B-"))
                  {
                    // B- prefix means we have two same entities next to each other
                    if (beginIndex != -1)
                    {
                      names.push_back(extract(beginIndex, endIndex, tags[beginIndex]));
                    }
                    beginIndex = i;
                    endIndex = i + 1;
                  }
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'startsWith' method:
                  else if (tag.startsWith("I-"))
                  {
                    // I- starts or continues a current name entity
                    if (beginIndex == -1)
                    {
                      beginIndex = i;
                      endIndex = i + 1;
                    }
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'endsWith' method:
                    else if (!tag.endsWith(tags[beginIndex].substr(1)))
                    {
                      // we have a new tag type following a tagged word series
                      // also may not have the same I- starting the previous!
                      names.push_back(extract(beginIndex, endIndex, tags[beginIndex]));
                      beginIndex = i;
                      endIndex = i + 1;
                    }
                    else
                    {
                      endIndex++;
                    }
                  }
                  else
                  {
                    throw IOException("Invalid tag: " + tag);
                  }
                }

                // if one span remains, create it here
                if (beginIndex != -1)
                  names.push_back(extract(beginIndex, endIndex, tags[beginIndex]));

                return new NameSample(sentence.toArray(new std::string[sentence.size()]), names.toArray(new Span[names.size()]), isClearAdaptiveData);
              }
              else if (line != "")
              {
                // Just filter out empty events, if two lines in a row are empty
                return read();
              }
              else
              {
                // source stream is not returning anymore lines
                return 0;
              }
            }

            void Conll03NameSampleStream::reset() throw(IOException, UnsupportedOperationException)
            {
              lineStream->reset();
            }

            void Conll03NameSampleStream::close() throw(IOException)
            {
              lineStream->close();
            }
        }
    }
}
