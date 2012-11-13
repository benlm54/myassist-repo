#include "BioNLP2004NameSampleStream.h"
#include "tools/util/StringUtil.h"
#include "tools/util/Span.h"

namespace opennlp
{
    namespace tools
    {
        namespace formats
        {
            using opennlp::tools::namefind::NameSample;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::PlainTextByLineStream;
            using opennlp::tools::util::Span;
            using opennlp::tools::util::StringUtil;

            BioNLP2004NameSampleStream::BioNLP2004NameSampleStream(InputStream *in_Renamed, int types) : types(types), lineStream(new PlainTextByLineStream(in_Renamed, "UTF-8"))
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

            opennlp::tools::namefind::NameSample *BioNLP2004NameSampleStream::read() throw(IOException)
            {

              std::vector<std::string> sentence = std::vector<std::string>();
              std::vector<std::string> tags = std::vector<std::string>();

              bool isClearAdaptiveData = false;

              // Empty line indicates end of sentence

              std::string line;
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'trim' method:
              while ((line = lineStream->read()) != "" && !StringUtil::isEmpty(line.trim()))
              {

//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'startsWith' method:
                if (line.startsWith("###MEDLINE:"))
                {
                  isClearAdaptiveData = true;
                  lineStream->read();
                  continue;
                }

                if (line.find("ABSTRACT TRUNCATED") != string::npos)
                  continue;

//ORIGINAL LINE: String fields[] = line.split("\t");
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'split' method:
                std::string *fields = line.split("\t");

                if (fields->length == 2)
                {
                  sentence.push_back(fields[0]);
                  tags.push_back(fields[1]);
                }
                else
                {
                  throw IOException("Expected two fields per line in training data!");
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
                  if (tag.endsWith("DNA") && (types & GENERATE_DNA_ENTITIES) == 0)
                    tag = "O";

//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'endsWith' method:
                  if (tag.endsWith("protein") && (types & GENERATE_PROTEIN_ENTITIES) == 0)
                    tag = "O";

//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'endsWith' method:
                  if (tag.endsWith("cell_type") && (types & GENERATE_CELLTYPE_ENTITIES) == 0)
                    tag = "O";

//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'endsWith' method:
                  if (tag.endsWith("cell_line") && (types & GENERATE_CELLTYPE_ENTITIES) == 0)
                    tag = "O";
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'endsWith' method:
                  if (tag.endsWith("RNA") && (types & GENERATE_RNA_ENTITIES) == 0)
                    tag = "O";

//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'startsWith' method:
                  if (tag.startsWith("B-"))
                  {

                    if (beginIndex != -1)
                    {
                      names.push_back(new Span(beginIndex, endIndex, tags[beginIndex].substr(2)));
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
                      names.push_back(new Span(beginIndex, endIndex, tags[beginIndex].substr(2)));
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
                  names.push_back(new Span(beginIndex, endIndex, tags[beginIndex].substr(2)));

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

            void BioNLP2004NameSampleStream::reset() throw(IOException, UnsupportedOperationException)
            {
              lineStream->reset();
            }

            void BioNLP2004NameSampleStream::close() throw(IOException)
            {
              lineStream->close();
            }
        }
    }
}
