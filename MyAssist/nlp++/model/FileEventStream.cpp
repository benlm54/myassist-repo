#include "FileEventStream.h"
#include "model/EventStream.h"
#include "maxent/GIS.h"
#include "model/AbstractModel.h"
#include "maxent/io/SuffixSensitiveGISModelWriter.h"
#include "StringBuffer.h"

namespace opennlp
{
    namespace model
    {
        using opennlp::maxent::GIS;
        using opennlp::maxent::io::SuffixSensitiveGISModelWriter;

        FileEventStream::FileEventStream(const std::string &fileName, const std::string &encoding) throw(IOException)
        {
          if (encoding == "")
          {
            reader = new BufferedReader(new FileReader(fileName));
          }
          else
          {
            reader = new BufferedReader(new InputStreamReader(new FileInputStream(fileName),encoding));
          }
        }

        FileEventStream::FileEventStream(const std::string &fileName) throw(IOException)
        {
        }

        FileEventStream::FileEventStream(File *file) throw(IOException)
        {
          reader = new BufferedReader(new InputStreamReader(new FileInputStream(file),"UTF8"));
        }

        bool FileEventStream::hasNext()
        {
          try
          {
            return (0 != (line = reader->readLine()));
          }
          catch (IOException e)
          {
            System::err::println(e);
            return (false);
          }
        }

        opennlp::model::Event *FileEventStream::next()
        {
          StringTokenizer *st = new StringTokenizer(line);
          std::string outcome = st->nextToken();
          int count = st->countTokens();
          std::string context[count];
          for (int ci = 0; ci < count; ci++)
          {
            context[ci] = st->nextToken();
          }
          return (new Event(outcome, context));
        }

        std::string FileEventStream::toLine(Event *event_Renamed)
        {
          StringBuffer *sb = new StringBuffer();
          sb->append(event_Renamed->getOutcome());
//ORIGINAL LINE: String[] context = event.getContext();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
          std::string *context = event_Renamed->getContext();
          for (int ci = 0,cl = context->length;ci < cl;ci++)
          {
            sb->append(" " + context[ci]);
          }
          sb->append(System::getProperty("line.separator"));
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
          return sb->toString();
        }

        void FileEventStream::main(std::string args[]) throw(IOException)
        {
          if (sizeof(args) / sizeof(args[0]) == 0)
          {
            System::err::println("Usage: FileEventStream eventfile [iterations cutoff]");
            exit(1);
          }
          int ai = 0;
          std::string eventFile = args[ai++];
          EventStream *es = new FileEventStream(eventFile);
          int iterations = 100;
          int cutoff = 5;
          if (ai < sizeof(args) / sizeof(args[0]))
          {
            iterations = StringConverterHelper::fromString<int>(args[ai++]);
            cutoff = StringConverterHelper::fromString<int>(args[ai++]);
          }
          AbstractModel *model = GIS::trainModel(es,iterations,cutoff);
          (new SuffixSensitiveGISModelWriter(model, new File(eventFile + ".bin.gz")))->persist();
        }
    }
}
