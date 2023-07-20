#ifndef USER_HPP
#define USER_HPP

#include "bin.hpp"

class User {
	public :
		User();
		~User();

		void test();

		/* ~~ Getters ~~ */
		std::string getUsername();
		std::string getRealname();
		std::string getHostname();
	
	private :
		User(User const &src); // private constructor to prevent copy

		std::string _nickname;
		std::string _username;
		std::string _realname;
		std::string _hostname;
}
