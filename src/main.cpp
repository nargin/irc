/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstride <rstride@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 03:44:17 by romaurel          #+#    #+#             */
/*   Updated: 2023/08/03 03:44:33 by rstride          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

/* 
 * Toggle signal echo on/off
 * @param mode: int (1 to turn on, 0 to turn off)
 */
void echo_ctl(int mode) {
	struct termios term;
	tcgetattr(0, &term);
	if (mode)
		term.c_lflag |= (ICANON | ECHO);
	else
		term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, TCSANOW, &term);
}

/* 
 * 
 * @param sig: int
 */
void handle_sigint(int sig) {
	std::cout << "signal num: " << sig << std::endl;
	if (sig == SIGINT) {
		std::cout << SERVERSPEAK << RED << "Server shutting down..." << RESET << std::endl;
		exit(0);
	}
}

int main(int ac, char *av[]) {
	if (ac != 3)
		return printError("Usage: ./ircserv [port] [password]");
	
	// echo_ctl(1);
	signal(SIGINT, handle_sigint);
	
	int port = 0;
	if ((port = atoi(av[1])) < 1024 || port > 65535)
		return printError("Port must be between 1024 and 65535");

	Server server(port, std::string (av[2]));

	server.launchServer();

	if (server.loopingServer())
		return printError("Error on server loop");

	return 0;
}