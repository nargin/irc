#include "user.hpp"


/* ~~ Public ~~ */

	/* ~~ Constructors / Destructors ~~ */
	User::User() : _username("unset"), _realname("unset"), _hostname("unset") {	std::cout << "User default constructor called" << std::endl; }
	User::~User() {	std::cout << "User destructor called" << std::endl;	}

/* ~~ Methods ~~ */
void User::test() {
	std::cout << "User test called" << std::endl;
}

/* ~~ Private ~~ */

	/* ~~ Getters ~~ */
	std::string User::getUsername() { return this->_username;}
	std::string User::getRealname() { return this->_realname;}
	std::string User::getHostname() { return this->_hostname;}
	int User::getFd() { return this->_fd;}

	/* ~~ Setters ~~ */
	void User::setUsername(std::string username) { this->_username = username;}
	void User::setRealname(std::string realname) { this->_realname = realname;}	
	void User::setHostname(std::string hostname) { this->_hostname = hostname;}
	void User::setFd(int fd) { this->_fd = fd;}

User::User(User const &src) {
	std::cout << "User copy constructor called" << std::endl;
	*this = src;
}