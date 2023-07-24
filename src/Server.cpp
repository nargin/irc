#include "Server.hpp"

Server::Server(int port, std::string password) : _port(port), _nbUsers(0), _pass(password), _time(NULL) {
	std::cout << SERVERSPEAK << GREEN << "Server starting..." << RESET << std::endl;
	std::cout << SERVERSPEAK << YELLOW << "IRC server launched on port " << this->_port << RESET << std::endl;
	std::cout << SERVERSPEAK << YELLOW << "Password: " << this->_pass << RESET << std::endl;
	
	/* Set hints to 0 */
	bzero(&this->_hints, sizeof(this->_hints));
	
	/* Get current time */
	time_t rawtime;
	(time(&rawtime), this->_time = localtime(&rawtime));
	/* Set datetime */
	this->setDateTime(this->_time);

	std::cout << SERVERSPEAK << YELLOW << "Date: " << this->_datetime << RESET << std::endl;

}

Server::~Server() { std::cout << SERVERSPEAK << RED << "Server shutting down..." << RESET << std::endl; }

void Server::setDateTime(struct tm *time) {
	char buffer[80];

	strftime(buffer, sizeof(buffer),"%d-%m-%Y %H:%M:%S",time);

	this->_datetime = std::string(buffer);
}

/* 
 * Set hints for getaddrinfo()
 * @param hints: struct addrinfo *
 * @return: int (0 on success, 1 on failure)
 */
int Server::setHints(struct addrinfo *hints) {
	hints->ai_family = AF_INET;	hints->ai_socktype = SOCK_STREAM; hints->ai_flags = AI_PASSIVE;
	/* ↑↑ AF_INET: IPv4, SOCK_STREAM: TCP, AI_PASSIVE: localhost by default for bind() ↑↑ */

	std::stringstream ss;
	ss << this->_port;
	std::string port = ss.str();
	if (getaddrinfo(NULL, port.c_str(), hints, &_servinfo) != 0)
		return FAILURE;
	return SUCCESS;
}

/* 
 * Launch server
 * @return: int (0 on success, 1 on failure)
 */
int Server::launchServer() {
	/* >> Refer above << */
	if (setHints(&_hints))
		return printError(SERVERSPEAK RED "Error on setting hints" RESET);

	/* >> Initialize socket << */
	if ((this->_sockfd = socket(_servinfo->ai_family, _servinfo->ai_socktype, _servinfo->ai_protocol)) == FAILURE)
		return printError(SERVERSPEAK RED "Error opening socket" RESET);

	/* >> Set socket options << */
	int optionValue = 1; // Enable address reuse
	/* SOL_SOCKET: socket level, SO_REUSEADDR: reuse address, &optionValue: enable option, sizeof(optionValue): size of option */
	if (setsockopt(this->_sockfd, SOL_SOCKET, SO_REUSEADDR, &optionValue, sizeof(optionValue)) == FAILURE)
		return printError(SERVERSPEAK RED "Error on setsockopt" RESET);

	/*  >> Bind socket << */
	if (bind(this->_sockfd, _servinfo->ai_addr, _servinfo->ai_addrlen) == FAILURE)
		return printError(SERVERSPEAK RED "Error on binding" RESET);
	
	/* >> Listen << */
	if (listen(this->_sockfd, 10) == FAILURE)
		return printError(SERVERSPEAK RED "Error on listening" RESET);\

	return SUCCESS;
}

/* ~~ Getters ~~ */
int Server::getNbUsers() { return this->_nbUsers; }
int Server::getPort() { return this->_port; }
int Server::getSockfd() { return this->_sockfd; }
std::string Server::getDateTime() { return this->_datetime; }
std::string Server::getPass() { return this->_pass; }