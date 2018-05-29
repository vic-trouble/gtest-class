#include "recent.h"

#include <iostream>

int main(int argc, char **argv)
{
	Recent::RUList rul;
	if (argc == 2)
		rul = Recent::RUList(std::stoi(argv[1]));

	std::string item;
	while (std::getline(std::cin, item))
	{
		rul.push(item);

		for (size_t i = 0; i < rul.size(); i++)
			std::cout << i << ": " << rul[i] << std::endl;
		std::cout << "----------------" << std::endl;
	}
}