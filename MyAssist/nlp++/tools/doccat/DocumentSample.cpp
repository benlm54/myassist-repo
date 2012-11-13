#include "DocumentSample.h"
#include "StringBuilder.h"

namespace opennlp
{
    namespace tools
    {
        namespace doccat
        {
            using opennlp::tools::tokenize::WhitespaceTokenizer;

            DocumentSample::DocumentSample(const std::string &category, const std::string &text)
            {
            }

            DocumentSample::DocumentSample(const std::string &category, std::string text[]) : category(category), text(Collections::unmodifiableList(std::vector<std::string>(Arrays::asList(text))))
            {
              if (category == "" || text == 0)
              {
                throw IllegalArgumentException();
              }

            }

            std::string DocumentSample::getCategory()
            {
              return category;
            }

            std::string *DocumentSample::getText()
            {
              return text.toArray(new std::string[text.size()]);
            }

            std::string DocumentSample::ToString()
            {

              StringBuilder *sampleString = new StringBuilder();

              sampleString->append(category)->append('\t');

              for (int i = 0; i < text.size(); i++)
              {
                sampleString->append(text[i])->append(' ');
              }

              if (sampleString->length() > 0)
              {
                // remove last space
                sampleString->setLength(sampleString->length() - 1);
              }

//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              return sampleString->toString();
            }

            bool DocumentSample::Equals(void *obj)
            {
              if (this == obj)
              {
                return true;
              }
              else if (dynamic_cast<DocumentSample*>(obj) != 0)
              {
                DocumentSample *a = static_cast<DocumentSample*>(obj);

                return getCategory() == a->getCategory() && Arrays::equals(getText(), a->getText());
              }
              else
              {
                return false;
              }
            }
        }
    }
}
