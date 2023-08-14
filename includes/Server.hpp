/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romaurel <romaurel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 03:42:07 by romaurel          #+#    #+#             */
/*   Updated: 2023/08/14 14:24:14 by romaurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Irc.hpp"
#include "Client.hpp"
#include "Channel.hpp"

bool isValidNick(std::map<int, Client>_clients, std::string nick);

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
		int commandExec(std::string inputUser, std::vector<pollfd>::iterator& it);
		int loopingServer();
		int setHints(struct addrinfo *hints);
		void setDateTime(struct tm *time);
		void welcomeMessage(int fd);

		void handlePrivMsg(std::string command, std::vector<pollfd>::iterator& it);
		void handlePassCommand(std::string inputUser, std::vector<pollfd>::iterator& iter);
		void handleNickCommand(std::string command, std::vector<pollfd>::iterator& it);
		void quitClient(std::vector<pollfd>::iterator &it);
		void botCommand(std::string command, std::vector<pollfd>::iterator &it);

		/* ~~ Getters ~~ */
		int getNbUsers();
		int getPort();
		int getSockfd();
		std::string getDateTime();
		std::string getPass();
};
