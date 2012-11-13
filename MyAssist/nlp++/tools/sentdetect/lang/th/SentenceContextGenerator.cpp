#include "SentenceContextGenerator.h"

namespace opennlp
{
    namespace tools
    {
        namespace sentdetect
        {
            namespace lang
            {
                namespace th
                {
                    using opennlp::tools::sentdetect::DefaultSDContextGenerator;
const char SentenceContextGenerator::eosCharacters[2] = {' ','\n'};

                    SentenceContextGenerator::SentenceContextGenerator() : opennlp.tools.sentdetect.DefaultSDContextGenerator(eosCharacters)
                    {
                    }

                    void SentenceContextGenerator::collectFeatures(const std::string &prefix, const std::string &suffix, const std::string &previous, const std::string &next)
                    {
                      buf->append("p=");
                      buf->append(prefix);
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                      collectFeats.push_back(buf->toString());
                      buf->setLength(0);

                      buf->append("s=");
                      buf->append(suffix);
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                      collectFeats.push_back(buf->toString());
                      buf->setLength(0);

                      collectFeats.push_back("p1=" + prefix.substr(__max(prefix.length() - 1,0)));
                      collectFeats.push_back("p2=" + prefix.substr(__max(prefix.length() - 2,0)));
                      collectFeats.push_back("p3=" + prefix.substr(__max(prefix.length() - 3,0)));
                      collectFeats.push_back("p4=" + prefix.substr(__max(prefix.length() - 4,0)));
                      collectFeats.push_back("p5=" + prefix.substr(__max(prefix.length() - 5,0)));
                      collectFeats.push_back("p6=" + prefix.substr(__max(prefix.length() - 6,0)));
                      collectFeats.push_back("p7=" + prefix.substr(__max(prefix.length() - 7,0)));

                      collectFeats.push_back("n1=" + suffix.substr(0,__min(1,suffix.length())));
                      collectFeats.push_back("n2=" + suffix.substr(0,__min(2,suffix.length())));
                      collectFeats.push_back("n3=" + suffix.substr(0,__min(3,suffix.length())));
                      collectFeats.push_back("n4=" + suffix.substr(0,__min(4,suffix.length())));
                      collectFeats.push_back("n5=" + suffix.substr(0,__min(5,suffix.length())));
                      collectFeats.push_back("n6=" + suffix.substr(0,__min(6,suffix.length())));
                      collectFeats.push_back("n7=" + suffix.substr(0,__min(7,suffix.length())));
                    }
                }
            }
        }
    }
}
