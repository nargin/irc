#ifndef SERVER_HPP
#define SERVER_HPP

#include "Irc.hpp"
#include "Client.hpp"

class Server {
	private :
		int _port;
		int _nbUsers;
		int _sockfd;
		std::string _pass;
		std::string _datetime;
		struct tm *_time;
		struct addrinfo _hints;
		struct addrinfo *_servinfo;
		std::vector<Client> _clients;

	public :
		Server(int port, std::string password);
		~Server();

		int launchServer();
		void newClient();
		int setHints(struct addrinfo *hints);
		void setDateTime(struct tm *time);

		/* ~~ Getters ~~ */
		int getNbUsers();
		int getPort();
		int getSockfd();
		std::string getDateTime();
		std::string getPass();
};

#endif