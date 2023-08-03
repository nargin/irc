/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstride <rstride@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 03:42:11 by rstride           #+#    #+#             */
/*   Updated: 2023/08/03 03:46:10 by rstride          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Channel.hpp"
#include "Commands.hpp"

void Server::handle_kick_command(int client_fd, const std::string& channel_name, const std::string& user_to_kick) {
    auto it = _channels.find(channel_name);
    if (it != _channels.end()) {
        Channel& channel = it->second;
        Client& client = _clients[client_fd];
        if (channel.is_operator(client)) {
            for (auto& pair : _clients) {
                if (pair.second.getNickname() == user_to_kick) {
                    if (channel.remove_user(pair.second)) {
                        std::cout << "Kicked " << user_to_kick << " from " << channel_name << std::endl;
                        return;
                    }
                }
            }
            std::cout << "User " << user_to_kick << " not found" << std::endl;
        } else {
            std::cout << "User " << client.getNickname() << " is not an operator" << std::endl;
        }
    } else {
        std::cout << "Channel " << channel_name << " not found" << std::endl;
    }
}

void Server::handle_invite_command(int client_fd, const std::string& channel_name, const std::string& user_to_invite) {
    auto it_channel = _channels.find(channel_name);
    if (it_channel != _channels.end()) {
        Channel& channel = it_channel->second;
        Client& client = _clients[client_fd];
        if (channel.is_operator(client)) {
            for (auto& pair : _clients) {
                if (pair.second.getNickname() == user_to_invite) {
                    std::cout << "Invited " << user_to_invite << " to " << channel_name << std::endl;
                    return;
                }
            }
            std::cout << "User " << user_to_invite << " not found" << std::endl;
        } else {
            std::cout << "User " << client.getNickname() << " is not an operator" << std::endl;
        }
    } else {
        std::cout << "Channel " << channel_name << " not found" << std::endl;
    }
}

void Server::handle_topic_command(int client_fd, const std::string& channel_name, const std::string& new_topic) {
    auto it_channel = _channels.find(channel_name);
    if (it_channel != _channels.end()) {
        Channel& channel = it_channel->second;
        Client& client = _clients[client_fd];
        if (new_topic.empty()) {
            std::cout << "Topic of " << channel_name << ": " << channel.getTopic() << std::endl;
        } else if (channel.is_operator(client)) {
            std::cout << "Topic of " << channel_name << " changed to " << new_topic << std::endl;
        } else {
            std::cout << "User " << client.getNickname() << " is not an operator" << std::endl;
        }
    } else {
        std::cout << "Channel " << channel_name << " not found" << std::endl;
    }
}

void Server::handle_mode_command(int client_fd, const std::string& channel_name, const std::string& mode, const std::string& value) {
    auto it_channel = _channels.find(channel_name);
    if (it_channel != _channels.end()) {
        Channel& channel = it_channel->second;
        Client& client = _clients[client_fd];
        if (channel.is_operator(client)) {
            std::cout << "Mode of " << channel_name << " changed to " << mode << " " << value << std::endl;
        } else {
            std::cout << "User " << client.getNickname() << " is not an operator" << std::endl;
        }
    } else {
        std::cout << "Channel " << channel_name << " not found" << std::endl;
    }
}