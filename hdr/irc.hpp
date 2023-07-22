#ifndef IRC_HPP
#define IRC_HPP

#include "bin.hpp"
#include "user.hpp"

int	printError(std::string error);

class IRC {
	public:
		IRC();
		IRC(int port, std::string password);
		~IRC();

		void launch();
		void newClient();
		std::string slisten();
		void connect(struct sockaddr_in serv_addr);
		void socketisation();
		
		/* ~~ GETTERS ~~ */
		int	getNbUsers();
		int	getPort();
		int	getSockfd();
		std::string getPass();

	private:
		int _port;
		int	sockfd;
		int _nbUsers;
		User _user[10];
		std::string _pass;

};

#endif