#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Irc.hpp"

class Client {
	private :
		int _fd;
		std::string _nickname;
		std::string _username;
		std::string _realname;
		std::string _hostname;
		int _status;
		int _motd;
		int _registered;

	public :
		Client(int client_fd);
		~Client();

		void test();

		/* ~~ Getters ~~ */
		int getFd();
		std::string getNickname();
		std::string getUsername();
		std::string getRealname();
		std::string getHostname();

		/* ~~ Setters ~~ */
		void setFd(int fd);
		void setNickname(std::string nickname);
		void setUsername(std::string username);
		void setRealname(std::string realname);
		void setHostname(std::string hostname);
	
};

#endif