#include "irc.hpp"
#include "commands.hpp"

int	printError(std::string error) {
	std::cerr << error << std::endl;
	return 1;
};

IRC::IRC() {}

IRC::IRC(int port, std::string password) : _port(port),  _nbUsers(0), _pass(password){}
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

std::string IRC::slisten() {
	char buffer[512];

	for (int loop = 0; loop < this->getNbUsers(); loop++) {
		int n = recv(this->_user[loop].getFd(), buffer, sizeof(buffer), 0);
		if (n < 0)
			printError("Error reading from socket");
	}
	return buffer;
}

void	IRC::newClient(void) {
		int client_fd = accept(this->sockfd, (struct sockaddr *)NULL, NULL);

		if (client_fd < 0)
			exit(printError("Error on accept"));
		this->_nbUsers++;
		this->_user[this->_nbUsers].setFd(client_fd);
		this->_user[this->_nbUsers].setNickname("unset");
		this->_user[this->_nbUsers].setUsername("unset");
		this->_user[this->_nbUsers].setRealname("unset");
		this->_user[this->_nbUsers].setHostname("localhost");
}

void	IRC::launch() {
	this->socketisation();

	struct sockaddr_in serv_addr;
	this->connect(serv_addr);
	
	std::cout << "IRC server launched on port " << this->_port << std::endl;
	std::cout << "Password: " << this->_pass << std::endl;
	
	while (1) {
		std::string data;

		listen(this->getSockfd(), 10);

		std::cout << "Waiting for new client..." << std::endl;

		newClient();

		data = slisten();

		if (data == "QUIT")
			break;
		if (data.empty())
			continue;
		else
			std::cout << data << std::endl;
		// irc.parseCommand();
	}

	close(this->sockfd);
}


/* ~~ GETTERS ~~ */
int IRC::getNbUsers() { return this->_nbUsers; }
int IRC::getSockfd() { return this->sockfd; }
int IRC::getPort() { return this->_port; }
std::string IRC::getPass() { return this->_pass; }