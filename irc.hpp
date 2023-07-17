#pragma once

#include "bin.hpp"

class IRC {
	public:
		IRC();
		IRC(int port, std::string password);
		~IRC();
		void connect();
		int socketisation();
		int	getSockfd() const { return this->sockfd; }
		int	getPort() const { return this->_port; }
		std::string getPass() const { return this->_pass; }

	private:
		int	sockfd;
		int _port;
		std::string _pass;

};