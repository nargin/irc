/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 03:42:16 by romaurel          #+#    #+#             */
/*   Updated: 2023/08/17 19:07:52 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Irc.hpp"
#include "Server.hpp"

/*
 * Print error message
 * @param error: std::string
 * @return: int (FAILURE) -1
 */
int printError(std::string error) {
	std::cout << RED << error << RESET << std::endl;
	return FAILURE;
}

void Server::welcomeMessage(int fd) {
	send(fd, "Welcome to the IRC server!\n", 27, 0);
	send(fd, "Date: ", 6, 0);
	send(fd, this->getDateTime().c_str(), strlen(this->getDateTime().c_str()), 0);
	send(fd, "\r\n", 2, 0);

	int rand = std::rand();
	if (rand % 5 == 0 && rand % 7 == 0) {
		send(fd, COFFEE, strlen(COFFEE), 0);
		send(fd, "\033[31mRare Coffee !\033[0m\r\n", 24, 0);
	}
	else if (rand % 2 == 0)
		send(fd, DINO, strlen(DINO), 0);
	else
		send(fd, SNAIL, strlen(SNAIL), 0);
	send(fd, "\r\n", 2, 0);

	send(fd, "You are not registered yet.\n", 28, 0);
	send(fd, "Use PASS command to register then\r\n", 35, 0);
	send(fd, "Use the NICK command to be nicked !\r\n", 38, 0);
}

void sen(int fd, std::string msg) {
	send(fd, msg.c_str(), strlen(msg.c_str()), 0);
}

void sen(int fd, ...) {
	va_list ap;
	va_start(ap, fd);
	std::string msg;
	while ((msg = va_arg(ap, char *)) != "END") {
		send(fd, msg.c_str(), strlen(msg.c_str()), 0);
	}
	va_end(ap);
}
