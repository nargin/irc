/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstride <rstride@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 03:41:55 by romaurel          #+#    #+#             */
/*   Updated: 2023/08/03 03:45:40 by rstride          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Client.hpp"
#include <vector>
#include <string>

class Channel {
private:
    std::string _name;
    std::vector<Client> _clients;
    std::vector<Client> _operators;

public:
    Channel(const std::string& name) : _name(name) {}

    bool is_operator(const Client& client) const;
    bool add_operator(Client* client);
    bool remove_user(Client* user);
    bool add_user(Client* user);
};

