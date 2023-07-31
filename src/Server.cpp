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
		return printError(SERVERSPEAK RED "Error on listening" RESET);

	return SUCCESS;
}

void clientLimitReached(int clientFd) {
	std::cout << SERVERSPEAK << RED << "Client limit reached" << RESET << std::endl;
	send(clientFd, "\033[0;31mClient limit reached\033[0m", 32, 0);
	close(clientFd);
}

void Server::newClient(int clientFd, std::vector<pollfd>& pollFd) {
	pollfd clientPollfd;
	Client new_client(clientFd);

	clientPollfd.fd = clientFd;
	clientPollfd.events = POLLIN;
	pollFd.push_back(clientPollfd);
	std::cout << SERVERSPEAK << YELLOW << "New client fd #" << clientFd << " connected" << RESET << std::endl;

	this->_clients.insert(std::pair<int, Client>(clientFd, new_client));
	std::cout << "users : " << this->_clients.size() << std::endl;
}

int Server::acceptClient(std::vector<pollfd> fds, std::vector<pollfd>& tempNewFds) {
	struct sockaddr_storage client_addr;
	socklen_t sin_size = sizeof(client_addr);
	int new_fd = 0;

	if ((new_fd = accept(_sockfd, (struct sockaddr *)&client_addr, &sin_size)) == FAILURE) {
		printError(SERVERSPEAK RED "Error on accepting client" RESET);
		return CONTINUE;
	}

	std::cout << "size : " << fds.size() << " max : " << MAX_CLIENTS << std::endl;
	if (fds.size() - 1 >= MAX_CLIENTS)
		clientLimitReached(new_fd);
	else
		newClient(new_fd, tempNewFds);
	return SUCCESS;
}

int Server::receiveData(std::vector<pollfd> fds, std::vector<pollfd>::iterator iter) {
	// Clients client;
	
	char buffer[512];
	int n = 0;

	bzero(buffer, 512);
	n = recv(iter->fd, buffer, 510, 0);
	if (n == FAILURE) {
		std::cout << SERVERSPEAK << RED << "Error on receiving data" << RESET << std::endl;
		deleteClient(fds, iter);
		return BREAK;
	} else if (n == 0) {
		this->deleteClient(fds, iter);
		return BREAK;
	} else {
		buffer[n] = '\0';
		std::cout << SERVERSPEAK << ORANGE << "Received data from fd " << iter->fd << ": " << buffer << RESET << std::endl;
		return SUCCESS;
	}
}

void Server::deleteClient(std::vector<pollfd>& fds, std::vector<pollfd>::iterator& iter) {
	std::cout << SERVERSPEAK << YELLOW << "Client fd #" << iter->fd << " disconnected" << RESET << std::endl;
	close(iter->fd);
	fds.erase(iter);
	this->_clients.erase(iter->fd);
}

int Server::pollerrEvent(std::vector<pollfd> fds, std::vector<pollfd>::iterator iter) {
	if (iter->fd == this->_sockfd) {
		std::cout << SERVERSPEAK << RED << "Error on server socket" << RESET << std::endl;
		return BREAK;
	}

	std::cout << SERVERSPEAK << RED << "Error on client socket" << RESET << std::endl;
	send(iter->fd, "\033[0;31mError on client socket\033[0m", 35, 0);
	this->deleteClient(fds, iter);

	return SUCCESS;
}

int Server::loopingServer(void) {
	std::vector <pollfd> fds;
	pollfd serverPollfd;

	serverPollfd.fd = this->_sockfd;
	serverPollfd.events = POLLIN;

	fds.push_back(serverPollfd);
	std::cout << SERVERSPEAK << YELLOW << "Server fd: " << this->_sockfd << RESET << std::endl;

	while (1) {
		std::vector<pollfd> tempNewFds; // Temporary vector for new clients

		if (poll((pollfd *)&fds[0], (unsigned int)fds.size(), -1) < 1) {
			printError(SERVERSPEAK RED "Error on polling" RESET);
			break;
		}

		std::vector<pollfd>::iterator iter = fds.begin();
		
		DEBUG;
		while (iter != fds.end()) {

			if (iter->revents & POLLIN) {
			
				/* New client or data received */
				if (iter->fd == this->_sockfd) {
					if (this->acceptClient(fds, tempNewFds) == CONTINUE)
						continue;
				}
				else
					if (this->receiveData(fds, iter) == BREAK)
						break;
			
			}
			// else if (iter->revents & POLLOUT) {
				
			// }
			else if (iter->revents & POLLERR) {
				if (this->pollerrEvent(fds, iter) == BREAK)
					break;
				else return FAILURE;
			}
			iter++;
		}
		fds.insert(fds.end(), tempNewFds.begin(), tempNewFds.end());
	}

	return SUCCESS;
}

/* ~~ Getters ~~ */
int Server::getNbUsers() { return this->_nbUsers; }
int Server::getPort() { return this->_port; }
int Server::getSockfd() { return this->_sockfd; }
std::string Server::getDateTime() { return this->_datetime; }
std::string Server::getPass() { return this->_pass; }