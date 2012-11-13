#include "GeneratorFactory.h"
#include "tools/util/featuregen/AggregatedFeatureGenerator.h"
#include "tools/util/featuregen/CachedFeatureGenerator.h"
#include "tools/util/featuregen/CharacterNgramFeatureGenerator.h"
#include "tools/util/featuregen/OutcomePriorFeatureGenerator.h"
#include "tools/dictionary/Dictionary.h"
#include "tools/util/featuregen/DictionaryFeatureGenerator.h"
#include "tools/util/featuregen/PreviousMapFeatureGenerator.h"
#include "tools/util/featuregen/SentenceFeatureGenerator.h"
#include "tools/util/featuregen/TokenClassFeatureGenerator.h"
#include "tools/util/featuregen/TokenFeatureGenerator.h"
#include "tools/util/featuregen/BigramNameFeatureGenerator.h"
#include "tools/util/featuregen/TokenPatternFeatureGenerator.h"
#include "tools/util/featuregen/WindowFeatureGenerator.h"
#include "Element.h"
#include "NodeList.h"
#include "Node.h"
#include "NumberFormatException.h"
#include "Class.h"
#include "ClassNotFoundException.h"
#include "InstantiationException.h"
#include "IllegalAccessException.h"
#include "DocumentBuilderFactory.h"
#include "DocumentBuilder.h"
#include "ParserConfigurationException.h"
#include "Document.h"
#include "SAXException.h"

namespace opennlp
{
    namespace tools
    {
        namespace util
        {
            namespace featuregen
            {
                using javax::xml::parsers::DocumentBuilder;
                using javax::xml::parsers::DocumentBuilderFactory;
                using javax::xml::parsers::ParserConfigurationException;
                using opennlp::tools::dictionary::Dictionary;
                using opennlp::tools::util::InvalidFormatException;
                using org::w3c::dom::Element;
                using org::w3c::dom::Node;
                using org::w3c::dom::NodeList;
                using org::xml::sax::SAXException;

                opennlp::tools::util::featuregen::AdaptiveFeatureGenerator *GeneratorFactory::AggregatedFeatureGeneratorFactory::create(Element *generatorElement, FeatureGeneratorResourceProvider *resourceManager) throw(InvalidFormatException)
                {

                  Collection<AdaptiveFeatureGenerator*> *aggregatedGenerators = std::list<AdaptiveFeatureGenerator*>();

                  NodeList *childNodes = generatorElement->getChildNodes();

                  for (int i = 0; i < childNodes->getLength(); i++)
                  {
                    Node *childNode = childNodes->item(i);

                    if (dynamic_cast<Element*>(childNode) != 0)
                    {
                      Element *aggregatedGeneratorElement = static_cast<Element*>(childNode);

                      aggregatedGenerators->add(GeneratorFactory::createGenerator(aggregatedGeneratorElement, resourceManager));
                    }
                  }

                  return new AggregatedFeatureGenerator(aggregatedGenerators->toArray(new AdaptiveFeatureGenerator[aggregatedGenerators->size()]));
                }

                void GeneratorFactory::AggregatedFeatureGeneratorFactory::register_Renamed(Map<std::string, XmlFeatureGeneratorFactory*> *factoryMap)
                {
                  factoryMap->put("generators", new AggregatedFeatureGeneratorFactory());
                }

                GeneratorFactory::CachedFeatureGeneratorFactory::CachedFeatureGeneratorFactory()
                {
                }

                opennlp::tools::util::featuregen::AdaptiveFeatureGenerator *GeneratorFactory::CachedFeatureGeneratorFactory::create(Element *generatorElement, FeatureGeneratorResourceProvider *resourceManager) throw(InvalidFormatException)
                {

                  Element *cachedGeneratorElement = 0;

                  NodeList *kids = generatorElement->getChildNodes();

                  for (int i = 0; i < kids->getLength(); i++)
                  {
                    Node *childNode = kids->item(i);

                    if (dynamic_cast<Element*>(childNode) != 0)
                    {
                      cachedGeneratorElement = static_cast<Element*>(childNode);
                      break;
                    }
                  }

                  if (cachedGeneratorElement == 0)
                  {
                    throw InvalidFormatException("Could not find containing generator element!");
                  }

                  AdaptiveFeatureGenerator *chachedGenerator = GeneratorFactory::createGenerator(cachedGeneratorElement, resourceManager);

                  return new CachedFeatureGenerator(chachedGenerator);
                }

                void GeneratorFactory::CachedFeatureGeneratorFactory::register_Renamed(Map<std::string, XmlFeatureGeneratorFactory*> *factoryMap)
                {
                  factoryMap->put("cache", new CachedFeatureGeneratorFactory());
                }

                opennlp::tools::util::featuregen::AdaptiveFeatureGenerator *GeneratorFactory::CharacterNgramFeatureGeneratorFactory::create(Element *generatorElement, FeatureGeneratorResourceProvider *resourceManager) throw(InvalidFormatException)
                {

                  std::string minString = generatorElement->getAttribute("min");

                  int min;

                  try
                  {
                    min = StringConverterHelper::fromString<int>(minString);
                  }
                  catch (NumberFormatException e)
                  {
                    throw InvalidFormatException("min attribute is not a number!");
                  }

                  std::string maxString = generatorElement->getAttribute("max");

                  int max;

                  try
                  {
                    max = StringConverterHelper::fromString<int>(maxString);
                  }
                  catch (NumberFormatException e)
                  {
                    throw InvalidFormatException("max attribute is not a number!");
                  }

                  return new CharacterNgramFeatureGenerator(min, max);
                }

                void GeneratorFactory::CharacterNgramFeatureGeneratorFactory::register_Renamed(Map<std::string, XmlFeatureGeneratorFactory*> *factoryMap)
                {
                  factoryMap->put("charngram", new CharacterNgramFeatureGeneratorFactory());
                }

const std::string GeneratorFactory::DefinitionFeatureGeneratorFactory::ELEMENT_NAME = "definition";

                GeneratorFactory::DefinitionFeatureGeneratorFactory::DefinitionFeatureGeneratorFactory()
                {
                }

                opennlp::tools::util::featuregen::AdaptiveFeatureGenerator *GeneratorFactory::DefinitionFeatureGeneratorFactory::create(Element *generatorElement, FeatureGeneratorResourceProvider *resourceManager) throw(InvalidFormatException)
                {
                  return new OutcomePriorFeatureGenerator();
                }

                void GeneratorFactory::DefinitionFeatureGeneratorFactory::register_Renamed(Map<std::string, XmlFeatureGeneratorFactory*> *factoryMap)
                {
                  factoryMap->put(ELEMENT_NAME, new DefinitionFeatureGeneratorFactory());
                }

                opennlp::tools::util::featuregen::AdaptiveFeatureGenerator *GeneratorFactory::DictionaryFeatureGeneratorFactory::create(Element *generatorElement, FeatureGeneratorResourceProvider *resourceManager) throw(InvalidFormatException)
                {

                  std::string dictResourceKey = generatorElement->getAttribute("dict");

                  void *dictResource = resourceManager->getResource(dictResourceKey);

                  if (!(dynamic_cast<Dictionary*>(dictResource) != 0))
                  {
                    throw InvalidFormatException("No dictionary resource for key: " + dictResourceKey);
                  }

                  std::string prefix = generatorElement->getAttribute("prefix");

                  return new DictionaryFeatureGenerator(prefix, static_cast<Dictionary*>(dictResource));
                }

                void GeneratorFactory::DictionaryFeatureGeneratorFactory::register_Renamed(Map<std::string, XmlFeatureGeneratorFactory*> *factoryMap)
                {
                  factoryMap->put("dictionary", new DictionaryFeatureGeneratorFactory());
                }

                opennlp::tools::util::featuregen::AdaptiveFeatureGenerator *GeneratorFactory::PreviousMapFeatureGeneratorFactory::create(Element *generatorElement, FeatureGeneratorResourceProvider *resourceManager)
                {
                  return new PreviousMapFeatureGenerator();
                }

                void GeneratorFactory::PreviousMapFeatureGeneratorFactory::register_Renamed(Map<std::string, XmlFeatureGeneratorFactory*> *factoryMap)
                {
                  factoryMap->put("prevmap", new PreviousMapFeatureGeneratorFactory());
                }

                opennlp::tools::util::featuregen::AdaptiveFeatureGenerator *GeneratorFactory::SentenceFeatureGeneratorFactory::create(Element *generatorElement, FeatureGeneratorResourceProvider *resourceManager)
                {

                  std::string beginFeatureString = generatorElement->getAttribute("begin");

                  bool beginFeature = true;
                  if (beginFeatureString.length() != 0)
                    beginFeature = StringConverterHelper::fromString<bool>(beginFeatureString);

                  std::string endFeatureString = generatorElement->getAttribute("end");
                  bool endFeature = true;
                  if (endFeatureString.length() != 0)
                    endFeature = StringConverterHelper::fromString<bool>(endFeatureString);

                  return new SentenceFeatureGenerator(beginFeature, endFeature);
                }

                void GeneratorFactory::SentenceFeatureGeneratorFactory::register_Renamed(Map<std::string, XmlFeatureGeneratorFactory*> *factoryMap)
                {
                  factoryMap->put("sentence", new SentenceFeatureGeneratorFactory());
                }

                opennlp::tools::util::featuregen::AdaptiveFeatureGenerator *GeneratorFactory::TokenClassFeatureGeneratorFactory::create(Element *generatorElement, FeatureGeneratorResourceProvider *resourceManager)
                {
                  // TODO: Make it configurable ...
                  return new TokenClassFeatureGenerator(true);
                }

                void GeneratorFactory::TokenClassFeatureGeneratorFactory::register_Renamed(Map<std::string, XmlFeatureGeneratorFactory*> *factoryMap)
                {
                  factoryMap->put("tokenclass", new TokenClassFeatureGeneratorFactory());
                }

                opennlp::tools::util::featuregen::AdaptiveFeatureGenerator *GeneratorFactory::TokenFeatureGeneratorFactory::create(Element *generatorElement, FeatureGeneratorResourceProvider *resourceManager)
                {

                  return new TokenFeatureGenerator();
                }

                void GeneratorFactory::TokenFeatureGeneratorFactory::register_Renamed(Map<std::string, XmlFeatureGeneratorFactory*> *factoryMap)
                {
                  factoryMap->put("token", new TokenPatternFeatureGeneratorFactory());
                }

                opennlp::tools::util::featuregen::AdaptiveFeatureGenerator *GeneratorFactory::BigramNameFeatureGeneratorFactory::create(Element *generatorElement, FeatureGeneratorResourceProvider *resourceManager)
                {

                  return new BigramNameFeatureGenerator();
                }

                void GeneratorFactory::BigramNameFeatureGeneratorFactory::register_Renamed(Map<std::string, XmlFeatureGeneratorFactory*> *factoryMap)
                {
                  factoryMap->put("bigram", new BigramNameFeatureGeneratorFactory());
                }

                opennlp::tools::util::featuregen::AdaptiveFeatureGenerator *GeneratorFactory::TokenPatternFeatureGeneratorFactory::create(Element *generatorElement, FeatureGeneratorResourceProvider *resourceManager)
                {
                  return new TokenPatternFeatureGenerator();
                }

                void GeneratorFactory::TokenPatternFeatureGeneratorFactory::register_Renamed(Map<std::string, XmlFeatureGeneratorFactory*> *factoryMap)
                {
                  factoryMap->put("tokenpattern", new TokenPatternFeatureGeneratorFactory());
                }

                opennlp::tools::util::featuregen::AdaptiveFeatureGenerator *GeneratorFactory::WindowFeatureGeneratorFactory::create(Element *generatorElement, FeatureGeneratorResourceProvider *resourceManager) throw(InvalidFormatException)
                {

                  Element *nestedGeneratorElement = 0;

                  NodeList *kids = generatorElement->getChildNodes();

                  for (int i = 0; i < kids->getLength(); i++)
                  {
                    Node *childNode = kids->item(i);

                    if (dynamic_cast<Element*>(childNode) != 0)
                    {
                      nestedGeneratorElement = static_cast<Element*>(childNode);
                      break;
                    }
                  }

                  if (nestedGeneratorElement == 0)
                  {
                    throw InvalidFormatException("window feature generator must contain" + "a agregator element");
                  }

                  AdaptiveFeatureGenerator *nestedGenerator = GeneratorFactory::createGenerator(nestedGeneratorElement, resourceManager);

                  std::string prevLengthString = generatorElement->getAttribute("prevLength");

                  int prevLength;

                  try
                  {
                    prevLength = StringConverterHelper::fromString<int>(prevLengthString);
                  }
                  catch (NumberFormatException e)
                  {
                    throw InvalidFormatException("prevLength attribute is not a number!");
                  }

                  std::string nextLengthString = generatorElement->getAttribute("nextLength");

                  int nextLength;

                  try
                  {
                    nextLength = StringConverterHelper::fromString<int>(nextLengthString);
                  }
                  catch (NumberFormatException e)
                  {
                    throw InvalidFormatException("nextLength attribute is not a number!");
                  }

                  return new WindowFeatureGenerator(nestedGenerator, prevLength, nextLength);
                }

                void GeneratorFactory::WindowFeatureGeneratorFactory::register_Renamed(Map<std::string, XmlFeatureGeneratorFactory*> *factoryMap)
                {
                  factoryMap->put("window", new WindowFeatureGeneratorFactory());
                }

                opennlp::tools::util::featuregen::AdaptiveFeatureGenerator *GeneratorFactory::CustomFeatureGeneratorFactory::create(Element *generatorElement, FeatureGeneratorResourceProvider *resourceManager) throw(InvalidFormatException)
                {

                  std::string featureGeneratorClassName = generatorElement->getAttribute("class");

                  Class *featureGenClass;
                  try
                  {
                    featureGenClass = Class::forName(featureGeneratorClassName);
                  }
                  catch (ClassNotFoundException e)
                  {
                    throw NoClassDefFoundError(e->getMessage());
                  }

                  // TODO: How to inject configuration?
                  // TODO: How to provide access to resources?

                  // Special interface which defines configure method?!
                  // public interface CustomFeatureGenerator {
                  //   void initialize(Map<String, String>, FeatureGeneratoreResourceProvider)
                  //       throws InvalidFormatException;
                  // }

                  AdaptiveFeatureGenerator *generator = 0;
                  try
                  {
                    generator = static_cast<AdaptiveFeatureGenerator*>(featureGenClass->newInstance());
                  }
                  catch (InstantiationException e)
                  {
                    throw InvalidFormatException("Failed to instantiate custom class!", e);
                  }
                  catch (IllegalAccessException e)
                  {
                    throw InvalidFormatException("Failed to instantiate custom class!", e);
                  }

                  return generator;
                }

                void GeneratorFactory::CustomFeatureGeneratorFactory::register_Renamed(Map<std::string, XmlFeatureGeneratorFactory*> *factoryMap)
                {
                  factoryMap->put("custom", new CustomFeatureGeneratorFactory());
                }

java::util::Map<std::string, XmlFeatureGeneratorFactory*> *GeneratorFactory::factories = std::map<std::string, XmlFeatureGeneratorFactory*>();

                GeneratorFactory::GeneratorFactory()
                {
                  AggregatedFeatureGeneratorFactory::register_Renamed(factories);
                  CachedFeatureGeneratorFactory::register_Renamed(factories);
                  CharacterNgramFeatureGeneratorFactory::register_Renamed(factories);
                  DefinitionFeatureGeneratorFactory::register_Renamed(factories);
                  DictionaryFeatureGeneratorFactory::register_Renamed(factories);
                  PreviousMapFeatureGeneratorFactory::register_Renamed(factories);
                  SentenceFeatureGeneratorFactory::register_Renamed(factories);
                  TokenClassFeatureGeneratorFactory::register_Renamed(factories);
                  TokenFeatureGeneratorFactory::register_Renamed(factories);
                  BigramNameFeatureGeneratorFactory::register_Renamed(factories);
                  TokenPatternFeatureGeneratorFactory::register_Renamed(factories);
                  WindowFeatureGeneratorFactory::register_Renamed(factories);
                  CustomFeatureGeneratorFactory::register_Renamed(factories);
                }

                opennlp::tools::util::featuregen::AdaptiveFeatureGenerator *GeneratorFactory::createGenerator(Element *generatorElement, FeatureGeneratorResourceProvider *resourceManager) throw(InvalidFormatException)
                {

                  std::string elementName = generatorElement->getTagName();

                  XmlFeatureGeneratorFactory *generatorFactory = factories->get(elementName);

                  if (generatorFactory == 0)
                  {
                    throw InvalidFormatException("Unexpected element: " + elementName);
                  }

                  return generatorFactory->create(generatorElement, resourceManager);
                }

                opennlp::tools::util::featuregen::AdaptiveFeatureGenerator *GeneratorFactory::create(InputStream *xmlDescriptorIn, FeatureGeneratorResourceProvider *resourceManager) throw(IOException, InvalidFormatException)
                {

                  DocumentBuilderFactory *documentBuilderFacoty = DocumentBuilderFactory::newInstance();

                  DocumentBuilder *documentBuilder;

                  try
                  {
                    documentBuilder = documentBuilderFacoty->newDocumentBuilder();
                  }
                  catch (ParserConfigurationException e)
                  {
                    throw IllegalStateException(e);
                  }

                  org::w3c::dom::Document *xmlDescriptorDOM;

                  try
                  {
                    xmlDescriptorDOM = documentBuilder->parse(xmlDescriptorIn);
                  }
                  catch (SAXException e)
                  {
                    throw InvalidFormatException("Descriptor is not valid XML!", e);
                  }

                  Element *generatorElement = xmlDescriptorDOM->getDocumentElement();

                  return createGenerator(generatorElement, resourceManager);
                }
            }
        }
    }
}
