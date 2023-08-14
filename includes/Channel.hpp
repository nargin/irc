/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 03:41:55 by romaurel          #+#    #+#             */
/*   Updated: 2023/08/14 14:56:39 by maserrie         ###   ########.fr       */
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

	public:
		Channel(const std::string& name, const std::string &topic) : _name(name), _topic(topic) {}

		bool is_operator(const Client& client) const;
		bool add_operator(Client& client);
		bool remove_user(Client& user);
		bool add_user(Client& user);
};

