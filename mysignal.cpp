#include "mysignal.hpp"

void echo_ctl(int state) {
	struct termios	new_s;

	tcgetattr(0, &new_s);
	state ? new_s.c_lflag |= ECHO : new_s.c_lflag &= ~ECHO;
	tcsetattr(0, TCSANOW, &new_s);
}

void	handle_sigint(int sig) {
	(void)sig;
	std::cout << std::endl << "Exiting..." << std::endl;
	exit(1);
}