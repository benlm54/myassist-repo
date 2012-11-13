#ifndef SPAN
#define SPAN

#include "Comparable<Span>.h"
#include "CharSequence.h"
#include "StringBuffer.h"
#include <string>

/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
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

            /// <summary>
            /// Class for storing start and end integer offsets.
            /// 
            /// </summary>
            class Span : public Comparable<Span*>
            {

          private:
              const int start;
              const int end;

              const std::string type;

              /// <summary>
              /// Initializes a new Span Object.
              /// </summary>
              /// <param name="s"> start of span. </param>
              /// <param name="e"> end of span, which is +1 more than the last element in the span. </param>
              /// <param name="type"> the type of the span </param>
          public:
              Span(int s, int e, const std::string &type);

              /// <summary>
              /// Initializes a new Span Object.
              /// </summary>
              /// <param name="s"> start of span. </param>
              /// <param name="e"> end of span. </param>
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              Span(int s, int e); //this(s, e, nullptr);

              /// <summary>
              /// Initializes a new Span object with an existing Span
              /// which is shifted by an offset.
              /// </summary>
              /// <param name="span"> </param>
              /// <param name="offset"> </param>
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              Span(Span *span, int offset); //this(span.start + offset, span.end + offset, span.getType());

              /// <summary>
              /// Return the start of a span.
              /// </summary>
              /// <returns> the start of a span.
              ///  </returns>
              virtual int getStart();

              /// <summary>
              /// Return the end of a span.
              /// 
              /// Note: that the returned index is one past the
              /// actual end of the span in the text, or the first
              /// element past the end of the span.
              /// </summary>
              /// <returns> the end of a span.
              ///  </returns>
              virtual int getEnd();

              /// <summary>
              /// Retrieves the type of the span.
              /// </summary>
              /// <returns> the type or null if not set </returns>
              virtual std::string getType();

              /// <summary>
              /// Returns the length of this span.
              /// </summary>
              /// <returns> the length of the span. </returns>
              virtual int length();

              /// <summary>
              /// Returns true if the specified span is contained by this span.
              /// Identical spans are considered to contain each other.
              /// </summary>
              /// <param name="s"> The span to compare with this span.
              /// </param>
              /// <returns> true is the specified span is contained by this span;
              /// false otherwise. </returns>
              virtual bool contains(Span *s);

              /// <summary>
              /// Returns true if the specified index is contained inside this span.
              /// An index with the value of end is considered outside the span.
              /// </summary>
              /// <param name="index"> the index to test with this span.
              /// </param>
              /// <returns> true if the span contains this specified index;
              /// false otherwise. </returns>
              virtual bool contains(int index);

              /// <summary>
              /// Returns true if the specified span is the begin of this span and the
              /// specified span is contained in this span.
              /// </summary>
              /// <param name="s"> The span to compare with this span.
              /// </param>
              /// <returns> true if the specified span starts with this span and is
              /// contained in this span; false otherwise </returns>
              virtual bool startsWith(Span *s);

              /// <summary>
              /// Returns true if the specified span intersects with this span.
              /// </summary>
              /// <param name="s"> The span to compare with this span.
              /// </param>
              /// <returns> true is the spans overlap; false otherwise. </returns>
              virtual bool intersects(Span *s);

              /// <summary>
              /// Returns true is the specified span crosses this span.
              /// </summary>
              /// <param name="s"> The span to compare with this span.
              /// </param>
              /// <returns> true is the specified span overlaps this span and contains a
              /// non-overlapping section; false otherwise. </returns>
              virtual bool crosses(Span *s);

              /// <summary>
              /// Retrieves the string covered by the current span of the specified text.
              /// </summary>
              /// <param name="text">
              /// </param>
              /// <returns> the substring covered by the current span </returns>
              virtual CharSequence *getCoveredText(CharSequence *text);

              /// <summary>
              /// Compares the specified span to the current span.
              /// </summary>
              virtual int compareTo(Span *s);

              /// <summary>
              /// Generates a hash code of the current span.
              /// </summary>
              virtual int GetHashCode();

              /// <summary>
              /// Checks if the specified span is equal to the current span.
              /// </summary>
              virtual bool Equals(void *o);

              /// <summary>
              /// Generates a human readable string.
              /// </summary>
              virtual std::string ToString();

              /// <summary>
              /// Converts an array of <seealso cref="Span"/>s to an array of <seealso cref="String"/>s.
              /// </summary>
              /// <param name="spans"> </param>
              /// <param name="s"> </param>
              /// <returns> the strings </returns>
              static std::string *spansToStrings(Span spans[], CharSequence *s);

              static std::string *spansToStrings(Span spans[], std::string tokens[]);
            };

        }
    }
}


#endif	//#ifndef SPAN
