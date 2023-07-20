#ifndef USER_HPP
#define USER_HPP

#include "bin.hpp"

class User {
	public :
		User();
		User(std::string username, std::string realname, std::string hostname);
		~User();	
		void test();
		std::string getUsername();
		std::string getRealname();
		std::string getHostname();
	
	private :
		User(User const &src);
		std::string _username;
		std::string _realname;
		std::string _hostname;
}