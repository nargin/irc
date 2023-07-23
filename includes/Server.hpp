#ifndef SERVER_HPP
#define SERVER_HPP

#include "Irc.hpp"

class Server {
	private :
		int _port;
		int _nbUsers;
		int sockfd;
		std::string _pass;

	public :
		Server(int port, std::string password);
		~Server();

		void launchServer();
		void newClient();

		/* ~~ Getters ~~ */
		int getNbUsers();
		int getPort();
		int getSockfd();
		std::string getPass();
};

#endif