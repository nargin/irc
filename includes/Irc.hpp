/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robin <robin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 03:42:04 by romaurel          #+#    #+#             */
/*   Updated: 2023/08/03 22:30:03 by robin            ###   ########.fr       */
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

#include "Macro.hpp"
#include "Colors.hpp"

#define OP_PASS "[]"

int	printError(std::string error);
void setDatetime(struct tm *time);
int isCommand(std::string input);

 