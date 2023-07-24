#include "Server.hpp"

Server::Server(int port, std::string password) : _port(port),  _nbUsers(0), _pass(password){
	if (port < 1024 || port > 65535)
		exit(printError("Port must be between 1024 and 65535"));
	std::cout << SERVERSPEAK << GREEN << "Server starting..." << RESET << std::endl;
	std::cout << SERVERSPEAK << YELLOW << "IRC server launched on port " << this->_port << RESET << std::endl;
	std::cout << SERVERSPEAK << YELLOW << "Password: " << this->_pass << RESET << std::endl;
}
Server::~Server() { std::cout << SERVERSPEAK << RED << "Server shutting down..." << RESET << std::endl; }

void Server::launchServer() {
	/* >> Initialize socket << */
	this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->sockfd < 0)
		exit(printError("Error opening socket"));


	/*  >> Bind socket << */
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(this->_port);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	int optionValue = 1;
	setsockopt(this->sockfd, SOL_SOCKET, SO_REUSEADDR, &optionValue, sizeof(optionValue));
	if (bind(this->sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
		exit(printError("Error on binding"));
	
	/* >> Listen << */
	listen(this->sockfd, 10);

	/* >> Accept << */
	char buffer[1024];
	struct sockaddr_in cli_addr;
	socklen_t clilen = sizeof(cli_addr);
	while (1) {
		int newsockfd = accept(this->sockfd, (struct sockaddr *)&cli_addr, &clilen);
		if (newsockfd < 0)
			exit(printError("Error on accept"));
		bzero(buffer, 1024);
		int n = read(newsockfd, buffer, 1023);
		if (n < 0)
			exit(printError("Error reading from socket"));
		std::cout << SERVERSPEAK << YELLOW << "Message received: " << buffer << RESET << std::endl;
		n = write(newsockfd, MSGRECEIVED, strlen(MSGRECEIVED));
		if (n < 0)
			exit(printError("Error writing to socket"));
		close(newsockfd);
	}
	
}

/* ~~ Getters ~~ */
int Server::getNbUsers() { return this->_nbUsers; }
int Server::getPort() { return this->_port; }
int Server::getSockfd() { return this->sockfd; }
std::string Server::getPass() { return this->_pass; }