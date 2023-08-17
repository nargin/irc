/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maserrie <maserrie@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 03:41:55 by romaurel          #+#    #+#             */
/*   Updated: 2023/08/17 19:14:58 by maserrie         ###   ########.fr       */
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
		std::vector<Client> _invites;
		std::string		_key;
		bool _invite_only;
		bool _topic_opers_only;
		bool password_protected;

	public:
		Channel(const std::string& name, const std::string &topic);
		Channel(const Channel& channel);
		~Channel();

		Channel& operator = (const Channel& channel);

		bool is_operator(const Client& client) const;
		bool add_operator(Client& client);
		bool remove_operator(Client& client);
		bool is_user(const Client& client) const;
		bool remove_user(Client& user);
		bool add_user(Client& user);
		bool is_invite(Client& user) const;
		bool add_invite(Client &user);
		bool remove_invite(Client &user);

		std::string getname() const;
		std::string gettopic() const;
		std::vector <Client> get_users() const;
		bool	get_invite_only() const;
		bool	get_topic_opers_only() const;
		bool	get_password_protected() const;
		std::string	get_key() const;
};

