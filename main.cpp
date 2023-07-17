#include "irc.hpp"

int main(int ac, char *av[]) {
	if (ac != 3) {
		std::cout << "Usage: " << av[0] << " <port> <password>" << std::endl;
		return 1;
	}
	int port = atoi(av[1]);
	if (port < 1 || port > 65535) {
		std::cout << "Invalid port" << std::endl;
		return 1;
	}
	std::string password = av[2];

	IRC irc(port, password);
	if (irc.socketisation() == -1)
		return 1;
	irc.connect();
	std::cout << "socket fd : " << irc.getSockfd() << std::endl;
	listen(irc.getSockfd(), 3);
	return 0;
}