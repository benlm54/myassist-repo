#ifndef ABSTRACTCONTEXTGENERATOR
#define ABSTRACTCONTEXTGENERATOR

#include "Parse.h"
#include "Cons.h"
#include "StringBuilder.h"
#include "StringBuffer.h"
#include <string>
#include <vector>

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
        namespace parser
        {


            /// <summary>
            /// Abstract class containing many of the methods used to generate contexts for parsing.
            /// </summary>
            class AbstractContextGenerator
            {

          protected:
              static const std::string EOS;

              bool zeroBackOff;
              /// <summary>
              /// Set of punctuation to be used in generating features. </summary>
              Set<std::string> *punctSet;
              bool useLabel;

              /// <summary>
              /// Creates punctuation feature for the specified punctuation at the specified index based on the punctuation mark. </summary>
              /// <param name="punct"> The punctuation which is in context. </param>
              /// <param name="i"> The index of the punctuation with relative to the parse. </param>
              /// <returns> Punctuation feature for the specified parse and the specified punctuation at the specfied index. </returns>
              virtual std::string punct(Parse *punct, int i);

              /// <summary>
              /// Creates punctuation feature for the specified punctuation at the specfied index based on the punctuation's tag. </summary>
              /// <param name="punct"> The punctuation which is in context. </param>
              /// <param name="i"> The index of the punctuation relative to the parse. </param>
              /// <returns> Punctuation feature for the specified parse and the specified punctuation at the specfied index. </returns>
              virtual std::string punctbo(Parse *punct, int i);

              virtual std::string cons(Parse *p, int i);

              virtual std::string consbo(Parse *p, int i); //cons back-off

              /// <summary>
              /// Generates a string representing the grammar rule production that the specified parse
              /// is starting.  The rule is of the form p.type -> c.children[0..n].type. </summary>
              /// <param name="p"> The parse which stats teh production. </param>
              /// <param name="includePunctuation"> Whether punctuation should be included in the production. </param>
              /// <returns> a string representing the grammar rule production that the specified parse
              /// is starting. </returns>
              virtual std::string production(Parse *p, bool includePunctuation);

              virtual void cons2(std::vector<std::string> &features, Cons *c0, Cons *c1, Collection<Parse*> *punct1s, bool bigram);

              /// <summary>
              /// Creates cons features involving the 3 specified nodes and adds them to the specified feature list. </summary>
              /// <param name="features"> The list of features. </param>
              /// <param name="c0"> The first node. </param>
              /// <param name="c1"> The second node. </param>
              /// <param name="c2"> The third node. </param>
              /// <param name="punct1s"> The punctuation between the first and second node. </param>
              /// <param name="punct2s"> The punctuation between the second and third node. </param>
              /// <param name="trigram"> Specifies whether lexical tri-gram features between these nodes should be generated. </param>
              /// <param name="bigram1"> Specifies whether lexical bi-gram features between the first and second node should be generated. </param>
              /// <param name="bigram2"> Specifies whether lexical bi-gram features between the second and third node should be generated. </param>
              virtual void cons3(std::vector<std::string> &features, Cons *c0, Cons *c1, Cons *c2, Collection<Parse*> *punct1s, Collection<Parse*> *punct2s, bool trigram, bool bigram1, bool bigram2);

              /// <summary>
              /// Generates features for nodes surrounding a completed node of the specified type. </summary>
              /// <param name="node"> A surrounding node. </param>
              /// <param name="i"> The index of the surrounding node with respect to the completed node. </param>
              /// <param name="type"> The type of the completed node. </param>
              /// <param name="punctuation"> The punctuation adjacent and between the specified surrounding node. </param>
              /// <param name="features"> A list to which features are added. </param>
              virtual void surround(Parse *node, int i, const std::string &type, Collection<Parse*> *punctuation, std::vector<std::string> &features);

              /// <summary>
              /// Produces features to determine whether the specified child node is part of
              /// a complete constituent of the specified type and adds those features to the
              /// specfied list. </summary>
              /// <param name="child"> The parse node to consider. </param>
              /// <param name="i"> A string indicating the position of the child node. </param>
              /// <param name="type"> The type of constituent being built. </param>
              /// <param name="features"> List to add features to. </param>
              virtual void checkcons(Parse *child, const std::string &i, const std::string &type, std::vector<std::string> &features);

              virtual void checkcons(Parse *p1, Parse *p2, const std::string &type, std::vector<std::string> &features);

              /// <summary>
              /// Populates specified nodes array with left-most right frontier
              /// node with a unique head. If the right frontier doesn't contain
              /// enough nodes, then nulls are placed in the array elements. </summary>
              /// <param name="rf"> The current right frontier. </param>
              /// <param name="nodes"> The array to be populated. </param>
              virtual void getFrontierNodes(std::vector<Parse*> &rf, Parse nodes[]);

            };

        }
    }
}


#endif	//#ifndef ABSTRACTCONTEXTGENERATOR
