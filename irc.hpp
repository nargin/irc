#pragma once

#include "bin.hpp"

class IRC {
	public:
		IRC();
		IRC(int port, std::string password);
		~IRC();
		void connect();

	private:
		int _port;
		std::string _pass;

};