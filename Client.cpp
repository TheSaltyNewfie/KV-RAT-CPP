#include <iostream>
#include <SFML/Network.hpp>
#include "Utils.h"

int main()
{
	std::string addr = "71.7.242.3";
	int port = 4560;

	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(addr, port);

	sf::Packet packet;
	std::string data;
	std::vector<std::string> v;

	while (true)
	{
		try
		{
			if (status != sf::Socket::Done)
			{
				std::cout << "Unable to connect to server " << addr << ":" << port;
			}
			std::cout << "Connected to " << addr << ":" << port << std::endl;

			socket.receive(packet);
			packet >> data;

			std::cout << "Data:" << data << std::endl << "Received:" << "Maybe 3 could be 4" << std::endl;
			splitString(data, v);
			ParseCommand(v);
			v.clear();
		}
		catch (const std::exception& e) { std::cout << "Error: " << e.what(); }
	}
	
	return 0;
}
