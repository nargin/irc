/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romaurel <romaurel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 03:42:11 by rstride           #+#    #+#             */
/*   Updated: 2023/08/14 14:39:35 by romaurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Channel.hpp"
#include "Commands.hpp"

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

void Server::quitClient(std::vector<pollfd>::iterator &it) {
	std::cout << SERVERSPEAK << "Client #" << it->fd << " disconnected with quit command" << std::endl;
	send(it->fd, "You have been disconnected\r\n", 28, 0);
	close(it->fd);
	_clients.erase(it->fd);
}

void Server::botCommand(std::string command, std::vector<pollfd>::iterator &it) {
	std::vector<std::string> tokens;
	std::istringstream stream(command);
	std::string token;
	char delimiter = ' ';

	while (std::getline(stream, token, delimiter)) {
		tokens.push_back(token);
	}
	if (tokens.size() < 2) {
		send(it->fd, "\033[0;31mError\033[0m : Not enough arguments\r\n", 41, 0);
		return ;
	} else if (tokens.size() > 2) {
		send(it->fd, "\033[0;31mError\033[0m : Too many arguments\r\n", 39, 0);
		return ;
	}
	std::string cmd = tokens[0];
	std::string args = tokens[1];
	std::cout << SERVERSPEAK << "Client #" << it->fd << " used bot command " << cmd << " " << args << std::endl;

	if (args == "ping") {
		std::string pong = "Ping : " + patch::to_string(rand() % 250 + 1) + "\r\n";
		send(it->fd, pong.c_str(), pong.length(), 0);
	}
	else if (args == "time") {
		std::string time = _datetime.substr(0, _datetime.find("\n"));
		send(it->fd, time.c_str(), time.length(), 0);
		send(it->fd, "\r\n", 2, 0);
	}
	else if (args == "help") {
		send(it->fd, "Available commands : ping, time, help\r\n", 39, 0);
	}
	else
		send(it->fd, "\033[0;31mError\033[0m : Command not found\r\n", 40, 0);
}

void Server::handlePrivMsg(std::string command, std::vector<pollfd>::iterator& it) {
	if (_clients[it->fd].getRegistered() == 0 && _clients[it->fd].getNicked() == 1) {
		send(it->fd, "\033[0;31mError\033[0m : You have to be registered/nicked to send private message\r\n", 78, 0);
		return ;
	}
	std::vector<std::string> tokens;
    std::istringstream stream(command);
    std::string token;
	char delimiter = ' ';
    
    while (std::getline(stream, token, delimiter)) {
        tokens.push_back(token);
    }
	if (tokens.size() < 3) {
		send(it->fd, "\033[0;31mError\033[0m : Not enough arguments\r\n", 41, 0);
		return ;
	}
	std::string nick = tokens[1];
	std::string msg = tokens[2];
	std::map<int, Client>::iterator it1 = _clients.find(it->fd);
	if (it1 != _clients.end() && it1->second.getNicked() == 1) {
		std::map<int, Client>::iterator it2 = _clients.begin();
		while (it2 != _clients.end()) {
			if (it2->second.getNickname() == nick) {
				
				std::cout << SERVERSPEAK << it1->second.getNickname() << " sent private message to " << nick << std::endl;
				
				send(it1->second.getFd(), "You sent a private message to ", 31, 0);
				send(it1->second.getFd(), nick.c_str(), nick.length(), 0);
				send(it1->second.getFd(), "\r\n", 2, 0);

				send(it2->second.getFd(), "You received a private message from ", 36, 0);
				send(it2->second.getFd(), it1->second.getNickname().c_str(), it1->second.getNickname().length(), 0);
				send(it2->second.getFd(), " : ", 3, 0);
				while (tokens.size() > 2) {
					send(it2->second.getFd(), tokens[2].c_str(), tokens[2].length(), 0);
					tokens.erase(tokens.begin() + 2);
					if (tokens.size() > 2)
						send(it2->second.getFd(), " ", 1, 0);
				}
				send(it2->second.getFd(), "\r\n", 5, 0);
				return ;
			}
			it2++;
		}
		send(it1->second.getFd(), "\033[0;31mError\033[0m : Nickname not found\r\n", 40, 0);
	}
	else
		send(it1->second.getFd(), "\033[0;31mError\033[0m : You have to be registered/nicked to send private message\r\n", 78, 0);
	
}

void Server::handlePassCommand(std::string command, std::vector<pollfd>::iterator& iter) {
	std::string pass = command.substr(5);
	std::map<int, Client>::iterator it = _clients.find(iter->fd);
	if (pass == _pass && it != _clients.end())
	{
		std::cout << "Client #" << iter->fd << " is now registered" << std::endl;
		send(iter->fd, "\033[0;32mSuccess\033[0m : You are now registered\r\n", 46, 0);
		it->second.setRegistered(1);
	}
	else {
		std::cout << "Client #" << iter->fd << " tried password " << pass << std::endl;
		send(iter->fd, "\033[0;31mError\033[0m : Wrong password\r\n", 40, 0);
	}
		
}

void	Server::handleNickCommand(std::string command, std::vector<pollfd>::iterator& it) {
	if (_clients[it->fd].getRegistered() == 0) {
		send(it->fd, "\033[0;31mError\033[0m : You have to be registered to set nickname\r\n", 64, 0);
		return ;
	}
	if (command.length() < 7) {
		send(it->fd, "\033[0;31mError : Nickname too short\033[0m\r\n", 43, 0);
		return ;
	}
	std::string nick = command.substr(5);
	if (nick.length() > 0 &&  _clients.find(it->fd) != _clients.end() && isValidNick(_clients, nick))
	{
		std::cout << SERVERSPEAK <<"Client #" << it->fd << " changed nickname to " << nick << std::endl;
		send(it->fd, "\033[0;32mSuccess\033[0m : You are now nicked\r\n", 42, 0);
		_clients[it->fd].setNickname(nick);
		_clients[it->fd].setNicked(true);
	}
	else {
		std::cout << "Client #" << it->fd << " tried to set nickname to " << nick << std::endl;
		send(it->fd, "\033[0;31mError\033[0m : Nickname already taken\r\n", 43, 0);
	}
}

int	Server::commandExec(std::string inputUser, std::vector<pollfd>::iterator& it) {
	std::string checkCommand = inputUser.substr(0, inputUser.find(" "));
	std::transform(checkCommand.begin(), checkCommand.end(), checkCommand.begin(), ::toupper);
	
	if (checkCommand == "PASS" && inputUser.length() > 5 && _clients.find(it->fd) != _clients.end())
		handlePassCommand(inputUser, it);
	else if (checkCommand == "NICK")
		handleNickCommand(inputUser, it);
	else if (checkCommand == "PRIVMSG")
		handlePrivMsg(inputUser, it);
	else if (checkCommand == "QUIT")
		quitClient(it);
	else if (checkCommand == "/BOT")
		botCommand(inputUser, it);
	else
		return 0;
	return 1;
	
}

void Server::parseInput(std::string inputUser, std::vector<pollfd>::iterator& iter) {
	if (commandExec(inputUser, iter))
		return ;
	else if (_clients.find(iter->fd) != _clients.end() && _clients[iter->fd].getRegistered() == 0 && _clients[iter->fd].getNicked() == 0) {
		send(iter->fd, "\033[0;31mError\033[0m : You have to be registered to send messages\r\n", 64, 0);
	}
	else if (_clients.find(iter->fd) != _clients.end() && _clients[iter->fd].getRegistered() && _clients[iter->fd].getNicked() == 0) {
		send(iter->fd, "\033[0;31mError\033[0m : You have to be nicked to send messages\r\n", 60, 0);
	}
	else {
		if (_clients[iter->fd].getRegistered()) std::cout << CLIENTSPEAK;
		std::cout << "Client ";
		if (_clients[iter->fd].getNicked())
			std::cout << _clients[iter->fd].getNickname();
		else
			std::cout << "#" << iter->fd;
		std::cout << " sent " << inputUser << std::endl;
	}
}
