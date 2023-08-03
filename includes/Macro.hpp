/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Macro.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstride <rstride@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 03:42:05 by romaurel          #+#    #+#             */
/*   Updated: 2023/08/03 03:45:34 by rstride          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

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

 