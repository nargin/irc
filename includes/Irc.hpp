/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 03:42:04 by romaurel          #+#    #+#             */
/*   Updated: 2023/08/18 00:51:37 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

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
#include <netdb.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cstdarg>

#include "Macro.hpp"

#define OP_PASS "justask"

int	printError(std::string error);
void setDatetime(struct tm *time);
void send_msg(int fd, std::string msg);
void send_list(int fd, ...);
std::vector<std::string> split(std::string str, std::string token);
