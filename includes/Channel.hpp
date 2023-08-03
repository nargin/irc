/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robin <robin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 03:41:55 by romaurel          #+#    #+#             */
/*   Updated: 2023/08/03 22:25:45 by robin            ###   ########.fr       */
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

	public:
		Channel(const std::string& name) : _name(name) {}

		bool is_operator(const Client& client) const;
		bool add_operator(Client& client);
		bool remove_user(Client& user);
		bool add_user(Client& user);
};

