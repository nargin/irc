#include "user.hpp"

User::User() : _username("unset"), _realname("unset"), _hostname("unset") {
	std::cout << "User default constructor called" << std::endl;
}

User::User(std::string username, std::string realname, std::string hostname) : _username(username), _realname(realname), _hostname(hostname) {
	std::cout << "User constructor called" << std::endl;
}

User::~User() {
	std::cout << "User destructor called" << std::endl;
}

void User::test() {
	std::cout << "User test called" << std::endl;
}

std::string User::getUsername() { return this->_username;}
std::string User::getRealname() { return this->_realname;}
std::string User::getHostname() { return this->_hostname;}

User::User(User const &src) {
	std::cout << "User copy constructor called" << std::endl;
	*this = src;
}