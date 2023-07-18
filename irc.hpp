#ifndef IRC_HPP
#define IRC_HPP

#include "bin.hpp"

int	printError(std::string error);

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

#endif