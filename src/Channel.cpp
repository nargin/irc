/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 03:42:09 by rstride           #+#    #+#             */
/*   Updated: 2023/08/15 18:08:52 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(const std::string& name, const std::string &topic) : _name(name), _topic(topic), _invite_only(false) {}

Channel::~Channel() {}

bool Channel::is_operator(const Client& client) const {
	return std::find(_operators.begin(), _operators.end(), client) != _operators.end();
}

bool Channel::add_operator(Client& client) {
	if (!is_operator(client)) {
		_operators.push_back(client);
		return true;
	}
	return false;
}

bool Channel::remove_user(Client& user) {
	std::vector<Client>::iterator it = std::find(_clients.begin(), _clients.end(), user);
	if (it != _clients.end()) {
		_clients.erase(it);
		return true;
	}
	return false;
}

bool Channel::remove_operator(Client& client) {
	std::vector<Client>::iterator it = std::find(_operators.begin(), _operators.end(), client);
	if (it != _operators.end()) {
		_operators.erase(it);
		return true;
	}
	return false;
}

bool Channel::add_user(Client& user) {
	if (std::find(_clients.begin(), _clients.end(), user) == _clients.end()) {
		_clients.push_back(user);
		return true;
	}
	return false;
}

std::string Channel::getname() const {
	return _name;
}

std::string Channel::gettopic() const {
	return _topic;
}

bool Channel::is_user(const Client& client) const {
	for (std::vector<Client>::const_iterator it = _clients.begin(); it != _clients.end(); ++it) {
		if (*it == client)
			return true;
	}
	return false;
}

std::vector<Client> Channel::get_users() const {
	return _clients;
}

bool	Channel::get_invite_only() const {
	return _invite_only;
}
