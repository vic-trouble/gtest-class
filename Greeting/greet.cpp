#include "greet.h"

#include <algorithm>
#include <cctype>
#include <sstream>

std::string greet(const std::string &names)
{
	if (names.empty())
		return "Hello, my friend.";

	if (std::all_of(names.cbegin(), names.cend(), std::isupper))
		return "HELLO " + names + "!";

	if (names.find(',') != std::string::npos)
	{
		std::ostringstream ss;
		ss << "Hello, ";

		std::string temp = names;
		std::string::size_type p;
		const char *sep = "";
		while ((p = temp.find(',')) != std::string::npos)
		{
			ss << sep << temp.substr(0, p);
			temp.erase(0, p + 2);
			sep = ", ";
		}

		ss << " and " << temp << ".";
		return ss.str();
	}

	return "Hello, " + names + ".";
}