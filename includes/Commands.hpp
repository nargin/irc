/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robin <robin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 03:42:02 by romaurel          #+#    #+#             */
/*   Updated: 2023/08/03 22:14:43 by robin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Irc.hpp"


class Commands {
	public :
		Commands();
		~Commands();

		/* ~~ Getters ~~ */
		std::string getCommand();
		std::string getParam();
	
		void handle_mode_command(int client_fd, const std::string& channel_name, const std::string& mode, const std::string& value = "");
		void handle_invite_command(int client_fd, const std::string& channel_name, const std::string& user_to_invite);
		void handle_kick_command(int client_fd, const std::string& channel_name, const std::string& user_to_kick);
		void handle_topic_command(int client_fd, const std::string& channel_name, const std::string& topic);

	private :
		Commands(Commands const &src); // private constructor to prevent copy

		std::string _command;
		std::string _flags;
		std::string _param;
};

 