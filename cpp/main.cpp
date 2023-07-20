#include "irc.hpp"

#define default_port 6667

void handle_sigint(int sig) {
	(void)sig;
	std::cout << std::endl;
	exit(0);
}

void echo_ctl(int mode) {
	struct termios term;
	tcgetattr(0, &term);
	if (mode)
		term.c_lflag |= (ICANON | ECHO);
	else
		term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, TCSANOW, &term);
}

int main(int ac, char *av[]) {
	if (ac != 3)
		return printError("Usage: ./ircserv [port] [password]");
	
	int port = default_port;
	
	port = atoi(av[1]);
	if (port < 1 || port > 65535)
		port = default_port;	
	
	echo_ctl(1);
	signal(SIGINT, handle_sigint);
	
	std::string password = av[2];

	IRC irc(port, password);
	irc.launch();
	return 0;
}