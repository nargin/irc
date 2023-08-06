/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robin <robin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 03:42:11 by rstride           #+#    #+#             */
/*   Updated: 2023/08/06 18:05:38 by robin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Channel.hpp"
#include "Commands.hpp"

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
		send(it->fd, "\033[0;31mError\033[0m : You have to be registered to set nickname\r\n", 60, 0);
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
}

int	commandCheck(std::string isCommand) {
	if (isCommand.substr(0, 4) == "PASS")
		return 1;
	else if (isCommand.substr(0, 4) == "NICK")
		return 1;
	else if (isCommand.substr(0, 4) == "JOIN")
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
