/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Macro.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robin <robin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 03:42:05 by romaurel          #+#    #+#             */
/*   Updated: 2023/08/06 17:57:37 by robin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define MAX_CLIENTS 2
#define BUFFER_SIZE 512

#define FAILURE -1
#define SUCCESS 0
#define CONTINUE 90
#define BREAK 91
#define QUIT 99

# define RESET "\033[0m"
# define ORANGE "\033[0;33m"
# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"

#define SERVERSPEAK "\033[0;36m[SERVER]\033[0m : "
#define CLIENTSPEAK "\033[0;35m[CLIENT]\033[0m : "
#define OPERATOR	"\033[0;35m[OPERATOR]\033[0m : "
#define MSGRECEIVED "\033[0;36m[SERVER]\033[0m : I got your message\n"
#define DEBUG std::cout << RED << "DEBUG" << RESET << std::endl;
