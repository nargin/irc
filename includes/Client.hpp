/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robin <robin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 03:41:59 by romaurel          #+#    #+#             */
/*   Updated: 2023/08/04 09:35:50 by robin            ###   ########.fr       */
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
		bool _isop;

	public :
		Client();
		Client(int client_fd);
		~Client();

		void test();

		/* ~~ Getters ~~ */
		int getFd(void);
		std::string getNickname(void);
		std::string getUsername(void);
		std::string getRealname(void);
		std::string getHostname(void);
		int getStatus(void);
		int getMotd(void);
		int getRegistered(void);
		bool getOp(void);

		/* ~~ Setters ~~ */
		void setFd(int fd);
		void setNickname(std::string nickname);
		void setUsername(std::string username);
		void setRealname(std::string realname);
		void setHostname(std::string hostname);
		void setStatus(int status);
		void setMotd(int motd);
		void setRegistered(int registered);
		void setOp(int op);

		bool operator==(const Client& other) const { return this->_fd == other._fd;	}

	
};

 