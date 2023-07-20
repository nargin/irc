#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "bin.hpp"

Commands parseCommand(std::string command);

class Commands {
	public :
		Commands();
		~Commands();

		/* ~~ Getters ~~ */
		std::string getCommand();
		std::string getParam();
	
	private :
		Commands(Commands const &src); // private constructor to prevent copy

		std::string _command;
		std::string _flags;
		std::string _param;
};