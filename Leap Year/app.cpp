#include "leap.h"

#include <string>
#include <iostream>

int main()
{
	std::string year;
	while (std::getline(std::cin, year))
	{
		std::cout << (isLeap(std::stoi(year)) ? "leap" : "not leap") << std::endl;
	}
}