#include "irc.hpp"

#define default_port 6667

int main(int ac, char *av[]) {
	if (ac != 3)
		return printError("Usage: ./ircserv [port] [password]");
	
	int port = default_port;
	
	port = atoi(av[1]);
	if (port < 1 || port > 65535)
		port = default_port;	
	std::string password = av[2];

	IRC irc(port, password);
	irc.connect();
	return 0;
}