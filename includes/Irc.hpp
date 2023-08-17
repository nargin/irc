/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 03:42:04 by romaurel          #+#    #+#             */
/*   Updated: 2023/08/17 19:07:16 by maserrie         ###   ########.fr       */
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
void sen(int fd, std::string msg);
void sen(int fd, ...);

