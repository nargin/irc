/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robin <robin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 03:42:16 by romaurel          #+#    #+#             */
/*   Updated: 2023/08/04 09:04:28 by robin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Irc.hpp"

/* 
 * Print error message
 * @param error: std::string
 * @return: int (FAILURE) -1
 */
int printError(std::string error) {
	std::cout << RED << error << RESET << std::endl;
	return FAILURE;
}