#include "NameFinderEventStream.h"
#include "tools/util/featuregen/WindowFeatureGenerator.h"
#include "tools/namefind/NameFinderME.h"
#include "model/EventStream.h"
#include "tools/namefind/NameSampleDataStream.h"
#include "tools/util/PlainTextByLineStream.h"

namespace opennlp
{
    namespace tools
    {
        namespace namefind
        {
            using opennlp::model::Event;
            using opennlp::model::EventStream;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::PlainTextByLineStream;
            using opennlp::tools::util::Span;
            using opennlp::tools::util::featuregen::AdditionalContextFeatureGenerator;
            using opennlp::tools::util::featuregen::WindowFeatureGenerator;

            NameFinderEventStream::NameFinderEventStream(ObjectStream<NameSample*> *dataStream, const std::string &type, NameContextGenerator *contextGenerator) : opennlp.tools.util.AbstractEventStream<NameSample>(dataStream)
            {
              InitializeInstanceFields();

              this->contextGenerator = contextGenerator;
              this->contextGenerator->addFeatureGenerator(new WindowFeatureGenerator(additionalContextFeatureGenerator, 8, 8));

              if (type != "")
                this->type = type;
              else
                this->type = "default";
            }

            NameFinderEventStream::NameFinderEventStream(ObjectStream<NameSample*> *dataStream)
            {
              InitializeInstanceFields();
            }

            std::string *NameFinderEventStream::generateOutcomes(Span names[], const std::string &type, int length)
            {
              std::string outcomes[length];
              for (int i = 0; i < sizeof(outcomes) / sizeof(outcomes[0]); i++)
              {
                outcomes[i] = NameFinderME::OTHER;
              }
              for (int nameIndex = 0; nameIndex < sizeof(names) / sizeof(names[0]); nameIndex++)
              {
                Span *name = names[nameIndex];
                if (name->getType() == "")
                {
                  outcomes[name->getStart()] = type + "-" + NameFinderME::START;
                }
                else
                {
                  outcomes[name->getStart()] = name->getType() + "-" + NameFinderME::START;
                }
                // now iterate from begin + 1 till end
                for (int i = name->getStart() + 1; i < name->getEnd(); i++)
                {
                  if (name->getType() == "")
                  {
                    outcomes[i] = type + "-" + NameFinderME::CONTINUE;
                  }
                  else
                  {
                    outcomes[i] = name->getType() + "-" + NameFinderME::CONTINUE;
                  }
                }
              }
              return outcomes;
            }

            std::vector<Event*> NameFinderEventStream::generateEvents(std::string sentence[], std::string outcomes[], NameContextGenerator *cg)
            {
              std::vector<Event*> events = std::vector<Event*>(sizeof(outcomes) / sizeof(outcomes[0]));
              for (int i = 0; i < sizeof(outcomes) / sizeof(outcomes[0]); i++)
              {
                events.push_back(new Event(outcomes[i], cg->getContext(i, sentence, outcomes,0)));
              }

              cg->updateAdaptiveData(sentence, outcomes);

              return events;
            }

            Iterator<Event*> *NameFinderEventStream::createEvents(NameSample *sample)
            {

              if (sample->isClearAdaptiveDataSet())
              {
                contextGenerator->clearAdaptiveData();
              }

//ORIGINAL LINE: String outcomes[] = generateOutcomes(sample.getNames(), type, sample.getSentence().length);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              std::string *outcomes = generateOutcomes(sample->getNames(), type, sizeof(sample->getSentence()) / sizeof(sample->getSentence()[0]));
              additionalContextFeatureGenerator->setCurrentContext(sample->getAdditionalContext());
              std::string tokens[sample->getSentence()->length];

              for (int i = 0; i < sizeof(sample->getSentence()) / sizeof(sample->getSentence()[0]); i++)
              {
                tokens[i] = sample->getSentence()[i];
              }

              return generateEvents(tokens, outcomes, contextGenerator).begin();
            }

            std::string **NameFinderEventStream::additionalContext(std::string tokens[], Map<std::string, std::string> *prevMap)
            {
              std::string ac[sizeof(tokens) / sizeof(tokens[0])][1];
              for (int ti = 0;ti < sizeof(tokens) / sizeof(tokens[0]);ti++)
              {
                std::string pt = prevMap->get(tokens[ti]);
                ac[ti][0] = "pd=" + pt;
              }
              return ac;

            }

            void NameFinderEventStream::main(std::string args[]) throw(java::io::IOException)
            {
              if (sizeof(args) / sizeof(args[0]) != 0)
              {
                System::err::println("Usage: NameFinderEventStream < training files");
                exit(1);
              }
              EventStream *es = new NameFinderEventStream(new NameSampleDataStream(new PlainTextByLineStream(new java::io::InputStreamReader(System::in))));
              while (es->hasNext())
              {
                std::cout << es->next() << std::endl;
                  es++;
              }
            }

            void NameFinderEventStream::InitializeInstanceFields()
            {
                additionalContextFeatureGenerator = new opennlp::tools::util::featuregen::AdditionalContextFeatureGenerator();
            }
        }
    }
}
