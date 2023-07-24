#include "Irc.hpp"

/* 
 * Print error message
 * @param error: std::string
 * @return: int (FAILURE) -1
 */
int printError(std::string error) {
	std::cout << RED << error << RESET << std::endl;
	return FAILURE;
}