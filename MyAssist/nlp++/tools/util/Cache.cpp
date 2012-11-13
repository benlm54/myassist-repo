#include "Cache.h"

namespace opennlp
{
    namespace tools
    {
        namespace util
        {

            Cache::Cache(int size)
            {
              map = std::map(size);
              wrappers = new ObjectWrapper[size];
              this->size_Renamed = size;
              void *o = new Object();
              first = new DoubleLinkedListElement(0, 0, o);
              map->put(o, new ObjectWrapper(0, first));
              wrappers[0] = new ObjectWrapper(0, first);

              DoubleLinkedListElement *e = first;
              for (int i = 1; i < size; i++)
              {
                o = new Object();
                e = new DoubleLinkedListElement(e, 0, o);
                wrappers[i] = new ObjectWrapper(0, e);
                map->put(o, wrappers[i]);
                e->prev->next = e;
              }
              last = e;
            }

            void Cache::clear()
            {
              map->clear();
              DoubleLinkedListElement *e = first;
              for (int oi = 0;oi < size_Renamed;oi++)
              {
//JAVA TO C++ CONVERTER WARNING: Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
                delete wrappers[oi]->object;
                void *o = new Object();
                map->put(o,wrappers[oi]);
                e->object = o;
                e = e->next;
              }
            }

            void *Cache::put(void *key, void *value)
            {
              ObjectWrapper *o = static_cast<ObjectWrapper*>(map->get(key));
              if (o != 0)
              {
                /*
                 * this should never be the case, we only do a put on a cache miss which
                 * means the current value wasn't in the cache. However if the user screws
                 * up or wants to use this as a fixed size hash and puts the same thing in
                 * the list twice then we update the value and more the key to the front of the
                 * most recently used list.
                 */

                // Move o's partner in the list to front
                DoubleLinkedListElement *e = o->listItem;

                //move to front
                if (e != first)
                {
                  //remove list item
                  e->prev->next = e->next;
                  if (e->next != 0)
                  {
                    e->next->prev = e->prev;
                  }
                  else //were moving last
                  {
                    last = e->prev;
                  }

                  //put list item in front
                  e->next = first;
                  first->prev = e;
//JAVA TO C++ CONVERTER WARNING: Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
                  delete e->prev;

                  //update first
                  first = e;
                }
                return o->object;
              }
              // Put o in the front and remove the last one
              lastKey = last->object; // store key to remove from hash later
              last->object = key; //update list element with new key

              // connect list item to front of list
              last->next = first;
              first->prev = last;

              // update first and last value
              first = last;
              last = last->prev;
//JAVA TO C++ CONVERTER WARNING: Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
              delete first->prev;
//JAVA TO C++ CONVERTER WARNING: Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
              delete last->next;

              // remove old value from cache
              temp = static_cast<ObjectWrapper*>(map->remove(lastKey));
              //update wrapper
              temp->object = value;
              temp->listItem = first;

              map->put(key, temp);
              return 0;
            }

            void *Cache::get_Renamed(void *key)
            {
              ObjectWrapper *o = static_cast<ObjectWrapper*>(map->get(key));
              if (o != 0)
              {
                // Move it to the front
                DoubleLinkedListElement *e = o->listItem;

                //move to front
                if (e != first)
                {
                  //remove list item
                  e->prev->next = e->next;
                  if (e->next != 0)
                  {
                    e->next->prev = e->prev;
                  }
                  else //were moving last
                  {
                    last = e->prev;
                  }
                  //put list item in front
                  e->next = first;
                  first->prev = e;
//JAVA TO C++ CONVERTER WARNING: Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
                  delete e->prev;

                  //update first
                  first = e;
                }
                return o->object;
              }
              else
              {
                return 0;
              }
            }

            bool Cache::containsKey(void *key)
            {
              return map->containsKey(key);
            }

            bool Cache::containsValue(void *value)
            {
              return map->containsValue(value);
            }

            Set *Cache::entrySet()
            {
              return map->entrySet();
            }

            bool Cache::isEmpty()
            {
              return map->isEmpty();
            }

            Set *Cache::keySet()
            {
              return map->keySet();
            }

            void Cache::putAll(Map *t)
            {
              map->putAll(t);
            }

            void *Cache::remove(void *key)
            {
              return map->remove(key);
            }

            int Cache::size()
            {
              return map->size();
            }

            Collection *Cache::values()
            {
              return map->values();
            }

            ObjectWrapper::ObjectWrapper(void *o, DoubleLinkedListElement *li)
            {
              object = o;
              listItem = li;
            }

            void *ObjectWrapper::getObject()
            {
              return object;
            }

            opennlp::tools::util::DoubleLinkedListElement *ObjectWrapper::getListItem()
            {
              return listItem;
            }

            void ObjectWrapper::setObject(void *o)
            {
              object = o;
            }

            void ObjectWrapper::setListItem(DoubleLinkedListElement *li)
            {
              listItem = li;
            }

            bool ObjectWrapper::eqauls(void *o)
            {
              return object->equals(o);
            }

            DoubleLinkedListElement::DoubleLinkedListElement(DoubleLinkedListElement *p, DoubleLinkedListElement *n, void *o)
            {
              prev = p;
              next = n;
              object = o;

              if (p != 0)
              {
                  p->next = this;
              }

              if (n != 0)
              {
                  n->prev = this;
              }
            }

            DoubleLinkedList::DoubleLinkedList()
            {
//JAVA TO C++ CONVERTER WARNING: Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
              delete first;
//JAVA TO C++ CONVERTER WARNING: Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
              delete last;
//JAVA TO C++ CONVERTER WARNING: Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
              delete current;
            }

            void DoubleLinkedList::addFirst(void *o)
            {
              first = new DoubleLinkedListElement(0, first, o);

              if (current->next == 0)
              {
                  last = current;
              }
            }

            void DoubleLinkedList::addLast(void *o)
            {
              last = new DoubleLinkedListElement(last, 0, o);

              if (current->prev == 0)
              {
                  first = current;
              }
            }

            void DoubleLinkedList::insert(void *o)
            {
              if (current == 0)
              {
                  current = new DoubleLinkedListElement(0, 0, o);
              }
              else
              {
                  current = new DoubleLinkedListElement(current->prev, current, o);
              }

              if (current->prev == 0)
              {
                  first = current;
              }

              if (current->next == 0)
              {
                  last = current;
              }
            }

            opennlp::tools::util::DoubleLinkedListElement *DoubleLinkedList::getFirst()
            {
              current = first;
              return first;
            }

            opennlp::tools::util::DoubleLinkedListElement *DoubleLinkedList::getLast()
            {
              current = last;
              return last;
            }

            opennlp::tools::util::DoubleLinkedListElement *DoubleLinkedList::getCurrent()
            {
              return current;
            }

            opennlp::tools::util::DoubleLinkedListElement *DoubleLinkedList::next()
            {
              if (current->next != 0)
              {
                  current = current->next;
              }
              return current;
            }

            opennlp::tools::util::DoubleLinkedListElement *DoubleLinkedList::prev()
            {
              if (current->prev != 0)
              {
                  current = current->prev;
              }
              return current;
            }

            std::string DoubleLinkedList::ToString()
            {
              DoubleLinkedListElement *e = first;
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              std::string s = "[" + e->object->toString();

              e = e->next;

              while (e != 0)
              {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                  s = s + ", " + e->object->toString();
                  e = e->next;
              }

              s = s + "]";

              return s;
            }
        }
    }
}
