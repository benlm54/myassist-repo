#include "DetokenizationDictionary.h"
#include "tools/dictionary/serializer/DictionarySerializer.h"
#include "tools/util/StringList.h"
#include "tools/dictionary/serializer/Attributes.h"

namespace opennlp
{
    namespace tools
    {
        namespace tokenize
        {
            using opennlp::tools::dictionary::serializer::Attributes;
            using opennlp::tools::dictionary::serializer::DictionarySerializer;
            using opennlp::tools::dictionary::serializer::Entry;
            using opennlp::tools::dictionary::serializer::EntryInserter;
            using opennlp::tools::util::InvalidFormatException;
            using opennlp::tools::util::StringList;

            DetokenizationDictionary::DetokenizationDictionary(std::string tokens[], DetokenizationDictionary::Operation operations[]) : operationTable(std::map<std::string, DetokenizationDictionary::Operation>())
            {
              if (sizeof(tokens) / sizeof(tokens[0]) != sizeof(operations) / sizeof(operations[0]))
                throw IllegalArgumentException("tokens and ops must have the same length!");

              for (int i = 0; i < sizeof(tokens) / sizeof(tokens[0]); i++)
              {
                std::string token = tokens[i];
                DetokenizationDictionary::Operation operation = operations[i];

                if (token == ""_Renamed)
                  throw IllegalArgumentException("token at index " + i + " must not be null!");

                if (operation == nullptr_Renamed)
                  throw IllegalArgumentException("operation at index " + i + " must not be null!");

                operationTable->put(token, operation);
              }
            }

            DetokenizationDictionary::DetokenizationDictionary(InputStream *in_Renamed) throw(IOException, InvalidFormatException) : operationTable(std::map<std::string, DetokenizationDictionary::Operation>())
            {

              DictionarySerializer::create(in_Renamed, new EntryInserterAnonymousInnerClassHelper();
            }

            void DetokenizationDictionary::EntryInserterAnonymousInnerClassHelper::insert(Entry *entry) throw(InvalidFormatException)
            {

              std::string operationString = entry->getAttributes()->getValue("operation");

              StringList *word = entry->getTokens();

              if (word->size() != 1)
                throw InvalidFormatException("Each entry must have exactly one token! " + word);

              // parse operation
              Operation operation = PARSE(operationString);

              if (operation == outerInstance->nullptr_Renamed)
                  throw InvalidFormatException("Unkown operation type: " + operationString);

              outerInstance->operationTable->put(word->getToken(0), operation);
            }

            opennlp::tools::tokenize::DetokenizationDictionary::Operation DetokenizationDictionary::getOperation(const std::string &token)
            {
              return operationTable->get(token);
            }

            void DetokenizationDictionary::serialize(OutputStream *out) throw(IOException)
            {
              Iterator<Entry*> entries = new IteratorAnonymousInnerClassHelper();

              DictionarySerializer::serialize(out, entries, false);
            }

            bool DetokenizationDictionary::IteratorAnonymousInnerClassHelper::hasNext()
            {
              return iterator->hasNext();
            }

            opennlp::tools::dictionary::serializer::Entry *DetokenizationDictionary::IteratorAnonymousInnerClassHelper::next()
            {

              std::string token = iterator->next();

              Attributes *attributes = new Attributes();
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              attributes->setValue("operation", outerInstance->getOperation(token)->toString());

              return new Entry(new StringList(token), attributes);
            }

            void DetokenizationDictionary::IteratorAnonymousInnerClassHelper::remove()
            {
              throw UnsupportedOperationException();
            }
        }
    }
}
