#include "NameFinderME.h"
#include "tools/namefind/DefaultNameContextGenerator.h"
#include "tools/util/featuregen/WindowFeatureGenerator.h"
#include "tools/namefind/NameFinderSequenceValidator.h"
#include "tools/util/featuregen/BigramNameFeatureGenerator.h"
#include "tools/util/featuregen/CachedFeatureGenerator.h"
#include "tools/util/featuregen/OutcomePriorFeatureGenerator.h"
#include "tools/util/featuregen/PreviousMapFeatureGenerator.h"
#include "tools/util/featuregen/SentenceFeatureGenerator.h"
#include "tools/util/featuregen/TokenClassFeatureGenerator.h"
#include "tools/util/featuregen/TokenFeatureGenerator.h"
#include "tools/util/featuregen/GeneratorFactory.h"
#include "model/AbstractModel.h"
#include "model/TrainUtil.h"
#include "tools/namefind/NameFinderEventStream.h"
#include "tools/namefind/NameSampleSequenceStream.h"
#include "tools/util/model/ModelUtil.h"
#include "maxent/GIS.h"
#include "model/TwoPassDataIndexer.h"

namespace opennlp
{
    namespace tools
    {
        namespace namefind
        {
            using opennlp::maxent::GIS;
            using opennlp::maxent::GISModel;
            using opennlp::model::AbstractModel;
            using opennlp::model::EventStream;
            using opennlp::model::MaxentModel;
            using opennlp::model::TrainUtil;
            using opennlp::model::TwoPassDataIndexer;
            using opennlp::tools::util::BeamSearch;
            using opennlp::tools::util::ObjectStream;
            using opennlp::tools::util::Sequence;
            using opennlp::tools::util::SequenceValidator;
            using opennlp::tools::util::Span;
            using opennlp::tools::util::TrainingParameters;
            using opennlp::tools::util::featuregen::AdaptiveFeatureGenerator;
            using opennlp::tools::util::featuregen::AdditionalContextFeatureGenerator;
            using opennlp::tools::util::featuregen::BigramNameFeatureGenerator;
            using opennlp::tools::util::featuregen::CachedFeatureGenerator;
            using opennlp::tools::util::featuregen::FeatureGeneratorResourceProvider;
            using opennlp::tools::util::featuregen::GeneratorFactory;
            using opennlp::tools::util::featuregen::OutcomePriorFeatureGenerator;
            using opennlp::tools::util::featuregen::PreviousMapFeatureGenerator;
            using opennlp::tools::util::featuregen::SentenceFeatureGenerator;
            using opennlp::tools::util::featuregen::TokenClassFeatureGenerator;
            using opennlp::tools::util::featuregen::TokenFeatureGenerator;
            using opennlp::tools::util::featuregen::WindowFeatureGenerator;
            using opennlp::tools::util::model::ModelUtil;
std::string **NameFinderME::EMPTY = new std::string*[0][0];
java::util::regex::Pattern *const NameFinderME::typedOutcomePattern = java::util::regex::Pattern::compile("(.+)-\\w+");
const std::string NameFinderME::START = "start";
const std::string NameFinderME::CONTINUE = "cont";
const std::string NameFinderME::OTHER = "other";

            NameFinderME::NameFinderME(TokenNameFinderModel *model)
            {
              InitializeInstanceFields();
            }

            NameFinderME::NameFinderME(TokenNameFinderModel *model, AdaptiveFeatureGenerator *generator, int beamSize, SequenceValidator<std::string> *sequenceValidator)
            {
              InitializeInstanceFields();
              this->model = model->getNameFinderModel();

              // If generator is provided always use that one
              if (generator != 0)
              {
                contextGenerator = new DefaultNameContextGenerator(generator);
              }
              else
              {
                // If model has a generator use that one, otherwise create default 
                AdaptiveFeatureGenerator *featureGenerator = model->createFeatureGenerators();

                if (featureGenerator == 0)
                  featureGenerator = createFeatureGenerator();

                contextGenerator = new DefaultNameContextGenerator(featureGenerator);
              }

              contextGenerator->addFeatureGenerator(new WindowFeatureGenerator(additionalContextFeatureGenerator, 8, 8));

              if (sequenceValidator == 0)
                sequenceValidator = new NameFinderSequenceValidator();

              beam = new BeamSearch<std::string>(beamSize, contextGenerator, this->model, sequenceValidator, beamSize);
            }

            NameFinderME::NameFinderME(TokenNameFinderModel *model, AdaptiveFeatureGenerator *generator, int beamSize)
            {
              InitializeInstanceFields();
            }

            NameFinderME::NameFinderME(TokenNameFinderModel *model, int beamSize)
            {
              InitializeInstanceFields();
            }

            NameFinderME::NameFinderME(MaxentModel *mod)
            {
              InitializeInstanceFields();
            }

            NameFinderME::NameFinderME(MaxentModel *mod, NameContextGenerator *cg)
            {
              InitializeInstanceFields();
            }

            NameFinderME::NameFinderME(MaxentModel *mod, NameContextGenerator *cg, int beamSize)
            {
              InitializeInstanceFields();
              model = mod;
              contextGenerator = cg;

              contextGenerator->addFeatureGenerator(new WindowFeatureGenerator(additionalContextFeatureGenerator, 8, 8));
              beam = new BeamSearch<std::string>(beamSize, cg, mod, new NameFinderSequenceValidator(), beamSize);
            }

            opennlp::tools::util::featuregen::AdaptiveFeatureGenerator *NameFinderME::createFeatureGenerator()
            {
             return new CachedFeatureGenerator(new AdaptiveFeatureGenerator[]{ new WindowFeatureGenerator(new TokenFeatureGenerator(), 2, 2), new WindowFeatureGenerator(new TokenClassFeatureGenerator(true), 2, 2), new OutcomePriorFeatureGenerator(), new PreviousMapFeatureGenerator(), new BigramNameFeatureGenerator(), new SentenceFeatureGenerator(true, false)
            });
        }

            opennlp::tools::util::featuregen::AdaptiveFeatureGenerator *NameFinderME::createFeatureGenerator(char generatorDescriptor[], Map<std::string, void*> *const resources) throw(IOException)
            {
              AdaptiveFeatureGenerator *featureGenerator;

              if (generatorDescriptor != 0)
              {
                featureGenerator = GeneratorFactory::create(new ByteArrayInputStream(generatorDescriptor), new FeatureGeneratorResourceProviderAnonymousInnerClassHelper();
              }
              else
              {
//JAVA TO C++ CONVERTER WARNING: Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
                delete featureGenerator;
              }

              return featureGenerator;
            }

            void *NameFinderME::FeatureGeneratorResourceProviderAnonymousInnerClassHelper::getResource(const std::string &key)
            {
              return resources->get(key);
            }

            Span *NameFinderME::find(std::string tokens[])
            {
              return find(tokens, EMPTY);
            }

            Span *NameFinderME::find(std::string tokens[], std::string additionalContext[][])
            {
              additionalContextFeatureGenerator->setCurrentContext(additionalContext);
              bestSequence = beam->bestSequence(tokens, additionalContext);

              std::vector<std::string> c = bestSequence->getOutcomes();

              contextGenerator->updateAdaptiveData(tokens, c.toArray(new std::string[c.size()]));

              int start = -1;
              int end = -1;
              std::vector<Span*> spans = std::vector<Span*>(sizeof(tokens) / sizeof(tokens[0]));
              for (int li = 0; li < c.size(); li++)
              {
                std::string chunkTag = c[li];
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'endsWith' method:
                if (chunkTag.endsWith(NameFinderME::START))
                {
                  if (start != -1)
                  {
                    spans.push_back(new Span(start, end, extractNameType(chunkTag)));
                  }

                  start = li;
                  end = li + 1;

                }
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'endsWith' method:
                else if (chunkTag.endsWith(NameFinderME::CONTINUE))
                {
                  end = li + 1;
                }
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'endsWith' method:
                else if (chunkTag.endsWith(NameFinderME::OTHER))
                {
                  if (start != -1)
                  {
                    spans.push_back(new Span(start, end, extractNameType(c[li - 1])));
                    start = -1;
                    end = -1;
                  }
                }
              }

              if (start != -1)
              {
                spans.push_back(new Span(start, end, extractNameType(c[c.size() - 1])));
              }

              return spans.toArray(new Span[spans.size()]);
            }

            void NameFinderME::clearAdaptiveData()
            {
             contextGenerator->clearAdaptiveData();
            }

            void NameFinderME::probs(double probs[])
            {
              bestSequence->getProbs(probs);
            }

            double *NameFinderME::probs()
            {
              return bestSequence->getProbs();
            }

            double *NameFinderME::probs(Span spans[])
            {

              double sprobs[sizeof(spans) / sizeof(spans[0])];
//ORIGINAL LINE: double[] probs = bestSequence.getProbs();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              double *probs = bestSequence->getProbs();

              for (int si = 0; si < sizeof(spans) / sizeof(spans[0]); si++)
              {

                double p = 0;

                for (int oi = spans[si]->getStart(); oi < spans[si]->getEnd(); oi++)
                {
                  p += probs[oi];
                }

                p /= spans[si]->length();

                sprobs[si] = p;
              }

              return sprobs;
            }

            opennlp::tools::namefind::TokenNameFinderModel *NameFinderME::train(const std::string &languageCode, const std::string &type, ObjectStream<NameSample*> *samples, TrainingParameters *trainParams, AdaptiveFeatureGenerator *generator, Map<std::string, void*> *const resources) throw(IOException)
            {

              Map<std::string, std::string> *manifestInfoEntries = std::map<std::string, std::string>();

              AdaptiveFeatureGenerator *featureGenerator;

              if (generator != 0)
                featureGenerator = generator;
              else
                featureGenerator = createFeatureGenerator();

              AbstractModel *nameFinderModel;

              if (!TrainUtil::isSequenceTraining(trainParams->getSettings()))
              {
                EventStream *eventStream = new NameFinderEventStream(samples, type, new DefaultNameContextGenerator(featureGenerator));

                nameFinderModel = TrainUtil::train(eventStream, trainParams->getSettings(), manifestInfoEntries);
              }
              else
              {
                NameSampleSequenceStream *ss = new NameSampleSequenceStream(samples, featureGenerator);

                nameFinderModel = TrainUtil::train(ss, trainParams->getSettings(), manifestInfoEntries);
              }

              return new TokenNameFinderModel(languageCode, nameFinderModel, resources, manifestInfoEntries);
            }

            opennlp::tools::namefind::TokenNameFinderModel *NameFinderME::train(const std::string &languageCode, const std::string &type, ObjectStream<NameSample*> *samples, TrainingParameters *trainParams, char featureGeneratorBytes[], Map<std::string, void*> *const resources) throw(IOException)
            {

              TokenNameFinderModel *model = train(languageCode, type, samples, trainParams, createFeatureGenerator(featureGeneratorBytes, resources), resources);

              // place the descriptor in the model
              if (featureGeneratorBytes != 0)
              {
                model = model->updateFeatureGenerator(featureGeneratorBytes);
              }

              return model;
            }

            opennlp::tools::namefind::TokenNameFinderModel *NameFinderME::train(const std::string &languageCode, const std::string &type, ObjectStream<NameSample*> *samples, AdaptiveFeatureGenerator *generator, Map<std::string, void*> *const resources, int iterations, int cutoff) throw(IOException)
            {
              return train(languageCode, type, samples, ModelUtil::createTrainingParameters(iterations, cutoff), generator, resources);
            }

            opennlp::tools::namefind::TokenNameFinderModel *NameFinderME::train(const std::string &languageCode, const std::string &type, ObjectStream<NameSample*> *samples, Map<std::string, void*> *const resources, int iterations, int cutoff) throw(IOException)
            {
               return train(languageCode, type, samples, static_cast<AdaptiveFeatureGenerator*>(0), resources, iterations, cutoff);
            }

            opennlp::tools::namefind::TokenNameFinderModel *NameFinderME::train(const std::string &languageCode, const std::string &type, ObjectStream<NameSample*> *samples, Map<std::string, void*> *const resources) throw(IOException)
            {
              return NameFinderME::train(languageCode, type, samples, resources, 100, 5);
            }

            opennlp::tools::namefind::TokenNameFinderModel *NameFinderME::train(const std::string &languageCode, const std::string &type, ObjectStream<NameSample*> *samples, char generatorDescriptor[], Map<std::string, void*> *const resources, int iterations, int cutoff) throw(IOException)
            {

               // TODO: Pass in resource manager ...

               AdaptiveFeatureGenerator *featureGenerator = createFeatureGenerator(generatorDescriptor, resources);

               TokenNameFinderModel *model = train(languageCode, type, samples, featureGenerator, resources, iterations, cutoff);

               if (generatorDescriptor != 0)
               {
                 model = model->updateFeatureGenerator(generatorDescriptor);
               }

               return model;
            }

            opennlp::maxent::GISModel *NameFinderME::train(EventStream *es, int iterations, int cut) throw(IOException)
            {
              return GIS::trainModel(iterations, new TwoPassDataIndexer(es, cut));
            }

            std::string NameFinderME::extractNameType(const std::string &outcome)
            {
              Matcher *matcher = typedOutcomePattern->matcher(outcome);
              if (matcher->matches())
              {
                std::string nameType = matcher->group(1);
                return nameType;
              }

              return 0;
            }

            Span *NameFinderME::dropOverlappingSpans(Span spans[])
            {

              std::vector<Span*> sortedSpans = std::vector<Span*>(sizeof(spans) / sizeof(spans[0]));
              Collections::addAll(sortedSpans, spans);
              Collections::sort(sortedSpans);

              std::vector<Span*>::const_iterator it = sortedSpans.begin();


              Span *lastSpan = 0;

              while (it != sortedSpans.end())
              {
                Span *span = *it;

                if (lastSpan != 0)
                {
                  if (lastSpan->intersects(span))
                  {
                    (*it)->remove();
                    span = lastSpan;
                  }
                }

                lastSpan = span;
                  it++;
              }

              return sortedSpans.toArray(new Span[sortedSpans.size()]);
            }

            void NameFinderME::InitializeInstanceFields()
            {
                additionalContextFeatureGenerator = new opennlp::tools::util::featuregen::AdditionalContextFeatureGenerator();
            }
    }
}
}
