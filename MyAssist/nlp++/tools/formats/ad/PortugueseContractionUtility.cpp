#include "PortugueseContractionUtility.h"
#include "StringBuilder.h"

namespace opennlp
{
    namespace tools
    {
        namespace formats
        {
            namespace ad
            {

java::util::Map<std::string, std::string> *const PortugueseContractionUtility::CONTRACTIONS = 0;

                PortugueseContractionUtility::PortugueseContractionUtility()
                {
                  Map<std::string, std::string> *elems = std::map<std::string, std::string>();
                  // 103 CONTRACTIONS.
                  elems->put("a+a", "\u00e0");
                  elems->put("a+as", "\u00e0s");
                  elems->put("a+aquele", "\u00e0quele");
                  elems->put("a+aqueles", "\u00e0queles");
                  elems->put("a+aquela", "\u00e0quela");
                  elems->put("a+aquelas", "\u00e0quelas");
                  elems->put("a+aquilo", "\u00e0quilo");
                  elems->put("a+o", "ao");
                  elems->put("a+os", "aos");
                  elems->put("com+mim", "comigo");
                  elems->put("com+n\u00f2s", "conosco");
                  elems->put("com+si", "consigo");
                  elems->put("com+ti", "contigo");
                  elems->put("com+v\u00f2s", "convosco");
                  elems->put("de+a\u00ed", "da\u00ed");
                  elems->put("de+algu\u00e9m", "dalgu\u00e9m");
                  elems->put("de+algum", "dalgum");
                  elems->put("de+alguma", "dalguma");
                  elems->put("de+alguns", "dalguns");
                  elems->put("de+algumas", "dalgumas");
                  elems->put("de+ali", "dali");
                  elems->put("de+aqu\u00e9m", "daqu\u00e9m");
                  elems->put("de+aquele", "daquele");
                  elems->put("de+aquela", "daquela");
                  elems->put("de+aqueles", "daqueles");
                  elems->put("de+aquelas", "daquelas");
                  elems->put("de+aqui", "daqui");
                  elems->put("de+aquilo", "daquilo");
                  elems->put("de+ele", "dele");
                  elems->put("de+ela", "dela");
                  elems->put("de+eles", "deles");
                  elems->put("de+elas", "delas");
                  elems->put("de+entre", "dentre");
                  elems->put("de+esse", "desse");
                  elems->put("de+essa", "dessa");
                  elems->put("de+esses", "desses");
                  elems->put("de+essas", "dessas");
                  elems->put("de+este", "deste");
                  elems->put("de+esta", "desta");
                  elems->put("de+estes", "destes");
                  elems->put("de+estas", "destas");
                  elems->put("de+isso", "disso");
                  elems->put("de+isto", "disto");
                  elems->put("de+o", "do");
                  elems->put("de+a", "da");
                  elems->put("de+os", "dos");
                  elems->put("de+as", "das");
                  elems->put("de+outrem", "doutrem");
                  elems->put("de+outro", "doutro");
                  elems->put("de+outra", "doutra");
                  elems->put("de+outros", "doutros");
                  elems->put("de+outras", "doutras");
                  elems->put("de+um", "dum");
                  elems->put("de+uma", "duma");
                  elems->put("de+uns", "duns");
                  elems->put("de+umas", "dumas");
                  elems->put("esse+outro", "essoutro");
                  elems->put("essa+outra", "essoutra");
                  elems->put("este+outro", "estoutro");
                  elems->put("este+outra", "estoutra");
                  elems->put("ele+o", "lho");
                  elems->put("ele+a", "lha");
                  elems->put("ele+os", "lhos");
                  elems->put("ele+as", "lhas");
                  elems->put("em+algum", "nalgum");
                  elems->put("em+alguma", "nalguma");
                  elems->put("em+alguns", "nalguns");
                  elems->put("em+algumas", "nalgumas");
                  elems->put("em+aquele", "naquele");
                  elems->put("em+aquela", "naquela");
                  elems->put("em+aqueles", "naqueles");
                  elems->put("em+aquelas", "naquelas");
                  elems->put("em+aquilo", "naquilo");
                  elems->put("em+ele", "nele");
                  elems->put("em+ela", "nela");
                  elems->put("em+eles", "neles");
                  elems->put("em+elas", "nelas");
                  elems->put("em+esse", "nesse");
                  elems->put("em+essa", "nessa");
                  elems->put("em+esses", "nesses");
                  elems->put("em+essas", "nessas");
                  elems->put("em+este", "neste");
                  elems->put("em+esta", "nesta");
                  elems->put("em+estes", "nestes");
                  elems->put("em+estas", "nestas");
                  elems->put("em+isso", "nisso");
                  elems->put("em+isto", "nisto");
                  elems->put("em+o", "no");
                  elems->put("em+a", "na");
                  elems->put("em+os", "nos");
                  elems->put("em+as", "nas");
                  elems->put("em+outro", "noutro");
                  elems->put("em+outra", "noutra");
                  elems->put("em+outros", "noutros");
                  elems->put("em+outras", "noutras");
                  elems->put("em+um", "num");
                  elems->put("em+uma", "numa");
                  elems->put("em+uns", "nuns");
                  elems->put("em+umas", "numas");
                  elems->put("por+o", "pelo");
                  elems->put("por+a", "pela");
                  elems->put("por+os", "pelos");
                  elems->put("por+as", "pelas");
                  elems->put("para+a", "pra");
                  elems->put("para+o", "pro");
                  elems->put("para+as", "pras");
                  elems->put("para+os", "pros");
                  CONTRACTIONS = Collections::unmodifiableMap(elems);
                }

                std::string PortugueseContractionUtility::toContraction(const std::string &left, const std::string &right)
                {
                  std::string key = left + "+" + right;
                  if (CONTRACTIONS->containsKey(key))
                  {
                    return CONTRACTIONS->get(key);
                  }
                  else
                  {
                    StringBuilder *sb = new StringBuilder();
//ORIGINAL LINE: String[] parts = left.split("_");
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'split' method:
                    std::string *parts = left.split("_");
                    for (int i = 0; i < parts->length - 1; i++)
                    {
                      sb->append(parts[i] + " ");
                    }
                    key = parts[parts->length - 1] + "+" + right;
                    if (CONTRACTIONS->containsKey(key))
                    {
                      sb->append(CONTRACTIONS->get(key));
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                      return sb->toString();
                    }

                    if (right.find("_") != string::npos)
                    {
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'split' method:
                      parts = right.split("_");

                      key = left + "+" + parts[0];
                      if (CONTRACTIONS->containsKey(key))
                      {
                        sb->append(CONTRACTIONS->get(key) + " ");

                        for (int i = 1; i < parts->length; i++)
                        {
                          sb->append(parts[i] + " ");
                        }

//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                        return sb->toString();
                      }

                    }

                    std::string leftLower = parts[parts->length - 1].toLowerCase();
                    key = leftLower + "+" + right;
                    if (CONTRACTIONS->containsKey(key))
                    {
                      std::string r = CONTRACTIONS->get(key);
                      std::string firstChar = r.substr(0, 1);
                      r = firstChar.toUpperCase() + r.substr(1);
                      sb->append(r);
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                      return sb->toString();
                    }
                  }

                  return 0;
                }
            }
        }
    }
}
