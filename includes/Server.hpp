/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robin <robin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 03:42:07 by romaurel          #+#    #+#             */
/*   Updated: 2023/08/03 22:29:40 by robin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Irc.hpp"
#include "Client.hpp"
#include "Channel.hpp"

class Server {
	private :
		int _port;
		int _nbUsers;
		int _sockfd;
		std::string _pass;
		std::string _datetime;
		struct tm *_time;
		struct addrinfo _hints;
		struct addrinfo *_servinfo;
		std::map <int, Client> _clients;
		std::map<std::string, Channel> _channels;

	public :
		Server(int port, std::string password);
		~Server();

		int launchServer();
		int receiveData(std::vector <pollfd>& fds, std::vector <pollfd>::iterator& iter);
		int pollerrEvent(std::vector <pollfd>& fds, std::vector <pollfd>::iterator& iter);
		
		int acceptClient(std::vector <pollfd>& fds, std::vector <pollfd>& tempNewFds);
		void newClient(int client_fd, std::vector <pollfd>& tempNewFds);
		void deleteClient(std::vector <pollfd>& fds, std::vector <pollfd>::iterator& iter);

		void parseInput(std::string inputUser, std::vector<pollfd>::iterator& iter);
		int loopingServer();
		int setHints(struct addrinfo *hints);
		void setDateTime(struct tm *time);

		void handle_kick_command(int client_fd, const std::string& channel_name, const std::string& user_to_kick);

		/* ~~ Getters ~~ */
		int getNbUsers();
		int getPort();
		int getSockfd();
		std::string getDateTime();
		std::string getPass();
};
