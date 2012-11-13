#include "DefaultPOSContextGenerator.h"
#include "tools/util/StringList.h"

namespace opennlp
{
    namespace tools
    {
        namespace postag
        {
            using opennlp::tools::dictionary::Dictionary;
            using opennlp::tools::util::Cache;
            using opennlp::tools::util::StringList;
java::util::regex::Pattern *DefaultPOSContextGenerator::hasCap = java::util::regex::Pattern::compile("[A-Z]");
java::util::regex::Pattern *DefaultPOSContextGenerator::hasNum = java::util::regex::Pattern::compile("[0-9]");

            DefaultPOSContextGenerator::DefaultPOSContextGenerator(Dictionary *dict) : SE("*SE*"), SB("*SB*")
            {
            }

            DefaultPOSContextGenerator::DefaultPOSContextGenerator(int cacheSize, Dictionary *dict) : SE("*SE*"), SB("*SB*")
            {
              this->dict = dict;
              dictGram = new std::string[1];
              if (cacheSize > 0)
              {
                contextsCache = new Cache(cacheSize);
              }
            }

            std::string *DefaultPOSContextGenerator::getPrefixes(const std::string &lex)
            {
              std::string prefs[PREFIX_LENGTH];
              for (int li = 0, ll = PREFIX_LENGTH; li < ll; li++)
              {
                prefs[li] = lex.substr(0, __min(li + 1, lex.length()));
              }
              return prefs;
            }

            std::string *DefaultPOSContextGenerator::getSuffixes(const std::string &lex)
            {
              std::string suffs[SUFFIX_LENGTH];
              for (int li = 0, ll = SUFFIX_LENGTH; li < ll; li++)
              {
                suffs[li] = lex.substr(__max(lex.length() - li - 1, 0));
              }
              return suffs;
            }

            std::string *DefaultPOSContextGenerator::getContext(int index, std::string sequence[], std::string priorDecisions[], Object additionalContext[])
            {
              return getContext(index,sequence,priorDecisions);
            }

            std::string *DefaultPOSContextGenerator::getContext(int index, Object tokens[], std::string tags[])
            {
              std::string next, nextnext, lex, prev, prevprev;
              std::string tagprev, tagprevprev;
              tagprev = tagprevprev = "";
              next = nextnext = lex = prev = prevprev = "";

//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              lex = tokens[index]->toString();
              if (sizeof(tokens) / sizeof(tokens[0]) > index + 1)
              {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                next = tokens[index + 1]->toString();
                if (sizeof(tokens) / sizeof(tokens[0]) > index + 2)
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                  nextnext = tokens[index + 2]->toString();
                else
                  nextnext = SE; // Sentence End

              }
              else
              {
                next = SE; // Sentence End
              }

              if (index - 1 >= 0)
              {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                prev = tokens[index - 1]->toString();
                tagprev = tags[index - 1];

                if (index - 2 >= 0)
                {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                  prevprev = tokens[index - 2]->toString();
                  tagprevprev = tags[index - 2];
                }
                else
                {
                  prevprev = SB; // Sentence Beginning
                }
              }
              else
              {
                prev = SB; // Sentence Beginning
              }
              std::string cacheKey = index + tagprev + tagprevprev;
              if (contextsCache != 0)
              {
                if (wordsKey == tokens)
                {
//ORIGINAL LINE: String[] cachedContexts = (String[]) contextsCache.get(cacheKey);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                  std::string *cachedContexts = static_cast<std::string[]>(contextsCache->get_Renamed(cacheKey));
                  if (cachedContexts != 0)
                  {
                    return cachedContexts;
                  }
                }
                else
                {
                  contextsCache->clear();
                  wordsKey = tokens;
                }
              }
              std::vector<std::string> e = std::vector<std::string>();
              e.push_back("default");
              // add the word itself
              e.push_back("w=" + lex);
              dictGram[0] = lex;
              if (dict == 0 || !dict->contains(new StringList(dictGram)))
              {
                // do some basic suffix analysis
//ORIGINAL LINE: String[] suffs = getSuffixes(lex);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                std::string *suffs = getSuffixes(lex);
                for (int i = 0; i < suffs->length; i++)
                {
                  e.push_back("suf=" + suffs[i]);
                }

//ORIGINAL LINE: String[] prefs = getPrefixes(lex);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
                std::string *prefs = getPrefixes(lex);
                for (int i = 0; i < prefs->length; i++)
                {
                  e.push_back("pre=" + prefs[i]);
                }
                // see if the word has any special characters
                if (lex.find('-') != -1)
                {
                  e.push_back("h");
                }

                if (hasCap->matcher(lex)->find())
                {
                  e.push_back("c");
                }

                if (hasNum->matcher(lex)->find())
                {
                  e.push_back("d");
                }
              }
              // add the words and pos's of the surrounding context
              if (prev != "")
              {
                e.push_back("p=" + prev);
                if (tagprev != "")
                {
                  e.push_back("t=" + tagprev);
                }
                if (prevprev != "")
                {
                  e.push_back("pp=" + prevprev);
                  if (tagprevprev != "")
                  {
                    e.push_back("t2=" + tagprevprev + "," + tagprev);
                  }
                }
              }

              if (next != "")
              {
                e.push_back("n=" + next);
                if (nextnext != "")
                {
                  e.push_back("nn=" + nextnext);
                }
              }
//ORIGINAL LINE: String[] contexts = e.toArray(new String[e.size()]);
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              std::string *contexts = e.toArray(new std::string[e.size()]);
              if (contextsCache != 0)
              {
                contextsCache->put(cacheKey,contexts);
              }
              return contexts;
            }
        }
    }
}
