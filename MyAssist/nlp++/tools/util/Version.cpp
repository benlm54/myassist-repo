#include "Version.h"

namespace opennlp
{
    namespace tools
    {
        namespace util
        {

const std::string Version::DEV_VERSION_STRING = "1.5.2";
Version *const Version::DEV_VERSION = Version::parse(DEV_VERSION_STRING);
const std::string Version::SNAPSHOT_MARKER = "-SNAPSHOT";

            Version::Version(int major, int minor, int revision, bool snapshot) : major(major), minor(minor), revision(revision), snapshot(snapshot)
            {
            }

            Version::Version(int major, int minor, int revision)
            {
            }

            int Version::getMajor()
            {
              return major;
            }

            int Version::getMinor()
            {
              return minor;
            }

            int Version::getRevision()
            {
              return revision;
            }

            bool Version::isSnapshot()
            {
              return snapshot;
            }

            std::string Version::ToString()
            {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
              return int::toString(getMajor()) + "." + int::toString(getMinor()) + "." + int::toString(getRevision()) + (isSnapshot() ? SNAPSHOT_MARKER : "");
            }

            bool Version::Equals(void *o)
            {
              if (o == this)
              {
                return true;
              }
              else if (dynamic_cast<Version*>(o) != 0)
              {
                Version *version = static_cast<Version*>(o);

                return getMajor() == version->getMajor() && getMinor() == version->getMinor() && getRevision() == version->getRevision() && isSnapshot() == version->isSnapshot();
              }
              else
              {
                return false;
              }
            }

            opennlp::tools::util::Version *Version::parse(const std::string &version)
            {

              int indexFirstDot = version.find('.');

              int indexSecondDot = version.find('.', indexFirstDot + 1);

              if (indexFirstDot == -1 || indexSecondDot == -1)
                  throw NumberFormatException("Invalid version!");

              int indexFirstDash = version.find('-');

              int versionEnd;
              if (indexFirstDash == -1)
              {
                versionEnd = version.length();
              }
              else
              {
                versionEnd = indexFirstDash;
              }

//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'endsWith' method:
              bool snapshot = version.endsWith(SNAPSHOT_MARKER);

              return new Version(StringConverterHelper::fromString<int>(version.substr(0, indexFirstDot)), StringConverterHelper::fromString<int>(version.substr(indexFirstDot + 1, indexSecondDot - (indexFirstDot + 1))), StringConverterHelper::fromString<int>(version.substr(indexSecondDot + 1, versionEnd - (indexSecondDot + 1))), snapshot);
            }

            opennlp::tools::util::Version *Version::currentVersion()
            {

              Properties *manifest = new Properties();

              // Try to read the version from the version file if it is available,
              // otherwise set the version to the development version

              InputStream *versionIn = Version::typeid::getResourceAsStream("opennlp.version");

              if (versionIn != 0)
              {
                try
                {
                  manifest->load(versionIn);
                }
                catch (IOException e)
                {
                  // ignore error
                }
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
                finally
                {
                  try
                  {
                    versionIn->close();
                  }
                  catch (IOException e)
                  {
                    // ignore error
                  }
                }
              }

              std::string versionString = manifest->getProperty("OpenNLP-Version", DEV_VERSION_STRING);

              if (versionString == "${pom.version}")
                versionString = DEV_VERSION_STRING;

              return Version::parse(versionString);
            }
        }
    }
}
