/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 03:41:59 by romaurel          #+#    #+#             */
/*   Updated: 2023/08/17 18:08:59 by maserrie         ###   ########.fr       */
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
		std::string channel;
		int _status;
		int _motd;
		int _registered;
		int	_nicked;
		bool _isop;
		bool inChannel;

	public :
		Client();
		Client(int client_fd);
		~Client();

		void test();

		/* ~~ Getters ~~ */
		int getFd(void) const;
		std::string getNickname(void) const;
		std::string getUsername(void) const;
		std::string getRealname(void) const;
		std::string getHostname(void) const;
		std::string getChannel(void) const;
		int getStatus(void) const;
		int getMotd(void) const;
		int getRegistered(void) const;
		bool getNicked(void) const;
		bool getOp(void) const;
		bool getInChannel(void) const;

		/* ~~ Setters ~~ */
		void setFd(int fd);
		void setNickname(std::string nickname);
		void setUsername(std::string username);
		void setRealname(std::string realname);
		void setHostname(std::string hostname);
		void setStatus(int status);
		void setMotd(int motd);
		void setRegistered(int registered);
		void setNicked(bool nicked);
		void setOp(int op);
		void setInChannel(bool inChannel);
		void setChannel(std::string channel);

		bool operator==(const Client& other) const { return this->_fd == other._fd;	}


};

