#include "Mean.h"

namespace opennlp
{
    namespace tools
    {
        namespace util
        {
            namespace eval
            {

                void Mean::add(double value)
                {
                  add(value, 1);
                }

                void Mean::add(double value, long long count)
                {
                  sum += value * count;
                  this->count_Renamed += count;
                }

                double Mean::mean()
                {
                  return count_Renamed > 0 ? sum / count_Renamed : 0;
                }

                long long Mean::count()
                {
                  return count_Renamed;
                }

                std::string Mean::ToString()
                {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                  return double::toString(mean());
                }
            }
        }
    }
}
