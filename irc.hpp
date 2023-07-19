#ifndef IRC_HPP
#define IRC_HPP

#include "bin.hpp"

int	printError(std::string error);

class IRC {
	public:
		IRC();
		IRC(int port, std::string password);
		~IRC();

		void launch();
		void connect(struct sockaddr_in serv_addr);
		void socketisation();
		
		/* ~~ GETTERS ~~ */
		int	getSockfd();
		int	getPort();
		std::string getPass();

	private:
		int	sockfd;
		int _port;
		std::string _pass;

};

#endif