#include "ConllXPOSSampleStream.h"
#include "tools/util/InvalidFormatException.h"
#include "S.h"

namespace opennlp
{
    namespace tools
    {
        namespace formats
        {
            using opennlp::tools::postag::POSSample;
            using opennlp::tools::util::FilterObjectStream;
            using opennlp::tools::util::InvalidFormatException;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::ParagraphStream;
            using opennlp::tools::util::PlainTextByLineStream;

            ConllXPOSSampleStream::ConllXPOSSampleStream(ObjectStream<std::string> *lineStream) : opennlp.tools.util.FilterObjectStream<String, opennlp.tools.postag.POSSample>(new ParagraphStream(lineStream))
            {
            }

            ConllXPOSSampleStream::ConllXPOSSampleStream(Reader *in_Renamed) throw(IOException) : opennlp.tools.util.FilterObjectStream<String, opennlp.tools.postag.POSSample>(new ParagraphStream(new PlainTextByLineStream(in)))
            {
            }

            opennlp::tools::postag::POSSample *ConllXPOSSampleStream::read() throw(IOException)
            {

              // The CONLL-X data has a word per line and each line is tab separated
              // in the following format:
              // ID, FORM, LEMMA, CPOSTAG, POSTAG, ... (max 10 fields)

              // One paragraph contains a whole sentence and, the token
              // and tag will be read from the FORM and POSTAG field.

             std::string paragraph = samples->read();

             POSSample *sample = 0;

             if (paragraph != "")
             {

               // paragraph get lines
               BufferedReader *reader = new BufferedReader(new StringReader(paragraph));

               std::vector<std::string> tokens = std::vector<std::string>(100);
               std::vector<std::string> tags = std::vector<std::string>(100);

               std::string line;
               while ((line = reader->readLine()) != "")
               {

                 const int minNumberOfFields = 5;

//ORIGINAL LINE: String parts[] = line.split("\t");
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'split' method:
                 std::string *parts = line.split("\t");

                 if (parts->length >= minNumberOfFields)
                 {
                   tokens.push_back(parts[1]);
                   tags.push_back(parts[4]);
                 }
                 else
                 {
                   throw InvalidFormatException("Every non-empty line must have at least " + minNumberOfFields + " fields!");
                 }
               }

               // just skip empty samples and read next sample
               if (tokens.empty())
                 sample = read();

               sample = new POSSample(tokens.toArray(new std::string[tokens.size()]), tags.toArray(new std::string[tags.size()]));
             }

             return sample;
            }
        }
    }
}
