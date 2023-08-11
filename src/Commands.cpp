/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robin <robin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 03:42:11 by rstride           #+#    #+#             */
/*   Updated: 2023/08/11 15:35:16 by robin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Channel.hpp"
#include "Commands.hpp"

void Server::botCommand(std::string command, std::vector<pollfd>::iterator &it) {
	if (command.find("?") == command.npos) {
		send(it->fd, "Add ? to your question for our bot to answer\r\n", 46, 0);
		return ;
	}
	std::string question = command.substr(5);

	std::cout << SERVERSPEAK << "Client #" << it->fd << " asked : " << question << std::endl;
	std::vector<std::string> tokens;
	std::istringstream stream(question);
	std::string token;

	while (std::getline(stream, token, ' ')) {
		tokens.push_back(token);
	}
	if (tokens.size() == 0) {
		send(it->fd, "Add ? to your question for our bot to answer\r\n", 46, 0);
		return ;
	}

	std::vector<std::string> _botAnswers;
	_botAnswers.push_back("xerophyte");
	_botAnswers.push_back("drought");
	_botAnswers.push_back("sandstorm");
	_botAnswers.push_back("cosmos");
	_botAnswers.push_back("exoplanet");
	_botAnswers.push_back("celestial");
	
	std::string answer = _botAnswers[rand() % _botAnswers.size()];
	std::string word = tokens[rand() % tokens.size()];
	std::cout << SERVERSPEAK << "Bot answered : " << answer << " " << word << std::endl;
	if (rand() % 2 == 0)
		std::swap(answer, word);
	std::string msg = "The answer to your question is : " + answer + " " + word + "\r\n";
	send(it->fd, msg.c_str(), msg.length(), 0);
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

void	Server::commandExec(std::string inputUser, std::vector<pollfd>::iterator& it) {
	if (inputUser.substr(0, 4) == "PASS" && inputUser.length() > 5 && _clients.find(it->fd) != _clients.end())
		handlePassCommand(inputUser, it);
	else if (inputUser.substr(0, 4) == "NICK")
		handleNickCommand(inputUser, it);
	else if (inputUser.substr(0, 7) == "PRIVMSG")
		handlePrivMsg(inputUser, it);
	else if (inputUser.substr(0, 4) == "/bot")
		botCommand(inputUser, it);
	
}

int	commandCheck(std::string isCommand) {
	std::string checkCommand = isCommand.substr(0, isCommand.find(" "));

	if (checkCommand == "PASS")
		return 1;
	else if (checkCommand  == "NICK")
		return 1;
	else if (checkCommand == "PRIVMSG")
		return 1;
	else if (checkCommand == "/bot")
		return 1;
	return 0;
}

void Server::parseInput(std::string inputUser, std::vector<pollfd>::iterator& iter) {
	if (commandCheck(inputUser))
		commandExec(inputUser, iter);
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
