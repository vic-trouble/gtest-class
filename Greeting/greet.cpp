#include "greet.h"

#include <algorithm>
#include <cctype>
#include <sstream>
//#include <string_view>
#include <vector>

std::string greet(const std::string &names_)
{
	std::string names = names_.empty() ? "my friend" : names_;

	std::vector<std::string> normal;
	std::vector<std::string> caps;

	auto is_caps = [](const std::string &s)
	{
		return std::all_of(s.cbegin(), s.cend(), std::isupper);
	};

	std::string::size_type p;
	while ((p = names.find(',')) != std::string::npos)
	{
		std::string name = names.substr(0, p);
		names.erase(0, p + 2);
		if (is_caps(name))
			caps.push_back(name);
		else
			normal.push_back(name);
	}
	if (is_caps(names))
		caps.push_back(names);
	else
		normal.push_back(names);

	std::ostringstream ss;
	if (!normal.empty())
	{
		ss << "Hello, ";
		const char *sep = "";
		for (auto it = normal.cbegin(); it != normal.cend(); ++it)
		{
			ss << (it > normal.cbegin() ? (it == normal.cend() - 1 ? " and " : ", ") : "") << *it;
		}
		ss << ".";
	}

	if (!caps.empty())
	{
		if (ss.tellp() > 0)
			ss << " AND ";
		ss << "HELLO ";
		const char *sep = "";
		for (auto it = caps.cbegin(); it != caps.cend(); ++it)
		{
			ss << (it > caps.cbegin() ? (it == caps.cend() - 1 ? " AND " : ", ") : "") << *it;
		}
		ss << "!";
	}

	return ss.str();
}