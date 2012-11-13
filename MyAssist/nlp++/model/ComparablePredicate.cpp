#include "ComparablePredicate.h"

namespace opennlp
{
    namespace model
    {

        ComparablePredicate::ComparablePredicate(const std::string &n, int ocs[], double ps[])
        {
          name = n;
          outcomes = ocs;
          params = ps;
        }

        int ComparablePredicate::compareTo(ComparablePredicate *cp)
        {
          int smallerLength = (outcomes->length > cp->outcomes->length? cp->outcomes->length : outcomes->length);

          for (int i = 0; i < smallerLength; i++)
          {
            if (outcomes[i] < cp->outcomes[i])
                return -1;
            else if (outcomes[i] > cp->outcomes[i])
                return 1;
          }

          if (outcomes->length < cp->outcomes->length)
              return -1;
          else if (outcomes->length > cp->outcomes->length)
              return 1;

          return 0;
        }

        std::string ComparablePredicate::ToString()
        {
          std::string s = "";
          for (int i = 0; i < outcomes->length; i++)
              s += " " + outcomes[i];
          return s;
        }
    }
}
