#include "ArgumentParser.h"
#include "tools/cmdline/TerminateToolException.h"
#include "tools/cmdline/CmdLineUtil.h"
#include "T.h"
#include "Method.h"
#include "NumberFormatException.h"
#include "Class.h"
#include "const_iterator.h"
#include "StringBuilder.h"
#include "ParameterDescription.h"
#include "OptionalParameter.h"

namespace opennlp
{
    namespace tools
    {
        namespace cmdline
        {

const std::string ArgumentParser::ArgumentFactory::INVALID_ARG = "Invalid argument: %s %s \n";

            void *ArgumentParser::IntegerArgumentFactory::parseArgument(Method *method, const std::string &argName, const std::string &argValue)
            {

              void *value = 0;

              try
              {
                value = StringConverterHelper::fromString<int>(argValue);
              }
              catch (NumberFormatException e)
              {
                throw TerminateToolException(-1, std::string::format(INVALID_ARG, argName, argValue) + "Value must be an integer!");
              }

              return value;
            }

            void *ArgumentParser::BooleanArgumentFactory::parseArgument(Method *method, const std::string &argName, const std::string &argValue)
            {
              return StringConverterHelper::fromString<bool>(argValue);
            }

            void *ArgumentParser::StringArgumentFactory::parseArgument(Method *method, const std::string &argName, const std::string &argValue)
            {
              return argValue;
            }

            void *ArgumentParser::FileArgumentFactory::parseArgument(Method *method, const std::string &argName, const std::string &argValue)
            {
              return new File(argValue);
            }

            void *ArgumentParser::CharsetArgumentFactory::parseArgument(Method *method, const std::string &argName, const std::string &charsetName)
            {

              try
              {
                if (OptionalParameter::DEFAULT_CHARSET::equals(charsetName))
                {
                  return Charset::defaultCharset();
                }
                else if (Charset::isSupported(charsetName))
                {
                  return Charset::forName(charsetName);
                }
                else
                {
                  throw TerminateToolException(-1, std::string::format(INVALID_ARG, argName, charsetName) + "Encoding not supported on this platform.");
                }
              }
              catch (IllegalCharsetNameException e)
              {
                throw TerminateToolException(-1, std::string::format(INVALID_ARG, argName, charsetName) + "Illegal encoding name.");
              }
            }

            ArgumentParser::ArgumentProxy::ArgumentProxy(Map<std::string, void*> *arguments) : arguments(arguments)
            {
            }

            void *ArgumentParser::ArgumentProxy::invoke(void *proxy, Method *method, Object args[]) throw(Throwable)
            {

              if (args != 0)
                throw IllegalStateException();

              return arguments->get(method->getName());
            }

            ArgumentParser::OptionalParameter::OptionalParameter(ArgumentParser *outerInstance) : outerInstance(outerInstance)
            {
            }

const std::string ArgumentParser::OptionalParameter::DEFAULT_CHARSET = "DEFAULT_CHARSET";

            ArgumentParser::ParameterDescription::ParameterDescription(ArgumentParser *outerInstance) : outerInstance(outerInstance)
            {
            }

java::util::Map<Class*, ArgumentFactory*> *const ArgumentParser::argumentFactories = 0;

            ArgumentParser::ArgumentParser()
            {
              Map<Class*, ArgumentFactory*> *factories = std::map<Class*, ArgumentParser::ArgumentFactory*>();
              factories->put(int::typeid, new IntegerArgumentFactory());
              factories->put(bool::typeid, new BooleanArgumentFactory());
              factories->put(std::string::typeid, new StringArgumentFactory());
              factories->put(File::typeid, new FileArgumentFactory());
              factories->put(Charset::typeid, new CharsetArgumentFactory());

              argumentFactories = Collections::unmodifiableMap(factories);
            }

            ArgumentParser::ArgumentParser()
            {
            }

template<typename T>
            void ArgumentParser::checkProxyInterface(Class *proxyInterface)
            {
              if (!proxyInterface->isInterface())
                throw IllegalArgumentException("proxy interface is not an interface!");

              // all checks should also be performed for super interfaces

//ORIGINAL LINE: Method methods[] = proxyInterface.getMethods();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              Method *methods = proxyInterface->getMethods();

              if (methods->length == 0)
                throw IllegalArgumentException("proxy interface must at least declare one method!");

              for (Method::const_iterator method = methods->begin(); method != methods->end(); ++method)
              {

                // check that method names start with get
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'startsWith' method:
                if (!method->getName()->startsWith("get") && method->getName()->length() > 3)
                  throw IllegalArgumentException(method->getName() + " method name does not start with get!");

                // check that method has zero arguments
                if (method->getParameterTypes()->length != 0)
                  throw IllegalArgumentException(method->getName() + " method must have zero parameters!");

                // check return types of interface
                Class *returnType = method->getReturnType();

                Set<Class*> *compatibleReturnTypes = argumentFactories->keySet();

                if (!compatibleReturnTypes->contains(returnType))
                   throw IllegalArgumentException(method->getName() + " method must have compatible return type!");
              }
            }

            std::string ArgumentParser::methodNameToParameter(const std::string &methodName)
            {
              // remove get from method name
//ORIGINAL LINE: char parameterNameChars[] = methodName.toCharArray();
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
              char *parameterNameChars = methodName.toCharArray();

              // name length is checked to be at least 4 prior
              parameterNameChars[3] = tolower(parameterNameChars[3]);

              std::string parameterName = "-" + (std::string(parameterNameChars))->substr(3);

              return parameterName;
            }

template<typename T>
            std::string ArgumentParser::createUsage(Class *argProxyInterface)
            {

              checkProxyInterface(argProxyInterface);

              StringBuilder *usage = new StringBuilder();
              StringBuilder *details = new StringBuilder();

              for (unknown::const_iterator method = argProxyInterface->getMethods().begin(); method != argProxyInterface->getMethods().end(); ++method)
              {

                ParameterDescription *desc = method.getAnnotation(ParameterDescription::typeid);

                OptionalParameter *optional = method.getAnnotation(OptionalParameter::typeid);

                if (desc != 0)
                {
                  std::string paramName = methodNameToParameter(method.getName());

                  if (optional != 0)
                    usage->append('[');

                  usage->append(paramName)->append(' ')->append(desc->valueName());
                  details->append('\t')->append(paramName)->append(' ')->append(desc->valueName())->append('\n');
                  if (desc->description() != 0 && desc->description()->length() > 0)
                  {
                    details->append("\t\t")->append(desc->description())->append('\n');
                  }

                  if (optional != 0)
                    usage->append(']');

                  usage->append(' ');
                }
              }

              if (usage->length() > 0)
                usage->setLength(usage->length() - 1);

              if (details->length() > 0)
              {
                details->setLength(details->length() - 1);
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                usage->append("\n\nArguments description:\n")->append(details->toString());
              }

//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              return usage->toString();
            }

template<typename T>
            bool ArgumentParser::validateArguments(std::string args[], Class *argProxyInterface)
            {

              // number of parameters must be at least 2 and always be even
              if (sizeof(args) / sizeof(args[0]) < 2 || sizeof(args) / sizeof(args[0]) % 2 != 0)
                return false;

              int argumentCount = 0;

              for (unknown::const_iterator method = argProxyInterface->getMethods().begin(); method != argProxyInterface->getMethods().end(); ++method)
              {

                std::string valueString = CmdLineUtil::getParameter(methodNameToParameter(method.getName()), args);

                if (valueString == "")
                {
                  OptionalParameter *optionalParam = method.getAnnotation(OptionalParameter::typeid);

                  // missing mandatory parameter
                  if (optionalParam == 0)
                    return false;
                }
                else
                {
                  argumentCount++;
                }
              }

              if (sizeof(args) / sizeof(args[0]) / 2 != argumentCount)
                return false;

              return true;
            }

template<typename T>
            T ArgumentParser::parse(std::string args[], Class *argProxyInterface)
            {

              checkProxyInterface(argProxyInterface);

              if (!validateArguments(args, argProxyInterface))
                throw IllegalArgumentException("Passed args must be valid!");

              Map<std::string, void*> *arguments = std::map<std::string, void*>();

              for (unknown::const_iterator method = argProxyInterface->getMethods().begin(); method != argProxyInterface->getMethods().end(); ++method)
              {

                std::string parameterName = methodNameToParameter(method.getName());
                std::string valueString = CmdLineUtil::getParameter(parameterName, args);

                if (valueString == "")
                {
                  OptionalParameter *optionalParam = method.getAnnotation(OptionalParameter::typeid);

                  if (optionalParam->defaultValue()->length() > 0)
                    valueString = optionalParam->defaultValue();
                  else
                    valueString = "";
                }

                Class *returnType = method.getReturnType();

                void *value;

                if (valueString != "")
                {
                  ArgumentFactory *factory = argumentFactories->get(returnType);

                  if (factory == 0)
                    throw IllegalStateException();

                  value = factory->parseArgument(method, parameterName, valueString);
                }
                else
//JAVA TO C++ CONVERTER WARNING: Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
                  delete value;

                arguments->put(method.getName(), value);
              }

              return static_cast<T>(java::lang::reflect::Proxy::newProxyInstance(argProxyInterface->getClassLoader(), new Class[]{argProxyInterface}, new ArgumentProxy(arguments)));
            }
        }
    }
}
