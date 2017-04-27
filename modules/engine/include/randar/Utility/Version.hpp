#ifndef RANDAR_SYSTEM_VERSION_HPP
#define RANDAR_SYSTEM_VERSION_HPP

#include <cstdint>
#include <randar/Utility/String.hpp>

namespace randar
{
    /**
     * A version of variable parts.
     */
    class Version
    {
    protected:
        /**
         * The underlying parts that compose the version.
         *
         * We use a vector instead of an array for easier usage in Node.js.
         */
        std::vector<uint8_t> parts;

    public:
        /**
         * Default constructor.
         */
        Version()
        {
            this->set();
        }

        /**
         * Copy constructor.
         */
        Version(const Version& other)
        {
            *this = other;
        }

        /**
         * Constructors that initialize the version.
         */
        Version(const std::string& str)
        {
            this->set(str);
        }

        Version(const std::vector<uint8_t>& initParts)
        {
            this->set(initParts);
        }

        /**
         * Sets the version, given a string of parts split by periods.
         */
        void set(const std::string& str)
        {
            this->parts.clear();

            for (auto part : randar::split(str, '.')) {
                this->parts.push_back(std::stoi(part));
            }
        }

        /**
         * Sets the version, given a vector of parts.
         */
        void set(const std::vector<uint8_t>& newParts = { })
        {
            this->parts = newParts;
        }

        /**
         * Gets the major and minor parts of the version.

         */
        uint8_t major() const
        {
            if (this->parts.size() == 0) {
                return 0;
            } else {
                return this->parts[0];
            }
        }

        uint8_t minor() const
        {
            if (this->parts.size() == 1) {
                return 0;
            } else {
                return this->parts[1];
            }
        }

        /**
         * Converts the version to a string.
         */
        std::string toString() const
        {
            std::string result;
            for (uint8_t i = 0; i < this->parts.size(); i++) {
                result += std::to_string(this->parts[i]);
                if (i + 1 != this->parts.size()) {
                    result += ".";
                }
            }
            return result;
        }

        operator std::string() const
        {
            return this->toString();
        }

        /**
         * Assignment operator.
         */
        Version& operator =(const Version& other)
        {
            this->set(other.toString());
            return *this;
        }
    };
}

#endif
