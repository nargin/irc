#include "user.hpp"


/* ~~ Public ~~ */

	/* ~~ Constructors / Destructors ~~ */
	User::User() : _username("unset"), _realname("unset"), _hostname("unset") {}
	User::~User() {}

/* ~~ Methods ~~ */
void User::test() {
	std::cout << "User test called" << std::endl;
}

/* ~~ Private ~~ */

	/* ~~ Getters ~~ */
	int User::getFd() { return this->_fd;}
	std::string User::getNickname() { return this->_nickname;}
	std::string User::getUsername() { return this->_username;}
	std::string User::getRealname() { return this->_realname;}
	std::string User::getHostname() { return this->_hostname;}

	/* ~~ Setters ~~ */
	void User::setFd(int fd) { this->_fd = fd;}
	void User::setNickname(std::string nickname) { this->_nickname = nickname;}
	void User::setUsername(std::string username) { this->_username = username;}
	void User::setRealname(std::string realname) { this->_realname = realname;}	
	void User::setHostname(std::string hostname) { this->_hostname = hostname;}

User::User(User const &src) {
	std::cout << "User copy constructor called" << std::endl;
	*this = src;
}