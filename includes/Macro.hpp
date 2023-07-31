#ifndef BIN_HPP
#define BIN_HPP

#define MAX_CLIENTS 1
#define BUFFER_SIZE 512

#define FAILURE -1
#define SUCCESS 0
#define CONTINUE 90
#define BREAK 91
#define QUIT 99

#define SERVERSPEAK "\033[0;36m[SERVER]\033[0m : "
#define CLIENTSPEAK "\033[0;35m[CLIENT]\033[0m : "
#define MSGRECEIVED "\033[0;36m[SERVER]\033[0m : I got your message\n"
#define DEBUG std::cout << RED << "DEBUG" << RESET << std::endl;

#endif