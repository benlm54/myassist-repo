#include "IntegerPool.h"

namespace opennlp
{
    namespace maxent
    {

        IntegerPool::IntegerPool(int size)
        {
          _table = new int[size];
          for (int i = 0; i < size; i++)
          {
            _table[i] = int(i);
          } // end of for (int i = 0; i < size; i++)
        }

        int IntegerPool::get_Renamed(int value)
        {
          if (value < _table->length && value >= 0)
          {
            return _table[value];
          }
          else
          {
            return int(value);
          }
        }
    }
}
