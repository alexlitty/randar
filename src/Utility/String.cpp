#include <locale>
#include <set>
#include <sstream>
#include <randar/Utility/String.hpp>

// Whether a string is an integer.
bool randar::isInteger(const std::string& str)
{
    static const std::set<char> whitelist = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
    };

    for (unsigned int i = 0; i < str.size(); i++) {
        if (!whitelist.count(str[i])) {
            return false;
        }
    }

    return true;
}

// Converts a string to lowercase.
std::string randar::toLowercase(const std::string& str)
{
    static std::locale locale;
    std::string result;

    for (auto item : str) {
        result += std::tolower(item, locale);
    }

    return result;
}

// Splits a string into a vector based on a delimiter.
void randar::split(
    const std::string& str,
    char delimiter,
    std::vector<std::string>& results)
{
    std::stringstream ss;
    ss.str(str);
    std::string item;

    results.clear();
    while (std::getline(ss, item, delimiter)) {
        results.push_back(item);
    }
}

void randar::split(
	const std::string& str,
	const char* delimiters,
	std::vector<std::string>& results)
{
	std::stringstream ss;
	ss.str(str);
	std::string line;

	results.clear();
	while (std::getline(ss, line)) {
		std::size_t prev = 0, pos;
		while ((pos = line.find_first_of(delimiters, prev)) != std::string::npos) {
			if (pos >= prev)
				results.push_back(line.substr(prev, pos - prev));

			prev = pos + 1;
		}

		if (prev < line.length())
			results.push_back(line.substr(prev, std::string::npos));
	}
}

std::vector<std::string> randar::split(const std::string& str, char delimiter)
{
    std::vector<std::string> results;
    randar::split(str, delimiter, results);
    return results;
}

// Joins a list of strings together using a delimiter.
std::string randar::join(const std::vector<std::string>& parts, char delimiter)
{
    std::string result;

    uint32_t partCount = parts.size();
    for (uint32_t i = 0; i < partCount; i++) {
        result += parts[i];

        if ((i + 1) < partCount) {
            result += delimiter;
        }
    }

    return result;
}
