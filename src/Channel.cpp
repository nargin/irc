/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstride <rstride@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 03:42:09 by rstride           #+#    #+#             */
/*   Updated: 2023/08/03 03:46:22 by rstride          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

bool Channel::is_operator(const Client& client) const {
    return std::find(_operators.begin(), _operators.end(), &client) != _operators.end();
}

bool Channel::add_operator(Client* client) {
    if (!is_operator(*client)) {
        _operators.push_back(client);
        return true;
    }
    return false;
}

bool Channel::remove_user(Client* user) {
    auto it = std::find(_clients.begin(), _clients.end(), user);
    if (it != _clients.end()) {
        _clients.erase(it);
        return true;
    }
    return false;
}

bool Channel::add_user(Client* user) {
    if (std::find(_clients.begin(), _clients.end(), user) == _clients.end()) {
        _clients.push_back(user);
        return true;
    }
    return false;
}
