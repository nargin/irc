/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robin <robin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 03:42:10 by romaurel          #+#    #+#             */
/*   Updated: 2023/08/03 22:35:30 by robin            ###   ########.fr       */
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
		this->_passentered = 0;
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
	int Client::getStatus() { return this->_status;}
	int Client::getMotd() { return this->_motd;}
	int Client::getRegistered() { return this->_registered;}
	int Client::getPassEntered() { return this->_passentered;}

	/* ~~ Setters ~~ */
	void Client::setFd(int fd) { this->_fd = fd;}
	void Client::setNickname(std::string nickname) { this->_nickname = nickname;}
	void Client::setUsername(std::string username) { this->_username = username;}
	void Client::setRealname(std::string realname) { this->_realname = realname;}	
	void Client::setHostname(std::string hostname) { this->_hostname = hostname;}
	void Client::setStatus(int status) { this->_status = status;}
	void Client::setMotd(int motd) { this->_motd = motd;}
	void Client::setRegistered(int registered) { this->_registered = registered;}
	void Client::setPassEntered(int passentered) { this->_passentered = passentered;}
