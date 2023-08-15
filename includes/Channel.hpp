/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romaurel <romaurel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 03:41:55 by romaurel          #+#    #+#             */
/*   Updated: 2023/08/15 13:38:03 by romaurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Client.hpp"
#include "Irc.hpp"

class Channel {
	private:
		std::string _name;
		std::vector<Client> _clients;
		std::vector<Client> _operators;
		std::string _topic;
		bool _invite_only;

	public:
		Channel(const std::string& name, const std::string &topic) : _name(name), _topic(topic), _invite_only(false) {}
		~Channel() { std::cout << "Channel " << _name << " destroyed" << std::endl; }

		bool is_operator(const Client& client) const;
		bool add_operator(Client& client);
		bool remove_operator(Client& client);
		bool is_user(const Client& client) const;
		bool remove_user(Client& user);
		bool add_user(Client& user);

		std::string getname() const;
		std::string gettopic() const;
		std::vector <Client> get_users() const;
		bool	get_invite_only() const;
};

