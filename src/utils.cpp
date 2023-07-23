#include "Irc.hpp"

int printError(std::string error) {
	std::cout << RED << error << RESET << std::endl;
	return 1;
}