#include "POSEvaluator.h"

namespace opennlp
{
    namespace tools
    {
        namespace postag
        {
            using opennlp::tools::util::eval::Evaluator;
            using opennlp::tools::util::eval::Mean;

            POSEvaluator::POSEvaluator(POSTagger *tagger, ...) : opennlp.tools.util.eval.Evaluator<POSSample>(listeners)
            {
              InitializeInstanceFields();
              this->tagger = tagger;
            }

            opennlp::tools::postag::POSSample *POSEvaluator::processSample(POSSample *reference)
            {

//ORIGINAL LINE: String predictedTags[] = tagger.tag(reference.getSentence());
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              std::string *predictedTags = tagger->tag(reference->getSentence());
//ORIGINAL LINE: String referenceTags[] = reference.getTags();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              std::string *referenceTags = reference->getTags();

              for (int i = 0; i < referenceTags->length; i++)
              {
                if (referenceTags[i] == predictedTags[i])
                {
                  wordAccuracy->add(1);
                }
                else
                {
                  wordAccuracy->add(0);
                }
              }

              return new POSSample(reference->getSentence(), predictedTags);
            }

            double POSEvaluator::getWordAccuracy()
            {
              return wordAccuracy->mean();
            }

            long long POSEvaluator::getWordCount()
            {
              return wordAccuracy->count();
            }

            std::string POSEvaluator::ToString()
            {
              return "Accuracy:" + wordAccuracy->mean() + " Number of Samples: " + wordAccuracy->count();
            }

            void POSEvaluator::InitializeInstanceFields()
            {
                wordAccuracy = new opennlp::tools::util::eval::Mean();
            }
        }
    }
}
