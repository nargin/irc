/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 03:42:11 by rstride           #+#    #+#             */
/*   Updated: 2023/08/18 02:36:22 by maserrie         ###   ########.fr       */
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
	for (std::map<std::string, Channel>::iterator it_channel = _channels.begin(); it_channel != _channels.end(); )
	{
		it_channel->second.remove_operator(_clients[it->fd]);
		it_channel->second.remove_user(_clients[it->fd]);
		if (it_channel->second.get_users().size() == 0)
		{
			_channels.erase(it_channel++);
			std::cout << SERVERSPEAK << "Channel " << it_channel->first << " has been deleted" << std::endl;
		}
		else
			++it_channel;
	}
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
	if (tokens.size() != 2) {
		send_msg(it->fd, "\033[0;31mBot\033[0m bad usage : try /help bot\r\n");
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
	else if (args == "quoi") {
		std::string rep = rand() % 2 ? "coubeh\r\n" : "couille\r\n";
		send(it->fd, rep.c_str(), rep.length(), 0);
	}
	else if (args == "help") {
		send(it->fd, "Available commands : ping, time, quoi, help\r\n", 45, 0);
	}
	else
		send_msg(it->fd, "\033[0;31mBot\033[0m bad usage : try /help bot\r\n");
}

void Server::handlePrivMsg(std::string command, std::vector<pollfd>::iterator& it) {
	std::vector<std::string> tokens;
    std::istringstream stream(command);
    std::string token;
	char delimiter = ' ';

    while (std::getline(stream, token, delimiter)) {
        tokens.push_back(token);
    }
	if (tokens.size() < 3) {
		send_msg(it->fd, "\033[0;31mPrivmsg\033[0m bad usage : try /help privmsg\r\n");
		return ;
	}
	std::string nick = tokens[1];
	std::string msg = tokens[2];
	std::map<int, Client>::iterator it1 = _clients.find(it->fd);
	if (it1 != _clients.end()) {
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
				send(it2->second.getFd(), "\r\n", 2, 0);
				return ;
			}
			it2++;
		}
		send(it1->second.getFd(), "\033[0;31mError\033[0m : Nickname not found\r\n", 40, 0);
	}
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

void Server::handleListCommand(std::vector<pollfd>::iterator &it) {
	if (_channels.size() == 0) {
		send(it->fd, "No channel available\r\n", 22, 0);
		return ;
	}

	std::string list = "List of channels :\r\n";
	for (std::map<std::string, Channel>::iterator it_channel = _channels.begin(); it_channel != _channels.end(); it_channel++)
		list += it_channel->first + " : " + it_channel->second.gettopic() + "\r\n";

	send(it->fd, list.c_str(), list.length(), 0);
}

void	Server::handleCreateCommand(std::string command, std::vector<pollfd>::iterator &it)
{
	std::vector <std::string> tokens = split(command, " ");
	if (_clients[it->fd].getInChannel() == true)
	{
		send(it->fd, "\033[0;31mError\033[0m : You are already in a channel\r\n", 47, 0);
		return ;
	}
	if (tokens.size() != 3)
	{
		send_msg(it->fd, "\033[0;31mCreate\033[0m bad usage : try /help create\r\n");
		return ;
	}
	for (std::map<std::string, Channel>::iterator it_channel = _channels.begin(); it_channel != _channels.end(); it_channel++)
	{
		if (it_channel->first == tokens[1])
		{
			send(it->fd, "\033[0;31mError\033[0m : Channel already exists\r\n", 43, 0);
			return ;
		}
	}
	Channel new_channel(tokens[1], tokens[2]);
	_clients[it->fd].setInChannel(true);
	_clients[it->fd].setChannel(tokens[1]);
	new_channel.add_user(_clients[it->fd]);
	new_channel.add_operator(_clients[it->fd]);
	_channels.insert(std::pair<std::string, Channel>(tokens[1], new_channel));
	send(it->fd, "\033[0;32mSuccess\033[0m : You created the channel\r\n", 47, 0);
	std::cout << SERVERSPEAK << "Client #" << it->fd << " created channel " << tokens[1] << " which talk about " << tokens[2] << std::endl;
}

void	Server::handleJoinCommand(std::string command, std::vector<pollfd>::iterator &it)
{
	std::vector <std::string> tokens = split(command, " ");
	if (_clients[it->fd].getInChannel() == true)
	{
		send(it->fd, "\033[0;31mError\033[0m : You are already in a channel\r\n", 47, 0);
		return ;
	}
	if (tokens.size() != 2)
	{
		send_msg(it->fd, "\033[0;31mJoin\033[0m bad usage : try /help join\r\n");
		return ;
	}
	for (std::map<std::string, Channel>::iterator it_channel = _channels.begin(); it_channel != _channels.end(); it_channel++)
	{
		if (it_channel->first == tokens[1])
		{
			if (it_channel->second.get_invite_only() == true && !it_channel->second.is_invite(_clients[it->fd])) {
				send(it->fd, "\033[0;31mError\033[0m : Channel is invite only\r\n", 43, 0);
				return ;
			}
			if (it_channel->second.get_limit() && it_channel->second.get_users().size() >= (unsigned long long)it_channel->second.get_limit()) {
				send(it->fd, "\033[0;31mError\033[0m : Channel is full\r\n", 38, 0);
				return ;
			}
			it_channel->second.add_user(_clients[it->fd]);
			_clients[it->fd].setInChannel(true);
			_clients[it->fd].setChannel(tokens[1]);
			send(it->fd, "\033[0;32mSuccess\033[0m : You joined the channel\r\n", 45, 0);
			std::cout << SERVERSPEAK << "Client #" << it->fd << " joined channel " << tokens[1] << std::endl;
			return ;
		}
	}
	send(it->fd, "\033[0;31mError\033[0m : Channel not found\r\n", 38, 0);
}

void Server::handleInviteCommand(std::string command, std::vector<pollfd>::iterator &it)
{
	std::vector <std::string> tokens = split(command, " ");
	if (tokens.size() != 3)
		return (send_msg(it->fd, "\033[0;31mInvite\033[0m bad usage : try /help invite\r\n"));
	std::map<int, Client>::iterator it1 = _clients.begin();
	while (!(it1 == _clients.end()))
		if (it1->second.getUsername() == tokens[2])
			break ;
	if (it1 == _clients.end())
	{
		send(it->fd, "\033[0;31mError\033[0m : Nickname not found\r\n", 40, 0);
		return ;
	}
	std::map<std::string, Channel>::iterator it2 = _channels.find(tokens[1]);
	if (it2 == _channels.end())
	{
		send(it->fd, "\033[0;31mError\033[0m : Channel not found\r\n", 38, 0);
		return ;
	}
	Channel &channel = it2->second;
	if (channel.is_user(_clients[it->fd]) == false)
	{
		send_msg(it->fd, "\033[0;31mError\033[0m : You are not in this channel\r\n");
		return ;
	}
	if (channel.is_operator(_clients[it->fd]) == false)
	{
		send_msg(it->fd, "\033[0;31mError\033[0m : You are not operator of this channel\r\n");
		return ;
	}
	channel.add_invite(_clients[it1->first]);
	send_list(it->fd, "\033[0;32mSuccess\033[0m : You invited ", tokens[2].c_str(), " to ", tokens[1].c_str(), "\r\n", "END");
	send_list(it1->first, "\033[0;32mSuccess\033[0m : You have been invited to ", tokens[1].c_str(), "\r\n", "END");
	std::cout << SERVERSPEAK << "Client #" << it->fd << " invited " << tokens[2] << " to channel " << tokens[1] << std::endl;
}

void Server::handleKickCommand(std::string command, std::vector<pollfd>::iterator &it)
{
	std::vector <std::string> tokens = split(command, " ");
	if (tokens.size() != 2)
	{
		send_msg(it->fd, "\033[0;31mKick\033[0m bad usage : try /help kick\r\n");
		return ;
	}
	std::map<int, Client>::iterator it1 = _clients.find(it->fd);
	if (it1 == _clients.end())
	{
		send(it->fd, "\033[0;31mError\033[0m : Nickname not found\r\n", 40, 0);
		return ;
	}
	Channel &channel = _channels.find(_clients[it->fd].getChannel())->second;
	if (channel.is_operator(_clients[it->fd]) == false)
	{
		send_msg(it->fd, "\033[0;31mError\033[0m : You are not operator of this channel\r\n");
		return ;
	}
	if (channel.is_user(it1->second) == false){
		send_list(it1->first, "\033[0;31mError\033[0m : ", tokens[1].c_str(), " is not in this channel\r\n", "END");
		return ;
	}
	channel.remove_user(it1->second);
	send_list(it->fd, "\033[0;32mSuccess\033[0m : You kicked ", tokens[1].c_str(), "\r\n", "END");
	send_list(it1->first, "\033[0;32mSuccess\033[0m : You have been kicked from ", channel.getname().c_str(), "\r\n", "END");
	std::cout << SERVERSPEAK << "Client #" << it->fd << " kicked " << tokens[1] << " from channel " << channel.getname() << std::endl;
}

void Server::handleSendMessageChannel(std::string command, std::vector<pollfd>::iterator &it)
{
	Channel &channel = _channels.find(_clients[it->fd].getChannel())->second;
	std::cout << SERVERSPEAK << "Client #" << it->fd << " sent message to channel " << channel.getname() << std::endl;
	const std::vector<Client> &users = channel.get_users();
	for (std::vector<Client>::const_iterator it1 = users.begin(); it1 != users.end(); it1++)
	{
		if (it1->getFd() != it->fd)
			send_list(it1->getFd(), "\033[0;32m", _clients[it->fd].getNickname().c_str(), " : ", command.c_str(), "\r\n", "END");
	}
}

void Server::handleModeCommand(std::string command, std::vector<pollfd>::iterator &it) {
	std::vector <std::string> tokens = split(command, " ");
	if (tokens.size() < 2)
	{
		send_msg(it->fd, "\033[0;31mMode\033[0m bad usage : try /help mode\r\n");
		return ;
	}
	Channel &channel = _channels.find(_clients[it->fd].getChannel())->second;
	if (channel.is_operator(_clients[it->fd]) == false)
	{
		send_msg(it->fd, "\033[0;31mError\033[0m : You are not operator of this channel\r\n");
		return ;
	}
	if (tokens[1] == "-i")
	{
		if (channel.get_invite_only() == false)
		{
			channel.set_invite_only(true);
			std::cout << SERVERSPEAK << "Client #" << it->fd << " set channel " << channel.getname() << " to invite only" << std::endl;
			send_list(it->fd, "\033[0;32mSuccess\033[0m : You set channel ", channel.getname().c_str(), " to invite only\r\n", "END");
			handleSendMessageChannel("Your channel have been set invite only", it);
			return ;
		}
		channel.set_invite_only(false);
		std::cout << SERVERSPEAK << "Client #" << it->fd << " set channel " << channel.getname() << " to not invite only" << std::endl;
		send_list(it->fd, "\033[0;32mSuccess\033[0m : You set channel ", channel.getname().c_str(), " to not invite only\r\n", "END");
		handleSendMessageChannel("Your channel have been set not invite only", it);
		return ;
	}
	if (tokens[1] == "-t")
	{
		if (channel.get_topic_opers_only() == false)
		{
			channel.set_topic_opers_only(true);
			std::cout << SERVERSPEAK << "Client #" << it->fd << " set channel " << channel.getname() << " to topic change for opers only" << std::endl;
			send_list(it->fd, "\033[0;32mSuccess\033[0m : You set channel ", channel.getname().c_str(), " to topic change for opers only\r\n", "END");
			handleSendMessageChannel("Your channel have been set topic change for opers only", it);
			return ;
		}
		channel.set_topic_opers_only(false);
		std::cout << SERVERSPEAK << "Client #" << it->fd << " set channel " << channel.getname() << " to topic change for everyone" << std::endl;
		send_list(it->fd, "\033[0;32mSuccess\033[0m : You set channel ", channel.getname().c_str(), " to topic change for everyone\r\n", "END");
		handleSendMessageChannel("Your channel have been set topic change for everyone", it);
		return ;
	}
	if (tokens[1] == "-k")
	{
		if (tokens.size() != 3)
		{
			send_msg(it->fd, "\033[0;31mMode\033[0m bad usage : try /help mode\r\n");
			return ;
		}
		if (channel.get_password_protected() == true)
		{
			if (tokens[2] != channel.get_key())
			{
				send_list(it->fd, "\033[0;31mError\033[0m : Wrong password for channel ", channel.getname().c_str(), "\r\n", "END");
				return ;
			}
			channel.set_password_protected(false);
			channel.set_key("");
			std::cout << SERVERSPEAK << "Client #" << it->fd << " set channel " << channel.getname() << " to not password protected" << std::endl;
			send_list(it->fd, "\033[0;32mSuccess\033[0m : You set channel ", channel.getname().c_str(), " to not password protected\r\n", "END");
			handleSendMessageChannel("Your channel have been set not password protected and the password is", it);
			handleSendMessageChannel(channel.get_key(), it);
			return ;
		}
		channel.set_password_protected(true);
		channel.set_key(tokens[2]);
		std::cout << SERVERSPEAK << "Client #" << it->fd << " set channel " << channel.getname() << " to password protected" << std::endl;
		send_list(it->fd, "\033[0;32mSuccess\033[0m : You set channel ", channel.getname().c_str(), " to password protected\r\n", "END");
		handleSendMessageChannel("Your channel have been set password protected", it);
		return ;
	}
	if (tokens[1] == "-o")
	{
		if (tokens.size() != 3)
		{
			send_msg(it->fd, "\033[0;31mMode\033[0m bad usage : try /help mode\r\n");
			return ;
		}
		std::map<int, Client>::iterator it1 = getClient(tokens[2]);
		if (it1 == _clients.end())
		{
			send(it->fd, "\033[0;31mError\033[0m : Nickname not found\r\n", 40, 0);
			return ;
		}
		if (channel.is_user(it1->second) == false)
		{
			send_list(it1->first, "\033[0;31mError\033[0m : ", tokens[2].c_str(), " is not in this channel\r\n", "END");
			return ;
		}
		if (channel.is_operator(it1->second) == true)
		{
			channel.remove_operator(it1->second);
			send_list(it->fd, "\033[0;32mSuccess\033[0m : You removed ", tokens[2].c_str(), " operator of this channel\r\n", "END");
			send_list(it1->first, "\033[0;32mSuccess\033[0m : You have been removed operator of this channel\r\n", "END");
			std::cout << SERVERSPEAK << "Client #" << it->fd << " removed " << tokens[2] << " operator of channel " << channel.getname() << std::endl;
			return ;
		}
		channel.add_operator(it1->second);
		send_list(it->fd, "\033[0;32mSuccess\033[0m : You set ", tokens[2].c_str(), " operator of this channel\r\n", "END");
		send_list(it1->first, "\033[0;32mSuccess\033[0m : You have been set operator of this channel\r\n", "END");
		std::cout << SERVERSPEAK << "Client #" << it->fd << " set " << tokens[2] << " operator of channel " << channel.getname() << std::endl;
		return ;
	}
	if (tokens[1] == "-l")
	{
		if (tokens.size() != 3)
		{
			send_msg(it->fd, "\033[0;31mMode\033[0m bad usage : try /help mode\r\n");
			return ;
		}
		if (channel.get_limit() == 0)
		{
			channel.set_limit(atoi(tokens[2].c_str()));
			std::cout << SERVERSPEAK << "Client #" << it->fd << " set channel " << channel.getname() << " to limited to " << tokens[2] << " users" << std::endl;
			send_list(it->fd, "\033[0;32mSuccess\033[0m : You set channel ", channel.getname().c_str(), " to limited to ", tokens[2].c_str(), " users\r\n", "END");
			handleSendMessageChannel("Your channel have been set limited to " + tokens[2] + " users", it);
			return ;
		}
		channel.set_limit(0);
		std::cout << SERVERSPEAK << "Client #" << it->fd << " set channel " << channel.getname() << " to not limited" << std::endl;
		send_list(it->fd, "\033[0;32mSuccess\033[0m : You set channel ", channel.getname().c_str(), " to not limited\r\n", "END");
		handleSendMessageChannel("Your channel have been set not limited", it);
		return ;
	}
	send_msg(it->fd, "\033[0;31mMode\033[0m bad usage : try /help mode\r\n");
}

void Server::handleTopicCommand(std::string command, std::vector<pollfd>::iterator &it){
	std::vector <std::string> tokens = split(command, " ");
	if (tokens.size() < 2)
	{
		send_msg(it->fd, "\033[0;31mTopic\033[0m bad usage : try /help topic\r\n");
		return ;
	}
	Channel &channel = _channels.find(_clients[it->fd].getChannel())->second;
	if (channel.get_topic_opers_only() == true && channel.is_operator(_clients[it->fd]) == false)
	{
		send_msg(it->fd, "\033[0;31mError\033[0m : You are not operator of this channel\r\n");
		return ;
	}
	std::string topic = command.substr(7);
	channel.set_topic(topic);
	std::cout << SERVERSPEAK << "Client #" << it->fd << " set channel " << channel.getname() << " topic to " << topic << std::endl;
	send_list(it->fd, "\033[0;32mSuccess\033[0m : You set channel ", channel.getname().c_str(), " topic to ", topic.c_str(), "\r\n", "END");
	handleSendMessageChannel("Your channel topic have been set to " + topic, it);
}

void	Server::handleHelpCommand(std::string command, std::vector<pollfd>::iterator &it) {
	std::vector <std::string> tokens = split(command, " ");
	if (tokens.size() > 2)
	{
		send_msg(it->fd, "\033[0;31mHelp\033[0m bad usage : try /help help\r\n");
		return ;
	}
	if (tokens.size() == 1){
		send_msg(it->fd, "Available commands :\r\n");
		if (_clients[it->fd].getRegistered() == 0)
			send_msg(it->fd, "pass : register to the server\r\n");
		send_msg(it->fd, "nick : set your nickname\r\n");
		send_msg(it->fd, "/help : display help\r\n");
		send_msg(it->fd, "/bot : display bot help\r\n");
		send_msg(it->fd, "list : list channels\r\n");
		send_msg(it->fd, "privmsg : send private message to a user\r\n");
		if (!_clients[it->fd].getInChannel())
		{
			send_msg(it->fd, "create : create a channel\r\n");
			send_msg(it->fd, "join : join a channel\r\n");
		}
		if (_clients[it->fd].getInChannel() == true && _channels.find(_clients[it->fd].getChannel())->second.is_operator(_clients[it->fd]) == true)
		{
			send_msg(it->fd, "invite : invite a user to a channel\r\n");
			send_msg(it->fd, "kick : kick a user from a channel\r\n");
			send_msg(it->fd, "mode : set channel mode\r\n");
			if (_channels.find(_clients[it->fd].getChannel())->second.get_topic_opers_only() == true)
				send_msg(it->fd, "topic : set channel topic\r\n");
		}
		else if (_clients[it->fd].getInChannel() == true && _channels.find(_clients[it->fd].getChannel())->second.get_topic_opers_only() == false)
			send_msg(it->fd, "topic : set channel topic\r\n");
		return ;
	}
	std::transform(tokens[1].begin(), tokens[1].end(), tokens[1].begin(), ::tolower);
	if (tokens[1] == "bot")
	{
		send_msg(it->fd, "Usage : /bot <command>\r\n");
		send_msg(it->fd, "Available commands :\r\n");
		send_msg(it->fd, "help : display help\r\n");
		send_msg(it->fd, "time : display time\r\n");
		send_msg(it->fd, "ping : display ur ping\r\n");
		send_msg(it->fd, "quoi : try it\r\n");
		return ;
	}
	if (tokens[1] == "create")
	{
		send(it->fd, "Usage : /create <channel_name> <topic>\r\n", 41, 0);
		return ;
	}
	if (tokens[1] == "join")
	{
		send(it->fd, "Usage : /join <channel_name>\r\n", 30, 0);
		return ;
	}
	if (tokens[1] == "invite")
	{
		send(it->fd, "Usage : /invite <channel_name> <nickname>\r\n", 43, 0);
		return ;
	}
	if (tokens[1] == "kick")
	{
		send(it->fd, "Usage : /kick <nickname>\r\n", 26, 0);
		return ;
	}
	if (tokens[1] == "mode")
	{
		send(it->fd, "Usage : /mode <channel_name> <mode>\r\n", 37, 0);
		send(it->fd, "Available modes :\r\n", 20, 0);
		send(it->fd, "-i : set/unset invite only\r\n", 19, 0);
		send(it->fd, "-t : set/unset topic change for opers only\r\n", 34, 0);
		send(it->fd, "-k <password> : set/unset password protected\r\n", 37, 0);
		send(it->fd, "-o <nickname> : give/take operator to nickname\r\n", 44, 0);
		send(it->fd, "-l <number> : limit/unlimit to number of users\r\n", 40, 0);
		return ;
	}
	if (tokens[1] == "topic")
	{
		send(it->fd, "Usage : /topic <topic>\r\n", 24, 0);
		return ;
	}
	if (tokens[1] == "list")
	{
		send(it->fd, "Usage : /list\r\n", 15, 0);
		return ;
	}
	if (tokens[1] == "privmsg")
	{
		send(it->fd, "Usage : /privmsg <nickname> <message>\r\n", 39, 0);
		return ;
	}
	if (tokens[1] == "nick")
	{
		send(it->fd, "Usage : /nick <nickname>\r\n", 26, 0);
		return ;
	}
	if (tokens[1] == "pass")
	{
		send(it->fd, "Usage : /pass <password>\r\n", 26, 0);
		return ;
	}
}

int	Server::commandExec(std::string inputUser, std::vector<pollfd>::iterator& it) {
	std::string checkCommand = inputUser.substr(0, inputUser.find(" "));
	std::transform(checkCommand.begin(), checkCommand.end(), checkCommand.begin(), ::toupper);

	if (checkCommand == "PASS" && inputUser.length() > 5 && _clients.find(it->fd) != _clients.end())
		handlePassCommand(inputUser, it);
	else if (checkCommand == "QUIT" || checkCommand == "EXIT")
		quitClient(it);
	else if (checkCommand == "HELP")
		handleHelpCommand(inputUser, it);
	else if (_clients[it->fd].getRegistered() == 0)
		send_msg(it->fd, "\033[0;31mError\033[0m : You have to be registered to do anything on the server\r\n");
	else if (checkCommand == "NICK" && inputUser.length() > 5)
		handleNickCommand(inputUser, it);
	else if (_clients[it->fd].getNicked() == 0)
		send_msg(it->fd, "\033[0;31mError\033[0m : You have to be nicked to do anything on the server\r\n");
	else if (checkCommand == "PRIVMSG")
		handlePrivMsg(inputUser, it);
	else if (checkCommand == "CREATE")
		handleCreateCommand(inputUser, it);
	else if (checkCommand == "JOIN")
		handleJoinCommand(inputUser, it);
	else if (checkCommand == "LIST")
		handleListCommand(it);
	else if (checkCommand == "/BOT")
		botCommand(inputUser, it);
	else if (_clients[it->fd].getInChannel() == false)
		return (0);
	else if (checkCommand == "INVITE")
		handleInviteCommand(inputUser, it);
	else if (checkCommand == "KICK")
		handleKickCommand(inputUser, it);
	else if (checkCommand == "TOPIC")
		handleTopicCommand(inputUser, it);
	else if (checkCommand == "MODE")
		handleModeCommand(inputUser, it);
	else
		handleSendMessageChannel(inputUser, it);
	return 1;
}

void Server::parseInput(std::string inputUser, std::vector<pollfd>::iterator& iter) {
	if (commandExec(inputUser, iter))
		return ;
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
