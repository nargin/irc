/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 03:42:09 by rstride           #+#    #+#             */
/*   Updated: 2023/08/18 01:09:56 by maserrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

/* ~~ Public ~~ */
	/* Constructors / Destructors */
	Channel::Channel(const std::string& name, const std::string &topic) :
		_name(name),
		_topic(topic),
		_invite_only(false)
		{}
	Channel::~Channel() {}

	/* ~~ Copy constructor / Assignment operator ~~ */
	Channel::Channel(const Channel& other) :
		_name(other._name),
		_clients(other._clients),
		_operators(other._operators),
		_topic(other._topic),
		_invite_only(other._invite_only)
		{}

	Channel& Channel::operator=(const Channel& other) {
		if (this != &other) {
			_name = other._name;
			_topic = other._topic;
			_clients = other._clients;
			_operators = other._operators;
			_invite_only = other._invite_only;
		}
		return *this;
	}

/* ~~ Methods ~~ */

/* ~~ Private ~~ */
	/* ~~ Getters ~~ */
	bool Channel::is_operator(const Client& client) const {return std::find(_operators.begin(), _operators.end(), client) != _operators.end();}
	std::string Channel::getname() const {return _name;}
	std::string Channel::gettopic() const {return _topic;}
	bool	Channel::is_invite(Client &user) const {return std::find(_invites.begin(), _invites.end(), user) != _invites.end();}
	std::vector<Client> Channel::get_users() const {return _clients;}
	bool	Channel::get_invite_only() const {return _invite_only;}
	bool Channel::is_user(const Client& client) const {
		for (std::vector<Client>::const_iterator it = _clients.begin(); it != _clients.end(); ++it) {
			if (*it == client)
				return true;
		}
		return false;
	}

	/* ~~ Setters ~~ */
	void Channel::set_topic(const std::string& topic) {_topic = topic;}
	void Channel::set_invite_only(bool invite_only) {_invite_only = invite_only;}
	void Channel::set_topic_opers_only(bool topic_opers_only) {_topic_opers_only = topic_opers_only;}
	void Channel::set_password_protected(bool password_protected) {this->password_protected = password_protected;}
	void Channel::set_key(const std::string& key) {this->_key = key;}
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
	bool Channel::add_operator(Client& client) {
		if (!is_operator(client)) {
			_operators.push_back(client);
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
	bool	Channel::add_invite(Client &user) {
		if (std::find(_invites.begin(), _invites.end(), user) == _invites.end()) {
			_invites.push_back(user);
			return true;
		}
		return false;
	}

	bool	Channel::remove_invite(Client &user) {
		std::vector<Client>::iterator it = std::find(_invites.begin(), _invites.end(), user);
		if (it != _invites.end()) {
			_invites.erase(it);
			return true;
		}
		return false;
	}

