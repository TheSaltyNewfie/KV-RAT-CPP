#include <iostream>
#include <SFML/Network.hpp>
#include <string>
#include "Utils.h"

int checkConnection(sf::Packet &packet)
{
	/*
	100 - Good
	200 - Received
	300 - Error
	400 - Unknown
	500 - Disconnecting
	*/

	int STATUS;
	std::string extraData;
	sf::Packet RESP = packet;

	RESP >> STATUS >> extraData;

	if (STATUS == 100)
	{
		//std::cout << "[LOG] Server returned response code 100" << std::endl;
		logging::local("Server returned response code 100");
		return 0;
	}

	if (STATUS == 200)
	{
		logging::local("Server returned response code 200");
		return 0;
	}

	if (STATUS == 300)
	{
		logging::local("Server returned response code 300");
		logging::local(extraData);
		return 1;
	}

	if (STATUS == 400)
	{
		logging::local("Server returned response code 400");
		logging::local(extraData);
		return 1;
	}

	if (STATUS == 500)
	{
		logging::local("Server returned response code 500");
		return 2;
	}
}