#include "greet.h"

#include <iostream>

int main()
{
	std::string names;
	while (std::getline(std::cin, names))
	{
		std::cout << greet(names) << std::endl;
	}
}
