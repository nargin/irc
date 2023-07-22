#ifndef USER_HPP
#define USER_HPP

#include "bin.hpp"

class User {
	public :
		User();
		~User();

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
	
	private :
		User(User const &src); // private constructor to prevent copy

		int _fd;
		std::string _nickname;
		std::string _username;
		std::string _realname;
		std::string _hostname;
};

#endif