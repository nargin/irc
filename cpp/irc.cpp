#include "irc.hpp"
#include "commands.hpp"

int	printError(std::string error) {
	std::cerr << error << std::endl;
	return 1;
};

IRC::IRC() {}

IRC::IRC(int port, std::string password) : _port(port), _pass(password) {}
IRC::~IRC() {}

void IRC::socketisation() {
	this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->sockfd < 0)
		exit(printError("Error opening socket"));
}

void IRC::connect(struct sockaddr_in serv_addr) {
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(this->_port);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(this->sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
		exit(printError("Error on binding"));
}

std::string slisten(int client_fd) {
	char buffer[1024];
	int n = recv(client_fd, buffer, sizeof(buffer), 0);
	if (n < 0)
		printError("Error reading from socket");
	return std::string str(buffer);
}

void	IRC::launch() {
	this->socketisation();

	struct sockaddr_in serv_addr;
	this->connect(serv_addr);
	
	std::cout << "IRC server launched on port " << this->_port << std::endl;
	std::cout << "Password: " << this->_pass << std::endl;
	
	while (1) {
		std::string data = 0;

		listen(this->sockfd, 10);

		int client_fd = accept(this->sockfd, (struct sockaddr *)NULL, NULL);

		if (client_fd < 0)
			exit(printError("Error on accept"));

		data = slisten(client_fd);

		irc.parseCommand();
		std::cout << "Message received: " << buffer << std::endl;
	}

	std::cout << "Client disconnected" << std::endl;
	
	close(client_fd);
	close(this->sockfd);
}


/* ~~ GETTERS ~~ */

int IRC::getSockfd() { return this->sockfd; }
int IRC::getPort() { return this->_port; }
std::string IRC::getPass() { return this->_pass; }