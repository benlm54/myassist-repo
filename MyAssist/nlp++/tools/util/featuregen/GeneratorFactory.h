#ifndef GENERATORFACTORY
#define GENERATORFACTORY

#include "AdaptiveFeatureGenerator.h"
#include "FeatureGeneratorResourceProvider.h"
#include "../tools/util/InvalidFormatException.h"
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
#include <string>
#include <list>
#include "stringconverter.h"

/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreemnets.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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

                /// <summary>
                /// Creates a set of feature generators based on a provided XML descriptor.
                /// 
                /// Example of an XML descriptor:
                /// 
                /// <generators>
                ///   <charngram min = "2" max = "5"/>
                ///   <definition/>
                ///   <cache>
                ///     <window prevLength = "3" nextLength = "3">
                ///       <generators>
                ///         <prevmap/>
                ///         <sentence/>
                ///         <tokenclass/>
                ///         <tokenpattern/>
                ///       </generators>
                ///     </window>
                ///   </cache>
                /// </generators>
                /// 
                /// Each XML element is mapped to a <seealso cref="GeneratorFactory.XmlFeatureGeneratorFactory"/> which
                /// is responsible to process the element and create the specified
                /// <seealso cref="AdaptiveFeatureGenerator"/>. Elements can contain other
                /// elements in this case it is the responsibility of the mapped factory to process
                /// the child elements correctly. In some factories this leads to recursive
                /// calls the 
                /// <seealso cref="GeneratorFactory.XmlFeatureGeneratorFactory#create(Element, FeatureGeneratorResourceProvider)"/>
                /// method.
                /// 
                /// In the example above the generators element is mapped to the
                /// <seealso cref="GeneratorFactory.AggregatedFeatureGeneratorFactory"/> which then
                /// creates all the aggregated <seealso cref="AdaptiveFeatureGenerator"/>s to
                /// accomplish this it evaluates the mapping with the same mechanism
                /// and gives the child element to the corresponding factories. All
                /// created generators are added to a new instance of the
                /// <seealso cref="AggregatedFeatureGenerator"/> which is then returned.
                /// </summary>
                class GeneratorFactory
                {

                  /// <summary>
                  /// The <seealso cref="XmlFeatureGeneratorFactory"/> is responsible to construct
                  /// an <seealso cref="AdaptiveFeatureGenerator"/> from an given XML <seealso cref="Element"/>
                  /// which contains all necessary configuration if any.
                  /// </summary>
              public:
                  class XmlFeatureGeneratorFactory
                  {

                    /// <summary>
                    /// Creates an <seealso cref="AdaptiveFeatureGenerator"/> from a the describing
                    /// XML element.
                    /// </summary>
                    /// <param name="generatorElement"> the element which contains the configuration </param>
                    /// <param name="resourceManager"> the resource manager which could be used
                    ///     to access referenced resources
                    /// </param>
                    /// <returns> the configured <seealso cref="AdaptiveFeatureGenerator"/> </returns>
                public:
                    virtual AdaptiveFeatureGenerator *create(org::w3c::dom::Element *generatorElement, FeatureGeneratorResourceProvider *resourceManager) = 0;
                  };

                  /// <seealso cref= AggregatedFeatureGenerator </seealso>
              public:
                  class AggregatedFeatureGeneratorFactory : public XmlFeatureGeneratorFactory
                  {

                public:
                    virtual AdaptiveFeatureGenerator *create(Element *generatorElement, FeatureGeneratorResourceProvider *resourceManager) throw(InvalidFormatException);

                    static void register_Renamed(Map<std::string, XmlFeatureGeneratorFactory*> *factoryMap);
                  };

                  /// <seealso cref= CachedFeatureGenerator </seealso>
              public:
                  class CachedFeatureGeneratorFactory : public XmlFeatureGeneratorFactory
                  {

                private:
                    CachedFeatureGeneratorFactory();

                public:
                    virtual AdaptiveFeatureGenerator *create(Element *generatorElement, FeatureGeneratorResourceProvider *resourceManager) throw(InvalidFormatException);

                    static void register_Renamed(Map<std::string, XmlFeatureGeneratorFactory*> *factoryMap);
                  };

                  /// <seealso cref= CharacterNgramFeatureGenerator </seealso>
              public:
                  class CharacterNgramFeatureGeneratorFactory : public XmlFeatureGeneratorFactory
                  {

                public:
                    virtual AdaptiveFeatureGenerator *create(Element *generatorElement, FeatureGeneratorResourceProvider *resourceManager) throw(InvalidFormatException);

                    static void register_Renamed(Map<std::string, XmlFeatureGeneratorFactory*> *factoryMap);
                  };

                  /// <seealso cref= DefinitionFeatureGenerator </seealso>
              public:
                  class DefinitionFeatureGeneratorFactory : public XmlFeatureGeneratorFactory
                  {

                private:
                    static const std::string ELEMENT_NAME;

                    DefinitionFeatureGeneratorFactory();

                public:
                    virtual AdaptiveFeatureGenerator *create(Element *generatorElement, FeatureGeneratorResourceProvider *resourceManager) throw(InvalidFormatException);

                    static void register_Renamed(Map<std::string, XmlFeatureGeneratorFactory*> *factoryMap);
                  };

                  /// <seealso cref= DictionaryFeatureGenerator </seealso>
              public:
                  class DictionaryFeatureGeneratorFactory : public XmlFeatureGeneratorFactory
                  {

                public:
                    virtual AdaptiveFeatureGenerator *create(Element *generatorElement, FeatureGeneratorResourceProvider *resourceManager) throw(InvalidFormatException);

                    static void register_Renamed(Map<std::string, XmlFeatureGeneratorFactory*> *factoryMap);
                  };

                  /// <seealso cref= PreviousMapFeatureGenerator </seealso>
              public:
                  class PreviousMapFeatureGeneratorFactory : public XmlFeatureGeneratorFactory
                  {

                public:
                    virtual AdaptiveFeatureGenerator *create(Element *generatorElement, FeatureGeneratorResourceProvider *resourceManager);

                    static void register_Renamed(Map<std::string, XmlFeatureGeneratorFactory*> *factoryMap);
                  };

                  // TODO: Add parameters ... 

                  /// <seealso cref= SentenceFeatureGenerator </seealso>
              public:
                  class SentenceFeatureGeneratorFactory : public XmlFeatureGeneratorFactory
                  {

                public:
                    virtual AdaptiveFeatureGenerator *create(Element *generatorElement, FeatureGeneratorResourceProvider *resourceManager);

                    static void register_Renamed(Map<std::string, XmlFeatureGeneratorFactory*> *factoryMap);
                  };

                  /// <seealso cref= TokenClassFeatureGenerator </seealso>
              public:
                  class TokenClassFeatureGeneratorFactory : public XmlFeatureGeneratorFactory
                  {

                public:
                    virtual AdaptiveFeatureGenerator *create(Element *generatorElement, FeatureGeneratorResourceProvider *resourceManager);

                    static void register_Renamed(Map<std::string, XmlFeatureGeneratorFactory*> *factoryMap);
                  };

              public:
                  class TokenFeatureGeneratorFactory : public XmlFeatureGeneratorFactory
                  {

                public:
                    virtual AdaptiveFeatureGenerator *create(Element *generatorElement, FeatureGeneratorResourceProvider *resourceManager);

                    static void register_Renamed(Map<std::string, XmlFeatureGeneratorFactory*> *factoryMap);
                  };

              public:
                  class BigramNameFeatureGeneratorFactory : public XmlFeatureGeneratorFactory
                  {

                public:
                    virtual AdaptiveFeatureGenerator *create(Element *generatorElement, FeatureGeneratorResourceProvider *resourceManager);

                    static void register_Renamed(Map<std::string, XmlFeatureGeneratorFactory*> *factoryMap);
                  };

                  /// <seealso cref= TokenPatternFeatureGenerator </seealso>
              public:
                  class TokenPatternFeatureGeneratorFactory : public XmlFeatureGeneratorFactory
                  {

                public:
                    virtual AdaptiveFeatureGenerator *create(Element *generatorElement, FeatureGeneratorResourceProvider *resourceManager);

                    static void register_Renamed(Map<std::string, XmlFeatureGeneratorFactory*> *factoryMap);
                  };

                  /// <seealso cref= WindowFeatureGenerator </seealso>
              public:
                  class WindowFeatureGeneratorFactory : public XmlFeatureGeneratorFactory
                  {

                public:
                    virtual AdaptiveFeatureGenerator *create(Element *generatorElement, FeatureGeneratorResourceProvider *resourceManager) throw(InvalidFormatException);

                    static void register_Renamed(Map<std::string, XmlFeatureGeneratorFactory*> *factoryMap);
                  };

              public:
                  class CustomFeatureGeneratorFactory : public XmlFeatureGeneratorFactory
                  {

                public:
                    virtual AdaptiveFeatureGenerator *create(Element *generatorElement, FeatureGeneratorResourceProvider *resourceManager) throw(InvalidFormatException);

                    static void register_Renamed(Map<std::string, XmlFeatureGeneratorFactory*> *factoryMap);
                  };

              private:
                  static Map<std::string, XmlFeatureGeneratorFactory*> *factories;

//JAVA TO C++ CONVERTER TODO TASK: Static constructors are not allowed in native C++:
                  static GeneratorFactory();

                  /// <summary>
                  /// Creates a <seealso cref="AdaptiveFeatureGenerator"/> for the provided element.
                  /// To accomplish this it looks up the corresponding factory by the
                  /// element tag name. The factory is then responsible for the creation
                  /// of the generator from the element.
                  /// </summary>
                  /// <param name="generatorElement"> </param>
                  /// <param name="resourceManager">
                  /// 
                  /// @return </param>
              public:
                  static AdaptiveFeatureGenerator *createGenerator(Element *generatorElement, FeatureGeneratorResourceProvider *resourceManager) throw(InvalidFormatException);

                  /// <summary>
                  /// Creates an <seealso cref="AdaptiveFeatureGenerator"/> from an provided XML descriptor.
                  /// 
                  /// Usually this XML descriptor contains a set of nested feature generators
                  /// which are then used to generate the features by one of the opennlp
                  /// components.
                  /// </summary>
                  /// <param name="xmlDescriptorIn"> the <seealso cref="InputStream"/> from which the descriptor
                  /// is read, the stream remains open and must be closed by the caller.
                  /// </param>
                  /// <param name="resourceManager"> the resource manager which is used to resolve resources
                  /// referenced by a key in the descriptor
                  /// </param>
                  /// <returns> created feature generators
                  /// </returns>
                  /// <exception cref="IOException"> if an error occurs during reading from the descriptor
                  ///     <seealso cref="InputStream"/> </exception>
                  static AdaptiveFeatureGenerator *create(InputStream *xmlDescriptorIn, FeatureGeneratorResourceProvider *resourceManager) throw(IOException, InvalidFormatException);
                };

            }
        }
    }
}


#endif	//#ifndef GENERATORFACTORY
