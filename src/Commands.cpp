/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romaurel <romaurel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 03:42:11 by rstride           #+#    #+#             */
/*   Updated: 2023/08/07 10:41:06 by romaurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Channel.hpp"
#include "Commands.hpp"

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
		send(it->fd, "\033[0;31mError\033[0m : Not enough arguments\r\n", 43, 0);
		return ;
	}
	std::string nick = tokens[1];
	std::string msg = tokens[2];
	std::map<int, Client>::iterator it1 = _clients.find(it->fd);
	if (it1 != _clients.end() && it1->second.getNicked() == 1) {
		std::map<int, Client>::iterator it2 = _clients.begin();
		while (it2 != _clients.end()) {
			if (it2->second.getNickname() == nick) {
				std::cout << SERVERSPEAK << "Client #" << it1->second.getFd() << " sent private message to " << nick << std::endl;
				send(it2->second.getFd(), "You received a private message from ", 36, 0);
				send(it2->second.getFd(), it1->second.getNickname().c_str(), it1->second.getNickname().length(), 0);
				send(it2->second.getFd(), "\r\n", 2, 0);
				send(it2->second.getFd(), "\033[0;32mSuccess\033[0m : ", 23, 0);
				while (tokens.size() > 2) {
					send(it2->second.getFd(), tokens[2].c_str(), tokens[2].length(), 0);
					tokens.erase(tokens.begin() + 2);
					if (tokens.size() > 2)
						send(it2->second.getFd(), " ", 1, 0);
				}
				send(it2->second.getFd(), "\r\n", 2, 0);
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
	else
		std::cout << "Client #" << it->fd << " tried to set nickname to " << nick << std::endl;
}

void	Server::commandExec(std::string inputUser, std::vector<pollfd>::iterator& it) {
	if (inputUser.substr(0, 4) == "PASS" && inputUser.length() > 5 && _clients.find(it->fd) != _clients.end())
		handlePassCommand(inputUser, it);
	else if (inputUser.substr(0, 4) == "NICK")
		handleNickCommand(inputUser, it);
	else if (inputUser.substr(0, 7) == "PRIVMSG")
		handlePrivMsg(inputUser, it);
}

int	commandCheck(std::string isCommand) {
	std::string checkCommand = isCommand.substr(0, isCommand.find(" "));

	if (checkCommand == "PASS")
		return 1;
	else if (checkCommand  == "NICK")
		return 1;
	else if (checkCommand == "PRIVMSG")
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

// void Server::handle_kick_command(int client_fd, const std::string& channel_name, const std::string& user_to_kick) {
// 	auto it = _channels.find(channel_name);
// 	if (it != _channels.end()) {
// 		Channel& channel = it->second;
// 		Client& client = _clients[client_fd];
// 		if (channel.is_operator(client)) {
// 			for (auto& pair : _clients) {
// 				if (pair.second.getNickname() == user_to_kick) {
// 					if (channel.remove_user(pair.second)) {
// 						std::cout << "Kicked " << user_to_kick << " from " << channel_name << std::endl;
// 						return;
// 					}
// 				}
// 			}
// 			std::cout << "User " << user_to_kick << " not found" << std::endl;
// 		} else {
// 			std::cout << "User " << client.getNickname() << " is not an operator" << std::endl;
// 		}
// 	} else {
// 		std::cout << "Channel " << channel_name << " not found" << std::endl;
// 	}
// }

// void Server::handle_invite_command(int client_fd, const std::string& channel_name, const std::string& user_to_invite) {
// 	auto it_channel = _channels.find(channel_name);
// 	if (it_channel != _channels.end()) {
// 		Channel& channel = it_channel->second;
// 		Client& client = _clients[client_fd];
// 		if (channel.is_operator(client)) {
// 			for (auto& pair : _clients) {
// 				if (pair.second.getNickname() == user_to_invite) {
// 					std::cout << "Invited " << user_to_invite << " to " << channel_name << std::endl;
// 					return;
// 				}
// 			}
// 			std::cout << "User " << user_to_invite << " not found" << std::endl;
// 		} else {
// 			std::cout << "User " << client.getNickname() << " is not an operator" << std::endl;
// 		}
// 	} else {
// 		std::cout << "Channel " << channel_name << " not found" << std::endl;
// 	}
// }

// void Server::handle_topic_command(int client_fd, const std::string& channel_name, const std::string& new_topic) {
// 	auto it_channel = _channels.find(channel_name);
// 	if (it_channel != _channels.end()) {
// 		Channel& channel = it_channel->second;
// 		Client& client = _clients[client_fd];
// 		if (new_topic.empty()) {
// 			std::cout << "Topic of " << channel_name << ": " << channel.getTopic() << std::endl;
// 		} else if (channel.is_operator(client)) {
// 			std::cout << "Topic of " << channel_name << " changed to " << new_topic << std::endl;
// 		} else {
// 			std::cout << "User " << client.getNickname() << " is not an operator" << std::endl;
// 		}
// 	} else {
// 		std::cout << "Channel " << channel_name << " not found" << std::endl;
// 	}
// }

// void Server::handle_mode_command(int client_fd, const std::string& channel_name, const std::string& mode, const std::string& value) {
// 	auto it_channel = _channels.find(channel_name);
// 	if (it_channel != _channels.end()) {
// 		Channel& channel = it_channel->second;
// 		Client& client = _clients[client_fd];
// 		if (channel.is_operator(client)) {
// 			std::cout << "Mode of " << channel_name << " changed to " << mode << " " << value << std::endl;
// 		} else {
// 			std::cout << "User " << client.getNickname() << " is not an operator" << std::endl;
// 		}
// 	} else {
// 		std::cout << "Channel " << channel_name << " not found" << std::endl;
// 	}
// }
