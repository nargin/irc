/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 03:42:10 by romaurel          #+#    #+#             */
/*   Updated: 2023/08/17 18:09:16 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"


/* ~~ Public ~~ */

	/* ~~ Constructors / Destructors ~~ */
	Client::Client() {}
	Client::Client(int client_fd) {
		this->_fd = client_fd;
		this->_nickname = "";
		this->_username = "";
		this->_realname = "";
		this->_hostname = "";
		this->_status = 0;
		this->_nicked = 0;
		this->_motd = 0;
		this->_registered = 0;
		this->_isop = false;
		this->inChannel = false;
	}
	Client::~Client() {}

/* ~~ Methods ~~ */
void Client::test() { std::cout << RED << "Client test" << RESET << std::endl; }

/* ~~ Private ~~ */

	/* ~~ Getters ~~ */
	int Client::getFd() const { return this->_fd;}
	std::string Client::getNickname() const { return this->_nickname;}
	std::string Client::getUsername() const { return this->_username;}
	std::string Client::getRealname() const { return this->_realname;}
	std::string Client::getHostname() const { return this->_hostname;}
	std::string Client::getChannel() const { return this->channel;}
	int Client::getStatus() const { return this->_status;}
	int Client::getMotd() const { return this->_motd;}
	int Client::getRegistered() const { return this->_registered;}
	bool Client::getNicked() const { return this->_nicked;}
	bool Client::getOp() const { return this->_isop;}
	bool Client::getInChannel() const { return this->inChannel;}

	/* ~~ Setters ~~ */
	void Client::setFd(int fd) { this->_fd = fd;}
	void Client::setNickname(std::string nickname) { this->_nickname = nickname;}
	void Client::setUsername(std::string username) { this->_username = username;}
	void Client::setRealname(std::string realname) { this->_realname = realname;}
	void Client::setHostname(std::string hostname) { this->_hostname = hostname;}
	void Client::setStatus(int status) { this->_status = status;}
	void Client::setMotd(int motd) { this->_motd = motd;}
	void Client::setRegistered(int registered) { this->_registered = registered;}
	void Client::setNicked(bool nicked) { this->_nicked = nicked;}
	void Client::setOp(int op) { this->_isop = op;}
	void Client::setInChannel(bool inChannel) { this->inChannel = inChannel;}
	void Client::setChannel(std::string channel) { this->channel = channel;}
