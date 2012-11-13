#include "Sequence.h"

namespace opennlp
{
    namespace tools
    {
        namespace util
        {

const double Sequence::ONE = 1.0;

            Sequence::Sequence()
            {
              outcomes = std::vector<std::string>(1);
              probs = std::vector<double>(1);
              score = 0;
            }

            Sequence::Sequence(Sequence *s)
            {
              outcomes = std::vector<std::string>(s->outcomes->size() + 1);
              outcomes.addAll(s->outcomes);
              probs = std::vector<double>(s->probs->size() + 1);
              probs.addAll(s->probs);
              score = s->score;
            }

            Sequence::Sequence(Sequence *s, const std::string &outcome, double p)
            {
                outcomes = std::vector<std::string>(s->outcomes->size() + 1);
                outcomes.addAll(s->outcomes);
                outcomes.push_back(outcome);
                probs = std::vector<double>(s->probs->size() + 1);
                probs.addAll(s->probs);
                probs.push_back(p);
                score = s->score + log(p);
            }

            Sequence::Sequence(std::vector<std::string> &outcomes)
            {
              this->outcomes = outcomes;
              this->probs = Collections::nCopies(outcomes.size(),ONE);
            }

            int Sequence::compareTo(Sequence *s)
            {
              if (score < s->score)
                return 1;
              if (score > s->score)
                return -1;
              return 0;
            }

            void Sequence::add(const std::string &outcome, double p)
            {
              outcomes.push_back(outcome);
              probs.push_back(p);
              score += log(p);
            }

            std::vector<std::string> Sequence::getOutcomes()
            {
              return outcomes;
            }

            double *Sequence::getProbs()
            {
              double ps[probs.size()];
              getProbs(ps);
              return ps;
            }

            double Sequence::getScore()
            {
              return score;
            }

            void Sequence::getProbs(double ps[])
            {
              for (int pi = 0,pl = probs.size();pi < pl;pi++)
              {
                ps[pi] = probs[pi];
              }
            }

            std::string Sequence::ToString()
            {
              return score + " " + outcomes;
            }
        }
    }
}
