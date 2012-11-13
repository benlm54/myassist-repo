#include "Conll02NameSampleStream.h"
#include "tools/util/StringUtil.h"

namespace opennlp
{
    namespace tools
    {
        namespace formats
        {
            using opennlp::tools::namefind::NameSample;
            using opennlp::tools::util::InvalidFormatException;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::PlainTextByLineStream;
            using opennlp::tools::util::Span;
            using opennlp::tools::util::StringUtil;
const std::string Conll02NameSampleStream::DOCSTART = "-DOCSTART-";

            Conll02NameSampleStream::Conll02NameSampleStream(LANGUAGE lang, ObjectStream<std::string> *lineStream, int types) : lang(lang), lineStream(lineStream), types(types)
            {
            }

            Conll02NameSampleStream::Conll02NameSampleStream(LANGUAGE lang, InputStream *in_Renamed, int types) : lang(lang), lineStream(new PlainTextByLineStream(in_Renamed, "UTF-8")), types(types)
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

            opennlp::tools::util::Span *Conll02NameSampleStream::extract(int begin, int end, const std::string &beginTag) throw(InvalidFormatException)
            {

              std::string type = beginTag.substr(2);

              if ((std::string("PER")) == type)
              {
                type = "person";
              }
              else if ((std::string("LOC")) == type)
              {
                type = "location";
              }
              else if ((std::string("MISC")) == type)
              {
                type = "misc";
              }
              else if ((std::string("ORG")) == type)
              {
                type = "organization";
              }
              else
              {
                throw InvalidFormatException("Unkonw type: " + type);
              }

              return new Span(begin, end, type);
            }

            opennlp::tools::namefind::NameSample *Conll02NameSampleStream::read() throw(IOException)
            {

              std::vector<std::string> sentence = std::vector<std::string>();
              std::vector<std::string> tags = std::vector<std::string>();

              bool isClearAdaptiveData = false;

              // Empty line indicates end of sentence

              std::string line;
              while ((line = lineStream->read()) != "" && !StringUtil::isEmpty(line))
              {

//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'startsWith' method:
                if (NL::equals(lang) && line.startsWith(DOCSTART))
                {
                  isClearAdaptiveData = true;
                  continue;
                }

//ORIGINAL LINE: String fields[] = line.split(" ");
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'split' method:
                std::string *fields = line.split(" ");

                if (fields->length == 3)
                {
                  sentence.push_back(fields[0]);
                  tags.push_back(fields[2]);
                }
                else
                {
                  throw IOException("Expected three fields per line in training data!");
                }
              }

              // Always clear adaptive data for spanish
              if (ES::equals(lang))
                isClearAdaptiveData = true;

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
                  if (tag.endsWith("PER") && (types & GENERATE_PERSON_ENTITIES) == 0)
                    tag = "O";

//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'endsWith' method:
                  if (tag.endsWith("ORG") && (types & GENERATE_ORGANIZATION_ENTITIES) == 0)
                    tag = "O";

//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'endsWith' method:
                  if (tag.endsWith("LOC") && (types & GENERATE_LOCATION_ENTITIES) == 0)
                    tag = "O";

//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'endsWith' method:
                  if (tag.endsWith("MISC") && (types & GENERATE_MISC_ENTITIES) == 0)
                    tag = "O";

//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'startsWith' method:
                  if (tag.startsWith("B-"))
                  {

                    if (beginIndex != -1)
                    {
                      names.push_back(extract(beginIndex, endIndex, tags[beginIndex]));
                      beginIndex = -1;
                      endIndex = -1;
                    }

                    beginIndex = i;
                    endIndex = i + 1;
                  }
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'startsWith' method:
                  else if (tag.startsWith("I-"))
                  {
                    endIndex++;
                  }
                  else if (tag == "O")
                  {
                    if (beginIndex != -1)
                    {
                      names.push_back(extract(beginIndex, endIndex, tags[beginIndex]));
                      beginIndex = -1;
                      endIndex = -1;
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

            void Conll02NameSampleStream::reset() throw(IOException, UnsupportedOperationException)
            {
              lineStream->reset();
            }

            void Conll02NameSampleStream::close() throw(IOException)
            {
              lineStream->close();
            }
        }
    }
}
