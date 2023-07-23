#ifndef IRC_HPP
#define IRC_HPP

#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <map>
#include <math.h>
#include <netinet/in.h>
#include <poll.h>
#include <signal.h>
#include <stdlib.h>
#include <string>
#include <sys/socket.h>
#include <termios.h>
#include <unistd.h>
#include <vector>

#include "Macro.hpp"
#include "Colors.hpp"

int	printError(std::string error);

#endif