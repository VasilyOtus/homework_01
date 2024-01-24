#include <iostream>
#include <cstdlib>
#include <cstdint>

#include "lib.h"

int main()
{
	uint32_t ver = version();

	std::cout << "Version: " <<
		std::to_string(ver >> 16) << "." <<
		std::to_string((ver >> 8) & 0xff) << "." <<
		std::to_string(ver & 0xff) <<
		std::endl;

	std::cout << "Hello, world!" << std::endl;

	return EXIT_SUCCESS;
}
