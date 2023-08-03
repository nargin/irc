/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstride <rstride@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 03:42:10 by romaurel          #+#    #+#             */
/*   Updated: 2023/08/03 03:46:43 by rstride          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"


/* ~~ Public ~~ */

	/* ~~ Constructors / Destructors ~~ */
	Client::Client(int client_fd) {
		this->_fd = client_fd;
		this->_nickname = "";
		this->_username = "";
		this->_realname = "";
		this->_hostname = "";
		this->_status = 0;
		this->_motd = 0;
		this->_registered = 0;
	}
	Client::~Client() {}

/* ~~ Methods ~~ */
void Client::test() { std::cout << RED << "Client test" << RESET << std::endl; }

/* ~~ Private ~~ */

	/* ~~ Getters ~~ */
	int Client::getFd() { return this->_fd;}
	std::string Client::getNickname() { return this->_nickname;}
	std::string Client::getUsername() { return this->_username;}
	std::string Client::getRealname() { return this->_realname;}
	std::string Client::getHostname() { return this->_hostname;}

	/* ~~ Setters ~~ */
	void Client::setFd(int fd) { this->_fd = fd;}
	void Client::setNickname(std::string nickname) { this->_nickname = nickname;}
	void Client::setUsername(std::string username) { this->_username = username;}
	void Client::setRealname(std::string realname) { this->_realname = realname;}	
	void Client::setHostname(std::string hostname) { this->_hostname = hostname;}
