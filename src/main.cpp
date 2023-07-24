#include "Server.hpp"

void echo_ctl(int mode) {
	struct termios term;
	tcgetattr(0, &term);
	if (mode)
		term.c_lflag |= (ICANON | ECHO);
	else
		term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, TCSANOW, &term);
}

void handle_sigint(int sig) {
	std::cout << "signal num: " << sig << std::endl;
	if (sig == SIGINT) {
		std::cout << SERVERSPEAK << RED << "Server shutting down..." << RESET << std::endl;
		exit(0);
	} else if (sig == SIGQUIT) {
		std::cout << std::endl;
	}
}

int main(int ac, char *av[]) {
	if (ac != 3)
		return printError("Usage: ./ircserv [port] [password]");
	
	// echo_ctl(1);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigint);
	
	Server server(atoi(av[1]), std::string (av[2]));

	server.launchServer();

	return 0;
}