/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmohamm <anmohamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:31:09 by anmohamm          #+#    #+#             */
/*   Updated: 2024/10/06 16:31:11 by anmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <iostream>
#include <stdexcept>

bool isPortValid(std::string port){
	return (port.find_first_not_of("0123456789") == std::string::npos && \
	std::atoi(port.c_str()) >= 1024 && std::atoi(port.c_str()) <= 65535);
}

int main(int ac, char **av)
{
	Server ser;
	if (ac != 3)
		{std::cout << "Usage: " << av[0] << " <port number> <password>" << std::endl; return 1;}
	std::cout << "---- SERVER ----" << std::endl;
	try
	{
		signal(SIGINT, Server::SignalHandler);
		signal(SIGQUIT, Server::SignalHandler);
		signal(SIGPIPE, SIG_IGN);// or MSG_NOSIGNAL flag in send() to ignore SIGPIPE on linux systems
		if(!isPortValid(av[1]) || !*av[2] || std::strlen(av[2]) > 20)
			{std::cout << "invalid Port number / Password!" << std::endl; return 1;}
		ser.serverinit(std::atoi(av[1]), av[2]);
	}
	catch(const std::exception& e)
	{
		ser.close_fds();
		std::cerr << e.what() << std::endl;
	}
	std::cout << "The Server Closed!" << std::endl;
}
