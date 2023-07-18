#include "irc.hpp"

int	printError(std::string error) {
	std::cerr << error << std::endl;
	return 1;
};

IRC::IRC() {}

IRC::IRC(int port, std::string password) : _port(port), _pass(password) {}
IRC::~IRC() {}

int IRC::socketisation() {
	IRC::sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		return printError("Error opening socket");
	return 0;
}

void IRC::connect() {
	if (this->socketisation() != 0)
		exit(1);
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(this->_port);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(this->sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
		exit(printError("Error on binding"));
}