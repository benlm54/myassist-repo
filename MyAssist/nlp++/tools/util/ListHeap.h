#ifndef LISTHEAP
#define LISTHEAP

#include "Heap.h"
#include "Heap<E>.h"
#include "E.h"
#include <string>
#include <vector>
#include <stdexcept>
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


            /// <summary>
            /// This class implements the heap interface using a <seealso cref="java.util.List"/> as the underlying
            /// data structure.  This heap allows values which are equals to be inserted.  The heap will
            /// return the top K values which have been added where K is specified by the size passed to
            /// the constructor. K+1 values are not gaurenteed to be kept in the heap or returned in a
            /// particular order.
            /// </summary>
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
            template<typename E> where E : Comparable<E>
            class ListHeap : public Heap<E>
            {
          private:
              std::vector<E> list;

              Comparator<E> *comp;

//JAVA TO C++ CONVERTER NOTE: The variable size was renamed since C++ does not allow variables with the same name as methods:
              int size_Renamed;

              E max;

              /// <summary>
              /// Creates a new heap with the specified size using the sorted based on the
              /// specified comparator. </summary>
              /// <param name="sz"> The size of the heap. </param>
              /// <param name="c"> The comparator to be used to sort heap elements. </param>
          public:
              ListHeap(int sz, Comparator<E> *c)
              {
                InitializeInstanceFields();
                size_Renamed = sz;
                comp = c;
                list = std::vector<E>(sz);
              }

              /// <summary>
              /// Creates a new heap of the specified size. </summary>
              /// <param name="sz"> The size of the new heap. </param>
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
              ListHeap(int sz) //this(sz, nullptr);
              {
                InitializeInstanceFields();
              }

          private:
              int parent(int i)
              {
                return (i - 1) / 2;
              }

              int left(int i)
              {
                return (i + 1) * 2 - 1;
              }

              int right(int i)
              {
                return (i + 1) * 2;
              }

          public:
              virtual int size()
              {
                return list.size();
              }

          private:
              void swap(int x, int y)
              {
                E ox = list[x];
                E oy = list[y];

                list[y] = ox;
                list[x] = oy;
              }

              bool lt(E o1, E o2)
              {
                if (comp != 0)
                {
                  return comp->compare(o1, o2) < 0;
                }
                else
                {
                  return o1->compare(o2) < 0;
                }
              }

              bool gt(E o1, E o2)
              {
                if (comp != 0)
                {
                  return comp->compare(o1, o2) > 0;
                }
                else
                {
                  return o1->compare(o2) > 0;
                }
              }

              void heapify(int i)
              {
                while (true)
                {
                  int l = left(i);
                  int r = right(i);
                  int smallest;

                  if (l < list.size() && lt(list[l], list[i]))
                    smallest = l;
                  else
                    smallest = i;

                  if (r < list.size() && lt(list[r], list[smallest]))
                    smallest = r;

                  if (smallest != i)
                  {
                    swap(smallest, i);
                    i = smallest;
                  }
                  else
                    break;
                }
              }

          public:
              virtual E extract()
              {
                if (list.empty())
                {
                  throw std::exception("Heap Underflow");
                }
                E top = list[0];
                int last = list.size() - 1;
                if (last != 0)
                {
                  list[0] = list.remove(last);
                  heapify(0);
                }
                else
                {
                  list.remove(last);
                }

                return top;
              }

              virtual E first()
              {
                if (list.empty())
                {
                  throw std::exception("Heap Underflow");
                }
                return list[0];
              }

              virtual E last()
              {
                if (list.empty())
                {
                  throw std::exception("Heap Underflow");
                }
                return max;
              }

              virtual void add(E o)
              {
                /* keep track of max to prevent unnecessary insertion */
                if (max == 0)
                {
                  max = o;
                }
                else if (gt(o, max))
                {
                  if (list.size() < size_Renamed)
                  {
                    max = o;
                  }
                  else
                  {
                    return;
                  }
                }
                list.push_back(o);

                int i = list.size() - 1;

                //percolate new node to correct position in heap.
                while (i > 0 && gt(list[parent(i)], o))
                {
                  list[i] = list[parent(i)];
                  i = parent(i);
                }

                list[i] = o;
              }

              virtual void clear()
              {
                list.clear();
              }

              virtual Iterator<E> *iterator()
              {
                return list.begin();
              }

              virtual bool isEmpty()
              {
                return this->list.empty();
              }

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct native C++ equivalents:
//ORIGINAL LINE: @Deprecated public static void main(String[] args)
              static void main(std::string args[])
              {
               Heap<int> *heap = new ListHeap<int>(5);
               for (int ai = 0;ai < sizeof(args) / sizeof(args[0]);ai++)
               {
                 heap->add(static_cast<int>(StringConverterHelper::fromString<int>(args[ai])));
               }
               while (!heap->isEmpty())
               {
                 std::cout << heap->extract() + " ";
               }
               std::cout << std::endl;
              }

            private:
                void InitializeInstanceFields()
                {
                    max = 0;
                }
            };

        }
    }
}


#endif	//#ifndef LISTHEAP
