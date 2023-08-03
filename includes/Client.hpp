/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robin <robin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 03:41:59 by romaurel          #+#    #+#             */
/*   Updated: 2023/08/03 22:35:23 by robin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Irc.hpp"

class Client {
	private :
		int _fd;
		std::string _nickname;
		std::string _username;
		std::string _realname;
		std::string _hostname;
		int _status;
		int _motd;
		int _registered;
		int _passentered;

	public :
		Client(int client_fd);
		~Client();

		void test();

		/* ~~ Getters ~~ */
		int getFd();
		std::string getNickname();
		std::string getUsername();
		std::string getRealname();
		std::string getHostname();
		int getStatus();
		int getMotd();
		int getRegistered();
		int getPassEntered();

		/* ~~ Setters ~~ */
		void setFd(int fd);
		void setNickname(std::string nickname);
		void setUsername(std::string username);
		void setRealname(std::string realname);
		void setHostname(std::string hostname);
		void setStatus(int status);
		void setMotd(int motd);
		void setRegistered(int registered);
		void setPassEntered(int passentered);

		bool operator==(const Client& other) const {
			// Add your comparison logic here
			// For example, if you have a unique identifier in the Client class:
			return this->_fd == other._fd;
		}

	
};

 